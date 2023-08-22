#include "./includes/minishell.h"

enum e_type	get_type(char *str, int i)
{
	if (str[0] == '\"')
		return (D_QUOTE);
	else if (str[0] == '\'')
		return (S_QUOTE);
	else
		return (GENERIC);
}
