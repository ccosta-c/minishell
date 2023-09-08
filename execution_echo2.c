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
	printf("fazer este caralho\n");
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
