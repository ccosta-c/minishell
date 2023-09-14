/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:17:41 by macastan          #+#    #+#             */
/*   Updated: 2023/09/14 12:17:43 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	remove_quote_list(t_data *data)
{
	char	*tmp;

	while (data->top != NULL)
	{
		tmp = data->top->data;
		free(data->top->data);
		data->top->data = remove_quote(tmp);
		free(tmp);
		data->top = data->top->next;
	}
}

char	*remove_quote(char *data)
{
	int		i;
	int		j;
	char	q;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(data) - num_of_quotes(data)) + 1);
	while (data[i])
	{
		if (data[i] == '\'' || data[i] == '\"')
		{
			q = data[i];
			i++;
			while (data[i] != q)
			{
				new[j] = data[i];
				j++;
				i++;
			}
			i++;
		}
		else
		{
			new[j] = data[i];
			j++;
			i++;
		}
	}
	new[j] = '\0';
	return (new);
}

int	num_of_quotes(char *data)
{
	int		i;
	int		quote;
	char	q;

	i = 0;
	quote = 0;
	while (data[i])
	{
		if (data[i] == '\'' || data[i] == '\"')
		{
			q = data[i];
			quote++;
			i++;
			while (data[i] != q)
				i++;
			quote++;
		}
		i++;
	}
	return (quote);
}