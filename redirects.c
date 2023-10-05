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

int	redirects(t_data *data, t_tokens *tmp)
{
	while (tmp)
	{
		if (tmp->type == R_OUT)
		{
			if (redirects_out(data, &tmp->next, tmp->data, tmp->next->data) == -1)
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
	return (0);
}

int	redirects_out(t_data *data, t_tokens **lst, char *str, char *next)
{
	if (lst)
	{
		if (redi_out(data, str, next) == -1)
			return (-1);
		return (redirects(data, data->top));
	}
	else
	{
		if (redi_out(data, str, "maluca") == -1)
			return (-1);
		if (redi_out_search(str, 0, 0) != 0)
			return (redirects(data, data->top));
		return (0);
	}
}