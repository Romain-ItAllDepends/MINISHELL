/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:22:31 by tebandam          #+#    #+#             */
/*   Updated: 2024/06/22 15:38:04 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void    free_child_process(t_vars *vars, t_redirection *redirect
        , t_env **env)
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

int    child_process(t_vars *vars, t_redirection *redirect
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
	if (access(actual_cmd[0], X_OK) == 0)
    	execve(actual_cmd[0], actual_cmd, vars->env);
    ft_close_fd(vars);
    error_close_files(redirect);
    exit(1);
}

// void	error_close_files(t_redirection *redirect)
// {
// 	if (redirect->infile_fd != -1)
// 	{
// 		close(redirect->infile_fd);
// 		redirect->infile_fd = -1;
// 	}
// 	if (redirect->outfile_fd != -1)
// 	{
// 		close(redirect->outfile_fd);
// 		redirect->outfile_fd = -1;
// 	}
// }

// void	close_pipe_odd(t_vars *vars)
// {
// 	if (vars->pipe_1[1] != -1)
// 	{
// 		close(vars->pipe_1[1]);
// 		vars->pipe_1[1] = -1;
// 	}
// 	if (vars->pipe_2[0] != -1)
// 	{
// 		close(vars->pipe_2[0]);
// 		vars->pipe_2[0] = -1;
// 	}
// }

// void	close_pipe_even(t_vars *vars)
// {
// 	if (vars->pipe_1[0] != -1)
// 	{
// 		close(vars->pipe_1[0]);
// 		vars->pipe_1[0] = -1;
// 	}
// 	if (vars->pipe_2[1] != -1)
// 	{
// 		close(vars->pipe_2[1]);
// 		vars->pipe_2[1] = -1;
// 	}
// }

void	handle_pipe_closing(t_vars *vars)
{
	if ((vars->cmd_index - 1) % 2 == 1 && vars->nb_cmd > 1)
		close_pipe_odd(vars);
	if ((vars->cmd_index - 1) % 2 == 0 && vars->nb_cmd > 1)
		close_pipe_even(vars);
}
