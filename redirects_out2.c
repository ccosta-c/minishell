/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_out2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:53:09 by macastan          #+#    #+#             */
/*   Updated: 2023/10/04 15:53:14 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	redi_out_two_nodes(t_data *data, char *str, char *file)
{
	t_tokens	*tmp;
	int			fd_file;

	tmp = data->top;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->data, str) == 0)
		{
			fd_file = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (fd_file < 0)
			{
				printf("Minishell: %s: %s.\n", file, strerror(errno));
				return (-1);
			}
			dup2(fd_file, STDOUT_FILENO);
			close(fd_file);
			delete_redirects(&data->top, tmp->next->data);
			delete_redirects(&data->top, tmp->data);
			data->red_flag++;
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	redi_out_two_nodes_cut(t_data *data, char *str, char *temp)
{
	t_tokens	*tmp;
	int			fd_file;

	tmp = data->top;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->data, str) == 0)
		{
			fd_file = open(temp, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (fd_file < 0)
			{
				printf("Minishell: %s: %s.\n", temp, strerror(errno));
				return (-1);
			}
			dup2(fd_file, STDOUT_FILENO);
			close(fd_file);
			delete_redirects(&data->top, tmp->data);
			data->red_flag++;
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	redi_out_one_node_del(t_data *data, char *str, char *temp)
{
	t_tokens	*tmp;
	int			fd_file;

	tmp = data->top;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->data, str) == 0)
		{
			fd_file = open(temp, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (fd_file < 0)
			{
				printf("Minishell: %s: %s.\n", temp, strerror(errno));
				return (-1);
			}
			dup2(fd_file, STDOUT_FILENO);
			close(fd_file);
			delete_redirects(&data->top, tmp->data);
			data->red_flag++;
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	redi_out_one_node(t_data *data, char *str, char *temp)
{
	t_tokens	*tmp;
	int			fd_file;

	tmp = data->top;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->data, str) == 0)
		{
			printf("aquiiii %s\n", temp);
			fd_file = open(temp, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (fd_file < 0)
			{
				printf("Minishell: %s: %s.\n", temp, strerror(errno));
				return (-1);
			}
			dup2(fd_file, STDOUT_FILENO);
			close(fd_file);
			data->red_flag++;
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}
