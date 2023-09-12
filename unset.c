/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:22:07 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/09/11 15:37:29 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

//void	unset_builtin(t_data *data)
//{
//	t_tokens	*tmp;
//	t_charlist	*actualone;
//	t_charlist	*behind;
//
//	tmp = data->top->next;
//	actualone = data->env;
//	behind = data->env;
//
//	while (tmp != NULL)
//	{
//		if (name_variable(tmp->data, data->export) == 1)
//		{
//			name_variable(tmp->data, data->env);
//			continue ;
//		}
//		else
//		{
//			add_to_charlist(&data->export, tmp->data);
//			add_to_charlist(&data->env, tmp->data);
//			tmp = tmp->next;
//		}
//	}
//}
