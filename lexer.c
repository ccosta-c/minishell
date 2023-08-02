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
	check_quotes(input);
	str = handle_whitespaces(input);
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

int	check_quotes(char	*input)
{
	int	i;
	int	single;
	int	duble;

	i = 0;
	single = 0;
	duble = 0;
	while (input[i])
	{
		if (input[i] == 39)
			single++;
		if (input[i] == 34)
			duble++;
		i++;
	}
	if ((single % 2 != 0) || (duble % 2 != 0))
		exit (1);
	return (0);
}
