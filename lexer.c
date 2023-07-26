/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:29:55 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/07/25 11:09:01 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	lexer(t_data *data, char *input)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	str = handle_whitespaces(input);
	printf("str antes da lista: %s\n", str);
	while (1)
	{
		j = i;
		while (str[i] != ' ' && str[i] != '\0')
			i++;
		add_to_list(&data->top, initialize_tokens(i, j, str));
		i++;
		if (str[i] == '\0')
			break ;
	}
	free(str);
	print_list(data);
	ft_cleartokens(&data->top);
	print_list(data);
	return (0);
}

char	*handle_whitespaces(char *input)
{
	char	**tmp;
	char	*ret;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	ret = (char *)malloc((ft_strlen(input)) * sizeof(char));
	tmp = ft_split(input, ' ');f
	while (tmp[i] != NULL)
	{
		k = 0;
		while (tmp[i][k] != '\0')
		{
			ret[j] = tmp[i][k];
			j++;
			k++;
		}
		if (tmp[i + 1] == NULL)
			break ;
		ret[j] = ' ';
		j++;
		i++;
	}
	free(tmp);
	return (ret);
}
