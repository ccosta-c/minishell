/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:20:43 by macastan          #+#    #+#             */
/*   Updated: 2023/09/20 15:20:45 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	redirects(t_data *data, t_tokens *tmp)
{
	while (tmp)
	{
		if (tmp->type == R_OUT)
			return (redirects_out(data, tmp->next, tmp->data, tmp));
		else if (tmp->type == R_IN)
			return (redirects_in(data, tmp->next, tmp->data, tmp));
		else if (tmp->type == RR_IN)
			return (redirects_here(data, tmp->next, tmp->data, tmp));
		else if (tmp->type == RR_OUT)
			return (redirects_append(data, tmp->next, tmp->data, tmp));
		else
			tmp = tmp->next;
	}
	return (0);
}

int	redirects_out(t_data *data, t_tokens *n, char *str, t_tokens *c)
{
	t_tokens	*next;
	t_tokens	*current;

	next = n;
	current = c;
	(void)str;
	if (n)
	{
		if (redi_out(data, current->data, next->data) == -1)
			return (-1);
	}
	else
	{
		if (redi_out(data, current->data, "maluca") == -1)
			return (-1);
	}
	return (0);
}

int	redirects_in(t_data *data, t_tokens *n, char *str, t_tokens *c)
{
	t_tokens	*next;
	t_tokens	*current;

	next = n;
	current = c;
	(void)str;
	if (n)
	{
		if (redi_in(data, current->data, next->data) == -1)
			return (-1);
	}
	else
	{
		if (redi_in(data, current->data, "maluca") == -1)
			return (-1);
	}
	return (0);
}

int	redirects_here(t_data *data, t_tokens *n, char *str, t_tokens *c)
{
	t_tokens	*next;
	t_tokens	*current;

	next = n;
	current = c;
	(void)str;
	if (n)
	{
		if (redi_heredoc(data, current->data, next->data) == -1)
			return (-1);
	}
	else
	{
		if (redi_heredoc(data, current->data, "maluca") == -1)
			return (-1);
	}
	return (0);
}

int	redirects_append(t_data *data, t_tokens *n, char *str, t_tokens *c)
{
	t_tokens	*next;
	t_tokens	*current;

	next = n;
	current = c;
	(void)str;
	if (n)
	{
		if (redi_append(data, current->data, next->data) == -1)
			return (-1);
	}
	else
	{
		if (redi_append(data, current->data, "maluca") == -1)
			return (-1);
	}
	return (0);
}
