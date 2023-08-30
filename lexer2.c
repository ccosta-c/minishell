/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 10:43:13 by macastan          #+#    #+#             */
/*   Updated: 2023/08/29 15:49:14 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

enum e_type	get_type(char *str, int start)
{
	if (str[start] == '\"')
		return (D_QUOTE);
	else if (str[start] == '\'')
		return (S_QUOTE);
	else if (str[start] == '|')
		return (PIPE);
	else if (str[start] == '<' && str[start + 1] != '<' )
		return (R_IN);
	else if (str[start] == '>' && str[start + 1] != '>' )
		return (R_OUT);
	else if (str[start] == '<' && str[start + 1] == '<' )
		return (RR_IN);
	else if (str[start] == '>' && str[start + 1] == '>' )
		return (RR_OUT);
	else
		return (GENERIC);
}

int	pipes_num(t_data *data)
{
	int			p;
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
