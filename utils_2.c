/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 09:41:15 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/08/30 10:40:15 by ccosta-c         ###   ########.fr       */
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
	free(tmp);
	return (array);
}
