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
	int	d_q;
	int s_q;

	d_q = 0;
	s_q = 0;
	while (str[start])
	{
		if (str[start] == '\"')
			d_q++;
		else if (str[start] == '\'')
			s_q++;
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
		start++;
	}
	if (d_q > 0 && s_q == 0)
		return (D_QUOTE);
	else if (s_q > 0 && d_q == 0)
		return (S_QUOTE);
	else if (s_q > 0 && d_q > 0)
		return (SPECIAL_QUOTE);
	return (GENERIC);
}

int	pipes_num(t_data *data)
{
	int			p;
	int 		i;
	t_tokens	*tmp;

	p = 0;
	tmp = data->top;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->data[i])
		{
			if (tmp->data[i] == '|')
				p++;
			i++;
		}
		tmp = tmp->next;
	}
	printf("%i\n", p);
	free(tmp);
	return (p);
}
