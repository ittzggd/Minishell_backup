/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:01:46 by yukim             #+#    #+#             */
/*   Updated: 2022/06/09 10:39:27 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	ft_atoi(const char *str, t_data *data, t_astnode *args_node)
{
	size_t	n;
	int	negative;

	n = 0;
	negative = 1;
	if (*str == '-')
		negative = negative * (-1);
	if (*str == '-' || *str == '+')
		str++;
	if (!ft_isdigit(*str))
		ft_error();
	while (*str >= '0' && *str <= '9' && *str != '\0')
	{
		n = (n * 10) + (*str - '0');
		str++;
	}
	if ((n * negative) > LLONG_MAX)
	{
		exit_status_numeric_error(data, args_node);
	}
	else if ((n * negative) < LLONG_MIN)
	{
		printf("numeric argument required");
		return (255);
	}
	if ((*str <= '0' || *str >= '9') && *str != '\0')
		ft_error();
	return ((n * negative));
}
