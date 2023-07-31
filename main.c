/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:11:03 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/07/27 15:12:28 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*txt;

	(void)argv;
	(void)envp;
	if (argc > 1)
		return (printf("Wrong arguments!\n"));
	handle_signals();
	get_prompt(&data);
	while (1)
	{
		txt = readline(data.prompt);
		add_history(txt);
		lexer(&data, txt);
	}
}
