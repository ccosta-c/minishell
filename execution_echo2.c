/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_echo2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:33:38 by macastan          #+#    #+#             */
/*   Updated: 2023/09/12 14:02:04 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	echo_minus_n(t_data *data)
{
	t_tokens	*tmp;

	tmp = data->top->next->next;
	while (ft_strncmp("-n", remove_quote(tmp->data), ft_strlen(remove_quote(tmp->data))) == 0)
		tmp = tmp->next;
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
}

int	handle_specials1(char *str, int i)
{
	int	j;
	int	k;
	char	*tmp;

	j = i;
	k = 0;
	i++;
	while (str[i] != '\'')
		i++;
	tmp = malloc(sizeof(char) * ((i - j) + 1));
	while (j < (i + 1))
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
	int	j;
	int	k;
	char	*tmp;

	j = i;
	k = 0;
	i++;
	while (str[i] != '\"')
		i++;
	tmp = malloc(sizeof(char) * ((i - j) + 1));
	while (j < (i + 1))
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
	int j;
	int k;
	char *tmp;

	j = i;
	k = 0;
	i++;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '$' || str[i] == '\"' || str[i] == '-')
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
	search_print(tmp, data->export, count_variables(data->export));
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
	while (i < (size - 1))
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
