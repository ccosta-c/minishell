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

int	lexer(t_data *data, char *input)
{
	char	*str;

	if (!input)
		return (-1);
	str = ft_strtrim(input, " ");
	if (check_first(str) == -1)
		return (free(str), 0);
	lexer_continuation(data, str, 0, 0);
	free(str);
	//print_list(data);
	execution(data);
	return (0);
}

void	lexer_continuation(t_data *data, char *str, int i, int j)
{
	while (1)
	{
		while (str[i] == ' ')
			i++;
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
}

/*char	*handle_whitespaces(char *input)
{
	char	*ret;

	ret = ft_strtrim(input, " ");
	return (ret);
}*/

int	list_quote(char *input, int i)
{
	if (input[i] == '\'')
	{
		i++;
		while (input[i] != '\'')
		{
			i++;
		}
		return (i);
	}
	else if (input[i] == '\"')
	{
		i++;
		while (input[i] != '\"')
		{
			i++;
		}
		return (i);
	}
	return (i);
}
