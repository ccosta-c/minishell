/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:29:55 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/07/13 11:29:55 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	lexer(t_data *data, char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (1)
	{
		j = i;
		while (input[i] != ' ' || input[i] != '\0')
			i++;
		initialize_tokens(data, i, j, input);
		i++;
		if (input[i] == '\0')
			break;
	}
}
