/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:16:48 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/09 06:54:41 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	handle_initial_checks(char **command, t_vars *vars)
{
	if (!command[1])
	{
		write (1, "\n", 1);
		return (0);
	}
	if (print_value_exit_status(command) == 0)
	{
		printf("%d\n", vars->exit_code);
		return (0);
	}
	return (1);
}

int	ft_echo(char **command, t_vars *vars, t_redirection *redirect)
{
	int	no_newline;
	int	i;

	i = 1;
	no_newline = 0;
	if (!handle_initial_checks(command, vars))
		return (0);
	while (command && command[i] && command[i][0] == '-'
		&& ft_count_char(command[i], 'n')
		== ft_strlen(command[i]) - 1)
	{
		i++;
		no_newline = 1;
	}
	if (vars->nb_cmd == 1)
		echo_not_fd(command, i);
	else
		echo_in_fd(command, redirect->outfile_fd, i);
	if (!no_newline)
		write (1, "\n", 1);
	return (0);
}
