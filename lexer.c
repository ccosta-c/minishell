/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:29:55 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/08/29 17:25:53 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	lexer(t_data *data, char *input, int i, int j)
{
	char	*str;

	if (!input)
		return (-1);
	str = handle_whitespaces(input);
	if (check_first(str) == -1)
		return (free(str), 0);
	while (1)
	{
		j = i;
		while (str[i] != ' ' && str[i] != '\0')
		{
			if (str[i] == '\'' || str[i] == '\"')
				i = list_quote(str, i);
			i++;
		}
		add_to_list(&data->top, initialize_tokens(i, j, str));
		if (str[i++] == '\0')
			break ;
	}
	free(str);
	//print_list(data);
	execution(data);
	return (0);
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
	ret = (char *)malloc(((ft_strlen(input)) + 1) * sizeof(char));
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
	return (free(tmp), ret);
}

int	list_quote(char *input, int i)
{
	if (input[i] == '\'')
	{
		i++;
		while (input[i] != '\'')
			i++;
		return (i);
	}
	else if (input[i] == '\"')
	{
		i++;
		while (input[i] != '\"')
			i++;
		return (i);
	}
	return (i);
}
