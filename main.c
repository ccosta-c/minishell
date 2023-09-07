/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:11:03 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/09/06 12:44:48 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	g_exit;

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	(void)envp;
	if (argc > 1)
		return (printf("Wrong arguments!\n"));
	get_prompt(&data);
	handle_signals();
	data.env = NULL;
	data.export = NULL;
	copy_envp(&data, envp);
	prompt_loop(&data);
}

void	prompt_loop(t_data *data)
{
	char	*txt;

	while (1)
	{
		txt = readline(data->prompt);
		add_history(txt);
		if ((lexer(data, txt, 0, 0)) == -1)
		{
			printf("exit\n");
			frees(data);
			free(txt);
			exit(0);
		}
		ft_cleartokens(&data->top);
	}
}
