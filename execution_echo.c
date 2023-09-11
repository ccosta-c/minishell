/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:58:50 by macastan          #+#    #+#             */
/*   Updated: 2023/09/05 11:58:54 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	execution_echo(t_data *data)
{
	if (!data->top->next)
	{
		printf("\n");
		g_exit = 0;
		return ;
	}
	if (ft_strncmp("-n", data->top->next->data, data->top->next->len) == 0)
	{
		if (!data->top->next->next)
		{
			printf("\n");
			g_exit = 0;
			return ;
		}
		echo_minus_n(data);
	}
	else
	{
		echo_normal(data);
		printf("\n");
	}
	g_exit = 0;
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
		else if (str[i] == '$' && str[i])
		{
			i = handle_exp(str, i, data);
		}
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
			i = handle_specials1(str, i) + 1;
		else if (str[i] == '\"')
			i = handle_specials2(str, i, data) + 1;
		else if (str[i] == '$' && str[i + 1] == '?')
		{
			printf("%i", g_exit);
			i = i + 2;
		}
		else if (str[i] == '$' && str[i])
		{
			i = handle_exp(str, i, data);
		}
		else
		{
			printf("%c", str[i]);
			i++;
		}
	}
}

int	handle_exp(char *str, int i, t_data *data)
{
	int j;
	int k;
	char *tmp;

	j = i;
	k = 0;
	i++;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '$' || str[i] == '\"')
			break ;
		i++;
	}
	tmp = malloc(sizeof(char) * ((i - j)));
	j++;
	while (j < i)
	{
		tmp[k] = str[j];
		k++;
		j++;
	}
	tmp[k] = '\0';
	search_print(tmp, data->export, count_variables(data->export));
	return (free(tmp), i);
}

void	search_print(char *str, t_charlist *list, int size)
{
	int			i;
	int			j;
	t_charlist	*tmp;

	i = 0;
	j = 0;
	tmp = list;
	while (i < (size - 1))
	{
		if (ft_strncmp(str, tmp->content, ft_strlen(str)) == 0)
		{
			while (tmp->content[j] != '=')
				j++;
			j++;
			while (tmp->content[j])
			{
				printf("%c", tmp->content[j]);
				j++;
			}
		}
		i++;
		tmp = tmp->next;
	}
	free(tmp);
}

int	handle_specials1(char *str, int i)
{
	int	j;
	int	k;
	char	*tmp;

	j = i;
	k = 0;
	i++;
	while (str[i] != '\'')
		i++;
	tmp = malloc(sizeof(char) * ((i - j) + 1));
	while (j < (i + 1))
	{
		tmp[k] = str[j];
		k++;
		j++;
	}
	tmp[k] = '\0';
	simpleq_echo(tmp);
	return (free(tmp), i);
}

int	handle_specials2(char *str, int i, t_data *data)
{
	int	j;
	int	k;
	char	*tmp;

	j = i;
	k = 0;
	i++;
	while (str[i] != '\"')
		i++;
	tmp = malloc(sizeof(char) * ((i - j) + 1));
	while (j < (i + 1))
	{
		tmp[k] = str[j];
		k++;
		j++;
	}
	tmp[k] = '\0';
	doubleq_echo(tmp, data);
	return (free(tmp), i);
}