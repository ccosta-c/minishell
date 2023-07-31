/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:58:13 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/07/31 11:55:48 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	handle_signals(void)
{
	struct sigaction	si;

	si.sa_handler = &handler;
	sigemptyset(&si.sa_mask);
	si.sa_flags = 0;
	sigaction(SIGINT, &si, NULL);
}

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit = 130;
	}
}

