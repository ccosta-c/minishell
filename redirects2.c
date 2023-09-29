/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:45:42 by macastan          #+#    #+#             */
/*   Updated: 2023/09/29 11:45:45 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	redi_out_dois_nodes(t_data *data, char *str)
{
	t_tokens	*tmp;
	int			fd_file;

	tmp = data->top;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->data, str) == 0)
		{
			printf("deletar o node\n");
			fd_file = open(tmp->next->data, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (!fd_file)
			{
				printf("Minishell: no file specified in redirect '>'.\n");
				return (free(tmp), -1);
			}
			dup2(fd_file, STDOUT_FILENO);
			close(fd_file);
			printf("deletar proximo node\n");
			return (free(tmp), 0);
		}
		tmp = tmp->next;
	}
	return (free(tmp), 0);
}