/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:43:08 by hejang            #+#    #+#             */
/*   Updated: 2022/05/25 19:00:46 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*str;

	while (1)
	{
		str = readline("nanoshell >> ");
		if (str)
			printf("%s\n", str); //printf가 아니라 이후 minishell 실행 함수들로 넘어가야 함
		else
			break ; //break가 없어야 할 듯 아마 우리는 ctrl+C가 아닌 이상 prompt를 계속 띄운 상태여야 함
		add_history(str);
		free(str);
	}
	return (0);
}