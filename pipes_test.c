/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:31:29 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/10/17 14:41:07 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

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

int	lexer_pipes(t_data *data, char *input)
{
	char	*str;

	ft_cleartokens(&data->top);
	if (!input)
		return (-1);
	str = ft_strtrim(input, " ");
	if (check_first(str) == -1)
		return (free(str), 0);
	lexer_continuation(data, str, 0, 0);
	free(str);
	if (check_second(data) == -1)
		return (0);
	execution_pipes(data);
	exit (0);
}

void	execution_pipes(t_data *data)
{
	char	**arg;

	remove_quote_topdata(data);
	if (check_builtins(data) == 0)
	{
		arg = list_to_array(data);
		get_envpaths(data);
		execve_pipes(data, arg, 0);
		free_array(arg);
		free_array(data->paths);
	}
}

void	reset_fd(t_data *data)
{
	dup2(data->stdin_fd, STDIN_FILENO);
	dup2(data->stdout_fd, STDOUT_FILENO);
}

void	pipe_closing(t_data *data)
{
	int	i;

	i = 0;
	while (i < (data->pipes_nums * 2))
	{
		close(data->pipes_fds[i]);
		i++;
	}
}

void	execve_pipes(t_data *data, char **arg, int i)
{
	char	*tmp_path;

	while (data->paths[i] != NULL)
	{
		tmp_path = get_tmp_path(data, i);
		if (access(tmp_path, X_OK) == 0)
		{
			execve(tmp_path, arg, data->og_envp);
		}
		free(tmp_path);
		i++;
	}
	printf("%s: command not found\n", data->top->data);
}
