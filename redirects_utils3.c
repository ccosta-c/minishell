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
	int		j;
	char	*ret;
	char	*re;

	j = 0;
	ret = malloc(sizeof(char) * (ft_strlen(str)));
	while (str[j + 1] != '\0')
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

char	*cut_str_double(char *str, t_data *data, int i, int k)
{
	int		j;
	char	*ret;
	char	*re;
	char	*r;

	j = cut_str2(str, k, 0, 0);
	ret = malloc(sizeof(char) * (ft_strlen(str) - j + 2));
	re = malloc(sizeof(char) * (j + 1));
	while (++i < j)
		re[i] = str[i];
	re[i] = '\0';
	i = 0;
	while (str[j])
	{
		ret[i] = str[j];
		i++;
		j++;
	}
	ret[i] = '\0';
	change_data(ret, data, str);
	r = remove_quote(re, 0, 0, 0);
	return (free(ret), free(re), r);
}

char	*cut_str_end_double(char *str, t_data *data, int i, char *next_s)
{
	int		j;
	char	*ret;
	char	*re;

	j = 0;
	ret = malloc(sizeof(char) * (ft_strlen(str) - 1));
	while (str[j + 2] != '\0')
	{
		ret[i] = str[j];
		i++;
		j++;
	}
	ret[i] = '\0';
	change_data(ret, data, str);
	re = remove_quote(next_s, 0, 0, 0);
	return (free(ret), re);
}

char	*cut_str_end2_double(char *str, t_data *data, int i, char *next_s)
{
	int		j;
	char	*ret;
	char	*re;

	j = 0;
	ret = malloc(sizeof(char) * (ft_strlen(str) - 1));
	while (str[j + 2] != '\0')
	{
		ret[i] = str[j];
		i++;
		j++;
	}
	ret[i] = '\0';
	change_data(ret, data, str);
	re = cut_str_double(next_s, data, -1, 0);
	return (free(ret), re);
}