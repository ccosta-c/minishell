/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:20:43 by macastan          #+#    #+#             */
/*   Updated: 2023/09/20 15:20:45 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	redirects(t_data *data)
{
	t_tokens	*tmp;

	tmp = data->top;
	while (tmp != NULL)
	{
		if (tmp->type == R_OUT)
		{
			if (redi_out(data, tmp->data) == -1)
				return (-1);
		}
		else if (tmp->type == R_IN)
			printf("rin");
		else if (tmp->type == RR_IN)
			printf("rrin");
		else if (tmp->type == RR_OUT)
			printf("rrout");
		tmp = tmp->next;
	}
	return (0);
}

int	redi_out(t_data *data, char *str)
{
	char	*tmp;

	if (str[0] == '>' && !str[1])
	{
		if (redi_out_two_nodes(data, str) == -1)
			return (-1);
	}
	else if (str[0] == '>' && str[1])
	{
		tmp = change_str(str);
		if (redi_out_one_node(data, str, tmp) == -1)
			return (free(tmp), -1);
		free(tmp);
	}
	else if (str[0] != '>')
	{
		if (redi_out_search(str, 0, 0) == 0)
			return (0);
		/*if (redi_out_else_nodes2(data, str) == -1)
			return (-1);*/
	}
	return (0);
}

int	redi_out_search(char *str, int i, int red)
{
	int	flag_s;
	int	flag_d;

	flag_s = 0;
	flag_d = 0;
	while(str[i])
	{
		if (str[i] == '\"' && flag_d == 0)
			flag_d = 1;
		if (str[i] == '\"' && flag_d != 0)
			flag_d = 0;
		if (str[i] == '\'' && flag_s == 0)
			flag_s = 1;
		if (str[i] == '\'' && flag_s != 0)
			flag_s = 0;
		if (str[i] == '>' && flag_d == 0 && flag_s == 0)
			red++;
		i++;
	}
	if (red == 0)
		return (0);
	return (1);
}

char	*change_str(char *str)
{
	int		i;
	int 	j;
	char	*ret;
	char	*re;

	i = 0;
	j = 1;
	ret = malloc(sizeof(char) * (ft_strlen(str) - 1));
	while(str[j])
	{
		ret[i] = str[j];
		i++;
		j++;
	}
	re = remove_quote(ret);
	free(ret);
	return (re);
}