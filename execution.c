/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:10:31 by macastan          #+#    #+#             */
/*   Updated: 2023/09/28 12:33:45 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	execution(t_data *data)
{
	char	**arg;
	
	if (pipes_num(data) != 0)
		printf("exec pipe\n");
		//execution_pipe(data);
	else
	{
		remove_quote_topdata(data);
		if (check_builtins(data) == 0)
		{
			arg = list_to_array(data);
			get_envpaths(data);
			execution_single(data, 0, arg);
			free_array(arg);
			free_array(data->paths);
		}
		}
	}

void	execution_single(t_data *data, int j, char **arg)
{
	int		i;
	char	*tmp_path;
	pid_t	pid;

	i = 0;
	while (data->paths[i] != NULL)
	{
		tmp_path = get_tmp_path(data, i);
		if (access(tmp_path, X_OK) == 0)
		{
			j++;
			pid = fork();
			if (pid == 0)
			{
				execve(tmp_path, arg, NULL);
				exit (0);
			}
			wait(NULL);
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
