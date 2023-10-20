/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <macastan@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:46:06 by macastan          #+#    #+#             */
/*   Updated: 2023/10/18 15:46:11 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	signal_default(t_data *data)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	handler_sigint2(0, data);
}

int	check_not_exc(char *in)
{
	if (ecomercial_search(in, 0, 0) != 0)
	{
		printf("minishell: & not interpreted\n");
		return (g_exit = 127, -1);
	}
	if (backslash_search(in, 0, 0) != 0)
	{
		printf("minishell: \\ not interpreted\n");
		return (g_exit = 127, -1);
	}
	if (semicolon_search(in, 0, 0) != 0)
	{
		printf("minishell: ; not interpreted\n");
		return (g_exit = 127, -1);
	}
	return (0);
}

int	ecomercial_search(char *str, int i, int e)
{
	int	flag_s;
	int	flag_d;

	flag_s = 0;
	flag_d = 0;
	while (str[i])
	{
		if (str[i] == '\"' && flag_d == 0 && flag_s == 0)
			flag_d = 1;
		else if (str[i] == '\"' && flag_d != 0 && flag_s == 0)
			flag_d = 0;
		else if (str[i] == '\'' && flag_s == 0 && flag_d == 0)
			flag_s = 1;
		else if (str[i] == '\'' && flag_s != 0 && flag_d == 0)
			flag_s = 0;
		else if (str[i] == '&' && flag_d == 0 && flag_s == 0)
			e++;
		i++;
	}
	return (e);
}

int	backslash_search(char *str, int i, int b)
{
	int	flag_s;
	int	flag_d;

	flag_s = 0;
	flag_d = 0;
	while (str[i])
	{
		if (str[i] == '\"' && flag_d == 0 && flag_s == 0)
			flag_d = 1;
		else if (str[i] == '\"' && flag_d != 0 && flag_s == 0)
			flag_d = 0;
		else if (str[i] == '\'' && flag_s == 0 && flag_d == 0)
			flag_s = 1;
		else if (str[i] == '\'' && flag_s != 0 && flag_d == 0)
			flag_s = 0;
		else if (str[i] == '\\' && flag_d == 0 && flag_s == 0)
			b++;
		i++;
	}
	return (b);
}

int	semicolon_search(char *str, int i, int s)
{
	int	flag_s;
	int	flag_d;

	flag_s = 0;
	flag_d = 0;
	while (str[i])
	{
		if (str[i] == '\"' && flag_d == 0 && flag_s == 0)
			flag_d = 1;
		else if (str[i] == '\"' && flag_d != 0 && flag_s == 0)
			flag_d = 0;
		else if (str[i] == '\'' && flag_s == 0 && flag_d == 0)
			flag_s = 1;
		else if (str[i] == '\'' && flag_s != 0 && flag_d == 0)
			flag_s = 0;
		else if (str[i] == ';' && flag_d == 0 && flag_s == 0)
			s++;
		i++;
	}
	return (s);
}
