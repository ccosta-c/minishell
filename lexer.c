/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:29:55 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/08/02 16:28:59 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	lexer(t_data *data, char *input)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	if (!input)
		return (-1);
	str = handle_whitespaces(input);
	if (check_first(str) == -1)
		return (0);
	while (1)
	{
		j = i;
		while (str[i] != ' ' && str[i] != '\0')
			i++;
		add_to_list(&data->top, initialize_tokens(i, j, str));
		if (str[i++] == '\0')
			break ;
	}
	free(str);
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

int	check_quotes(char *input, int i)
{
	char q;

	q = 0;
	while (input[i] && q == 0)
	{
		if (ft_strrchr("\"\'", input[i]))
			q = input[i];
		i++;
	}
	while (input[i] && q != 0)
	{
		if (input[i] == q)
			q = 0;
		i++;
	}
	if (input[i])
		return (check_quotes(input,i));
	else if (q == 0)
		return (1);
	else
		return (0);
}
