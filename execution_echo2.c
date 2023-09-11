/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_echo2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:33:38 by macastan          #+#    #+#             */
/*   Updated: 2023/09/11 15:23:38 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	echo_minus_n(t_data *data)
{
	(void)data;
	printf("fazer este caralho\n");
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
