/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:50:38 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/09/07 16:47:21 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	ft_swap(t_charlist *list)
{
	char	*tmp;

	tmp = strdup(list->content);
	free(list->content);
	list->content = strdup(list->next->content);
	free(list->next->content);
	list->next->content = strdup(tmp);
	free(tmp);
}

int	count_variables(t_charlist *list)
{
	int			i;
	t_charlist	*tmp;

	tmp = list;
	i = 0;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	export_builtin(t_charlist *list)
{
	int			j;
	int			size;
	int			i;
	t_charlist	*tmp;

	size = count_variables(list);
	i = 0;
	tmp = list;
	while (i < (size - 1))
	{
		j = 0;
		if (tmp->content[j] == tmp->next->content[j])
		{
			while ((tmp->content[j] || tmp->next->content[j])
				&& (tmp->content[j] == tmp->next->content[j]))
				j++;
		}
		if (tmp->content[j] > tmp->next->content[j])
		{
			ft_swap(tmp);
			tmp = list;
			i = 0;
			continue ;
		}
		tmp = tmp->next;
		i++;
	}
}

void	print_export(t_charlist *list, int size)
{
	int			i;
	int			j;
	t_charlist	*tmp;

	i = 0;
	tmp = list;
	while (i < (size - 1))
	{
		j = 0;
		write(1, "declare -x ", 11);
		while (tmp->content[j])
		{
			write(1, &tmp->content[j], 1);
			if (tmp->content[j] == '=')
				write (1, "\"", 1);
			if (tmp->content[j + 1] == '\0')
				write (1, "\"", 1);
			j++;
		}
		tmp = tmp->next;
		i++;
		write(1, "\n", 1);
	}
}
