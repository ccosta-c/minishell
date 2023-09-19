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
	else
		exit_builtin2(data);
}

void	exit_builtin2(t_data *data)
{
	long long	e;

	e = ft_atol(data->top->next->data);
	printf("exit\n");
	g_exit = (e % 256);
	frees(data);
	exit(g_exit);
}

int	check_exit_data(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{

		if (str[i] < 48 || str[i] > 57)
			return (-1);
		i++;
	}
	return (0);
}