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
	ft_cleartokens(&data->top);
	ft_clearcharlist(&data->env);
	ft_clearcharlist(&data->export);
	if (data->og_command != NULL)
		free(data->og_command);
	free(data->prompt);
	free(data->pwd);
	free(data->old_pwd);
	free(data->home);
	frees2(data);
	rl_clear_history();
}

void	frees2(t_data *data)
{
	int		i;
	char	*h;
	char	*hd;

	i = 0;
	if (data->fd_out != NULL)
		free(data->fd_out);
	while (data->red_flag < 0)
	{
		h = ft_itoa(i);
		hd = ft_strjoin(".heredoc", h);
		unlink(hd);
		data->red_flag--;
		free(h);
		free(hd);
		i++;
	}
	if (data->heredoc != NULL)
		free(data->heredoc);
	if (data->tmp_r != NULL)
		free(data->tmp_r);
	if (data->h != NULL)
		free(data->h);
}

int	open_heredoc(char *h)
{
	char		*hd;
	int			fd_file;

	hd = ft_strjoin(".heredoc", h);
	fd_file = open(hd, O_RDONLY, 0444);
	if (fd_file == -1)
		return (free(hd), -1);
	dup2(fd_file, STDIN_FILENO);
	close(fd_file);
	free(hd);
	return (0);
}

void	open_fd_out(t_data *data)
{
	int	fd_file;

	if (data->fd_out != NULL)
	{
		fd_file = open(data->fd_out, O_WRONLY | data->o_flag_out, 0777);
		dup2(fd_file, STDOUT_FILENO);
		close(fd_file);
	}
}

void	handler_sigint(int sig)
{
	handler_sigint2(sig, 0);
}
