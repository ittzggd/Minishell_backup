/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_message.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 13:45:09 by hejang            #+#    #+#             */
/*   Updated: 2022/06/26 17:07:16 by yukim            ###   ########.fr       */
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
