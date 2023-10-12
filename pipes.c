/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:34:10 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/10/12 12:29:45 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

//void	pipes_execution(t_data *data)
//{
//	t_tokens *tmp;
//
//}

char	**pipes_commands(t_data *data)
{
	char		**commands;
	int			i;
	int			j;
	int			k;
	bool		quotes;

	i = 0;
	j = 0;
	k = 0;
	quotes = false;
	commands = malloc(sizeof (char *) * (data->pipes_nums + 2));
	commands[j] = malloc(sizeof(char) * strlen(data->original_command));
	while (data->original_command[i])
	{
		if (i == 0)
			if (data->original_command[i] == '\'' || data->original_command[i] == '\"')
			{
				if (quotes == true)
					quotes = false;
				else
					quotes = true;
			}
		if (data->original_command[i] == '|' && quotes == false)
		{
			commands[j][k] = '\0';
			i++;
			k = 0;
			j++;
			commands[j] = malloc(sizeof(char) * strlen(data->original_command));
			continue ;
		}
		if (data->original_command[i] == ' ' && data->original_command[i + 1] == '|' && quotes == false)
		{
			commands[j][k] = '\0';
			i = i + 2;
			k = 0;
			j++;
			commands[j] = malloc(sizeof(char) * strlen(data->original_command));
			continue ;
		}
			commands[j][k] = data->original_command[i];
			i++;
			k++;
	}
	commands[j][k] = '\0';
	commands[j + 1] = NULL;
	return (commands);
}
