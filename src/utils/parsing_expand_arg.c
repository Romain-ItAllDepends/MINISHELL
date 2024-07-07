/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expand_arg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 11:21:36 by rgobet            #+#    #+#             */
/*   Updated: 2024/07/06 11:38:53 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	rest_argument(t_char_list **tmp_char,
	t_char_list **splitted_chars)
{
	t_bool		in_quote;
	t_char_list	*arg;
	char		quote;

	arg = NULL;
	quote = 0;
	in_quote = FALSE;
	while (*tmp_char && (*tmp_char)->value != ' '
		&& (*tmp_char)->value != '\t' && (*tmp_char)->value != '\n'
		&& in_quote == FALSE)
	{
		fill_not_expand_arg(tmp_char, splitted_chars, &in_quote, &quote);
		fill_expanded_arg(tmp_char, splitted_chars);
	}
}

int	set_last_point(t_argument **tmp, t_char_list **tmp_char)
{
	while (*tmp_char && ((*tmp_char)->value == SPACE
			|| (*tmp_char)->value == TAB || (*tmp_char)->value == NEWLINE))
		*tmp_char = (*tmp_char)->next;
	if (*tmp_char == NULL)
	{
		*tmp = (*tmp)->next;
		if (*tmp != NULL)
			*tmp_char = (*tmp)->chars;
	}
	if (*tmp == NULL)
		return (0);
	(*tmp_char)->last_pos = TRUE;
	return (1);
}

void	set_var(t_argument *tmp, t_char_list **tmp_char)
{
	*tmp_char = tmp->chars;
	while (*tmp_char && (*tmp_char)->last_pos == FALSE)
		*tmp_char = (*tmp_char)->next;
	(*tmp_char)->last_pos = FALSE;
}
