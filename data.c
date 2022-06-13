/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:31:33 by yukim             #+#    #+#             */
/*   Updated: 2022/06/13 11:56:45 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data	*data;

int	init_data() // data malloc
{
	
}

int	reset_data() // data 내부의 주소가 NULL이 아니면 FREE(단, 현재 명령어 관련만 => envv_lst제외)
{

}

int	free_data() // data  envv_lst포함 모두 FREE
{
	
}
