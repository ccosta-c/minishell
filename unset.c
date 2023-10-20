/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:22:07 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/10/20 15:40:48 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	unset_builtin(t_data *data)
{
	t_tokens	*tmp;

	tmp = data->top->next;
	while (tmp != NULL)
	{
		actual_loop(tmp, data, data->export);
		actual_loop(tmp, data, data->env);
		tmp = tmp->next;
	}
}

void	actual_loop(t_tokens *tmp, t_data *data, t_charlst *list)
{
	t_charlst	*actual;
	t_charlst	*previous;
	int			i;

	i = 0;
	actual = list;
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
			else_unset(data, actual, previous, i);
			break ;
		}
		i++;
	}
}

void	else_unset(t_data *data, t_charlst *actl, t_charlst *prv, int i)
{
	if (i == 0)
	{
		data->export = actl->next;
		free(actl->content);
		free(actl);
	}
	else
	{
		prv->next = actl->next;
		free(actl->content);
		free(actl);
	}
}
