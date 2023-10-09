/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:46:27 by macastan          #+#    #+#             */
/*   Updated: 2023/10/04 10:46:30 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	redi_out_search(char *str, int i, int red)
{
	int	flag_s;
	int	flag_d;

	flag_s = 0;
	flag_d = 0;
	while(str[i])
	{
		if (str[i] == '\"' && flag_d == 0 && flag_s == 0)
			flag_d = 1;
		else if (str[i] == '\"' && flag_d != 0 && flag_s == 0)
			flag_d = 0;
		else if (str[i] == '\'' && flag_s == 0 && flag_d == 0)
			flag_s = 1;
		else if (str[i] == '\'' && flag_s != 0 && flag_d == 0)
			flag_s = 0;
		else if ((str[i] == '>' || str[i] == '<') && flag_d == 0 && flag_s == 0)
			red++;
		i++;
	}
	if (red == 0)
		return (0);
	return (red);
}

char	*change_str(char *str, t_data *data)
{
	int		i;
	int 	j;
	char	*ret;
	char	*re;

	i = 0;
	j = 1;
	ret = malloc(sizeof(char) * (ft_strlen(str)));
	while(str[j])
	{
		ret[i] = str[j];
		i++;
		j++;
	}
	ret[i] = '\0';
	re = get_exp(ret, 0 , data);
	//free(ret);
	ret = remove_quote(re);
	return (ret);
}

char	*cut_str(char *str, t_data *data, int i, int k)
{
	int 	j;
	char	*ret;
	char	*re;
	char	*r;
	char	*b;

	j = cut_str2(str, k, 0, 0);
	ret = malloc(sizeof(char) * (ft_strlen(str) - j + 2));
	re = malloc(sizeof(char) * (j + 1));
	while (++i < j)
		re[i] = str[i];
	re[i] = '\0';
	i = 0;
	while(str[j])
	{
		ret[i] = str[j];
		i++;
		j++;
	}
	ret[i] = '\0';
	change_data(ret, data, str);
	r = get_exp(re, 0, data);
	b = remove_quote(r);
	return (free(ret), free(re), b);
}

void	change_data(char *str, t_data *data, char *old)
{
	t_tokens	*tmp;

	tmp = data->top;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->data, old) == 0)
		{
			free(tmp->data);
			tmp->data = ft_strdup(str);
			tmp->type = get_type(tmp->data, 0);
			return ;
		}
		tmp = tmp->next;
	}
}

int	cut_str2(char *str, int i, int flag_s, int flag_d)
{
	while (str[i])
	{
		if (str[i] == '\"' && flag_d == 0)
			flag_d = 1;
		else if (str[i] == '\"' && flag_d != 0)
			flag_d = 0;
		else if (str[i] == '\'' && flag_s == 0)
			flag_s = 1;
		else if (str[i] == '\'' && flag_s != 0)
			flag_s = 0;
		else if ((str[i] == '>' || str[i] == '<') && flag_d == 0 && flag_s == 0)
			return (i);
		i++;
	}
	return (i);
}