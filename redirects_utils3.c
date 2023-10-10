/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:16:30 by macastan          #+#    #+#             */
/*   Updated: 2023/10/10 15:16:32 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char	*cut_str_end2(char *str, t_data *data, int i, char *next_s)
{
	int 	j;
	char	*ret;
	char	*re;

	j = 0;
	ret = malloc(sizeof(char) * (ft_strlen(str)));
	while(str[j + 1] != '\0')
	{
		ret[i] = str[j];
		i++;
		j++;
	}
	ret[i] = '\0';
	change_data(ret, data, str);
	re = cut_str(next_s, data, -1, 0);
	return (free(ret), re);
}