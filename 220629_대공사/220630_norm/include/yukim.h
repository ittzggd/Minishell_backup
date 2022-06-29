/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yukim.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 03:03:14 by yukim             #+#    #+#             */
/*   Updated: 2022/06/30 04:13:54 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

void    syntax_error(int *ret_status);
void    syntax_check_command(int *curr);
void    syntax_check_option(int *curr,  int *ret_status);
void    syntax_check_redirection(int *curr, int *ret_status);
void    syntax_check_pipe(int *curr,  int *ret_status);
void    syntax_check_null(int *curr,  int *ret_status);
void	calloc_nullcheck(void **address, int count, int size);
void	free_all_in_data(void);
void	free_data_envvlist(void);