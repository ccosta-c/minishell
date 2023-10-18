/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:20:22 by macastan          #+#    #+#             */
/*   Updated: 2023/09/25 15:34:03 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	check_exclamation(char *input, int i)
{
	int	flag;

	flag = 0;
	while (input[i])
	{
		if (input[i] == '\'' && flag == 1)
			flag = 0;
		else if (input[i] == '\'' && flag == 0)
			flag = 1;
		if ((input[i] == '!' && input[i + 1] == '!') && flag != 1)
			return (0);
		i++;
	}
	return (1);
}

int	check_pipes(char *input)
{
	if (input && input[0] == '|' && input[1] != '|')
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		return (g_exit = 2, 0);
	}
	else if (input && input[0] == '|' && input[1] == '|')
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		return (g_exit = 2, 0);
	}
	if (input[ft_strlen(input) - 1] == '|')
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		return (g_exit = 2, 0);
	}
	if (input[ft_strlen(input) - 1] == ';')
	{
		printf("minishell: syntax error near unexpected token `;'\n");
		return (g_exit = 2, 0);
	}
	return (1);
}

char	check_redirect(char *input, int i, char flag)
{
	char	*in;

	in = handle_whitespaces(input);
	while (in[++i])
	{
		if ((in[i] == '\'' || in[i] == '\"' ) && flag == in[i])
			flag = 0;
		else if ((in[i] == '\'' || in[i] == '\"' ) && flag == 0)
			flag = in[i];
		if (in[i] == '<' && (in[i + 1] == '>'
				|| (in[i + 1] == ' ' && in[i + 2] == '>')) && flag == 0)
			return (free(in), '>');
		if (in[i] == '>' && (in[i + 1] == '<'
				|| (in[i + 1] == ' ' && in[i + 2] == '<')) && flag == 0)
			return (free(in), '<');
		if (in[i] == '<' && in[i + 1] == '<' && in[i + 2] == '<' && flag == 0)
			return (free(in), '<');
		if (in[i] == '<' && in[i + 1] == ' ' && in[i + 2] == '<' && flag == 0)
			return (free(in), '<');
		if (in[i] == '>' && in[i + 1] == '>' && in[i + 2] == '>' && flag == 0)
			return (free(in), '>');
		if (in[i] == '>' && in[i + 1] == ' ' && in[i + 2] == '>' && flag == 0)
			return (free(in), '>');
	}
	return (free(in), 0);
}

int	check_quotes(char *input, int i)
{
	char	q;

	q = 0;
	while (input[i] && q == 0)
	{
		if (ft_strrchr("\"\'", input[i]))
			q = input[i];
		i++;
	}
	while (input[i] && q != 0)
	{
		if (input[i] == q)
			q = 0;
		i++;
	}
	if (input[i])
		return (check_quotes(input, i));
	else if (q == 0)
		return (1);
	else
		return (0);
}

int	search_red(t_data *data)
{
	t_tokens	*tmp;

	tmp = data->top;
	while (tmp != NULL)
	{
		if (tmp->type == RR_IN || tmp->type == RR_OUT
			|| tmp->type == R_IN || tmp->type == R_OUT)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
