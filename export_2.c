/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:31:20 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/10/20 17:54:05 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	check_if_exists(t_data *data, char *tmp)
{
	add_to_charlist(&data->export, tmp);
	if (ft_strchr(tmp, '=') != 0)
		add_to_charlist(&data->env, tmp);
}

int	execution_checks(char *data)
{
	int		i;

	i = 0;
	while (data[i] != '=' && data[i] != '\0')
	{
		if ((data[i] < 65 || data[i] > 90) && (data[i] < 97 || data[i] > 122)
			&& (data[i]) != '_')
		{
			printf("export: `%s': not a valid identifier\n", data);
			return (1);
		}
		i++;
	}
	return (0);
}
