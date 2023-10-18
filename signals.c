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
		rl_on_new_line();
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_replace_line("", 0);
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

void	get_exit_status_arr(t_data *data, int *pids)
{
	int		i;
	pid_t	pid;
	int		status;

	i = 0;
	status = 0;
	while (i < (data->pipes_nums + 1))
	{
		signal(SIGINT, &handler_sigint);
		pid = waitpid(pids[i], &status, 0);
		if (pid < 0)
			continue ;
		if (WIFEXITED(status))
			g_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit = 128 + WTERMSIG(status);
		i++;
	}
}

void	get_exit_status_one(int pids)
{
	pid_t	pid;
	int		status;

	status = 0;
	signal(SIGINT, &handler_sigint);
	pid = waitpid(pids, &status, 0);
	if (pid < 0)
		return ;
	if (WIFEXITED(status))
		g_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit = 128 + WTERMSIG(status);
}