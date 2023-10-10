/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:34:10 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/10/10 14:33:52 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

//void	pipes_execution(t_data *data)
//{
//	t_tokens *tmp;
//
//}

void	pipes_commands(t_data *data)
{
	t_tokens	*tmp;
	char		**commands;
	int			i;

	i = 0;
	tmp = data->top;
	while (tmp)
	{
		if (i == 0)
			i++;
		if(tmp[i])
		tmp = tmp->next;
	}
}
