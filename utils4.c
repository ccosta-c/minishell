/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:04:37 by macastan          #+#    #+#             */
/*   Updated: 2023/09/18 17:04:39 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

//str = strign que tem o $
//i = a posicao do $ na string
char	*get_exp(char *str, int i, t_data *data)
{
	char	*tmp;
	char	*ret;

	tmp = get_tmp(str, i, 0, i);
	ret = search_ex(tmp, data->env, count_variables(data->env), 0);
	return (free(tmp), ret);
}

char	*get_tmp(char *str, int j, int k, int i)
{
	char	*tmp;

	i++;
	while (str[i])
	{
		if (ft_stop_exp(str[i]) == 0)
			break ;
		i++;
	}
	tmp = malloc(sizeof(char) * ((i - j)));
	j++;
	while (j < i)
	{
		tmp[k] = str[j];
		k++;
		j++;
	}
	tmp[k] = '\0';
	return (tmp);
}

char	*search_ex(char *str, t_charlist *list, int size, int i)
{
	int			j;
	int			k;
	char		*fim;
	t_charlist	*l_tmp;

	j = 0;
	k = 0;
	l_tmp = list;
	fim = NULL;
	while (i <= (size - 1))
	{
		if (ft_strncmp(str, l_tmp->content, ft_strlen(str)) == 0)
		{
			while (l_tmp->content[j] != '=')
				j++;
			fim = malloc(sizeof (char) * (ft_strlen(l_tmp->content) - j));
			j++;
			while (l_tmp->content[j])
			{
				fim[k] = l_tmp->content[j];
				j++;
				k++;
			}
			fim[k] = '\0';
			break ;
		}
		i++;
		l_tmp = l_tmp->next;
	}
	return (fim);
}
