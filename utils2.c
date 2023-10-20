/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:22:38 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/09/14 14:52:20 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	check_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	return (i);
}

int	ft_stop_exp(char c)
{
	if (c == ' ' || (c >= 34 && c <= 37) || c == 39)
		return (0);
	if (c == 58 || (c >= 40 && c <= 47))
		return (0);
	if (c == 61 || c == 63 || c == 64)
		return (0);
	if (c >= 91 && c <= 94)
		return (0);
	if (c == 123 || c == 125 || c == 126)
		return (0);
	return (1);
}

int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	if (ft_strlen(str1) != ft_strlen(str2))
		return (-1);
	while (str1[i] != '\0' || str2[i] != '\0')
	{
		if (str1[i] > str2[i])
		{
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		}
		if (str1[i] < str2[i])
		{
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		}
		i++;
	}
	return (0);
}

void	change_env_exp(t_charlst *en, t_charlst *ex, char *old, char *nw)
{
	int			i;
	int			size;
	t_charlst	*l_tmp;

	i = 0;
	l_tmp = en;
	size = count_variables(en);
	while (i <= (size - 1))
	{
		if (ft_strncmp("OLDPWD", l_tmp->content, ft_strlen("OLDPWD")) == 0)
		{
			free(l_tmp->content);
			l_tmp->content = ft_strjoin("OLDPWD=", old);
		}
		if (ft_strncmp("PWD", l_tmp->content, ft_strlen("PWD")) == 0)
		{
			free(l_tmp->content);
			l_tmp->content = ft_strjoin("PWD=", nw);
		}
		i++;
		l_tmp = l_tmp->next;
	}
	change_env_exp2(ex, old, nw);
	return ;
}

void	change_env_exp2(t_charlst *exp, char *old, char *new)
{
	int			i;
	int			size;
	t_charlst	*l_tmp;

	l_tmp = exp;
	i = 0;
	size = count_variables(exp);
	while (i <= (size - 1))
	{
		if (ft_strncmp("OLDPWD", l_tmp->content, ft_strlen("OLDPWD")) == 0)
		{
			free(l_tmp->content);
			l_tmp->content = ft_strjoin("OLDPWD=", old);
		}
		if (ft_strncmp("PWD", l_tmp->content, ft_strlen("PWD")) == 0)
		{
			free(l_tmp->content);
			l_tmp->content = ft_strjoin("PWD=", new);
		}
		i++;
		l_tmp = l_tmp->next;
	}
	return ;
}
