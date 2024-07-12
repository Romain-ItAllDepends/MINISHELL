/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split_argument.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:56:30 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/12 10:48:55 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	fill_in_quote_arg(t_char_list **tmp_char,
	t_char_list **splitted_chars, char quote)
{
	t_char_list	*arg;

	arg = NULL;
	if (*tmp_char && (*tmp_char)->value != quote)
	{
		arg = lst_new_char_list();
		if (!arg)
			return ;
		arg->value = (*tmp_char)->value;
		arg->was_in_a_variable = (*tmp_char)->was_in_a_variable;
		ft_lstadd_back_char_list(splitted_chars, arg);
		(*tmp_char)->last_pos = FALSE;
		*tmp_char = (*tmp_char)->next;
	}
	else if (*tmp_char)
		*tmp_char = (*tmp_char)->next;
}

static void	fill_arg(t_char_list **tmp_char,
	t_char_list **splitted_chars)
{
	t_char_list	*arg;

	arg = NULL;
	if (*tmp_char)
	{
		arg = lst_new_char_list();
		if (!arg)
			return ;
		arg->value = (*tmp_char)->value;
		arg->was_in_a_variable = (*tmp_char)->was_in_a_variable;
		ft_lstadd_back_char_list(splitted_chars, arg);
		(*tmp_char)->last_pos = FALSE;
		*tmp_char = (*tmp_char)->next;
	}
}

void	fill_expanded_arg(t_char_list **tmp_char,
	t_char_list **splitted_chars, char *quote)
{
	while (*tmp_char && (*tmp_char)->was_in_a_variable == TRUE)
	{
		if ((*tmp_char)->value == SPACE
			|| (*tmp_char)->value == NEWLINE
			|| (*tmp_char)->value == TAB)
			break ;
		if (*quote && *quote == (*tmp_char)->value)
			break ;
		fill_arg(tmp_char, splitted_chars);
	}
	if (*tmp_char && *quote && *quote != (*tmp_char)->value
		&& (*tmp_char)->value != SPACE
		&& (*tmp_char)->value != NEWLINE
		&& (*tmp_char)->value != TAB)
		fill_arg(tmp_char, splitted_chars);
}

void	fill_not_expand_arg(t_char_list **tmp_char,
	t_char_list **splitted_chars, t_bool *in_quote, char *quote)
{
	while (*tmp_char && *in_quote == FALSE
		&& (*tmp_char)->was_in_a_variable == FALSE)
	{
		if (function_verif_quote(tmp_char, quote, in_quote) == 1)
			break ;
		fill_no_quote_arg(tmp_char, splitted_chars, *quote);
	}
	while (*tmp_char && *in_quote == TRUE
		&& (*tmp_char)->was_in_a_variable == FALSE)
	{
		*in_quote = quote_function(tmp_char, quote, *in_quote);
		fill_in_quote_arg(tmp_char, splitted_chars, *quote);
	}
}

int	ft_split_argument(t_argument *argument_to_split,
	t_argument **args)
{
	char		quote;
	t_char_list	*tmp_char;
	t_argument	*tmp;
	t_argument	*splitted_arguments;
	t_bool		in_quote;

	in_quote = init_function(&quote, &tmp, &splitted_arguments,
			argument_to_split);
	set_var(tmp, &tmp_char);
	fill_not_expand_arg(&tmp_char, &splitted_arguments->chars,
		&in_quote, &quote);
	rest_argument(&tmp_char, &splitted_arguments->chars, &quote);
	ft_lstadd_back_argument(args, splitted_arguments);
	if (set_last_point(&tmp, &tmp_char) == 0)
		return (0);
	return (1);
}
