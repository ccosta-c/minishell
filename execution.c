/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:10:31 by macastan          #+#    #+#             */
/*   Updated: 2023/08/30 17:02:02 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	execution(t_data *data)
{
	int	j;

	j = pipes_num(data);
	printf("Pipes: %i\n", j);
	if (pipes_num(data) != 0)
		printf("exec pipe\n");
		//execution_pipe(data);
	else
		execution_single(data);
}

void	execution_single(t_data *data)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	**arg;
	pid_t	pid;

	i = 0;
	get_envpaths(data);
	arg = list_to_array(data);
	while (data->paths[i] != NULL)
	{
		tmp = ft_strjoin("/", data->top->data);
		tmp2 = ft_strjoin(data->paths[i], tmp);
		if (access(tmp2, X_OK) == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				execve(tmp2, arg, NULL);
				waitpid(pid, 0, 0);
				return ;
			}
		}
		free(tmp);
		free(tmp2);
		i++;
	}
}
