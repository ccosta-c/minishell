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

int	redi_here_two_nodes(t_data *data, char *str, char *here)
{
	t_tokens	*tmp;
	int			fd_file;

	tmp = data->top;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->data, str) == 0)
		{
			fd_file = do_here(here);
			if (fd_file == -1)
				return (-1);
			dup2(fd_file, STDIN_FILENO);
			close(fd_file);
			delete_redirects(&data->top, tmp->next->data, data, 0);
			delete_redirects(&data->top, tmp->data, data, 0);
			data->red_flag++;
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	do_here(char *hered)
{
	char	*input;
	int		fd_file;

	fd_file = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_file < 0)
		return (printf("minishell: '.heredoc' %s.\n", strerror(errno)), -1);
	while (1)
	{
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
	fd_file = open(".heredoc", O_RDONLY, 0444);
	if (input)
		free(input);
	return (fd_file);
}

int	redi_here_two_nodes_cut(t_data *data, char *str, char *here)
{
	t_tokens	*tmp;
	int			fd_file;

	tmp = data->top;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->data, str) == 0)
		{
			fd_file = do_here(here);
			if (fd_file == -1)
				return (-1);
			dup2(fd_file, STDIN_FILENO);
			close(fd_file);
			delete_redirects(&data->top, tmp->data, data, 0);
			data->red_flag++;
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	redi_here_one_node_del(t_data *data, char *str, char *here)
{
	t_tokens	*tmp;
	int			fd_file;

	tmp = data->top;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->data, str) == 0)
		{
			fd_file = do_here(here);
			if (fd_file == -1)
				return (-1);
			dup2(fd_file, STDIN_FILENO);
			close(fd_file);
			delete_redirects(&data->top, tmp->data, data, 0);
			data->red_flag++;
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	redi_here_no_node(t_data *data, char *here)
{
	int			fd_file;

	fd_file = do_here(here);
	if (fd_file == -1)
		return (-1);
	dup2(fd_file, STDIN_FILENO);
	close(fd_file);
	data->red_flag++;
	return (0);
}
