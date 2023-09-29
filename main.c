/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:11:03 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/09/28 14:49:59 by ccosta-c         ###   ########.fr       */
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
		return (printf("minishell: %s: No such file or directory\n", argv[1]));
	get_prompt(&data);
	handle_signals();
	data.env = NULL;
	data.export = NULL;
	data.paths = NULL;
	data.top = NULL;
	copy_envp(&data, envp);
	data.pwd = get_variable("PWD", data.env, count_variables(data.env));
	data.old_pwd = get_variable("OLDPWD", data.env, count_variables(data.env));
	data.home = get_variable("HOME", data.env, count_variables(data.env));
	data.stdin_fd = STDIN_FILENO;
	data.stdout_fd = STDOUT_FILENO;
	printf("out: %i in: %i\n", data.stdout_fd, data.stdin_fd);
	data.red_flag = 0;
	prompt_loop(&data);
}

void	prompt_loop(t_data *data)
{
	char	*txt;

	while (1)
	{
		txt = readline(data->prompt);
		add_history(txt);
		if ((lexer(data, txt)) == -1)
		{
			printf("exit\n");
			frees(data);
			free(txt);
			exit(g_exit);
		}
		free(txt);
		ft_cleartokens(&data->top);
	}
}
