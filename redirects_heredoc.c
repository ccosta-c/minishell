/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:43:40 by macastan          #+#    #+#             */
/*   Updated: 2023/10/11 17:43:42 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	redi_heredoc(t_data *data, char *str, char *next_s, char *h)
{
	char	*tmp;

	if (str[0] == '<' && str[1] == '<' && !str[2])
	{
		if (redi_out_search(next_s, 0, 0) == 0)
		{
			tmp = remove_quote(next_s, 0, 0, 0);
			if (redi_here_two_nodes(data, str, tmp, h) == -1)
				return (free(tmp), -1);
			return (free(tmp), 0);
		}
		else if (redi_out_search(next_s, 0, 0) != 0)
		{
			tmp = cut_str_here(next_s, data, -1, 0);
			if (redi_here_two_n_cut(data, str, tmp, h) == -1)
				return (free(tmp), -1);
			return (free(tmp), 0);
		}
	}
	else if (redi_here2(data, str, next_s, h) == -1)
		return (-1);
	return (0);
}

int	redi_here4(t_data *data, char *str, char *h)
{
	char	*tmp;

	if (str[0] == '<' && str[1] == '<' && str[2])
	{
		if (redi_out_search(str, 2, 0) == 0)
		{
			tmp = change_str_here(str, 2);
			if (redi_here_one_n_del(data, str, tmp, h) == -1)
				return (free(tmp), -1);
			return (free(tmp), 0);
		}
		else if (redi_out_search(str, 2, 0) != 0)
		{
			tmp = cut_str_1_here(str, data, -1, 2);
			if (redi_here_no_node(data, tmp, h) == -1)
				return (free(tmp), -1);
			return (free(tmp), 0);
		}
	}
	else if (redi_here5(data, str, h) == -1)
		return (-1);
	return (0);
}

int	redi_here5(t_data *data, char *str, char *h)
{
	char	*tmp;
	int		j;

	j = cut_str2(str, 0, 0, 0);
	if (str[0] != '<'
		&& (str[ft_strlen(str) - 1] != '>' || str[ft_strlen(str) - 1] != '<'))
	{
		if (redi_out_search(str, 0, 0) == 1)
		{
			tmp = cut_str_else_here(str, data, j, 0);
			if (redi_here_no_node(data, tmp, h) == -1)
				return (free(tmp), -1);
			return (free(tmp), 0);
		}
		else if (redi_out_search(str, 0, 0) > 1)
		{
			tmp = cut_str_else_here(str, data, j, 0);
			if (redi_here_no_node(data, tmp, h) == -1)
				return (free(tmp), -1);
			return (free(tmp), 0);
		}
	}
	return (0);
}

int	redi_here2(t_data *data, char *str, char *next_s, char *h)
{
	char	*tmp;

	if (str[0] != '<'
		&& str[ft_strlen(str) - 2] == '<' && str[ft_strlen(str) - 1] == '<')
	{
		if (redi_out_search(str, 0, 0) == 1
			&& redi_out_search(next_s, 0, 0) == 0)
		{
			tmp = cut_str_end_here(str, data, 0, next_s);
			if (redi_here_one_n_del(data, next_s, tmp, h) == -1)
				return (free(tmp), -1);
			return (free(tmp), 0);
		}
		else if (redi_out_search(str, 0, 0) == 1
			&& redi_out_search(next_s, 0, 0) != 0)
		{
			tmp = cut_str_end2_here(str, data, 0, next_s);
			if (redi_here_no_node(data, tmp, h) == -1)
				return (free(tmp), -1);
			return (free(tmp), 0);
		}
	}
	else if (redi_here3(data, str, h) == -1)
		return (-1);
	return (0);
}

int	redi_here3(t_data *data, char *str, char *h)
{
	char	*tmp;

	if (str[0] != '<'
		&& (str[ft_strlen(str) - 1] == '>' || str[ft_strlen(str) - 1] == '<'))
	{
		if (redi_out_search(str, 0, 0) > 1)
		{
			tmp = cut_str_else_here(str, data, cut_str2(str, 0, 0, 0), 0);
			if (redi_here_no_node(data, tmp, h) == -1)
				return (free(tmp), -1);
			return (free(tmp), 0);
		}
	}
	else if (redi_here4(data, str, h) == -1)
		return (-1);
	return (0);
}
