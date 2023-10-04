/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:21:16 by macastan          #+#    #+#             */
/*   Updated: 2023/10/04 14:21:17 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char	*cut_str_else(char *str, t_data *data, int j, int i)
{
	int		k;
	int		r;
	char	*ret;
	char	*re;

	r = j + 1;
	k = cut_str2(str, j, 0, 0);
	re = malloc(sizeof(char) * (k - j));
	while (++i < (k - j))
		re[i] = str[r++];
	re[i] = '\0';
	cut_str_else2(str, data, j, k);
	ret = remove_quote(re);
	return (free(re), ret);
}

void	cut_str_else2(char *str, t_data *data, int j, int k)
{
	char	*ret;
	int		i;
	int		r;

	ret = malloc(sizeof(char) * (ft_strlen(str) - (k - j) + 1));
	i = 0;
	r = 0;
	while(i < j)
	{
		ret[i] = str[r];
		i++;
		r++;
	}
	r = k;
	while(str[r])
	{
		ret[i] = str[r];
		i++;
		r++;
	}
	ret[i] = '\0';
	change_data(ret, data, str);
	free(ret);
}

char	*cut_str_1(char *str, t_data *data, int i, int k)
{
	int 	j;
	char	*ret;
	char	*re;
	char	*r;

	j = cut_str2(str, 1, 0, 0);
	printf("%i\n", j);
	ret = malloc(sizeof(char) * (ft_strlen(str) - j + 2));
	re = malloc(sizeof(char) * (j));
	while (++i < (j - 1))
	{
		re[i] = str[k];
		k++;
	}
	re[i] = '\0';
	printf("%s\n", re);
	i = 0;
	while(str[j])
	{
		ret[i] = str[j];
		i++;
		j++;
	}
	ret[i] = '\0';
	printf("%s\n", ret);
	change_data(ret, data, str);
	r = remove_quote(re);
	return (free(ret), free(re), r);
}