/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:20:13 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/07/10 18:38:49 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

/// Builds the prompt with all the information obtain to replicate the
/// original bash.
/// \param data the main structure of minishell.
void	get_prompt(t_data *data)
{
	char	*user;
	char	*tmp2;
	char	*tmp1;
	char	*path;

	user = getenv("USER");
	tmp1 = get_pc_id();
	tmp2 = ft_strjoin(user, tmp1);
	free(tmp1);
	tmp1 = ft_strjoin(tmp2, ":~");
	path = get_path();
	free(tmp2);
	tmp2 = ft_strjoin(tmp1, path);
	data->prompt = ft_strjoin(tmp2, "$ ");
	free(tmp1);
	free(tmp2);
	free (path);
}

/// Obtains the pc id of the school computers.
/// \return the pc id in a string format.
char	*get_pc_id(void)
{
	char	*session_manager;
	char	*result;
	int		i;
	int		j;

	j = 0;
	i = 0;
	session_manager = getenv("SESSION_MANAGER");
	while (session_manager[i] != 47 && session_manager[i])
		i++;
	result = malloc(sizeof(char) * 8);
	i++;
	result[j++] = '@';
	while (session_manager[i] != '.' && session_manager[i])
	{
		result[j] = session_manager[i];
		i++;
		j++;
	}
	result[j] = '\0';
	return (result);
}

/// Obtains the path we are currently in with our minishell.
/// \return the path in a string format.
char	*get_path(void)
{
	char	*result;
	char	*tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	tmp = getcwd(0, 0);
	while (tmp[i])
	{
		if (tmp[i] == 47)
			j++;
		if (j == 4)
			break ;
		i++;
	}
	result = strdup(tmp + i);
	return (result);
}
