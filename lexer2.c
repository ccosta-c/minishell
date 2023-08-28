/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 10:43:13 by macastan          #+#    #+#             */
/*   Updated: 2023/08/28 10:43:16 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

enum e_type	get_type(char *str)
{
	if (str[0] == '\"')
		return (D_QUOTE);
	else if (str[0] == '\'')
		return (S_QUOTE);
	else
		return (GENERIC);
}
