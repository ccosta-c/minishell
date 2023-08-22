/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:12:48 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/07/24 15:21:17 by ccosta-c         ###   ########.fr       */
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
		printf("Type-%s\n", tmp->type);
		tmp = tmp->next;
	}
}
