/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:24:53 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/10/18 14:48:47 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char	**pipes_commands_aux(t_data *data)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	return (pipes_commands(data, i, j, k));
}

char	**pipes_commands(t_data *data, int i, int j, int k)
{
	char	**commands;
	bool	quotes;

	quotes = false;
	commands = malloc(sizeof (char *) * (data->pipes_nums + 2));
	commands[j] = malloc(sizeof(char) * strlen(data->original_command));
	while (data->original_command[i])
	{
		first_pipes_cmd_check(data->original_command[i], &quotes);
		if (data->original_command[i] == '|' && quotes == false)
		{
			commands[j][k] = '\0';
			i++;
			k = 0;
			j++;
			commands[j] = malloc(sizeof(char) * strlen(data->original_command));
			continue ;
		}
		if (data->original_command[i] == ' '
			&& data->original_command[i + 1] == '|' && quotes == false)
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

void	first_pipes_cmd_check(char original_command, bool *quotes)
{
	if (original_command == '\'' || original_command == '\"')
	{
		if (*(quotes) == true)
			*(quotes) = false;
		else
			*(quotes) = true;
	}
}
