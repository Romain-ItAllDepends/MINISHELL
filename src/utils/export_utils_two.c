/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:15:56 by rgobet            #+#    #+#             */
/*   Updated: 2024/07/01 11:38:55 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_export(char *var_name, char *value)
{
	if (var_name)
		free(var_name);
	if (value)
		free(value);
}

void	var_set(char **var_name, char **value,
	int *export_status, char *cmd)
{
	*value = NULL;
	*var_name = NULL;
	*export_status = 0;
	*export_status = verif_export(cmd);
}
