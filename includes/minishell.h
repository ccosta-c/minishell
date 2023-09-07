/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:01:41 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/09/07 16:55:05 by ccosta-c         ###   ########.fr       */
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
	SPECIAL_QUOTE,
	PIPE,
	R_IN,
	R_OUT,
	RR_IN,
	RR_OUT,
	CMD,
};

typedef struct s_charlist
{
	char				*content;
	struct s_charlist	*next;
}			t_charlist;

typedef struct s_tokens
{
	char			*data;
	int				len;
	enum e_type		type;
	struct s_tokens	*next;
}			t_tokens;

typedef struct s_data
{
	t_charlist	*env;
	t_charlist	*export;
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

////////////////////////lstops.c//////////////////////
void		copy_envp(t_data *data, char **envp);
t_tokens	*initialize_tokens(int end, int start, char *arg);
void		add_to_list(t_tokens **lst, t_tokens *new);
void		ft_cleartokens(t_tokens **lst);

////////////////////////utils.c//////////////////////
char		**list_to_array(t_data *data);
void		get_envpaths(t_data *data);
void		free_array(char **array, int y);
int			len_of(char *str);

////////////////////////lstops2.c//////////////////////
void		add_to_charlist(t_charlist **top, char *content);
t_charlist	*ft_addnew(char *content);
t_charlist	*ft_golast(t_charlist *lst);

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
void		print_lstchar(t_charlist *data);

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

//////////////////////export.c/////////////////////
void		ft_swap(t_charlist *list);
void		export_builtin(t_charlist *list);
void		print_export(t_charlist *list, int size);
void		add_export(t_charlist *list, t_data	*data);
int			count_variables(t_charlist *list);


//////////////////////builtins.c///////////////////
int			check_builtins(t_data *data);
int			check_builtins2(t_data *data);

//////////////////////execution2.c/////////////////
void		execution_pwd(t_data *data);
void		execution_env(t_data *data);
void		execution_export(t_data *data);
void		execution_unset(t_data *data);

//////////////////////execution_echo.c///////////////
void		execution_echo(t_data *data);
void		simple_echo(char *str);
void		double_echo(char *str);
void		echo_normal(t_data *data);
void		handle_spaces_echo(char *str);

//////////////////////execution_echo2.c//////////////
void		echo_minus_n(t_data *data);

#endif
