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
		if (!data->top->next)
		{
			export_builtin(data->export);
			g_exit = 0;
			return (1);
		}
		else
		{
			add_export(data->export, data);
			g_exit = 0;
			return (1);
		}
	}
	else if (ft_strncmp("unset", data->top->data, data->top->len) == 0)
	{
		if (!data->top->next)
		{
			printf("\n");
			g_exit = 0;
			return (1);
		}
		else
		{
			printf("unset execution\n");
			return (1);
		}
	}
	else if (check_builtins2(data) == 1)
		return (1);
	return (0);
}

int	check_builtins2(t_data *data)
{
	if (ft_strncmp("env", data->top->data, data->top->len) == 0)
	{
		if (!data->top->next)
		{
			print_array(data->env);
			g_exit = 0;
			return (1);
		}
		else
		{
			printf("env: No options or arguments supported\n");
			g_exit = 127;
			return (1);
		}
	}
	else if (ft_strncmp("exit", data->top->data, data->top->len) == 0)
	{
		printf("exit execution\n");
		//execut_exit(data); please check if t !data->top->next
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
