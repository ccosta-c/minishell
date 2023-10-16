/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:34:10 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/10/16 12:25:52 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	pipes_execution(t_data *data)
{
	char	**commands;
	int		i;

	i = 0;
	data->stdin_fd = STDIN_FILENO;
	data->stdout_fd = STDOUT_FILENO;
	data->pid = malloc(sizeof(int) * (data->pipes_nums + 1));
	commands = pipes_commands(data);
	data->pipes_fds = malloc(sizeof(int) * (data->pipes_nums * 2));
	while (i <= data->pipes_nums)
	{
		if (pipe(data->pipes_fds) < 0)
		{
			ft_putstr_fd("Error while creating pipes", 2);
			return ;
		}
		i++;
	}
	i = 0;
	while (commands[i])
	{
		execute_pipes_command(data, commands[i], i);
		i++;
	}
}

int	execute_pipes_command(t_data *data, char *command, int i)
{

	data->pid[i] = fork();
	if (data->pid[i] < 0)
		return (-1);
	if (data->pid[i] == 0)
	{
		pipes_wiring(data, i);
		lexer_pipes(data, command);
	}
	waitpid(data->pid[i], NULL, 0);
	return (0);
}

void	pipes_wiring(t_data *data, int i)
{
	if (i == 0)
		dup2(data->pipes_fds[1], STDOUT_FILENO);
	else if (i == data->pipes_nums)
		dup2(data->pipes_fds[2 * i - 2], STDIN_FILENO);
	else
	{
		dup2(data->pipes_fds[2 * i - 2], STDIN_FILENO);
		dup2(data->pipes_fds[2 * i + 1], STDOUT_FILENO);
	}
	pipe_closing(data);
}

char	**pipes_commands(t_data *data)
{
	char	**commands;
	int		i;
	int		j;
	int		k;
	bool	quotes;

	i = 0;
	j = 0;
	k = 0;
	quotes = false;
	commands = malloc(sizeof (char *) * (data->pipes_nums + 2));
	commands[j] = malloc(sizeof(char) * strlen(data->original_command));
	while (data->original_command[i])
	{
		if (data->original_command[i] == '\'' || data->original_command[i] == '\"')
		{
			if (quotes == true)
				quotes = false;
			else
				quotes = true;
		}
		if (data->original_command[i] == '|' && quotes == false)
		{
			commands[j][k] = '\0';
			i++;
			k = 0;
			j++;
			commands[j] = malloc(sizeof(char) * strlen(data->original_command));
			continue ;
		}
		if (data->original_command[i] == ' ' && data->original_command[i + 1] == '|' && quotes == false)
		{
			commands[j][k] = '\0';
			i = i + 2;
			k = 0;
			j++;
			commands[j] = malloc(sizeof(char) * strlen(data->original_command));
			continue ;
		}
			commands[j][k] = data->original_command[i];
			i++;
			k++;
	}
	commands[j][k] = '\0';
	commands[j + 1] = NULL;
	return (commands);
}
