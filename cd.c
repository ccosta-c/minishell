/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:18:40 by macastan          #+#    #+#             */
/*   Updated: 2023/09/13 12:18:42 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	cd(t_data *data)
{
	remove_quote_list(data);
	if (data->top->next->next)
	{
		printf("minishell: cd: too many arguments\n");
		g_exit = 1;
		return ;
	}
	if (ft_strncmp("-", data->top->next->data, ft_strlen(data->top->next->data)) == 0)
	{
		printf("exec volta 1\n");
	}
	else if (ft_strncmp("..", data->top->next->data, ft_strlen(data->top->next->data)) == 0)
	{
		printf("exec volta 1\n");
	}
	else if (ft_strncmp(".", data->top->next->data, ft_strlen(data->top->next->data)) == 0)
	{
		printf("faz nada\n");
	}
	else
	{
		printf("check se pode mudar e muda\n");
	}
}