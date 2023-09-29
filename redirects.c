/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:20:43 by macastan          #+#    #+#             */
/*   Updated: 2023/09/20 15:20:45 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	redirects(t_data *data)
{
	t_tokens	*tmp;

	tmp = data->top;
	while (tmp != NULL)
	{
		if (tmp->type == R_OUT)
		{
			if (redi_out(data, tmp->data) == -1)
				return (-1);
		}
		else if (tmp->type == R_IN)
			printf("rin");
		else if (tmp->type == RR_IN)
			printf("rrin");
		else if (tmp->type == RR_OUT)
			printf("rrout");
		tmp = tmp->next;
	}
	return (free(tmp), 0);
}

int	redi_out(t_data *data, char *str)
{
	if (str[0] == '>' && !str[1])
	{
		if (redi_out_dois_nodes(data, str) == -1)
			return (-1);
	}
	/*else if (str[0] == '>' && str[1])
	{
		if (redi_out_um_node(data, str) == -1)
			return (-1);
	}
	else if (str[0] != '>')
	{
		if (redi_out_search(str) == 1)
			return (0);
		if (redi_out_dois_nodes2(data, str) == -1)
			return (-1);
	}*/
	return (0);
}