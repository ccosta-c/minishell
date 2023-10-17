/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:31:29 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/10/16 15:59:00 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

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
	reset_fd(data);
	exit(0);
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
			exit (0);
		}
		free(tmp_path);
		i++;
	}
	printf("%s: command not found\n", data->top->data);
}
