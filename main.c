/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:11:03 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/07/06 12:07:27 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*txt;
	int		i;

	i = 0;
	(void)argc;
	(void)argv;
	(void)envp;
	copy_envp(&data, envp);
	while (data.env[i])
	{
		printf("%s\n", data.env[i]);
		i++;
	}
	while (1)
	{
		data.prompt = getcwd(data.prompt, 0);
		txt = readline(data.prompt);
		printf("%s\n", txt);
	}
}
