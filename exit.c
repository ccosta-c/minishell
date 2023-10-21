/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:14:36 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/10/11 15:41:42 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	exit_builtin(t_data *data)
{
	remove_quote_list(data);
	if (check_exit_data(data->top->next->data) == -1)
	{
		printf("exit\n");
		printf("bash: exit: %s:", data->top->next->data);
		printf(" numeric argument required\n");
		g_exit = 2;
		frees(data);
		exit(g_exit);
	}
	else
		exit_builtin2(data);
}

void	exit_builtin2(t_data *data)
{
	long long	e;

	e = ft_atol(data->top->next->data);
	if (e == 0)
	{
		printf("exit\n");
		g_exit = 0;
		frees(data);
		exit(g_exit);
	}
	if (ft_nlen(e) != ft_strlen(data->top->next->data))
	{
		printf("exit\n");
		printf("bash: exit: %s:", data->top->next->data);
		printf(" numeric argument required\n");
		g_exit = 2;
		frees(data);
		exit(g_exit);
	}
	printf("exit\n");
	g_exit = (e % 256);
	frees(data);
	exit(g_exit);
}

size_t	ft_nlen(long long n)
{
	size_t	i;

	i = 0;
	if (n < 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	check_exit_data(char *str)
{
	char	*ws;
	int		i;

	i = 0;
	ws = handle_whitespaces(str);
	if (ws[i] == '-' || ws[i] == '+')
		i++;
	while (ws[i])
	{
		if (ws[i] < 48 || ws[i] > 57)
			return (-1);
		i++;
	}
	return (free(ws), 0);
}

char	*handle_whitespaces(char *input)
{
	char	**tmp;
	char	*ret;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	ret = (char *) malloc(((ft_strlen(input)) + 1) * sizeof(char));
	tmp = ft_split(input, ' ');
	while (tmp[++i] != NULL)
	{
		k = 0;
		while (tmp[i][k] != '\0')
			ret[j++] = tmp[i][k++];
		if (tmp[i + 1] == NULL)
		{
			ret[j] = '\0';
			break ;
		}
		ret[j++] = ' ';
	}
	return (free_array(tmp), ret);
}
