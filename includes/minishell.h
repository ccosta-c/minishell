/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:01:41 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/07/10 18:19:07 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_data
{
	char	**env;
	char	*prompt;

}			t_data;

////////////////////////prompt.c//////////////////////
void	get_prompt(t_data *data);
char	*get_pc_id(void);
char	*get_path(void);

////////////////////////utils.c//////////////////////
void	copy_envp(t_data *data, char **envp);

#endif