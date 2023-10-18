/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:34:10 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/10/17 16:42:24 by ccosta-c         ###   ########.fr       */
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
	data->pid = malloc(sizeof(pid_t) * (data->pipes_nums + 1));
	commands = pipes_commands(data);
	data->pipes_fds = malloc(sizeof(int) * (data->pipes_nums * 2));
	while (i < data->pipes_nums)
	{
		if (pipe(data->pipes_fds + (i * 2)) < 0)
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
	get_exit_status_arr(data, data->pid);
	pipe_closing(data);
	while (waitpid(-1, NULL, 0) != -1)
		;
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
	return (0);
}

void	redirect(int fd_in, int fd_out)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
}

void	pipes_wiring(t_data	*data, int i)
{
	if (i == 0)
		redirect(data->stdin_fd, data->pipes_fds[1]);
	else if (i == data->pipes_nums)
		redirect(data->pipes_fds[i * 2 - 2], data->stdout_fd);
	else
		redirect(data->pipes_fds[i * 2 - 2], data->pipes_fds[i * 2 + 1]);
	pipe_closing(data);
}
