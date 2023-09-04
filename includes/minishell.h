/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:01:41 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/09/04 15:47:03 by ccosta-c         ###   ########.fr       */
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
# include <sys/wait.h>

extern int	g_exit;

enum	e_type
{
	GENERIC,
	D_QUOTE,
	S_QUOTE,
	PIPE,
	R_IN,
	R_OUT,
	RR_IN,
	RR_OUT,
	CMD,
};

typedef struct s_tokens
{
	char			*data;
	int				len;
	enum e_type		type;
	struct s_tokens	*next;
}			t_tokens;

typedef struct s_data
{
	char		**env;
	char		**export;
	char		*prompt;
	char		**paths;
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

////////////////////////utils_2.c//////////////////////
char		**list_to_array(t_data *data);
void		get_envpaths(t_data *data);
void		free_array(char **array, int y);

////////////////////////lexer.c//////////////////////
int			lexer(t_data *data, char *input, int i, int j);
char		*handle_whitespaces(char *input);
int			list_quote(char *input, int i);

////////////////////////lexer2.c/////////////////////
enum e_type	get_type(char *str, int start);
int			pipes_num(t_data *data);

//////////////////////debugging.c////////////////////
void		print_list(t_data *data);
void		print_array(char **array);

//////////////////////signals.c//////////////////////
void		handle_signals(void);
void		handler(int sig);

//////////////////////frees.c////////////////////////
void		frees(t_data *data);

//////////////////////first_checks.c/////////////////
int			check_first(char *input);
int			check_pipes(char *input);
int			check_redirect(char *input);
int			check_quotes(char	*input, int i);
int			search_red(t_data *data);

//////////////////////execution.c///////////////////
void		execution(t_data *data);
void		execution_single(t_data *data, int j, char **arg);
char		*get_tmp_path(t_data *data, int i);

//////////////////////test.c///////////////////
void		ft_swap(char **a, char **b);
void		ft_putchar2(char **b, int a, int i);
void		export_builtin(char **array);
void		print_export(char **array);
void		add_export(char	**array, t_data *data);

//////////////////////builtins.c///////////////////
int			check_builtins(t_data *data);
int			check_builtins2(t_data *data);

#endif
