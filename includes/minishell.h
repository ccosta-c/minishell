/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:01:41 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/07/24 15:22:04 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
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
	t_tokens	*top;
}			t_data;

////////////////////////prompt.c//////////////////////
void		get_prompt(t_data *data);
char		*get_pc_id(void);
char		*get_path(void);

////////////////////////utils.c//////////////////////
void		copy_envp(t_data *data, char **envp);
t_tokens	*initialize_tokens(int end, int start, char *arg);
void		add_to_list(t_tokens **lst, t_tokens *new);

////////////////////////lexer.c//////////////////////
int			lexer(t_data *data, char *input);

//////////////////////debugging.c////////////////////
void	print_list(t_data *data);

#endif
