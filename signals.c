/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:58:13 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/08/01 15:05:59 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

//NAO DA HANDLE QUANDO ESTA ALGO EM ESPERA NO TERMINAL!!!!!!!!!!!!!

void	handle_signals(void)
{
	struct sigaction	si;

	si.sa_flags = SA_RESTART;
	sigemptyset(&si.sa_mask);
	si.sa_handler = &handler;
	sigaddset(&si.sa_mask, SIGINT);
	sigaction(SIGINT, &si, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	handler_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	signal_default(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

void	get_exit_status(t_data *data)
{
	int		i;
	pid_t	pid;
	int		status;

	i = 0;
	status = 0;
	while (i < (data->pipes_nums + 1))
	{
		signal(SIGINT, &handler_sigint);
		pid = waitpid(data->pid[i], &status, 0);
		if (pid < 0)
			continue ;
		if (WIFEXITED(status))
			g_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit = 128 + WTERMSIG(status);
		i++;
	}
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
