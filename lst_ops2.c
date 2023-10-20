/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:20:04 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/09/29 17:35:38 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	add_to_charlist(t_charlst **top, char *content)
{
	t_charlst	*tmp;

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

t_charlst	*ft_addnew(char *content)
{
	t_charlst	*ptr;

	ptr = malloc(sizeof(t_charlst));
	if (!ptr)
		return (NULL);
	ptr->content = ft_strdup(content);
	ptr->next = NULL;
	return (ptr);
}

t_charlst	*ft_golast(t_charlst *lst)
{
	t_charlst	*ptr;

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

int	delete_redirects(t_tokens **lst, char *symb, t_data *data, int i)
{
	t_tokens	*tmp;
	t_tokens	*before;
	t_tokens	*after;

	tmp = *lst;
	before = *lst;
	if (data->lst_size == 1 && ft_strcmp(tmp->data, symb) == 0)
		return (ft_cleartokens(lst), data->lst_size--);
	while (tmp)
	{
		after = tmp->next;
		if (ft_strcmp(tmp->data, symb) == 0)
		{
			free(tmp->data);
			if (i == 0)
				return (free(tmp), data->top = after, data->lst_size--);
			if (i > 0)
				return (free(tmp), before->next = after, data->lst_size--);
		}
		i++;
		before = tmp;
		tmp = tmp->next;
	}
	return (0);
}

int	get_size_lst(t_data *data)
{
	t_tokens	*tmp;
	int			size;

	size = 0;
	tmp = data->top;
	while (tmp != NULL)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}
