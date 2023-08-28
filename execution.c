/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:10:31 by macastan          #+#    #+#             */
/*   Updated: 2023/08/28 14:10:34 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	execution(t_data *data)
{
	int	j;

	j = pipes_num(data);
	printf("Pipes: %i\n", j);
	if (pipes_num(data) != 0)
		printf("exec pipe\n");
		//execution_pipe(data);
	else
		printf("exec single\n");
		//execution_single(data);
}
