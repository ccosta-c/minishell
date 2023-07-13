/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:18:24 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/07/10 11:18:24 by ccosta-c         ###   ########.fr       */
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

void	initialize_tokens(t_tokens *node, int end, int start, char *arg)
{
	node = malloc(sizeof(t_tokens));
	node->data = 0;
	node->len = 0;

}
