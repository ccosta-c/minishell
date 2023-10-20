/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_heredoc2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:56:56 by macastan          #+#    #+#             */
/*   Updated: 2023/10/11 17:57:01 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	redi_here_two_nodes(t_data *data, char *str, char *here, char *h)
{
	t_tokens	*tmp;

	tmp = data->top;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->data, str) == 0)
		{
			if (do_here(here, h, data, 0) == -1)
				return (-1);
			if (data->red_n == (ft_atoi(h) + 1))
			{
				open_heredoc(h);
			}
			delete_redirects(&data->top, tmp->next->data, data, 0);
			delete_redirects(&data->top, tmp->data, data, 0);
			return (data->red_flag++, 0);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	do_here(char *hered, char *h, t_data *data, int fd_file)
{
	char	*input;
	char	*tmp;

	tmp = ft_strjoin(".heredoc", h);
	fd_file = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_file < 0)
		return (printf("minishell: '.heredoc' %s.\n", strerror(errno)), -1);
	while (1)
	{
		if (data->fd_out != NULL)
			dup2(0, STDOUT_FILENO);
		signal(SIGQUIT, SIG_IGN);
		input = readline("> ");
		if (!input)
			break ;
		if (ft_strcmp(hered, input) == 0)
			break ;
		write(fd_file, input, ft_strlen(input));
		write(fd_file, "\n", 1);
		free(input);
	}
	close(fd_file);
	open_fd_out(data);
	free(input);
	return (free(tmp), 0);
}

int	redi_here_two_n_cut(t_data *data, char *str, char *here, char *h)
{
	t_tokens	*tmp;

	tmp = data->top;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->data, str) == 0)
		{
			if (do_here(here, h, data, 0) == -1)
				return (-1);
			if (data->red_n == (ft_atoi(h) + 1))
			{
				open_heredoc(h);
			}
			delete_redirects(&data->top, tmp->data, data, 0);
			data->red_flag++;
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	redi_here_one_n_del(t_data *data, char *str, char *here, char *h)
{
	t_tokens	*tmp;

	tmp = data->top;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->data, str) == 0)
		{
			if (do_here(here, h, data, 0) == -1)
				return (-1);
			if (data->red_n == (ft_atoi(h) + 1))
			{
				open_heredoc(h);
			}
			delete_redirects(&data->top, tmp->data, data, 0);
			return (data->red_flag++, 0);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	redi_here_no_node(t_data *data, char *here, char *h)
{
	int			fd_file;
	char		*hd;

	if (do_here(here, h, data, 0) == -1)
		return (-1);
	if (data->red_n == (ft_atoi(h) + 1))
	{
		hd = ft_strjoin(".heredoc", h);
		fd_file = open(hd, O_RDONLY, 0444);
		if (fd_file == -1)
			return (free(hd), -1);
		dup2(fd_file, STDIN_FILENO);
		close(fd_file);
		free(hd);
	}
	data->red_flag++;
	return (0);
}
