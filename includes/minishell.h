/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:01:41 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/10/11 17:56:44 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>

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
	char		*original_command;
	char		*prompt;
	char		**paths;
	char		**og_envp;
	char		*pwd;
	char		*old_pwd;
	char		*home;
	int			stdin_fd;
	int			stdout_fd;
	int			red_flag;
	int			pipes_nums;
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
void		free_array(char **array);
int			len_of(char *str);
int			name_variable(char *str, t_charlist *data);

////////////////////////utils2.c//////////////////////
int			check_name(char *str);
int			ft_stop_exp(char c);
int			ft_strcmp(const char *str1, const char *str2);
void		change_env_exp(t_charlist *en, t_charlist *ex, char *old, char *nw);
void		change_env_exp2(t_charlist *exp, char *old, char *new);

////////////////////////utils3.c//////////////////////
void		remove_quote_list(t_data *data);
void		remove_quote_topdata(t_data *data);
char		*remove_quote(char *data, int i, int j, char q);
int			num_of_quotes(char *data);
char		*get_variable(char *str, t_charlist *list, int size);

////////////////////////utils4.c//////////////////////
char		*get_exp(char *str, int i, t_data *data);
char		*get_tmp(char *str, int j, int k, int i);
char		*search_ex(char *str, t_charlist *list, int size, int i);
char		*join_exp_str(char *exp, char *str, int total, int j);
char		*cut_exp_str(char *str, int total, int j);

////////////////////////utils5.c//////////////////////
int			cut_str_exp(char *str, int i, int flag_s);
int			count_str_exp(char *str, int i, int flag_s);
int			check_minus_n(char *s);
char		*cut_env_exp(char *env, int j, int k);

////////////////////////lstops2.c//////////////////////
void		add_to_charlist(t_charlist **top, char *content);
t_charlist	*ft_addnew(char *content);
t_charlist	*ft_golast(t_charlist *lst);
void		delete_redirects(t_tokens **lst, char *symb);

////////////////////////lexer.c//////////////////////
int			lexer(t_data *data, char *input);
int			check_first(char *in);
int			check_second(t_data *data);
int			list_quote(char *input, int i);
void		lexer_continuation(t_data *data, char *str, int i, int j);

////////////////////////lexer2.c/////////////////////
enum e_type	get_type(char *str);
enum e_type	get_type2(char *str, int i);
int			search_quote(char *str, char q);
void		pipes_num(t_data *data);
int			pipes_num2(char *str, int i, int p);

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
int			check_exclamation(char *input, int i);
int			check_pipes(char *input);
char		check_redirect(char *input, int i, char flag);
int			check_quotes(char	*input, int i);
int			search_red(t_data *data);

//////////////////////execution.c///////////////////
void		fork_redirects(t_data *data);
int			search_red_total(t_data *data, int redi);
void		execution(t_data *data);
void		execution_single(t_data *data, int j, char **arg, int i);
char		*get_tmp_path(t_data *data, int i);

//////////////////////export.c/////////////////////
void		ft_swap(t_charlist *list);
void		export_builtin(t_charlist *list);
void		print_export(t_charlist *list, int size);
void		add_export(t_data *data);
int			count_variables(t_charlist *list);

//////////////////////builtins.c///////////////////
int			check_builtins(t_data *data);
int			check_builtins2(t_data *data);
int			check_builtins3(t_data *data);

//////////////////////execution2.c/////////////////
void		execution_pwd(t_data *data);
void		execution_env(t_data *data);
void		execution_export(t_data *data);
void		execution_unset(t_data *data);
void		execution_exit(t_data *data);

//////////////////////echo.c/////////////////////////
void		execution_echo(t_data *data);
void		simpleq_echo(char *str);
void		doubleq_echo(char *str, t_data *data);
void		echo_normal(t_data *data);
void		echo_normal2(char *str, t_data *data);

//////////////////////echo2.c////////////////////////
void		echo_minus_n(t_data *data);
int			handle_specials1(char *str, int i);
int			handle_specials2(char *str, int i, t_data *data);
int			handle_exp(char *str, int i, t_data *data);
void		search_print(char *str, t_charlist *list, int size);

//////////////////////cd.c///////////////////////////
void		cd(t_data *data, char *str);
void		cd_home_dir(t_data *data);
void		cd_minus_dir(t_data *data);
void		cd_double_dot_dir(t_data *data);
void		cd_else_dir(t_data *data, char *dir);

//////////////////////unset.c////////////////////////
void		unset_builtin(t_data *data);
void		actual_loop(t_tokens *tmp, t_data *data, t_charlist *list);

//////////////////////exit.c///////////////////////////
void		exit_builtin(t_data *data);
void		exit_builtin2(t_data *data);
int			check_exit_data(char *str);
char		*handle_whitespaces(char *input);

//////////////////////redirects.c///////////////////////
int			redirects(t_data *data, t_tokens *tmp);
int			redirects_out(t_data *data, t_tokens *lst, char *str, t_tokens *c);
int			redirects_in(t_data *data, t_tokens *n, char *str, t_tokens *c);

//////////////////////redirects_out2.c//////////////////////
int			redi_out_two_nodes(t_data *data, char *str, char *file);
int			redi_out_two_nodes_cut(t_data *data, char *str, char *temp);
int			redi_out_one_node_del(t_data *data, char *str, char *temp);
int			redi_out_no_node(t_data *data, char *temp);

//////////////////////redirects_out.c///////////////////////
int			redi_out(t_data *data, char *str, char *next_s);
int			redi_out4(t_data *data, char *str);
int			redi_out5(t_data *data, char *str);
int			redi_out2(t_data *data, char *str, char *next_s);
int			redi_out3(t_data *data, char *str);

//////////////////////redirects_utils.c//////////////////
int			redi_out_search(char *str, int i, int red);
char		*change_str(char *str, t_data *data);
char		*cut_str(char *str, t_data *data, int i, int k);
void		change_data(char *str, t_data *data, char *old);
int			cut_str2(char *str, int i, int flag_s, int flag_d);

//////////////////////redirects_utils2.c//////////////////
char		*str_exp_quote(t_data *data, char *str, int ex);
char		*cut_str_else(char *str, t_data *data, int j, int i);
void		cut_str_else2(char *str, t_data *data, int j, int k);
char		*cut_str_1(char *str, t_data *data, int i, int k);
char		*cut_str_end(char *str, t_data *data, int i, char *next_s);

//////////////////////redirects_utils3.c//////////////////
char		*cut_str_end2(char *str, t_data *data, int i, char *next_s);

//////////////////////redirects_in.c///////////////////////
int			redi_in(t_data *data, char *str, char *next_s);
int			redi_in4(t_data *data, char *str);
int			redi_in5(t_data *data, char *str);
int			redi_in2(t_data *data, char *str, char *next_s);
int			redi_in3(t_data *data, char *str);

//////////////////////redirects_in2.c//////////////////////
int			redi_in_two_nodes(t_data *data, char *str, char *file);
int			redi_in_two_nodes_cut(t_data *data, char *str, char *temp);
int			redi_in_one_node_del(t_data *data, char *str, char *temp);
int			redi_in_no_node(t_data *data, char *temp);

//////////////////////pipes.c//////////////////////
void		pipes_execution(t_data *data);
char		**pipes_commands(t_data *data);

#endif
