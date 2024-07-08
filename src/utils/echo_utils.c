/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:37:59 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/08 14:59:56 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	print_value_exit_status(char **command)
{
	if (command[1][0] && command[1][0] == '$' && command[1][1] == '?')
		return (0);
	return (1);
}

void	echo_in_fd(char **command, int fd, int i)
{
	while (command[i])
	{
		ft_putstr_fd(command[i], fd);
		if (command[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
}

void	echo_not_fd(char **command, int i)
{
	while (command[i])
	{
		ft_putstr_fd(command[i], 1);
		if (command[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
}

int	ft_count_char(char *str, char to_find)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == to_find)
			count++;
		i++;
	}
	return (count);
}
