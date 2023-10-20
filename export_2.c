/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:31:20 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/10/20 11:46:16 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	check_if_exists(t_data *data, char *tmp)
{
	add_to_charlist(&data->export, tmp);
	if (ft_strchr(tmp, '=') != 0)
		add_to_charlist(&data->env, tmp);
}
