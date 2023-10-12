/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:34:07 by macastan          #+#    #+#             */
/*   Updated: 2023/10/11 11:34:11 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	redi_in(t_data *data, char *str, char *next_s)
{
	char	*tmp;

	if (str[0] == '<' && !str[1])
	{
		if (redi_out_search(next_s, 0, 0) == 0)
		{
			tmp = str_exp_quote(data, next_s, count_str_exp(next_s, 0, 0));
			if (redi_in_two_nodes(data, str, tmp) == -1)
				return (free(tmp), -1);
			return (free(tmp), 0);
		}
		else if (redi_out_search(next_s, 0, 0) != 0)
		{
			tmp = cut_str(next_s, data, -1, 0);
			if (redi_in_two_nodes_cut(data, str, tmp) == -1)
				return (free(tmp), -1);
			return (free(tmp), 0);
		}
	}
	else if (redi_in2(data, str, next_s) == -1)
		return (-1);
	return (0);
}

int	redi_in4(t_data *data, char *str)
{
	char	*tmp;

	if (str[0] == '<' && str[1])
	{
		if (redi_out_search(str, 1, 0) == 0)
		{
			tmp = change_str(str, data, 1);
			if (redi_in_one_node_del(data, str, tmp) == -1)
				return (free(tmp), -1);
			return (free(tmp), 0);
		}
		else if (redi_out_search(str, 1, 0) != 0)
		{
			tmp = cut_str_1(str, data, -1, 1);
			if (redi_in_no_node(data, tmp) == -1)
				return (free(tmp), -1);
			return (free(tmp), 0);
		}
	}
	else if (redi_in5(data, str) == -1)
		return (-1);
	return (0);
}

int	redi_in5(t_data *data, char *str)
{
	char	*tmp;
	int		j;

	j = cut_str2(str, 0, 0, 0);
	if (str[0] != '<'
		&& (str[ft_strlen(str) - 1] != '>' || str[ft_strlen(str) - 1] != '<'))
	{
		if (redi_out_search(str, 0, 0) == 1)
		{
			tmp = cut_str_else(str, data, j, 0);
			if (redi_in_no_node(data, tmp) == -1)
				return (free(tmp), -1);
			return (free(tmp), 0);
		}
		else if (redi_out_search(str, 0, 0) > 1)
		{
			tmp = cut_str_else(str, data, j, 0);
			if (redi_in_no_node(data, tmp) == -1)
				return (free(tmp), -1);
			return (free(tmp), 0);
		}
	}
	return (0);
}

int	redi_in2(t_data *data, char *str, char *next_s)
{
	char	*tmp;

	if (str[0] != '<'
		&& (str[ft_strlen(str) - 1] == '>' || str[ft_strlen(str) - 1] == '<'))
	{
		if (redi_out_search(str, 0, 0) == 1
			&& redi_out_search(next_s, 0, 0) == 0)
		{
			tmp = cut_str_end(str, data, 0, next_s);
			if (redi_in_one_node_del(data, next_s, tmp) == -1)
				return (free(tmp), -1);
			return (free(tmp), 0);
		}
		else if (redi_out_search(str, 0, 0) == 1
			&& redi_out_search(next_s, 0, 0) != 0)
		{
			tmp = cut_str_end2(str, data, 0, next_s);
			if (redi_in_no_node(data, tmp) == -1)
				return (free(tmp), -1);
			return (free(tmp), 0);
		}
	}
	else if (redi_in3(data, str) == -1)
		return (-1);
	return (0);
}

int	redi_in3(t_data *data, char *str)
{
	char	*tmp;

	if (str[0] != '<'
		&& (str[ft_strlen(str) - 1] == '>' || str[ft_strlen(str) - 1] == '<'))
	{
		if (redi_out_search(str, 0, 0) > 1)
		{
			tmp = cut_str_else(str, data, cut_str2(str, 0, 0, 0), 0);
			if (redi_in_no_node(data, tmp) == -1)
				return (free(tmp), -1);
			return (free(tmp), 0);
		}
	}
	else if (redi_in4(data, str) == -1)
		return (-1);
	return (0);
}