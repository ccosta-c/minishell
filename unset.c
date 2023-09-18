/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:22:07 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/09/18 15:07:38 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	unset_builtin(t_data *data)
{
	t_tokens	*tmp;

	tmp = data->top->next;
	while (tmp != NULL)
	{
		actual_loop(tmp, data);
		tmp = tmp->next;
	}
}

void	actual_loop(t_tokens *tmp, t_data *data)
{
	t_charlist	*actual;
	t_charlist	*previous;
	int			i;

	i = 0;
	actual = data->export;
	previous = actual;
	while (actual != NULL)
	{
		if (ft_strncmp(actual->content, tmp->data, check_name(tmp->data)) != 0)
		{
			previous = actual;
			actual = actual->next;
		}
		else
		{
			if (i == 0)
			{
				data->export = actual->next;
				free(actual->content);
				free(actual);
			}
			else
			{
				previous->next = actual->next;
				free(actual->content);
				free(actual);
			}
			break ;
		}
		i++;
	}
}
