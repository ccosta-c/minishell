/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:18:24 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/07/14 15:24:45 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	copy_envp(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	data->env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		data->env[i] = strdup(envp[i]);
		i++;
	}
	data->env[i] = NULL;
}

t_tokens	*initialize_tokens(int end, int start, char *arg)
{
	t_tokens	*tmp;
	int			i;

	i = 0;
	tmp = malloc(sizeof(t_tokens));
	tmp->next = NULL;
	tmp->tokens = 0;
	tmp->type = GENERIC;
	tmp->data = malloc(sizeof(char) * ((end - start) + 1));
	while (start < end)
	{
		tmp->data[i] = arg[start];
		start++;
		i++;
	}
	tmp->data[i] = '0';
	tmp->len = strlen(tmp->data);
	return (tmp);
}
