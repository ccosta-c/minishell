/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:16:30 by macastan          #+#    #+#             */
/*   Updated: 2023/10/10 15:16:32 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char	*cut_str_else_double(char *str, t_data *data, int j, int i)
{
	int		k;
	int		r;
	char	*ret;
	char	*re;

	r = j + 2;
	k = cut_str2(str, (j + 2), 0, 0);
	re = malloc(sizeof(char) * (k - j));
	while (i < (k - j - 2))
	{
		re[i] = str[r];
		i++;
		r++;
	}
	re[i] = '\0';
	cut_str_else2_double(str, data, j, k);
	ret = remove_quote(re, 0, 0, 0);
	return (free(re), ret);
}

void	cut_str_else2_double(char *str, t_data *data, int j, int k)
{
	char	*ret;
	int		i;
	int		r;

	ret = malloc(sizeof(char) * (ft_strlen(str) - (k - j) + 1));
	i = 0;
	r = 0;
	while (i < j)
	{
		ret[i] = str[r];
		i++;
		r++;
	}
	r = k;
	while (str[r])
	{
		ret[i] = str[r];
		i++;
		r++;
	}
	ret[i] = '\0';
	change_data(ret, data, str);
	free(ret);
}

char	*cut_str_1_double(char *str, t_data *data, int i, int k)
{
	int		j;
	char	*ret;
	char	*re;
	char	*r;

	j = cut_str2(str, 2, 0, 0);
	ret = malloc(sizeof(char) * (ft_strlen(str) - j + 1));
	re = malloc(sizeof(char) * (j - 1));
	while (++i < (j - 1))
	{
		re[i] = str[k];
		k++;
	}
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