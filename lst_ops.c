/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:18:24 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/09/28 15:27:30 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

/// Copies the envp sent by the main function to an 2D array.
/// \param data the minishell main structure.
/// \param envp the environment variables sent by the main.
void	copy_envp(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		add_to_charlist(&data->env, envp[i]);
		add_to_charlist(&data->export, envp[i]);
		i++;
	}
}

/// Initializes the tokens node and attributes the data and the
/// len parameters of the node.
/// \param end the end of the string excerpt to copy.
/// \param start the start of the string excerpt to copy.
/// \param arg the string from which to copy.
/// \return the tokens node with all the values initialized and
/// the data and len already filled.
t_tokens	*initialize_tokens(int end, int start, char *arg)
{
	t_tokens	*tmp;
	int			i;

	i = 0;
	tmp = malloc(sizeof(t_tokens));
	tmp->next = NULL;
	tmp->data = malloc(sizeof(char) * ((end - start) + 1));
	while (start < end)
	{
		tmp->data[i] = arg[start];
		start++;
		i++;
	}
	tmp->data[i] = '\0';
	tmp->type = get_type(tmp->data, 0);
	tmp->len = ft_strlen(tmp->data);
	return (tmp);
}

/// this function adds a node to the tokens list.
/// \param lst a pointer to the top of the list.
/// \param new the new content to be added.
void	add_to_list(t_tokens **lst, t_tokens *new)
{
	t_tokens	*ptr;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			ptr = *lst;
			while (ptr->next != NULL)
				ptr = ptr->next;
			ptr->next = new;
		}
	}
}

/// deletes all the nodes from the tokens structure.
/// \param lst the tokens structure.
void	ft_cleartokens(t_tokens **lst)
{
	t_tokens	*temp;
	t_tokens	*prox;

	if (!lst)
		return ;
	temp = *lst;
	while (temp)
	{
		prox = temp->next;
		free(temp->data);
		free(temp);
		temp = prox;
	}
	*lst = NULL;
}
