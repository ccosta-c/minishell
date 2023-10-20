/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 09:41:15 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/10/18 17:21:50 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char	**list_to_array(t_data *data)
{
	t_tokens	*tmp;
	char		**array;
	int			i;
	char		*tmp_s;

	i = 0;
	tmp = data->top;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	array = malloc(sizeof(char *) * (i + 1));
	tmp = data->top;
	i = 0;
	while (tmp != NULL)
	{
		tmp_s = str_exp_quote(data, tmp->data, count_str_exp(tmp->data, 0, 0));
		array[i] = ft_strdup(tmp_s);
		i++;
		tmp = tmp->next;
		free(tmp_s);
	}
	array[i] = NULL;
	return (array);
}

void	get_envpaths(t_data *data)
{
	char	*tmp;
	char	*tmp2;

	tmp = get_variable("PATH", data->env, count_variables(data->env));
	if (tmp)
	{
		tmp2 = ft_strjoin(tmp, ":");
		free(tmp);
		tmp = ft_strjoin(tmp2, data->pwd);
		free(tmp2);
	}
	else
	{
		tmp = ft_strdup(data->pwd);
	}
	data->paths = ft_split(tmp, ':');
	free(tmp);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	len_of(char *str)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (str[i] != 47 && str[i])
		i++;
	i++;
	j = i;
	while (str[i] != '.' && str[i])
		i++;
	return ((i - j) + 2);
}

int	name_variable(char *str, t_charlst *data)
{
	t_charlst	*tmp;

	tmp = data;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, str, check_name(str)) == 0)
		{
			free(tmp->content);
			tmp->content = ft_strdup(str);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
