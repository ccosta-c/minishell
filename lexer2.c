/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 10:43:13 by macastan          #+#    #+#             */
/*   Updated: 2023/08/28 10:43:16 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

enum e_type	get_type(char *str)
{
	if (str[0] == '\"')
		return (1);
	else if (str[0] == '\'')
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
