/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_append.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:58:28 by macastan          #+#    #+#             */
/*   Updated: 2023/10/12 15:58:52 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	redi_append(t_data *data, char *str, char *next_s)
{
	if (data->fd_out != NULL)
		free(data->fd_out);
	if (data->tmp_r != NULL)
		free(data->tmp_r);
	if (str[0] == '>' && str[1] == '>' && !str[2])
	{
		if (redi_out_search(next_s, 0, 0) == 0)
		{
			data->tmp_r = str_exp_quote(data, next_s,
					count_str_exp(next_s, 0, 0));
			if (redi_append_two_nodes(data, str, data->tmp_r) == -1)
				return (free(data->tmp_r), data->tmp_r = NULL, -1);
			return (free(data->tmp_r), data->tmp_r = NULL, 0);
		}
		else if (redi_out_search(next_s, 0, 0) != 0)
		{
			data->tmp_r = cut_str_append(next_s, data, -1, 0);
			if (redi_append_two_nodes_cut(data, str, data->tmp_r) == -1)
				return (free(data->tmp_r), data->tmp_r = NULL, -1);
			return (free(data->tmp_r), data->tmp_r = NULL, 0);
		}
	}
	else if (redi_append2(data, str, next_s) == -1)
		return (-1);
	return (0);
}

int	redi_append4(t_data *data, char *str)
{
	if (str[0] == '<' && str[1] == '<' && str[2])
	{
		if (redi_out_search(str, 2, 0) == 0)
		{
			data->tmp_r = change_str(str, data, 2);
			if (redi_append_one_node_del(data, str, data->tmp_r) == -1)
				return (free(data->tmp_r), data->tmp_r = NULL, -1);
			return (free(data->tmp_r), data->tmp_r = NULL, 0);
		}
		else if (redi_out_search(str, 2, 0) != 0)
		{
			data->tmp_r = cut_str_1_append(str, data, -1, 2);
			if (redi_append_no_node(data, data->tmp_r) == -1)
				return (free(data->tmp_r), data->tmp_r = NULL, -1);
			return (free(data->tmp_r), data->tmp_r = NULL, 0);
		}
	}
	else if (redi_append5(data, str) == -1)
		return (-1);
	return (0);
}

int	redi_append5(t_data *data, char *str)
{
	int		j;

	j = cut_str2(str, 0, 0, 0);
	if (str[0] != '<'
		&& (str[ft_strlen(str) - 1] != '>' || str[ft_strlen(str) - 1] != '<'))
	{
		if (redi_out_search(str, 0, 0) == 1)
		{
			data->tmp_r = cut_str_else_append(str, data, j, 0);
			if (redi_append_no_node(data, data->tmp_r) == -1)
				return (free(data->tmp_r), data->tmp_r = NULL, -1);
			return (free(data->tmp_r), data->tmp_r = NULL, 0);
		}
		else if (redi_out_search(str, 0, 0) > 1)
		{
			data->tmp_r = cut_str_else_append(str, data, j, 0);
			if (redi_append_no_node(data, data->tmp_r) == -1)
				return (free(data->tmp_r), data->tmp_r = NULL, -1);
			return (free(data->tmp_r), data->tmp_r = NULL, 0);
		}
	}
	return (0);
}

int	redi_append2(t_data *data, char *str, char *next_s)
{
	if (str[0] != '<'
		&& str[ft_strlen(str) - 2] == '>' && str[ft_strlen(str) - 1] == '>')
	{
		if (redi_out_search(str, 0, 0) == 1
			&& redi_out_search(next_s, 0, 0) == 0)
		{
			data->tmp_r = cut_str_end_append(str, data, 0, next_s);
			if (redi_append_one_node_del(data, next_s, data->tmp_r) == -1)
				return (free(data->tmp_r), data->tmp_r = NULL, -1);
			return (free(data->tmp_r), data->tmp_r = NULL, 0);
		}
		else if (redi_out_search(str, 0, 0) == 1
			&& redi_out_search(next_s, 0, 0) != 0)
		{
			data->tmp_r = cut_str_end2_append(str, data, 0, next_s);
			if (redi_append_no_node(data, data->tmp_r) == -1)
				return (free(data->tmp_r), data->tmp_r = NULL, -1);
			return (free(data->tmp_r), data->tmp_r = NULL, 0);
		}
	}
	else if (redi_append3(data, str) == -1)
		return (-1);
	return (0);
}

int	redi_append3(t_data *data, char *str)
{
	if (str[0] != '<'
		&& (str[ft_strlen(str) - 1] == '>' || str[ft_strlen(str) - 1] == '<'))
	{
		if (redi_out_search(str, 0, 0) > 1)
		{
			data->tmp_r = cut_str_else_append(str, data,
					cut_str2(str, 0, 0, 0), 0);
			if (redi_append_no_node(data, data->tmp_r) == -1)
				return (free(data->tmp_r), data->tmp_r = NULL, -1);
			return (free(data->tmp_r), data->tmp_r = NULL, 0);
		}
	}
	else if (redi_append4(data, str) == -1)
		return (-1);
	return (0);
}
