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
	while (str[start])
	{
		if (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
		{
			if (search_quote(str, '\"') == 0)
				return (D_QUOTE);
		}
		if (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
		{
			if (search_quote(str, '\'') == 0)
				return (S_QUOTE);
		}
		if (str[start] == '|')
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
	return (GENERIC);
}

int	search_quote(char *str, char q)
{
	int		i;

	i = 1;
	while (str[i + 1] != '\0')
	{
		if (str[i] == q)
			return (-1);
		i++;
	}
	return (0);
}

int	pipes_num(t_data *data)
{
	int			p;
	int			i;
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
	free(tmp);
	return (p);
}
