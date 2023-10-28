/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:01:41 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/10/28 11:52:44 by ccosta-c         ###   ########.fr       */
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

typedef struct s_charlst
{
	char				*content;
	struct s_charlst	*next;
}			t_charlst;

typedef struct s_tokens
{
	char			*data;
	int				len;
	enum e_type		type;
	struct s_tokens	*next;
}			t_tokens;

typedef struct s_data
{
	t_charlst	*env;
	t_charlst	*export;
	pid_t		*pid;
	char		*og_command;
	char		*prompt;
	char		**paths;
	char		**og_envp;
	char		*pwd;
	char		*old_pwd;
	char		*home;
	char		*heredoc;
	char		*tmp_r;
	char		*h;
	int			sti;
	int			lst_size;
	int			*pipes_fds;
	int			stdin_fd;
	int			stdout_fd;
	int			red_flag;
	int			pipes_nums;
	int			red_n;
	char		*fd_out;
	int			o_flag_out;
	t_tokens	*top;
}			t_data;

////////////////////////main.c//////////////////////
void		prompt_loop(t_data *data);
void		init_stuff(t_data *data, char **envp);

////////////////////////prompt.c//////////////////////
void		get_prompt(t_data *data);
char		*get_pc_id(void);
char		*get_path(void);

////////////////////////lstops.c//////////////////////
void		copy_envp(t_data *data, char **envp);
t_tokens	*initialize_tokens(int end, int start, char *arg);
void		add_to_list(t_tokens **lst, t_tokens *new);
void		ft_cleartokens(t_tokens **lst);
void		ft_clearcharlist(t_charlst **lst);

////////////////////////utils.c//////////////////////
char		**list_to_array(t_data *data);
void		get_envpaths(t_data *data);
void		free_array(char **array);
int			len_of(char *str);
int			name_variable(char *str, t_charlst *lst, t_data *data);

////////////////////////utils2.c//////////////////////
int			check_name(char *str);
int			ft_stop_exp(char c);
int			ft_strcmp(const char *str1, const char *str2);
void		change_env_exp(t_charlst *en, t_charlst *ex, char *old, char *nw);
void		change_env_exp2(t_charlst *exp, char *old, char *new);

////////////////////////utils3.c//////////////////////
void		remove_quote_list(t_data *data);
void		remove_quote_topdata(t_data *data);
char		*remove_quote(char *data, int i, int j, char q);
int			num_of_quotes(char *data);
char		*get_variable(char *str, t_charlst *list, int size);

////////////////////////utils4.c//////////////////////
char		*get_exp(char *str, int i, t_data *data);
char		*get_tmp(char *str, int j, int k, int i);
char		*search_ex(char *str, t_charlst *list, int size, int i);
char		*join_exp_str(char *exp, char *str, int total, int j);
char		*cut_exp_str(char *str, int total, int j);

////////////////////////utils5.c//////////////////////
int			cut_str_exp(char *str, int i, int flag_s);
int			count_str_exp(char *str, int i, int flag_s);
int			check_minus_n(char *s);
char		*cut_env_exp(char *env, int j, int k);
int			minus(char *s);

////////////////////////utils6.c//////////////////////
void		signal_default(t_data *data);
int			check_not_exc(char *in);
int			ecomercial_search(char *str, int i, int e);
int			backslash_search(char *str, int i, int b);
int			semicolon_search(char *str, int i, int s);

////////////////////////lstops2.c//////////////////////
void		add_to_charlist(t_charlst **top, char *content);
t_charlst	*ft_addnew(char *content);
t_charlst	*ft_golast(t_charlst *lst);
int			delete_redirects(t_tokens **lst, char *symb, t_data *data, int i);
int			get_size_lst(t_data *data);

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
void		print_lstchar(t_charlst *data);
int			ck_whitespaces(char *in);

//////////////////////signals.c//////////////////////
void		handle_signals(void);
void		handler(int sig);
void		handler_sigint2(int sig, void *data);
void		get_exit_status_arr(t_data *data, int *pids);
void		get_exit_status_one(int pids, t_data *data);

//////////////////////frees.c////////////////////////
void		frees(t_data *data);
void		frees2(t_data *data);
int			open_heredoc(char *h);
void		open_fd_out(t_data *data);
void		handler_sigint(int sig);

//////////////////////first_checks.c/////////////////
int			check_exclamation(char *input, int i);
int			check_pipes(char *input);
char		check_redirect(char *input, int i, char flag);
int			check_quotes(char	*input, int i);
int			search_red(t_data *data);

//////////////////////execution.c///////////////////
void		execution(t_data *data);
int			execution_single(t_data *data, int j, char **arg, int i);
char		*get_tmp_path(t_data *data, int i, char **arg);
void		cut_top_data_b(char *str, char **arg, size_t f);
void		print_error(char *arg, char *erro);

//////////////////////export.c/////////////////////
void		ft_swap(t_charlst *list);
void		export_builtin(t_charlst *list, int i);
void		print_export(t_charlst *list, int size, int i);
void		add_export(t_data *data);
int			count_variables(t_charlst *list);

//////////////////////builtins.c///////////////////
void		fork_redirects(t_data *data, int redi);
int			search_red_total(t_data *data, int redi);
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
int			execution_echo(t_data *data);
void		simpleq_echo(char *str);
void		doubleq_echo(char *str, t_data *data);
void		echo_normal(t_data *data);
void		echo_normal2(char *str, t_data *data);

//////////////////////echo2.c////////////////////////
void		echo_minus_n(t_data *data);
int			handle_specials1(char *str, int i);
int			handle_specials2(char *str, int i, t_data *data);
int			handle_exp(char *str, int i, t_data *data);
void		search_print(char *str, t_charlst *list, int size);

//////////////////////cd.c///////////////////////////
int			cd(t_data *data, char *str);
void		cd_home_dir(t_data *data);
void		cd_minus_dir(t_data *data);
void		cd_double_dot_dir(t_data *data);
void		cd_else_dir(t_data *data, char *dir);

//////////////////////unset.c////////////////////////
void		unset_builtin(t_data *data);
void		actual_loop(t_tokens *tmp, t_data *data, t_charlst *list);
void		else_unset(t_data *data, t_charlst *actl, t_charlst *prv, int i);
void		handle_exit_pipes(t_data *data, long long e);
int			unset_checks(char *data);

//////////////////////exit.c///////////////////////////
void		exit_builtin(t_data *data);
void		exit_builtin2(t_data *data);
int			check_exit_data(char *str);
char		*handle_whitespaces(char *input);
size_t		ft_nlen(long long n);

//////////////////////redirects.c///////////////////////
int			redirects(t_data *data, t_tokens *tmp);
int			redirects_out(t_data *data, t_tokens *lst, char *str, t_tokens *c);
int			redirects_in(t_data *data, t_tokens *n, char *str, t_tokens *c);
int			redirects_here(t_data *data, t_tokens *n, t_tokens *c);
int			redirects_append(t_data *data, t_tokens *n, char *str, t_tokens *c);

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
char		*change_str(char *str, t_data *data, int j);
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
char		*cut_str_here(char *str, t_data *data, int i, int k);
char		*cut_str_end_here(char *str, t_data *data, int i, char *next_s);
char		*cut_str_end2_here(char *str, t_data *data, int i, char *next_s);
char		*change_str_here(char *str, int j);

//////////////////////redirects_utils4.c//////////////////
char		*cut_str_else_here(char *str, t_data *data, int j, int i);
void		cut_str_else2_here(char *str, t_data *data, int j, int k);
char		*cut_str_1_here(char *str, t_data *data, int i, int k);
char		*cut_str_append(char *str, t_data *data, int i, int k);
char		*cut_str_end_append(char *str, t_data *data, int i, char *next_s);

//////////////////////redirects_utils5.c//////////////////
char		*cut_str_end2_append(char *str, t_data *data, int i, char *next_s);
char		*cut_str_else_append(char *str, t_data *data, int j, int i);
void		cut_str_else2_append(char *str, t_data *data, int j, int k);
char		*cut_str_1_append(char *str, t_data *data, int i, int k);

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

//////////////////////redirects_heredoc.c///////////////////////
int			redi_heredoc(t_data *data, char *str, char *next_s, char *h);
int			redi_here4(t_data *data, char *str, char *h);
int			redi_here5(t_data *data, char *str, char *h);
int			redi_here2(t_data *data, char *str, char *next_s, char *h);
int			redi_here3(t_data *data, char *str, char *h);

//////////////////////redirects_heredoc2.c//////////////////////
int			redi_here_two_nodes(t_data *data, char *str, char *file, char *h);
int			do_here(char *hered, char *h, t_data *data, int fd_file);
int			redi_here_two_n_cut(t_data *data, char *str, char *here, char *h);
int			redi_here_one_n_del(t_data *data, char *str, char *here, char *h);
int			redi_here_no_node(t_data *data, char *here, char *h);

//////////////////////redirects_append.c///////////////////////
int			redi_append(t_data *data, char *str, char *next_s);
int			redi_append4(t_data *data, char *str);
int			redi_append5(t_data *data, char *str);
int			redi_append2(t_data *data, char *str, char *next_s);
int			redi_append3(t_data *data, char *str);

//////////////////////redirects_append2.c//////////////////////
int			redi_append_two_nodes(t_data *data, char *str, char *file);
int			redi_append_two_nodes_cut(t_data *data, char *str, char *temp);
int			redi_append_one_node_del(t_data *data, char *str, char *temp);
int			redi_append_no_node(t_data *data, char *temp);

//////////////////////pipes.c//////////////////////
void		pipes_execution(t_data *data);
int			execute_pipes_command(t_data *data, char **commands, int i);
void		redirect(int fd_in, int fd_out);
void		pipes_wiring(t_data *data, int i);
void		execve_pipes(t_data *data, char **arg, int i, char **commands);

//////////////////////pipes_utils.c//////////////////////

int			lexer_pipes(t_data *data, char **commands, int i);
void		execution_pipes(t_data *data, char **commands);
void		reset_fd(t_data *data);
void		pipe_closing(t_data *data);

//////////////////////pipes_utils2.c//////////////////////

char		**pipes_commands_aux(t_data *data);
char		**pipes_commands(t_data *data, int i, int j, int k);
void		first_pipes_cmd_check(char original_command, bool *quotes);
void		free_child(t_data *data, char **array);

//////////////////////export_2.c//////////////////////
void		check_if_exists(t_data *data, char *tmp);
int			execution_checks(char *data);

////////////////////////utils7.c//////////////////////
int			write_here(char *in, t_data *data, int fd_file);
void		write_here2(char *in, int fd_file);
int			count_exp(char *in, int i);
int			cut_exp(char *str, t_data *data);
char		*get_exp_here(char *str, int i, t_data *data);

#endif
