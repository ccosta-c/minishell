/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:50:38 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/09/07 16:18:29 by ccosta-c         ###   ########.fr       */
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
	print_export(list);
}

void	print_export(t_charlist *list)
{
	int	i;
	int	j;
	int	size;

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
