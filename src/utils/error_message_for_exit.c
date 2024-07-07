/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message_for_exit.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:39:20 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/07 15:11:17 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit_message_0(void)
{
	printf("exit\n");
}

void	ft_exit_message_argument_required(char *command)
{
	ft_putstr_fd("exit\nminishell: exit: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}
