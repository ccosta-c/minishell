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
	if (pipes_num(data) != 0)
		printf("exec pipe\n");
		//execution_pipe(data);
	else
	{
//		if (check_builtins(data) == 0)
//			execution_single(data);
	}
}

void	execution_single(t_data *data)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	**arg;
	pid_t	pid;
	int		j;

	j = 0;
	i = 0;
	get_envpaths(data);
	arg = list_to_array(data);
	while (data->paths[i] != NULL)
	{
		tmp = ft_strjoin("/", data->top->data);
		tmp2 = ft_strjoin(data->paths[i], tmp);
		if (access(tmp2, X_OK) == 0)
		{
			j++;
			pid = fork();
			if (pid == 0)
			{
				execve(tmp2, arg, NULL);
				exit (0);
			}
			wait(NULL);
			return ;
		}
		free(tmp);
		free(tmp2);
		i++;
	}
	if (j == 0)
	{
		printf("%s: command not found\n", data->top->data);
	}
}
