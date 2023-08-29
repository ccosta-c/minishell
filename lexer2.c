/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 10:43:13 by macastan          #+#    #+#             */
/*   Updated: 2023/08/29 15:38:54 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

enum e_type	get_type(char *str, int start)
{
	if (str[start] == '\"')
		return (1);
	else if (str[start] == '\'')
		return (2);
	else
		return (0);
}

int	pipes_num(t_data *data)
{
	int	p;
	t_tokens	*tmp;

	p = 0;
	tmp = data->top;
	while (tmp != NULL)
	{
		if (tmp->data[0] == '|')
			p++;
		tmp = tmp->next;
	}
	free(tmp);
	return (p);
}
