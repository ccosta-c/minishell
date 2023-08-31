/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:10:31 by macastan          #+#    #+#             */
/*   Updated: 2023/08/31 12:13:20 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	execution(t_data *data)
{
	char	**arg;

	arg = list_to_array(data);
	if (pipes_num(data) != 0)
		printf("exec pipe\n");
		//execution_pipe(data);
	else
	{
		if (check_builtins(data) == 0)
		{
			get_envpaths(data);
			execution_single(data, 0, arg);
		}
	}
	free(arg);
}

void	execution_single(t_data *data, int j, char **arg)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (data->paths[i] != NULL)
	{
		if (access(get_tmp_path(data), X_OK) == 0)
		{
			j++;
			pid = fork();
			if (pid == 0)
			{
				execve(get_tmp_path(data), arg, NULL);
				exit (0);
			}
			wait(NULL);
			return ;
		}
		free(tmp);
		i++;
	}
	if (j == 0)
		printf("%s: command not found\n", data->top->data);
}

char	*get_tmp_path(t_data *data)
{
	char	*tmp;
	char	*final;

	tmp = ft_strjoin("/", data->top->data);
	final = ft_strjoin(data->paths[i], tmp);
	free(tmp);
	return (final);
}
