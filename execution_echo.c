/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:58:50 by macastan          #+#    #+#             */
/*   Updated: 2023/09/05 11:58:54 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void execution_echo(t_data *data)
{
	if (!data->top->next)
	{
		printf("\n");
		g_exit = 0;
		return ;
	}
	if (ft_strncmp("-n", data->top->next->data, data->top->next->len) == 0)
	{
		if (!data->top->next->next)
		{
			printf("\n");
			g_exit = 0;
			return ;
		}
		echo_minus_n(data);
		g_exit = 0;
		return ;
	}
	else
		echo_normal(data);
}

void simple_echo(char *str)
{
	size_t i;

	i = 0;
	while(str[i])
	{
		write(1,&str[i], 1);
		i++;
	}
	write(1,"\n", 1);
}

void echo_normal(t_data *data)
{
	t_tokens	*tmp;

	tmp = data->top->next;
	while (tmp != NULL)
	{
		if (tmp->type == S_QUOTE)
			simple_echo(tmp->data);
		else
			printf("b\n");
		tmp = tmp->next;
	}
	free(tmp);
}

