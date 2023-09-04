/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:44:34 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/08/31 16:36:55 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	check_builtins(t_data *data)
{
	if (ft_strncmp("echo", data->top->data, data->top->len) == 0)
	{
		printf("echo execution\n");
		//execut_echo(data);
		return (1);
	}
	else if (ft_strncmp("pwd", data->top->data, data->top->len) == 0)
	{
		printf("pwd execution\n");
		//execut_pwd(data);
		return (1);
	}
	else if (ft_strncmp("export", data->top->data, data->top->len) == 0)
	{
		export_builtin(data->export);
		return (1);
	}
	else if (ft_strncmp("unset", data->top->data, data->top->len) == 0)
	{
		printf("unset execution\n");
		//execut_unset(data);
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
		print_array(data->env);
		return (1);
	}
	else if (ft_strncmp("exit", data->top->data, data->top->len) == 0)
	{
		printf("exit execution\n");
		//execut_exit(data);
		return (1);
	}
	else if (ft_strncmp("cd", data->top->data, data->top->len) == 0)
	{
		if (data->top->next)
		{
			if (ft_strncmp("-n", data->top->next->data, data->top->next->len) == 0)
			{
				printf("cd execution\n");
				//execut_cd(data);
				return (1);
			}
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
