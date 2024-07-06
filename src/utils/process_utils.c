/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:22:31 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/06 11:33:30 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	free_child_process(t_vars *vars,
	t_redirection *redirect, t_env **env)
{
	if (vars->env)
		free(vars->env);
	if (env)
		ft_lstclear_env(env);
	if (redirect)
		ft_lstclear_final_redirection(&redirect);
	if (vars->cmd)
		ft_free_tab_3d(vars);
	if (vars)
		free(vars);
}

static void	verif_or_builtins(t_vars *vars, t_redirection *redirect
	, char **actual_cmd, t_env **env)
{
	if (actual_cmd != NULL && is_builtins_exec(vars) == 1)
	{
		cmd_selector(env, vars->cmd[vars->cmd_index - 1], vars, redirect);
		free_child_process(vars, redirect, env);
		exit(0);
	}
	if (actual_cmd == NULL || actual_cmd[0][0] == 0)
	{
		free_child_process(vars, redirect, env);
		exit (0);
	}
	if (access(actual_cmd[0], X_OK) == -1)
	{
		free_child_process(vars, redirect, env);
		exit(127);
	}
}

int	child_process(t_vars *vars, t_redirection *redirect
	, char **actual_cmd, t_env **env)
{
	if (check_error_redirect_infifle_fd(redirect) == 1
		|| check_error_redirect_outfile_fd(redirect) == 1
		|| redirect->ambiguous == TRUE)
	{
		ft_close_fd(vars);
		free_child_process(vars, redirect, env);
		exit (1);
	}
	ft_flow_redirection(vars, redirect);
	ft_close_fd(vars);
	verif_or_builtins(vars, redirect, actual_cmd, env);
	execve(actual_cmd[0], actual_cmd, vars->env);
	ft_close_fd(vars);
	error_close_files(redirect);
	exit(1);
}

void	handle_pipe_closing(t_vars *vars)
{
	if ((vars->cmd_index - 1) % 2 == 1 && vars->nb_cmd > 1)
		close_pipe_odd(vars);
	if ((vars->cmd_index - 1) % 2 == 0 && vars->nb_cmd > 1)
		close_pipe_even(vars);
}
