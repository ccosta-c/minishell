/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:19:48 by macastan          #+#    #+#             */
/*   Updated: 2023/10/26 12:19:50 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	write_here(char *in, t_data *data, int fd_file)
{
	char	*ret;
	char	*re;
	int		ex;

	data->sti = 0;
	ex = count_exp(in, 0);
	if (ex == 0)
		return (write_here2(in, fd_file), 0);
	ret = ft_strdup(in);
	while (ex > 0)
	{
		if (ex == 1)
			re = get_exp_here(ret, 0, data);
		else
		{
			re = get_exp_here(ret, 0, data);
			free(ret);
			ret = ft_strdup(re);
			free(re);
		}
		ex--;
	}
	free(ret);
	write_here2(re, fd_file);
	return (free(re), 0);
}

void	write_here2(char *in, int fd_file)
{
	ft_putstr_fd(in, fd_file);
	write(fd_file, "\n", 1);
}

int	count_exp(char *in, int i)
{
	int	ex;

	ex = 0;
	while (in[i])
	{
		if (in[i] == '$')
			ex++;
		i++;
	}
	return (ex);
}

int	cut_exp(char *str, t_data *data)
{
	while (str[data->sti])
	{
		while (str[data->sti] == '$' && str[data->sti + 1] == '$')
			data->sti++;
		if (str[data->sti] == '$' && str[data->sti + 1] != '$')
			return (data->sti);
		data->sti++;
	}
	return (data->sti);
}

char	*get_exp_here(char *str, int i, t_data *data)
{
	char	*tmp;
	char	*ret;
	int		total;

	i = cut_exp(str, data);
	if (str[i] == '\0')
		return (ret = ft_strdup(str), ret);
	tmp = get_tmp(str, i, 0, i);
	if (tmp[0] == '$')
		return (free(tmp), ret = ft_strdup(str), ret);
	ret = search_ex(tmp, data->env, count_variables(data->env), 0);
	if (ret)
	{
		total = ft_strlen(tmp) + 1;
		free(tmp);
		tmp = join_exp_str(ret, str, total, i);
	}
	else
	{
		total = ft_strlen(tmp) + 1;
		free(tmp);
		tmp = cut_exp_str(str, total, i);
	}
	return (free(ret), tmp);
}
