/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:35 by yukim             #+#    #+#             */
/*   Updated: 2022/06/09 17:45:39 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

int	ft_export(t_data *data, t_astnode *args_node) // export USER=1 HI=2 HOME=3
{
	char	*input;
	char	*key;
	char	*value;
	char	*p_equal;
	int		init_flag;
	int		i;

	init_flag = FALSE;
	data->exit_status = 0;
	input = data->plexer->pptokens[args_node->pvalue_index[1]];
	if(!input) // 아스키 코드순으로 출력 = env 실행
	{
		ft_env(data, TRUE);
		return (data->exit_status);	 // exit_status : 성공
	}
	i = 1;
	while (args_node->pvalue_index[i] != -1)
	{
		input = remove_quote(data->plexer->pptokens[args_node->pvalue_index[i]]);
		if (init_envp(input, &key, &value) == ERROR)
		{
			data->exit_status = 1;
			return (data->exit_status);
		}
		if (!is_valid_env(key))
		{
			data->exit_status = 1;
			return (data->exit_status);
		}
		insert_envv(data, key, value);
		if (!value)
			continue ;
		else
		{
			free(key);
			free(value);
		}
	}
}

int	init_envp(char *input, char **key, char **value)
{
	int		i;
	int		init_flag;
	char	*p_equal;

	p_equal = ft_strchr(input, '=');
	if (p_equal) // 키와 값 저장
	{
		init_flag = TRUE;
		// 키와 값을 분리하기 == ft_split시 = 기준 분린
		*key = (char *)ft_calloc(p_equal - input + 1, sizeof(char));
		if (!(*key))
			return (ERROR);
		*key = ft_strlcpy(*key, input, p_equal - input + 1);
		*value = ft_strdup(p_equal + 1);
		if (!(*value))
			return (ERROR);
	}
	else
	{
		*key = input;
		*value = NULL;
	}
	return (0);
}