/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:20:22 by macastan          #+#    #+#             */
/*   Updated: 2023/08/28 11:37:25 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	check_first(char *input)
{
	if (check_quotes(input, 0) == 0)
	{
		printf("minishell: unclosed quotes\n");
		g_exit = 2;
		return (-1);
	}
	if (check_pipes(input) == 0)
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		g_exit = 2;
		return (-1);
	}
	if (check_redirect(input, 0) == 0)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		g_exit = 2;
		return (-1);
	}
	return (0);
}

int	check_pipes(char *input)
{
	if (input && input[0] == '|' && input[1] != '|')
		return (0);
	else if (input && input[0] == '|' && input[1] == '|')
		return (0);
	if (input[ft_strlen(input) - 1] == '|')
		return (0);
	return (1);
}

int	check_redirect(char *input, int i)
{
	while (input[i])
	{
		if (input[i] == '<' && (input[i + 1] == '>' || (input[i + 1] == ' ' && input[i + 2] == '>')))
				return (0);
		if (input[i] == '>' && (input[i + 1] == '<' || (input[i + 1] == ' ' && input[i + 2] == '<')))
				return (0);
		if (input[i] == '<' && input[i + 1] == '<' && input[i + 2] == '<')
			return (0);
		if (input[i] == '<' && input[i + 1] == ' ' && input[i + 2] == '<')
			return (0);
		if (input[i] == '>' && input[i + 1] == '>' && input[i + 2] == '>')
			return (0);
		if (input[i] == '<' && input[i + 1] == ' ' && input[i + 2] == '<')
			return (0);
		i++;
	}
	if (input[ft_strlen(input) - 1] == '<')
		return (0);
	if (input[ft_strlen(input) - 1] == '>')
		return (0);
	return (1);
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
		if (ft_strchr(tmp->data, '<') || ft_strchr(tmp->data, '>'))
			return (1);
		tmp = tmp->next;
	}
	free(tmp);
	return (0);
}
