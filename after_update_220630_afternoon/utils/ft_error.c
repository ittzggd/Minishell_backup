/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 06:48:55 by hejang            #+#    #+#             */
/*   Updated: 2022/07/01 13:03:52 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_error_message(char *message, int exit_status)
{
	int	len;

	len = ft_strlen(message);
	write(2, message, len);
	data.exit_status = exit_status;
}


void	ft_error(char *error_msg)
{
	ft_error_message(error_msg, 1);
	exit(data.exit_status);
}
