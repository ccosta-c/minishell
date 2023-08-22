/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:01:41 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/08/02 16:01:54 by ccosta-c         ###   ########.fr       */
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
# include <signal.h>

extern int	g_exit;

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

////////////////////////main.c//////////////////////
void		prompt_loop(t_data *data);

////////////////////////prompt.c//////////////////////
void		get_prompt(t_data *data);
char		*get_pc_id(void);
char		*get_path(void);

////////////////////////utils.c//////////////////////
void		copy_envp(t_data *data, char **envp);
t_tokens	*initialize_tokens(int end, int start, char *arg);
void		add_to_list(t_tokens **lst, t_tokens *new);
void		ft_cleartokens(t_tokens **lst);
int			len_of(char *str);

////////////////////////lexer.c//////////////////////
int			lexer(t_data *data, char *input, int i, int j);
char		*handle_whitespaces(char *input);
int			list_quote(char *input, int i);

////////////////////////lexer2.c/////////////////////
enum e_type		get_type(char *str, int i);

//////////////////////debugging.c////////////////////
void		print_list(t_data *data);

//////////////////////signals.c//////////////////////
void		handle_signals(void);
void		handler(int sig);

//////////////////////frees.c////////////////////////
void		frees(t_data *data);

//////////////////////first_checks.c/////////////////
int         check_first(char *input);
int         check_pipes(char *input);
int         check_redirect(char *input);
int			check_quotes(char	*input, int i);

#endif
