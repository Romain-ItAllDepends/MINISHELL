/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:21:16 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/06 15:41:18 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_error_ft_cd_home(char **command)
{
	const char	*home;

	home = getenv("HOME");
	if (command[1] == NULL)
	{
		if (home == NULL)
		{
			ft_putstr_fd("The HOME environment variable is not defined.\n", 2);
			return (1);
		}
		if (chdir(home) != 0)
		{
			ft_putstr_fd("Error when changing directory.\n", 2);
			return (1);
		}
	}
	return (0);
}

int	check_error_ft_cd(char **command)
{
	if (check_error_ft_cd_home(command) == 1)
		return (1);
	if (command[1] != NULL && command[2] != NULL)
	{
		write (2, " too many arguments\n", 20);
		return (1);
	}
	return (0);
}

t_env	*find_env_by_var_name(t_env *env, const char *var_name)
{
	t_env	*current;

	current = env;
	while (current != NULL)
	{
		if (strcmp(current->var_name, var_name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

char	*ft_chdid_and_verif(char *stock)
{
	if (chdir(stock) == -1)
	{
		ft_putstr_fd(stock, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (stock);
	}
	return (stock);
}

int	ft_cd(char **command, t_env **env)
{
	char	*path_current;
	char	*stock;
	t_env	*current;

	current = *env;
	if (check_error_ft_cd(command) == 1)
		return (1);
	current = find_env_by_var_name(*env, "OLDPWD");
	path_current = getcwd(NULL, 0);
	free(current->full_path);
	current->full_path = ft_strjoin("OLDPWD=", path_current);
	free(path_current);
	current = *env;
	current = find_env_by_var_name(*env, "PWD");
	stock = command[1];
	if (command[1])
		stock = ft_chdid_and_verif(stock);
	free(current->full_path);
	path_current = getcwd(NULL, 0);
	current->full_path = ft_strjoin("PWD=", path_current);
	free(path_current);
	return (EXIT_SUCCESS);
}
