/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:50:38 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/10/02 14:02:59 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	ft_swap(t_charlist *list)
{
	char	*tmp;

	tmp = ft_strdup(list->content);
	free(list->content);
	list->content = ft_strdup(list->next->content);
	free(list->next->content);
	list->next->content = ft_strdup(tmp);
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
	int			check_equal;

	i = 0;
	tmp = list;
	while (i < (size))
	{
		j = 0;
		write(1, "declare -x ", 11);
		check_equal = 0;
		while (tmp->content[j])
		{
			write(1, &tmp->content[j], 1);
			if (tmp->content[j] == '=')
			{
				write (1, "\"", 1);
				check_equal = 1;
			}
			if (tmp->content[j + 1] == '\0' && check_equal == 1)
				write (1, "\"", 1);
			j++;
		}
		tmp = tmp->next;
		i++;
		write(1, "\n", 1);
	}
}

void	add_export(t_data *data)
{
	t_tokens	*tmp;
	char		*no_quotes;

	tmp = data->top->next;
	while (tmp != NULL)
	{
		if ((strchr(tmp->data, '\'') != 0) || (strchr(tmp->data, '\"') != 0))
		{
			no_quotes = remove_quote(tmp->data, 0, 0, 0);
			free(tmp->data);
			tmp->data = ft_strdup(no_quotes);
			free (no_quotes);
		}
		if (name_variable(tmp->data, data->export) == 1)
		{
			if (strchr(tmp->data, '=') != 0)
				name_variable(tmp->data, data->env);
			return ;
		}
		else
		{
			add_to_charlist(&data->export, tmp->data);
			if (strchr(tmp->data, '=') != 0)
				add_to_charlist(&data->env, tmp->data);
			tmp = tmp->next;
		}
	}
}
