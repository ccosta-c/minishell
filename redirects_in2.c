/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_in2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:34:15 by macastan          #+#    #+#             */
/*   Updated: 2023/10/11 11:34:20 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	redi_in_two_nodes(t_data *data, char *str, char *file)
{
	t_tokens	*tmp;
	int			fd_file;

	tmp = data->top;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->data, str) == 0)
		{
			fd_file = open(file, O_RDONLY);
			if (fd_file < 0)
			{
				printf("Minishell: %s: %s.\n", file, strerror(errno));
				return (-1);
			}
			dup2(fd_file, STDIN_FILENO);
			close(fd_file);
			delete_redirects(&data->top, tmp->next->data, data);
			delete_redirects(&data->top, tmp->data, data);
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	redi_in_two_nodes_cut(t_data *data, char *str, char *temp)
{
	t_tokens	*tmp;
	int			fd_file;

	tmp = data->top;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->data, str) == 0)
		{
			fd_file = open(temp, O_RDONLY);
			if (fd_file < 0)
			{
				printf("Minishell: %s: %s.\n", temp, strerror(errno));
				return (-1);
			}
			dup2(fd_file, STDIN_FILENO);
			close(fd_file);
			delete_redirects(&data->top, tmp->data, data);
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	redi_in_one_node_del(t_data *data, char *str, char *temp)
{
	t_tokens	*tmp;
	int			fd_file;

	tmp = data->top;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->data, str) == 0)
		{
			fd_file = open(temp, O_RDONLY);
			if (fd_file < 0)
			{
				printf("Minishell: %s: %s.\n", temp, strerror(errno));
				return (-1);
			}
			dup2(fd_file, STDIN_FILENO);
			close(fd_file);
			delete_redirects(&data->top, tmp->data, data);
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	redi_in_no_node(t_data *data, char *temp)
{
	int			fd_file;

	(void)data;
	fd_file = open(temp, O_RDONLY);
	if (fd_file < 0)
	{
		printf("Minishell: %s: %s.\n", temp, strerror(errno));
		return (-1);
	}
	dup2(fd_file, STDIN_FILENO);
	close(fd_file);
	return (0);
}
