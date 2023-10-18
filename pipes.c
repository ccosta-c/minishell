/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:34:10 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/10/18 16:16:16 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	pipes_execution(t_data *data)
{
	char	**commands;
	int		i;

	i = 0;
	commands = pipes_commands_aux(data);
	while (i < data->pipes_nums)
	{
		if (pipe(data->pipes_fds + (i * 2)) < 0)
			return ;
		i++;
	}
	i = 0;
	while (commands[i])
	{
		execute_pipes_command(data, commands[i], i);
		i++;
	}
	pipe_closing(data);
	get_exit_status_arr(data, data->pid);
	free_child(data, commands);
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
		frees(data);
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

void	execve_pipes(t_data *data, char **arg, int i)
{
	char	*tmp_path;

	while (data->paths[i] != NULL)
	{
		tmp_path = get_tmp_path(data, i);
		if (access(tmp_path, X_OK) == 0)
		{
			reset_fd(data);
			execve(tmp_path, arg, data->og_envp);
		}
		free(tmp_path);
		i++;
	}
	write(2, data->top->data, ft_strlen(data->top->data));
	write(2, ": command not found\n", 21);
	exit (127);
}
