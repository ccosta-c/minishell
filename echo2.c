/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:17:22 by macastan          #+#    #+#             */
/*   Updated: 2023/09/18 16:49:53 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	echo_minus_n(t_data *data)
{
	t_tokens	*tmp;
	char		*s;

	tmp = data->top->next->next;
	s = remove_quote(tmp->data, 0, 0, 0);
	while (s[0] == '-' && s[1] == 'n' && check_minus_n(s) == 0)
	{
		tmp = tmp->next;
		s = remove_quote(tmp->data, 0, 0, 0);
	}
	while (tmp != NULL)
	{
		if (tmp->type == S_QUOTE)
			simpleq_echo(tmp->data);
		else if (tmp->type == D_QUOTE)
			doubleq_echo(tmp->data, data);
		else
			echo_normal2(tmp->data, data);
		if (tmp->next)
			printf(" ");
		tmp = tmp->next;
	}
	free(tmp);
	free(s);
}

int	handle_specials1(char *str, int i)
{
	int		j;
	int		k;
	char	*tmp;

	if (str[i + 1] == '\'')
		return (i + 2);
	j = i;
	k = 0;
	i++;
	while (str[i] != '\'')
		i++;
	tmp = malloc(sizeof(char) * ((i - j) + 1));
	while (j < i)
	{
		tmp[k] = str[j];
		k++;
		j++;
	}
	tmp[k] = '\0';
	simpleq_echo(tmp);
	return (free(tmp), i);
}

int	handle_specials2(char *str, int i, t_data *data)
{
	int		j;
	int		k;
	char	*tmp;

	if (str[i + 1] == '\"')
		return (i + 2);
	j = i;
	k = 0;
	i++;
	while (str[i] != '\"')
		i++;
	tmp = malloc(sizeof(char) * ((i - j) + 1));
	while (j < i)
	{
		tmp[k] = str[j];
		k++;
		j++;
	}
	tmp[k] = '\0';
	doubleq_echo(tmp, data);
	return (free(tmp), i);
}

int	handle_exp(char *str, int i, t_data *data)
{
	int		j;
	int		k;
	char	*tmp;

	j = i;
	k = 0;
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
	search_print(tmp, data->env, count_variables(data->env));
	return (free(tmp), i);
}

void	search_print(char *str, t_charlist *list, int size)
{
	int			i;
	int			j;
	t_charlist	*l_tmp;

	i = 0;
	j = 0;
	l_tmp = list;
	while (i <= (size - 1))
	{
		if (ft_strncmp(str, l_tmp->content, ft_strlen(str)) == 0)
		{
			while (l_tmp->content[j] != '=')
				j++;
			j++;
			while (l_tmp->content[j])
			{
				printf("%c", l_tmp->content[j]);
				j++;
			}
			break ;
		}
		i++;
		l_tmp = l_tmp->next;
	}
}
