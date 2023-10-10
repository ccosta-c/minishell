/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:36:00 by macastan          #+#    #+#             */
/*   Updated: 2023/10/10 17:36:05 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char	*cut_env_exp(char *env, int j, int k)
{
	char	*fim;

	while (env[j] != '=')
		j++;
	fim = malloc(sizeof (char) * (ft_strlen(env) - j));
	j++;
	while (env[j])
	{
		fim[k] = env[j];
		j++;
		k++;
	}
	fim[k] = '\0';
	return (fim);
}

int	cut_str_exp(char *str, int i, int flag_s)
{
	while (str[i])
	{
		if (str[i] == '\'' && flag_s == 0)
			flag_s = 1;
		else if (str[i] == '\'' && flag_s != 0)
			flag_s = 0;
		else if (str[i] == '$' && flag_s == 0)
			return (i);
		i++;
	}
	return (i);
}

int	count_str_exp(char *str, int i, int flag_s)
{
	int	ex;

	ex = 0;
	while (str[i])
	{
		if (str[i] == '\'' && flag_s == 0)
			flag_s = 1;
		else if (str[i] == '\'' && flag_s != 0)
			flag_s = 0;
		else if (str[i] == '$' && flag_s == 0)
			ex++;
		i++;
	}
	return (ex);
}

int	check_minus_n(char *s)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (s[i] != 'n')
			return (-1);
		i++;
	}
	return (0);
}
