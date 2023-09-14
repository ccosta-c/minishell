/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:22:07 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/09/14 15:13:22 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	unset_builtin(t_data *data)
{
	t_tokens	*tmp;
	t_charlist	*actual;
	t_charlist	*previous;

	actual = data->export;
	tmp = data->top->next;
	while (tmp != NULL)
	{
		while (actual != NULL)
		{
			if (ft_strncmp(actual->content, tmp->data, check_name(tmp->data)) != 0)
			{
				previous = actual;
				actual = actual->next;
			}
			else
			{
				previous->next = actual->next;
				free(actual->content);
				free(actual);
				actual = previous->next;
			}
		}
		tmp = tmp->next;
	}
}
