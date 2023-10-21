/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:38:42 by macastan          #+#    #+#             */
/*   Updated: 2023/10/20 17:13:25 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	execution_pwd(t_data *data)
{
	char	*path;

	if (data->top->next)
	{
		if (remove_quote(data->top->next->data, 0, 0, 0)[0] == '-')
		{
			printf("pwd: No options supported\n");
			g_exit = 2;
			return ;
		}
	}
	path = getcwd(0, 0);
	printf("%s\n", path);
	g_exit = 0;
	free(path);
}

void	execution_env(t_data *data)
{
	char	*tmp;

	tmp = get_variable("PATH", data->export, count_variables(data->export));
	if (!tmp)
	{
		printf("minishell: env: No such file or directory\n");
		g_exit = 127;
	}
	else if (data->top->next)
	{
		printf("minishell: env: No options or arguments supported\n");
		g_exit = 2;
	}
	else
	{
		print_lstchar(data->env);
		g_exit = 0;
	}
	free(tmp);
}

void	execution_export(t_data *data)
{
	char	*tmp;
	int		i;

	i = 0;
	if (data->top->next)
	{
		tmp = remove_quote(data->top->next->data, 0, 0, 0);
		if (tmp[0] == '-')
		{
			printf("export: No options supported\n");
			g_exit = 2;
			return ;
		}
		add_export(data);
		free(tmp);
		g_exit = 0;
	}
	else
	{
		export_builtin(data->export, 0);
		print_export(data->export, count_variables(data->export), 0);
		g_exit = 0;
	}
}

void	execution_unset(t_data *data)
{
	char	*tmp;

	if (!data->top->next)
	{
		g_exit = 0;
	}
	else
	{
		tmp = remove_quote(data->top->next->data, 0, 0, 0);
		if (tmp[0] == '-')
		{
			printf("unset: No options supported\n");
			g_exit = 2;
			free(tmp);
			return ;
		}
		unset_builtin(data);
		free(tmp);
		g_exit = 0;
	}
}

void	execution_exit(t_data *data)
{
	if (!data->top->next)
	{
		printf("exit\n");
		frees(data);
		exit(g_exit);
	}
	else if (data->top->next->next
		&& check_exit_data(data->top->next->data) == 0)
	{
		printf("exit\nminishell: exit: too many arguments\n");
		g_exit = 1;
		return ;
	}
	else if (ft_strcmp("\"\"", data->top->next->data) == 0
		|| ft_strcmp("\'\'", data->top->next->data) == 0)
	{
		printf("exit\nbash: exit: : numeric argument required\n");
		g_exit = 2;
		frees(data);
		exit(g_exit);
	}
	else
		exit_builtin(data);
}
