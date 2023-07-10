/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:20:13 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/07/10 18:08:20 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	get_prompt(t_data *data)
{
	char	*user;
	char	*pc_id;

	user = getenv("USER");
	pc_id = get_pc_id();
	data->prompt = ft_strjoin(user, pc_id);
}

char	*get_pc_id(void)
{
	char	*session_manager;
	char	*result;
	int		i;
	int		j;

	j = 0;
	i = 0;
	session_manager = getenv("SESSION_MANAGER");
	while (session_manager[i] != 47 && session_manager[i])
		i++;
	result = malloc(sizeof(char) * 8);
	i++;
	result[j++] = '@';
	while (session_manager[i] != '.' && session_manager[i])
	{
		result[j] = session_manager[i];
		i++;
		j++;
	}
	result[j] = '\0';
	return (result);
}
