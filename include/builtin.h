/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 09:52:55 by hejang            #+#    #+#             */
/*   Updated: 2022/06/07 21:28:37 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell_define.h"

int		ft_echo(t_data *data, t_astnode *args_node);
int		ft_pwd(void);
int		ft_env(t_data *data, int export_flag);
int		ft_unset(t_data *data, t_astnode *args_node);
int		ft_export(t_data *data, t_astnode *args_node);


#endif
