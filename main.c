/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:11:03 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/07/10 18:09:30 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*txt;


	(void)argc;
	(void)argv;
	(void)envp;
	get_prompt(&data);
	while (1)
	{

		txt = readline(data.prompt);
		printf("%s\n", txt);
	}
}
