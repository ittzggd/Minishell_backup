/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 19:20:08 by yukim             #+#    #+#             */
/*   Updated: 2022/05/27 19:20:08 by yukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	*ft_memset(void *s, int c, size_t n)
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

static void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t number, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(number * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, (number * size));
	return (ptr);
}