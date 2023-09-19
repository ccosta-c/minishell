/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:14:36 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/09/18 16:57:37 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	exit_builtin(t_data *data)
{
	if (check_exit_data(data->top->next->data) == -1)
	{
		printf("exit\n");
		printf("bash: exit: %s: numeric argument required\n", data->top->next->data);
		g_exit = 2;
		frees(data);
		exit(g_exit);
	}
	printf("exit continue\n");
}

int	check_exit_data(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{

		if (str[i] < 48 || str[i] > 57)
			return (-1);
		i++;
	}
	return (0);
}