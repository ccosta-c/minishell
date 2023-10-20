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
	if (data->fd_out != NULL)
		free(data->fd_out);
	while (data->red_flag < 0)
	{
		h = ft_itoa(i);
		unlink(ft_strjoin(".heredoc", h));
		data->red_flag--;
		free(h);
		i++;
	}
	free(data->prompt);
	free(data->pwd);
	free(data->old_pwd);
	free(data->home);
	rl_clear_history();
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
