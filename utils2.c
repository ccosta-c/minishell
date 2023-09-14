/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:22:38 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/09/11 15:22:38 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	check_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

/*char	*remove_quote(char *data)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(data) - num_of_quotes(data)) + 1);
	while (data[i])
	{
		if (data[i] == '\'' || data[i] == '\"')
		{
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
}*/

int	ft_stop_exp(char c)
{
	if (c == ' '|| (c >= 34 && c <= 37))
		return (0);
	if (c == 58 || (c >= 40 && c <= 47))
		return (0);
	if (c == 61 || c == 63 || c == 64)
		return (0);
	if (c >= 91 && c <= 94)
		return (0);
	if (c == 123 || c == 125 || c == 126)
		return (0);
	return (1);
}
