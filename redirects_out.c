/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_out.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:51:48 by macastan          #+#    #+#             */
/*   Updated: 2023/10/04 15:51:52 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	redi_out(t_data *data, char *str, char *next_s)
{
	if (data->fd_out != NULL)
		free(data->fd_out);
	if (data->tmp_r != NULL)
		free(data->tmp_r);
	if (str[0] == '>' && !str[1])
	{
		if (redi_out_search(next_s, 0, 0) == 0)
		{
			data->tmp_r = str_exp_quote(data, next_s,
					count_str_exp(next_s, 0, 0));
			if (redi_out_two_nodes(data, str, data->tmp_r) == -1)
				return (free(data->tmp_r), data->tmp_r = NULL, -1);
			return (free(data->tmp_r), data->tmp_r = NULL, 0);
		}
		else if (redi_out_search(next_s, 0, 0) != 0)
		{
			data->tmp_r = cut_str(next_s, data, -1, 0);
			if (redi_out_two_nodes_cut(data, str, data->tmp_r) == -1)
				return (free(data->tmp_r), data->tmp_r = NULL, -1);
			return (free(data->tmp_r), data->tmp_r = NULL, 0);
		}
	}
	else if (redi_out2(data, str, next_s) == -1)
		return (-1);
	return (0);
}

int	redi_out4(t_data *data, char *str)
{
	if (str[0] == '>' && str[1])
	{
		if (redi_out_search(str, 1, 0) == 0)
		{
			data->tmp_r = change_str(str, data, 1);
			if (redi_out_one_node_del(data, str, data->tmp_r) == -1)
				return (free(data->tmp_r), data->tmp_r = NULL, -1);
			return (free(data->tmp_r), data->tmp_r = NULL, 0);
		}
		else if (redi_out_search(str, 1, 0) != 0)
		{
			data->tmp_r = cut_str_1(str, data, -1, 1);
			if (redi_out_no_node(data, data->tmp_r) == -1)
				return (free(data->tmp_r), data->tmp_r = NULL, -1);
			return (free(data->tmp_r), data->tmp_r = NULL, 0);
		}
	}
	else if (redi_out5(data, str) == -1)
		return (-1);
	return (0);
}

int	redi_out5(t_data *data, char *str)
{
	int		j;

	j = cut_str2(str, 0, 0, 0);
	if (str[0] != '>'
		&& (str[ft_strlen(str) - 1] != '>' || str[ft_strlen(str) - 1] != '<'))
	{
		if (redi_out_search(str, 0, 0) == 1)
		{
			data->tmp_r = cut_str_else(str, data, j, 0);
			if (redi_out_no_node(data, data->tmp_r) == -1)
				return (free(data->tmp_r), data->tmp_r = NULL, -1);
			return (free(data->tmp_r), data->tmp_r = NULL, 0);
		}
		else if (redi_out_search(str, 0, 0) > 1)
		{
			data->tmp_r = cut_str_else(str, data, j, 0);
			if (redi_out_no_node(data, data->tmp_r) == -1)
				return (free(data->tmp_r), data->tmp_r = NULL, -1);
			return (free(data->tmp_r), data->tmp_r = NULL, 0);
		}
	}
	return (0);
}

int	redi_out2(t_data *data, char *str, char *next_s)
{
	if (str[0] != '>'
		&& (str[ft_strlen(str) - 1] == '>' || str[ft_strlen(str) - 1] == '<'))
	{
		if (redi_out_search(str, 0, 0) == 1
			&& redi_out_search(next_s, 0, 0) == 0)
		{
			data->tmp_r = cut_str_end(str, data, 0, next_s);
			if (redi_out_one_node_del(data, next_s, data->tmp_r) == -1)
				return (free(data->tmp_r), data->tmp_r = NULL, -1);
			return (free(data->tmp_r), data->tmp_r = NULL, 0);
		}
		else if (redi_out_search(str, 0, 0) == 1
			&& redi_out_search(next_s, 0, 0) != 0)
		{
			data->tmp_r = cut_str_end2(str, data, 0, next_s);
			if (redi_out_no_node(data, data->tmp_r) == -1)
				return (free(data->tmp_r), data->tmp_r = NULL, -1);
			return (free(data->tmp_r), data->tmp_r = NULL, 0);
		}
	}
	else if (redi_out3(data, str) == -1)
		return (-1);
	return (0);
}

int	redi_out3(t_data *data, char *str)
{
	if (str[0] != '>'
		&& (str[ft_strlen(str) - 1] == '>' || str[ft_strlen(str) - 1] == '<'))
	{
		if (redi_out_search(str, 0, 0) > 1)
		{
			data->tmp_r = cut_str_else(str, data, cut_str2(str, 0, 0, 0), 0);
			if (redi_out_no_node(data, data->tmp_r) == -1)
				return (free(data->tmp_r), data->tmp_r = NULL, -1);
			return (free(data->tmp_r), data->tmp_r = NULL, 0);
		}
	}
	else if (redi_out4(data, str) == -1)
		return (-1);
	return (0);
}
