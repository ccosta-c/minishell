/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:12:48 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/09/06 12:41:12 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	print_list(t_data *data)
{
	t_tokens	*tmp;

	tmp = data->top;
	while (tmp != NULL)
	{
		printf("Content-%s\n", tmp->data);
		printf("Length-%i\n", tmp->len);
		printf("Type-%u\n", tmp->type);
		tmp = tmp->next;
	}
}

void	print_lstchar(t_charlst *data)
{
	while (data != NULL)
	{
		printf("%s\n", data->content);
		data = data->next;
	}
}

void	print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		printf("%s", array[i]);
		i++;
		printf("\n");
	}
}
