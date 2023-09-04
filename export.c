/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:50:38 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/09/04 16:09:59 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	ft_swap(char **a, char **b)
{
	char	*c;

	c = *a;
	*a = *b;
	*b = c;
}

int	count_variables(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

void	export_builtin(char **array)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	size = count_variables(array);
	while (i < size - 1)
	{
		j = 0;
		if (array[i][j] == array[i + 1][j])
		{
			while ((array[i][j] || array[i + 1][j])
				&& (array[i][j] == array[i + 1][j]))
				j++;
		}
		if (array[i][j] > array[i + 1][j])
		{
			ft_swap(&array[i], &array[i + 1]);
			i = 0;
			continue ;
		}
		i++;
	}
	print_export(array);
}

void	print_export(char **array)
{
	int	i;
	int	j;

	i = 0;
	while (array[i] != NULL)
	{
		j = 0;
		write(1, "declare -x ", 11);
		while (array[i][j])
		{
			write(1, &array[i][j], 1);
			if (array[i][j] == '=')
				write (1, "\"", 1);
			if (array[i][j + 1] == '\0')
				write (1, "\"", 1);
			j++;
		}
		i++;
		write(1, "\n", 1);
	}
}

/*void	add_export(char	**array, t_data *data)
{
	int		size;
	char	**tmp;
	int		i;

	i = 0;
	size = count_variables(array);

	return ;
}*/