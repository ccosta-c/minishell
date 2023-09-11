/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 09:41:15 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/09/11 14:43:55 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char	**list_to_array(t_data *data)
{
	t_tokens	*tmp;
	char		**array;
	int			i;

	i = 0;
	tmp = data->top;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	free(tmp);
	array = malloc(sizeof(char *) * (i + 1));
	tmp = data->top;
	i = 0;
	while (tmp != NULL)
	{
		array[i] = malloc(sizeof(char) * (tmp->len + 1));
		array[i] = tmp->data;
		i++;
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (free(tmp), array);
}

void	get_envpaths(t_data *data)
{
	char	*tmp;

	tmp = getenv("PATH");
	data->paths = ft_split(tmp, ':');
}

void	free_array(char **array, int y)
{
	int	i;

	i = 0;
	while (i < y)
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

int	name_variable(char *str, t_charlist *data)
{
	t_charlist	*tmp;

	tmp = data;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, str, check_name(str)) == 0)
		{
			free(tmp->content);
			tmp->content = strdup(str);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}
