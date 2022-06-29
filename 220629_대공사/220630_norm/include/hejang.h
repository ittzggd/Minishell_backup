/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hejang.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 02:52:58 by hejang            #+#    #+#             */
/*   Updated: 2022/06/30 03:13:22 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	    check_env(char	*token, int i, int j);
void	get_value(char *key, char *token, int key_len);
char	**create_argv(int cnt, t_astnode *argsnode);
void	command_not_found_error(char *cmd);