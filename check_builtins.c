/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:44:34 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/09/18 16:13:58 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	check_builtins(t_data *data)
{
	if (search_red(data) == 1)
		printf("Go to Redirections/n");
	if (ft_strcmp("echo", data->top->data) == 0)
	{
		execution_echo(data);
		return (g_exit = 0, 1);
	}
	if (ft_strcmp("pwd", data->top->data) == 0)
	{
		execution_pwd(data);
		return (1);
	}
	else if (ft_strcmp("export", data->top->data) == 0)
	{
		execution_export(data);
		return (1);
	}
	else if (ft_strcmp("unset", data->top->data) == 0)
	{
		execution_unset(data);
		return (1);
	}
	else if (check_builtins2(data) == 1)
		return (1);
	return (0);
}

int	check_builtins2(t_data *data)
{
	if (ft_strcmp("env", data->top->data) == 0)
	{
		execution_env(data);
		return (1);
	}
	else if (ft_strcmp("exit", data->top->data) == 0)
	{
		execution_exit(data);
		return (1);
	}
	else if (ft_strcmp("cd", data->top->data) == 0)
	{
		if (data->top->next)
		{
			if (ft_strcmp("\"\"", data->top->next->data) == 0 || ft_strcmp("\'\'", data->top->next->data) == 0)
				return (g_exit = 0,1);
			else
				return (cd(data), 1);
		}
		else
			return (cd_home_dir(data), 1);
	}
	return (0);
}
