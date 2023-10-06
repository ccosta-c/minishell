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
//i = comeca em 0 e procura a posicao do $ na string
char	*get_exp(char *str, int i, t_data *data)
{
	char	*tmp;
	char	*ret;
	int		total;

	while(str[i] != '$' && str[i])
		i++;
	if (str[i] == '\0')
		return (0);
	tmp = get_tmp(str, i, 0, i);
	ret = search_ex(tmp, data->env, count_variables(data->env), 0);
	if (ret)
	{
		total = ft_strlen(tmp) + 1;
		free(tmp);
		tmp = join_exp_str(ret, str, total, 0);
	}
	else
	{
		total = ft_strlen(tmp) + 1;
		free(tmp);
		tmp = cut_exp_str(str, total);
	}
	if (ft_strchr(tmp, '$'))
	{
		free(ret);
		ret = get_exp(tmp, 0, data);
		return (free(tmp), ret);
	}
	return (free(ret), tmp);
}

char	*join_exp_str(char *exp, char *str, int total, int j)
{
	char	*ret;
	int		i;
	int		k;

	ret = malloc(sizeof (char) * ((ft_strlen(str)) + (ft_strlen(exp)) - total));
	i = 0;
	while (str[i] != '$' && str[i])
	{
		ret[i] = str[i];
		i++;
	}
	k = i + total;
	while (exp[j])
	{
		ret[i] = exp[j];
		i++;
		j++;
	}
	while (str[k])
	{
		ret[i] = str[k];
		i++;
		k++;
	}
	return (ret[i] = '\0', ret);
}

char	*cut_exp_str(char *str, int total)
{
	char	*ret;
	int		i;
	int		k;

	ret = malloc(sizeof (char) * ((ft_strlen(str)) - total + 1));
	i = 0;
	while (str[i] != '$' && str[i])
	{
		ret[i] = str[i];
		i++;
	}
	k = i + total;
	while (str[k])
	{
		ret[i] = str[k];
		i++;
		k++;
	}
	return (ret[i] = '\0', ret);
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

int	check_minus_n(char *s)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (s[i] != 'n')
			return (-1);
		i++;
	}
	return (0);
}