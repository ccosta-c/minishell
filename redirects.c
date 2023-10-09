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
			if (redirects_out(data, tmp->next, tmp->data, tmp) == -1)
				return (-1);
			break ;
		}
		else if (tmp->type == R_IN)
			printf("rin");
		else if (tmp->type == RR_IN)
			printf("rrin");
		else if (tmp->type == RR_OUT)
			printf("rrout");
		else
			tmp = tmp->next;
	}
	if (search_red(data) == 1)
	{
		if (redirects(data, data->top) == -1)
			return (-1);
	}
	return (0);
}

int	redirects_out(t_data *data, t_tokens *n, char *str, t_tokens *c)
{
	t_tokens	*next;
	t_tokens	*current;

	next = n;
	current = c;
	(void)str;
	if (n)
	{
		if (redi_out(data, current->data, next->data) == -1)
			return (-1);
		/*if (search_red(data) == 1)
			return (redirects(data, data->top));*/
	}
	else
	{
		if (redi_out(data, current->data, "maluca") == -1)
			return (-1);
		/*if (redi_out_search(current->data, 0, 0) != 0)
			return (redirects(data, data->top));*/
		return (0);
	}
	return (0);
}