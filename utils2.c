/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:22:38 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/09/14 14:52:20 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	check_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	return (i);
}

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

int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	if (ft_strlen(str1) != ft_strlen(str2))
		return (-1);
	while (str1[i] != '\0' || str2[i] != '\0')
	{
		if (str1[i] > str2[i])
		{
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		}
		if (str1[i] < str2[i])
		{
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		}
		i++;
	}
	return (0);
}