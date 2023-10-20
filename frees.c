/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:13:46 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/10/18 16:05:14 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	frees(t_data *data)
{
	int		i;
	char	*h;

	i = 0;
	ft_cleartokens(&data->top);
	ft_clearcharlist(&data->env);
	ft_clearcharlist(&data->export);
	if (data->og_command != NULL)
		free(data->og_command);
	while (data->red_flag < 0)
	{
		h = ft_itoa(i);
		unlink(ft_strjoin(".heredoc", h));
		data->red_flag--;
		i++;
	}
	free(data->prompt);
	free(data->pwd);
	free(data->old_pwd);
	free(data->home);
	rl_clear_history();
}
