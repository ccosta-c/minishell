/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:11:03 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/10/11 19:27:27 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	g_exit;

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	if (argc > 1)
		return (printf("minishell: %s: No such file or directory\n", argv[1]));
	get_prompt(&data);
	handle_signals();
	init_stuff(&data, envp);
	prompt_loop(&data);
}

void	init_stuff(t_data *data, char **envp)
{
	int	cv;

	data->env = NULL;
	data->export = NULL;
	data->paths = NULL;
	data->og_command = NULL;
	data->top = NULL;
	data->og_envp = envp;
	copy_envp(data, envp);
	cv = count_variables(data->env);
	data->pwd = get_variable("PWD", data->env, cv);
	data->old_pwd = get_variable("OLDPWD", data->env, cv);
	data->home = get_variable("HOME", data->env, cv);
	data->stdin_fd = STDIN_FILENO;
	data->stdout_fd = STDOUT_FILENO;
	data->red_flag = 0;
	data->red_n = 0;
	data->fd_out = NULL;
	data->o_flag_out = 0;
	data->heredoc = NULL;
	data->tmp_r = NULL;
	data->h = NULL;
	data->sti = 0;
}

void	prompt_loop(t_data *data)
{
	char	*txt;

	while (1)
	{
		handle_signals();
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
