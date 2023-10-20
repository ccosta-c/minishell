/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:18:40 by macastan          #+#    #+#             */
/*   Updated: 2023/10/20 18:13:47 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	cd(t_data *data, char *str)
{
	char	*tmp;

	if (data->top->next->next)
	{
		g_exit = 1;
		return (printf("minishell: cd: too many arguments\n"));
	}
	if (ft_strncmp("-", str, ft_strlen(str)) == 0)
		cd_minus_dir(data);
	else if (ft_strncmp("~", str, ft_strlen(str)) == 0)
		cd_home_dir(data);
	else if (ft_strncmp("..", str, ft_strlen(str)) == 0)
		cd_double_dot_dir(data);
	else if (ft_strncmp(".", str, ft_strlen(str)) == 0)
		return (g_exit = 0);
	else
	{
		tmp = str_exp_quote(data, data->top->next->data,
				count_str_exp(data->top->next->data, 0, 0));
		cd_else_dir(data, tmp);
		free(tmp);
	}
	return (0);
}

void	cd_home_dir(t_data *data)
{
	free(data->pwd);
	free(data->old_pwd);
	data->pwd = getcwd(0, 0);
	data->old_pwd = ft_strdup(data->pwd);
	free(data->pwd);
	chdir(data->home);
	data->pwd = getcwd(0, 0);
	change_env_exp(data->env, data->export, data->old_pwd, data->pwd);
	free(data->prompt);
	get_prompt(data);
	g_exit = 0;
}

void	cd_minus_dir(t_data *data)
{
	int	i;

	i = count_variables(data->env);
	free(data->pwd);
	free(data->old_pwd);
	data->pwd = getcwd(0, 0);
	data->old_pwd = get_variable("OLDPWD", data->env, i);
	if (!data->old_pwd)
	{
		printf("minishell: cd: OLDPWD not set\n");
		g_exit = 1;
		return ;
	}
	chdir(data->old_pwd);
	free(data->old_pwd);
	data->old_pwd = ft_strdup(data->pwd);
	free(data->pwd);
	data->pwd = getcwd(0, 0);
	change_env_exp(data->env, data->export, data->old_pwd, data->pwd);
	free(data->prompt);
	get_prompt(data);
	g_exit = 0;
}

void	cd_double_dot_dir(t_data *data)
{
	free(data->pwd);
	free(data->old_pwd);
	data->pwd = getcwd(0, 0);
	data->old_pwd = ft_strdup(data->pwd);
	free(data->pwd);
	chdir("..");
	data->pwd = getcwd(0, 0);
	change_env_exp(data->env, data->export, data->old_pwd, data->pwd);
	free(data->prompt);
	get_prompt(data);
	g_exit = 0;
}

void	cd_else_dir(t_data *data, char *dir)
{
	char	*temp;

	free(data->pwd);
	free(data->old_pwd);
	temp = get_variable("OLDPWD", data->env, count_variables(data->env));
	data->pwd = getcwd(0, 0);
	data->old_pwd = ft_strdup(data->pwd);
	if (chdir(dir) == -1)
	{
		printf("%s: No such file or directory\n", dir);
		free(data->old_pwd);
		data->old_pwd = ft_strdup(temp);
		g_exit = 1;
		free(temp);
		return ;
	}
	free(data->pwd);
	data->pwd = getcwd(0, 0);
	free(temp);
	change_env_exp(data->env, data->export, data->old_pwd, data->pwd);
	free(data->prompt);
	get_prompt(data);
	g_exit = 0;
}
