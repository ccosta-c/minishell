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
	while (tmp)
	{
		if (tmp->type == R_OUT)
		{
			if (tmp->next)
			{
				if (redi_out(data, tmp->data, tmp->next->data) == -1)
					return (-1);
				return (redirects(data));
			}
			else
			{
				if (redi_out(data, tmp->data, "maluca") == -1)
					return (-1);
				return (0);
			}
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

int	redi_out(t_data *data, char *str, char *next_s)
{
	char	*tmp;

	if (str[0] == '>' && !str[1] && redi_out_search(next_s, 0, 0) == 0)
	{
		if (redi_out_two_nodes(data, str) == -1)
			return (-1);
	}
	else if (str[0] == '>' && !str[1] && redi_out_search(next_s, 0, 0) != 0)
	{
		tmp = cut_str(next_s, data);
		if (redi_out_two_nodes_cut(data, str, tmp) == -1)
			return (free(tmp), -1);
		free(tmp);
	}
	else if (str[0] == '>' && str[1] && redi_out_search(next_s, 0, 0) == 0)
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
		if ((str[i] == '>' || str[i] == '<') && flag_d == 0 && flag_s == 0)
			red++;
		i++;
	}
	if (red == 0)
		return (0);
	return (red);
}

char	*change_str(char *str)
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
	re = remove_quote(ret);
	free(ret);
	return (re);
}

char	*cut_str(char *str, t_data *data)
{
	int		i;
	int 	j;
	char	*ret;
	char	*re;

	i = -1;
	j = cut_str2(str, 0, 0, 0);
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
	return (free(ret), re);
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
		if ((str[i] == '>' || str[i] == '<') && flag_d == 0 && flag_s == 0)
			return (i);
		i++;
	}
	return (i);
}