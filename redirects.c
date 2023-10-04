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
	while (tmp)
	{
		if (tmp->type == R_OUT)
		{
			if (tmp->next)
			{
				if (redi_out(data, tmp->data, tmp->next->data) == -1)
					return (-1);
				return (redirects(data));
			}
			else
			{
				if (redi_out(data, tmp->data, "maluca") == -1)
					return (-1);
				return (0);
			}
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