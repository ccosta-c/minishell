/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 19:08:10 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/09/28 15:31:13 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *str1, char const *str2)

{
	char	*memall;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str1)
		return (NULL);
	if (!str2 && str1)
		return ((char *)str1);
	len = ft_strlen(str1) + ft_strlen(str2);
	memall = malloc(len + 1 * sizeof(char));
	if (memall == NULL)
		return (NULL);
	while (str1[i])
	{
		memall[i] = str1[i];
		i++;
	}
	while (str2[j])
		memall[i++] = str2[j++];
	memall[i] = '\0';
	return (memall);
}
