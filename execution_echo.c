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
		g_exit = 0;
		return ;
	}
	else
	{
		echo_normal(data);
		write (1, "\n", 1);
	}
}

void	simpleq_echo(char *str)
{
	size_t	i;

	i = 1;
	while (str[i] != '\'')
	{
		write (1, &str[i], 1);
		i++;
	}
}

void	doubleq_echo(char *str)
{
	int	i;

	i = 1;
	while (str[i] != '\"')
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			printf("%d", g_exit);
			i = i + 2;
		}
		else if (str[i] == '$' && str[i])
		{
			printf("check se eh explandivel");
			while (str[i] != ' ')
				i++;
		}
		else
		{
			write (1, &str[i], 1);
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
			doubleq_echo(tmp->data);
		else
			echo_normal2(tmp->data);
		write(1, " ", 1);
		tmp = tmp->next;
	}
	free(tmp);
}

void	echo_normal2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			printf("%d", g_exit);
			i = i + 2;
		}
		else if (str[i] == '$' && str[i])
		{
			printf("check se eh explandivel");
			while (str[i] != ' ')
				i++;
		}
		else
		{
			write (1, &str[i], 1);
			i++;
		}
	}
}

void	handle_spaces_echo(char *str)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(str, ' ');
	while (tmp[i])
	{
		doubleq_echo(tmp[i]);
		write(1, " ", 1);
		i++;
	}
	free(tmp);
}
