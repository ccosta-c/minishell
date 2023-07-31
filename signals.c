/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:58:13 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/07/27 15:03:23 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	handle_signals(void)
{
	struct sigaction	si;

	si.sa_handler = &handler;
	sigemptyset(&si.sa_mask);
	si.sa_flags = 0;
}

void	handler(int sig)
{
	if (sig == SIGINT)
		exit (0);
}
