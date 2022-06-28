/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 01:24:22 by yukim             #+#    #+#             */
/*   Updated: 2022/06/25 01:24:22 by yukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*copy;

	copy = (unsigned char *)s;
	while (n > 0)
	{
		*(copy++) = (unsigned char)c;
		n--;
	}
	return (s);
}