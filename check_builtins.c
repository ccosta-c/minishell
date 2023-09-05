/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:44:34 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/09/04 15:43:03 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	check_builtins(t_data *data)
{
	if (search_red(data) == 1)
		printf("Go to Redirections/n");
	if (ft_strncmp("echo", data->top->data, data->top->len) == 0)
	{
		execution_echo(data);
		return (1);
	}
	else if (ft_strncmp("pwd", data->top->data, data->top->len) == 0)
	{
		execution_pwd(data);
		return (1);
	}
	else if (ft_strncmp("export", data->top->data, data->top->len) == 0)
	{
		execution_export(data);
		return (1);
	}
	else if (ft_strncmp("unset", data->top->data, data->top->len) == 0)
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
	if (ft_strncmp("env", data->top->data, data->top->len) == 0)
	{
		execution_env(data);
		return (1);
	}
	else if (ft_strncmp("exit", data->top->data, data->top->len) == 0)
	{
		printf("exit execution\n");
		//execut_exit(data); please check if !data->top->next
		return (1);
	}
	else if (ft_strncmp("cd", data->top->data, data->top->len) == 0)
	{
		if (data->top->next)
		{
				printf("cd execution\n");
				//execut_cd(data);
				return (1);
		}
		else
		{
			printf("cd execution\n");
			//execut_cd(data);
			return (1);
		}
	}
	return (0);
}
