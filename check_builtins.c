/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:44:34 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/10/20 16:59:42 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	fork_redirects(t_data *data, int redi)
{
	pid_t	pid;

	pid = fork();
	redi = search_red_total(data, 0);
	data->red_n = redi;
	if (pid == 0)
	{
		signal_default(data);
		signal(SIGINT, &handler_sigint);
		while (redi > 0)
		{
			if (redirects(data, data->top) == -1)
			{
				frees(data);
				exit(1);
			}
			redi--;
		}
		if (data->lst_size > 0)
			execution(data);
		frees(data);
		exit (0);
	}
	get_exit_status_one(pid, data);
	wait(NULL);
}

int	search_red_total(t_data *data, int redi)
{
	t_tokens	*tmp;

	tmp = data->top;
	while (tmp != NULL)
	{
		redi = redi + redi_out_search(tmp->data, 0, 0);
		tmp = tmp->next;
	}
	return (redi);
}

int	check_builtins(t_data *data)
{
	if (search_red(data) == 1)
	{
		fork_redirects(data, 0);
		return (1);
	}
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
	else if (check_builtins2(data) == 1)
		return (1);
	return (0);
}

int	check_builtins2(t_data *data)
{
	if (ft_strcmp("exit", data->top->data) == 0)
	{
		execution_exit(data);
		return (1);
	}
	else if (ft_strcmp("cd", data->top->data) == 0)
	{
		if (data->top->next)
		{
			if (ft_strcmp("\"\"", data->top->next->data) == 0
				|| ft_strcmp("\'\'", data->top->next->data) == 0)
				return (g_exit = 0, 1);
			remove_quote_list(data);
			return (cd(data, data->top->next->data), 1);
		}
		else
			return (cd_home_dir(data), 1);
	}
	else if (check_builtins3(data) == 1)
		return (1);
	return (0);
}

int	check_builtins3(t_data *data)
{
	if (ft_strcmp("export", data->top->data) == 0)
	{
		execution_export(data);
		return (1);
	}
	else if (ft_strcmp("unset", data->top->data) == 0)
	{
		execution_unset(data);
		return (1);
	}
	else if (ft_strcmp("env", data->top->data) == 0)
	{
		execution_env(data);
		return (1);
	}
	return (0);
}
