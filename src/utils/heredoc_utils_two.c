/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:40:40 by rgobet            #+#    #+#             */
/*   Updated: 2024/07/07 16:01:42 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	quit(int sig_num)
{
	g_sig = sig_num + 128;
}

void	complete_heredoc(t_redirection *redirection,
	t_command_line_parsing *tmp_command, t_env *env, t_vars *vars)
{
	if (redirection->nb_heredoc && redirection->infile_fd != -1)
		heredoc_setup(redirection, tmp_command, env, vars);
	else
		perror("Error opening heredoc files");
}
