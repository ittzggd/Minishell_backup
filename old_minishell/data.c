/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:31:33 by yukim             #+#    #+#             */
/*   Updated: 2022/06/14 12:34:06 by hejang           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data	*data;

int	init_data() // data malloc
{
	// 헤더파일에 전역변수를 포인터가 아닌 t_data data로 바꾸기, 다른 함수들도 모두 ㅁㅐ개변수 수정 및 포인터참조 수정
}

int	reset_data() // data 내부의 주소가 NULL이 아니면 FREE(단, 현재 명령어 관련만 => envv_lst제외)
{

}

int	free_data() // data  envv_lst포함 모두 FREE
{
	
}
