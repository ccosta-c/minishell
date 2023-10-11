/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:10:31 by macastan          #+#    #+#             */
/*   Updated: 2023/10/11 18:36:14 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	execution(t_data *data)
{
	char	**arg;
	char	**cmd_pipes;

	pipes_num(data);
	if (data->pipes_nums != 0)
	{
		printf("pipes=%d\n", data->pipes_nums);
		cmd_pipes = pipes_commands(data);
		printf("fodasse o minishell\n");
		print_array(cmd_pipes);
	}
	else
	{
		remove_quote_topdata(data);
		if (check_builtins(data) == 0)
		{
			arg = list_to_array(data);
			get_envpaths(data);
			execution_single(data, 0, arg, 0);
			free_array(arg);
			free_array(data->paths);
		}
	}
	/*if (data->red_flag != 0)
	{
		dup2(0, STDIN_FILENO);
		//dup2(0, STDOUT_FILENO);
	}*/
}

void	execution_single(t_data *data, int j, char **arg, int i)
{
	char	*tmp_path;
	pid_t	pid;

	while (data->paths[i] != NULL)
	{
		tmp_path = get_tmp_path(data, i);
		if (access(tmp_path, X_OK) == 0)
		{
			j++;
			pid = fork();
			if (pid == 0)
			{
				execve(tmp_path, arg, data->og_envp);
				exit (0);
			}
			wait(NULL);
			free(tmp_path);
			return ;
		}
		free(tmp_path);
		i++;
	}
	if (j == 0)
		printf("%s: command not found\n", data->top->data);
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
