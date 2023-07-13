/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:01:41 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/07/11 14:31:56 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int	exit_st;

enum	e_token
{
	WORD = 'w';
};

typedef struct s_tokens
{
	char	*data;
	int		len;
	enum
}			t_tokens;

typedef struct s_data
{
	char		**env;
	char		*prompt;
	t_tokens	*commands;
}			t_data;

////////////////////////prompt.c//////////////////////
void	get_prompt(t_data *data);
char	*get_pc_id(void);
char	*get_path(void);

////////////////////////utils.c//////////////////////
void	copy_envp(t_data *data, char **envp);

#endif
