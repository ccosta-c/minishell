/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:10:31 by macastan          #+#    #+#             */
/*   Updated: 2023/10/20 16:59:13 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	execution(t_data *data)
{
	char	**arg;

	pipes_num(data);
	if (data->pipes_nums != 0)
		pipes_execution(data);
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

int	execution_single(t_data *data, int j, char **arg, int i)
{
	char	*tmp_path;
	pid_t	pid;

	while (data->paths[++i] != NULL)
	{
		tmp_path = get_tmp_path(data, i, arg);
		if (access(tmp_path, X_OK) == 0)
		{
			j++;
			pid = fork();
			if (pid == 0)
				execve(tmp_path, arg, data->og_envp);
			get_exit_status_one(pid, data);
			wait(NULL);
			return (free(tmp_path), 0);
		}
		free(tmp_path);
	}
	if (j == 0)
		print_error(arg[0], strerror(errno));
	return (0);
}

void	print_error(char *arg, char *erro)
{
	write(2, arg, ft_strlen(arg));
	write(2, ": ", 2);
	ft_putstr_fd(erro, 2);
	write(2, "\n", 1);
	g_exit = 127;
}

void	cut_top_data_b(char *str, char **arg, size_t f)
{
	char	*tmp;
	int		i;

	i = 0;
	f = ft_strlen(str);
	while (f > 0)
	{
		if (str[f] == '/')
			break ;
		f--;
	}
	tmp = malloc(sizeof (char) * (ft_strlen(str) - i));
	f++;
	while (str[f] != '\0')
	{
		tmp[i] = str[f];
		i++;
		f++;
	}
	tmp[i] = '\0';
	free(arg[0]);
	arg[0] = tmp;
	return ;
}

char	*get_tmp_path(t_data *data, int i, char **arg)
{
	char	*tmp;
	char	*final;

	if (ft_strchr(data->top->data, '/') != 0)
	{
		final = ft_strdup(data->top->data);
		cut_top_data_b(data->top->data, arg, 0);
		return (final);
	}
	tmp = ft_strjoin("/", data->top->data);
	final = ft_strjoin(data->paths[i], tmp);
	free(tmp);
	return (final);
}
