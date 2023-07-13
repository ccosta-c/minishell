/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:01:41 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/07/13 14:44:50 by ccosta-c         ###   ########.fr       */
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

enum	e_tokens
{
	WORD = 'w',
	WHITE_SPACE = ' ',
	DOUBLE_QUOTE = '\"',
	SINGLE_QUOTE = '\'',
	ESCAPE = '\\',
	PIPES = '|',
	REDIRECT_IN = '<',
	REDIRECT_OUT = '>',
	ENV = '$',
	NEW_LINE = '\n',
	HERE_DOC,
};

enum	e_type
{
	GENERIC,
	D_QUOTE,
	S_QUOTE,
	CMD,
};

typedef struct s_tokens
{
	char			*data;
	int				len;
	enum e_tokens	tokens;
	enum e_type		type;
	struct s_tokens	*next;
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

////////////////////////lexer.c//////////////////////
void	initialize_tokens(t_tokens *node, int end, int start, char *arg);

#endif
