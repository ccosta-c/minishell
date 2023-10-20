/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:10:31 by macastan          #+#    #+#             */
/*   Updated: 2023/10/17 12:26:56 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	execution(t_data *data)
{
	char	**arg;

	pipes_num(data);
	if (data->pipes_nums != 0)
	{
		pipes_execution(data);
	}
	else
	{
		remove_quote_topdata(data);
		if (check_builtins(data) == 0)
		{
			arg = list_to_array(data);
			get_envpaths(data);
			execution_single(data, 0, arg, -1);
			free_array(arg);
			free_array(data->paths);
		}
	}
}

void	execution_single(t_data *data, int j, char **arg, int i)
{
	char	*tmp_path;
	pid_t	pid;

	while (data->paths[++i] != NULL)
	{
		tmp_path = get_tmp_path(data, i);
		if (access(tmp_path, X_OK) == 0)
		{
			j++;
			pid = fork();
			if (pid == 0)
				execve(tmp_path, arg, data->og_envp);
			get_exit_status_one(pid, data);
			wait(NULL);
			free(tmp_path);
			return ;
		}
		free(tmp_path);
	}
	if (j == 0)
	{
		write(2, data->top->data, ft_strlen(data->top->data));
		ft_putstr_fd(": command not found\n", 2);
		g_exit = 127;
	}
}

char	*get_tmp_path(t_data *data, int i)
{
	char	*tmp;
	char	*final;

	tmp = ft_strjoin("/", data->top->data);
	final = ft_strjoin(data->paths[i], tmp);
	free(tmp);
	return (final);
}
