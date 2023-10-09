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
	char	*tmp;

	if (str[0] == '>' && !str[1])
	{
		if (redi_out_search(next_s, 0, 0) == 0)
		{
			tmp = get_exp(next_s, 0, data);
			if (redi_out_two_nodes(data, str, tmp) == -1)
				return (-1);
			//free(tmp);
		}
		else if (redi_out_search(next_s, 0, 0) != 0)
		{
			tmp = cut_str(next_s, data, -1, 0);
			if (redi_out_two_nodes_cut(data, str, tmp) == -1)
				return (-1);
			//free(tmp);
		}
	}
	else if (redi_out2(data, str) == -1)
		return (-1);
	return (0);
}

int	redi_out2(t_data *data, char *str)
{
	char	*tmp;

	if (str[0] == '>' && str[1])
	{
		if (redi_out_search(str, 1, 0) == 0)
		{
			tmp = change_str(str, data);
			if (redi_out_one_node_del(data, str, tmp) == -1)
				return (-1);
			//free(tmp);
		}
		else if (redi_out_search(str, 1, 0) != 0)
		{
			tmp = cut_str_1(str, data, -1, 1);
			if (redi_out_one_node(data, str, tmp) == -1)
				return (-1);
			//free(tmp);
		}
	}
	else if (redi_out3(data, str) == -1)
		return (-1);
	return (0);
}

int	redi_out3(t_data *data, char *str)
{
	char	*tmp;
	int	j;

	j = cut_str2(str, 0, 0, 0);
	if (str[0] != '>')
	{
		if (redi_out_search(str, 0, 0) == 1)
		{
			tmp = cut_str_else(str, data, j, 0);
			if (redi_out_one_node(data, str, tmp) == -1)
				return (-1);
			//free(tmp);
		}
		else if (redi_out_search(str, 0, 0) > 1)
		{
			tmp = cut_str_else(str, data, j, 0);
			if (redi_out_one_node(data, str, tmp) == -1)
				return (-1);
			//free(tmp);
		}
	}
	return (0);
}