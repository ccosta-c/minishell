/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:29:55 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/10/12 11:34:27 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	lexer(t_data *data, char *input)
{
	char	*str;

	if (!input)
		return (-1);
	data->og_command = ft_strdup(input);
	str = ft_strtrim(input, " ");
	if (check_first(str) == -1)
		return (free (data->og_command), data->og_command = NULL, free(str), 0);
	lexer_continuation(data, str, 0, 0);
	free(str);
	if (check_second(data) == -1)
		return (free (data->og_command), data->og_command = NULL, 0);
	execution(data);
	free (data->og_command);
	data->og_command = NULL;
	return (0);
}

void	lexer_continuation(t_data *data, char *str, int i, int j)
{
	while (1)
	{
		while (str[i] == ' ')
			i++;
		j = i;
		while (str[i] != ' ' && str[i] != '\0')
		{
			if (str[i] == '\'' || str[i] == '\"')
				i = list_quote(str, i);
			i++;
		}
		add_to_list(&data->top, initialize_tokens(i, j, str));
		if (str[i++] == '\0')
			break ;
	}
	data->lst_size = get_size_lst(data);
}

int	check_first(char *in)
{
	char	c;

	if (!in || ck_whitespaces(in) == -1)
		return (g_exit = 0, -1);
	c = check_redirect(in, -1, 0);
	if (check_quotes(in, 0) == 0)
	{
		write(2, "minishell: unclosed quotes\n", 27);
		return (g_exit = 2, -1);
	}
	if (check_pipes(in) == 0 || check_not_exc(in) == -1)
		return (-1);
	if (c != 0 || in[ft_strlen(in) - 1] == '<' || in[ft_strlen(in) - 1] == '>')
	{
		write(2, "minishell: syntax error near unexpected token ", 46);
		write(2, &c, 1);
		write(2, "\n", 1);
		return (g_exit = 2, -1);
	}
	if (check_exclamation(in, 0) == 0)
	{
		write(2, "minishell: don't handle double exclamations points\n", 51);
		return (g_exit = 2, -1);
	}
	return (0);
}

int	check_second(t_data *data)
{
	int			i;
	t_tokens	*tmp;

	tmp = data->top;
	while (tmp != NULL)
	{
		i = 0;
		if (tmp->type == GENERIC)
		{
			while (tmp->data[i])
			{
				if (tmp->data[i] == '(' || tmp->data[i] == ')')
				{
					write(2, "minishell:", 10);
					write(2, " syntax error near unexpected token\n", 36);
					return (g_exit = 2, -1);
				}
				i++;
			}
		}
		tmp = tmp->next;
	}
	return (free(tmp), 0);
}

int	list_quote(char *input, int i)
{
	if (input[i] == '\'')
	{
		i++;
		while (input[i] != '\'')
		{
			i++;
		}
		return (i);
	}
	else if (input[i] == '\"')
	{
		i++;
		while (input[i] != '\"')
		{
			i++;
		}
		return (i);
	}
	return (i);
}
