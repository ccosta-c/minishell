/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:17:13 by macastan          #+#    #+#             */
/*   Updated: 2023/09/13 12:17:17 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	execution_echo(t_data *data)
{
	char	*s;

	if (!data->top->next)
		return (printf("\n"), g_exit = 0, 0);
	s = remove_quote(data->top->next->data, 0, 0, 0);
	if (minus(s) == 2)
		return (free(s), 2);
	if (minus(s) == 1)
	{
		if (check_minus_n(s) == 0)
		{
			if (!data->top->next->next)
				return (free(s), g_exit = 0, 0);
			else
			{
				echo_minus_n(data);
				return (free(s), g_exit = 0, 0);
			}
		}
	}
	echo_normal(data);
	printf("\n");
	return (free(s), g_exit = 0, 0);
}

void	simpleq_echo(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			i++;
		else
		{
			printf("%c", str[i]);
			i++;
		}
	}
}

void	doubleq_echo(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			i++;
		else if (str[i] == '$' && str[i + 1] == '?')
		{
			printf("%i", g_exit);
			i = i + 2;
		}
		else if (str[i] == '$' && str[i + 1])
			i = handle_exp(str, i, data);
		else
		{
			printf("%c", str[i]);
			i++;
		}
	}
}

void	echo_normal(t_data *data)
{
	t_tokens	*tmp;

	tmp = data->top->next;
	while (tmp != NULL)
	{
		if (tmp->type == S_QUOTE)
			simpleq_echo(tmp->data);
		else if (tmp->type == D_QUOTE)
			doubleq_echo(tmp->data, data);
		else
			echo_normal2(tmp->data, data);
		if (tmp->next)
			printf(" ");
		tmp = tmp->next;
	}
	free(tmp);
}

void	echo_normal2(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			i = handle_specials1(str, i);
		else if (str[i] == '\"')
			i = handle_specials2(str, i, data);
		else if (str[i] == '$' && str[i + 1] == '?')
		{
			printf("%i", g_exit);
			i = i + 2;
		}
		else if (str[i] == '$' && (str[i + 1] == '\'' || str[i + 1] == '\"'))
			i = i + 2;
		else if (str[i] == '$' && str[i + 1])
			i = handle_exp(str, i, data);
		else
		{
			printf("%c", str[i]);
			i++;
		}
	}
}
