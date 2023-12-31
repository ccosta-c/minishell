/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:22:07 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/10/21 15:35:15 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	unset_builtin(t_data *data)
{
	t_tokens	*tmp;

	tmp = data->top->next;
	while (tmp != NULL)
	{
		if (unset_checks(tmp->data) == 1)
			return ;
		actual_loop(tmp, data, data->export);
		actual_loop(tmp, data, data->env);
		tmp = tmp->next;
	}
	g_exit = 0;
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

int	unset_checks(char *data)
{
	int		i;

	i = 0;
	while (data[i] != '\0')
	{
		if ((data[i] < 65 || data[i] > 90) && (data[i] < 97 || data[i] > 122))
		{
			g_exit = 1;
			printf("unset: not a valid identifier\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	handle_exit_pipes(t_data *data, long long e)
{
	if (!data->top->next)
		g_exit = 0;
	else
	{
		e = ft_atol(data->top->next->data);
		remove_quote_list(data);
		if (e == 0)
			g_exit = 0;
		else if (check_exit_data(data->top->next->data) == -1)
		{
			write(2, "minishell: exit: ", 17);
			write(2, data->top->next->data, ft_strlen(data->top->next->data));
			write(2, " numeric argument required\n", 27);
			g_exit = 2;
		}
		else if (ft_nlen(e) != ft_strlen(data->top->next->data))
		{
			write(2, "minishell: exit: ", 17);
			write(2, &data->top->next->data, ft_strlen(data->top->next->data));
			write(2, " numeric argument required\n", 27);
			g_exit = 2;
		}
		g_exit = (e % 256);
	}
}
