/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:20:04 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/09/07 15:27:35 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	add_to_charlist(t_charlist **top, char *content)
{
	t_charlist	*tmp;

	if ((*top) == NULL)
	{
		(*top) = ft_addnew(content);
	}
	else
	{
		tmp = ft_golast((*top));
		tmp->next = ft_addnew(content);
	}
}

t_charlist	*ft_addnew(char *content)
{
	t_charlist	*ptr;

	ptr = malloc(sizeof(t_charlist));
	if (!ptr)
		return (NULL);
	ptr->content = strdup(content);
	ptr->next = NULL;
	return (ptr);
}

t_charlist	*ft_golast(t_charlist *lst)
{
	t_charlist	*ptr;

	ptr = lst;
	if (ptr == NULL)
	{
		return (0);
	}
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	return (ptr);
}
