/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_echo2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:33:38 by macastan          #+#    #+#             */
/*   Updated: 2023/09/05 12:33:40 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void simple_echo_minus_n(char *str)
{
	size_t i;

	i = 0;
	while(str[i])
	{
		write(1,&str[i], 1);
		i++;
	}
}

void echo_minus_n(t_data *data)
{
	t_tokens	*tmp;

	tmp = data->top->next->next;
	while (tmp != NULL)
	{
		if (ft_strncmp("-n", tmp->data, tmp->len) == 0)
			continue ;
		else if (tmp->type == S_QUOTE)
			simple_echo_minus_n(tmp->data);
		else
			printf("c\n");
		tmp = tmp->next;
	}
	free(tmp);
}