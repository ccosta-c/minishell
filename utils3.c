/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:17:41 by macastan          #+#    #+#             */
/*   Updated: 2023/09/14 14:36:10 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	remove_quote_topdata(t_data *data)
{
	char		*tmp;

	tmp = ft_strdup(data->top->data);
	free(data->top->data);
	data->top->data = remove_quote(tmp, 0, 0, 0);
	free(tmp);
}

void	remove_quote_list(t_data *data)
{
	char		*tmp;
	t_tokens	*tmp_list;

	tmp_list = data->top;
	while (tmp_list != NULL)
	{
		tmp = ft_strdup(tmp_list->data);
		free(tmp_list->data);
		tmp_list->data = remove_quote(tmp, 0, 0, 0);
		free(tmp);
		tmp_list = tmp_list->next;
	}
}

char	*remove_quote(char *data, int i, int j, char q)
{
	char	*new;

	new = malloc(sizeof(char) * (ft_strlen(data) - num_of_quotes(data)) + 1);
	while (data[i])
	{
		if (data[i] == '\'' || data[i] == '\"')
		{
			q = data[i];
			i++;
			while (data[i] != q)
			{
				new[j] = data[i];
				j++;
				i++;
			}
			i++;
		}
		else
		{
			new[j] = data[i];
			j++;
			i++;
		}
	}
	return (new[j] = '\0', new);
}

int	num_of_quotes(char *data)
{
	int		i;
	int		quote;
	char	q;

	i = 0;
	quote = 0;
	while (data[i])
	{
		if (data[i] == '\'' || data[i] == '\"')
		{
			q = data[i];
			quote++;
			i++;
			while (data[i] != q)
				i++;
			quote++;
		}
		i++;
	}
	return (quote);
}

char	*get_variable(char *str, t_charlst *list, int size)
{
	int			i;
	char		*ret;
	t_charlst	*l_tmp;

	i = 0;
	l_tmp = list;
	while (i <= (size - 1))
	{
		if (ft_strncmp(str, l_tmp->content, ft_strlen(str)) == 0)
		{
			ret = cut_env_exp(l_tmp->content, 0, 0);
			return (ret);
		}
		i++;
		l_tmp = l_tmp->next;
	}
	return (0);
}
