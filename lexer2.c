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

enum e_type	get_type(char *str)
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
	if (get_type2(str, 0) != GENERIC)
		return (get_type2(str, 0));
	return (GENERIC);
}

enum e_type	get_type2(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '|')
			return (PIPE);
		else if (str[i] == '<' && str[i + 1] != '<'
			&& i == cut_str2(str, 0, 0, 0))
			return (R_IN);
		else if (str[i] == '>' && str[i + 1] != '>'
			&& i == cut_str2(str, 0, 0, 0))
			return (R_OUT);
		else if (str[i] == '<' && str[i + 1] == '<'
			&& i == cut_str2(str, 0, 0, 0))
			return (RR_IN);
		else if (str[i] == '>' && str[i + 1] == '>'
			&& i == cut_str2(str, 0, 0, 0))
			return (RR_OUT);
		i++;
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
	t_tokens	*tmp;

	p = 0;
	tmp = data->top;
	while (tmp != NULL)
	{
		p = p + pipes_num2(tmp->data, 0, 0);
		tmp = tmp->next;
	}
	free(tmp);
	return (p);
}

int	pipes_num2(char *str, int i, int p)
{
	int	flag_d;
	int	flag_s;

	flag_d = 0;
	flag_s = 0;
	while (str[i])
	{
		if (str[i] == '\"' && flag_d == 0 && flag_s == 0)
			flag_d = 1;
		else if (str[i] == '\"' && flag_d != 0 && flag_s == 0)
			flag_d = 0;
		else if (str[i] == '\'' && flag_s == 0 && flag_d == 0)
			flag_s = 1;
		else if (str[i] == '\'' && flag_s != 0 && flag_d == 0)
			flag_s = 0;
		else if (str[i] == '|' && flag_d == 0 && flag_s == 0)
			p++;
		i++;
	}
	return (p);
}
