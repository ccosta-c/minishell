/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:11:03 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/08/01 16:51:36 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	g_exit;

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*txt;

	(void)argv;
	(void)envp;
	if (argc > 1)
		return (printf("Wrong arguments!\n"));
	get_prompt(&data);
	handle_signals();
	while (1)
	{
		txt = readline(data.prompt);
		add_history(txt);
		if ((lexer(&data, txt)) == -1)
		{
			printf("exit\n");
			return (frees(&data), free(txt), 0);
		}
		ft_cleartokens(&data.top);
	}
}
