/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_echo2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:33:38 by macastan          #+#    #+#             */
/*   Updated: 2023/09/05 12:33:40 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	echo_minus_n(t_data *data)
{
	t_tokens	*tmp;

	tmp = data->top->next;
	while (tmp != NULL)
	{
		if (ft_strncmp("-n", tmp->data, tmp->len) == 0)
			continue ;
		else if (tmp->type == S_QUOTE)
			simple_echo(tmp->data);
		else if (tmp->type == D_QUOTE)
			double_echo(tmp->data);
		else
		{
			if (tmp->data[0] == '$' && tmp->data[1] == '?')
			{
				printf("%d\n", g_exit);
				g_exit = 0;
				return ;
			}
			else if (tmp->data[0] == '$' && tmp->data[1])
				printf("check se eh explandivel");
			else
				simple_echo(tmp->data);
		}
		write(1, " ", 1);
		tmp = tmp->next;
	}
	free(tmp);
}

char	*remove_quote(char *data)
{
	int	i;
	int	j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(data) - num_of_quotes(data)));
	while (data[i])
	{
		if (data[i] == '\'' || data[i] == '\"')
		{
			i++;
		}
		new[j] = data[i];
		j++;
		i++;
	}
	new[j] = '\0';
	return (new);
}

int	num_of_quotes(char *data)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (data[i])
	{
		if (data[i] == '\'' || data[i] == '\"')
			quote++;
		i++;
	}
	return (quote);
}