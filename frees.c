/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:13:46 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/09/20 15:46:29 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	frees(t_data *data)
{
	ft_cleartokens(&data->top);
	free(data->prompt);
	free(data->pwd);
	free(data->old_pwd);
	free(data->home);
	if (data->paths != NULL)
		free_array(data->paths);
//	if (data->arg != NULL)
//		free_array(data->arg);
	rl_clear_history();
}
