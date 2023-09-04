/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:38:42 by macastan          #+#    #+#             */
/*   Updated: 2023/09/04 17:38:47 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void execution_pwd(t_data *data)
{
	char *path;

	if (data->top->next)
	{
		if (data->top->next->data[0] == '-')
		{
			printf("pwd: No options supported\n");
			g_exit = 127; //ou 2 decidir
			return  ;
		}
	}
	path = getcwd(0, 0);
	printf("%s\n", path);
	g_exit = 0;
	free(path);
}

void execution_env(t_data *data)
{
	if (!data->top->next)
	{
		print_array(data->env);
		g_exit = 0;
	}
	else
	{
		printf("env: No options or arguments supported\n");
		g_exit = 127; //ou 2 decidir
	}
}

void execution_export(t_data *data)
{
	if (data->top->next)
	{
		if (data->top->next->data[0] == '-')
		{
			printf("export: No options supported\n");
			g_exit = 127; //ou 2 decidir
			return  ;
		}
		//add_export(data->export, data);
		g_exit = 0;
	}
	else
	{
		export_builtin(data->export);
		g_exit = 0;
	}
}

void execution_unset(t_data *data)
{
	if (!data->top->next)
	{
		g_exit = 0;
	}
	else
	{
		if (data->top->next->data[0] == '-')
		{
			printf("unset: No options supported\n");
			g_exit = 127; //ou 2 decidir
			return  ;
		}
		printf("unset execution\n");
		g_exit = 0;
	}
}