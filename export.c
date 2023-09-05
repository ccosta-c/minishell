/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:50:38 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/09/05 15:53:36 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	ft_swap(char **a, char **b)
{
	char	*c;

	c = *a;
	*a = *b;
	*b = c;
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
	int	i;
	int	j;
	int	size;

	i = 0;
	size = count_variables(list);
	while (i < size - 1)
	{
		j = 0;
		if (list->content[j] == list->next->content[j])
		{
			while ((list->content[j] || list->next->content[j])
				&& (list->content[j] == list->next->content[j]))
				j++;
		}
		if (list->content[j] > list->next->content[j])
		{
			ft_swap(&list->content, &list->next->content);
			i = 0;
			continue ;
		}
		i++;
	}
	print_lstchar(list);
	//print_export(array);
}

void	print_export(char **array)
{
	int	i;
	int	j;

	i = 0;
	while (array[i] != NULL)
	{
		j = 0;
		write(1, "declare -x ", 11);
		while (array[i][j])
		{
			write(1, &array[i][j], 1);
			if (array[i][j] == '=')
				write (1, "\"", 1);
			if (array[i][j + 1] == '\0')
				write (1, "\"", 1);
			j++;
		}
		i++;
		write(1, "\n", 1);
	}
}
