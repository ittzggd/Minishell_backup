/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 09:59:43 by hejang            #+#    #+#             */
/*   Updated: 2022/06/07 17:27:05 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"



// 환경변수를 비교하여 교체
void	replace_env_to_value(int i, t_data *data)
{
	/*
	strncmp로 환경변수 목록에서 찾아오기 => get_env함수 존재
	$와 괄호를 제외한 문자열구하기 = name
	원래 환경변수 $()문자열 free!
	data->ptype[i] = T_WORD
	return (new env)  혹은 data->pptokens[i] = new env
	*/
	char	*key;
	char	*token;
	char	*argv;
	int		j;
	int		key_len;

	token = data->plexer->pptokens[i]; // $USER 혹은 "$USER"
	j = 0;
	while (token[j] && (token[j] == '$' || token[j] == '\"'))
		j++;
	key_len = ft_strlen(&token[j]);
	if (token[key_len - 1] == '\"')
		key_len--;
	key = (char *)malloc(ft_strlen(key_len) + 1);
	if (key)
	{
		ft_strlcpy(key, token[j], key_len);
	// 알고보니 strlcpy에서는 dst를 할당해서 return 해주지 않는다는 사실,,, 할당해주는거로 바꿔봐야겟금,,,널가드를 lcpy에 추가했는데 맞느지 머르겟슴...아는게 멀까....
		argv = get_envv(data, key);
		free(token);
		free(key);
		data->plexer->pptokens[i] = argv;
	}
}

void	insert_envv(t_data *data, char *key, char *value) // export시 환경변수 설정
{
	t_envv_node	element;
	t_envv_node	*is_exist;
	t_envv_node	*new;
	
	is_exist = get_el_node(data->envv_list, key);
	if (is_exist)
	{
		free(is_exist->value);
		is_exist->value = ft_strdup(value);
	}
	else
	{
		element.key = key;
		element.value = value;
		new = ft_lstnew(element);
		ft_lstadd_back(data, new);
	}
}

char	*get_envv(t_data *data, char *key)
{
	t_envv_node *key_node;

	key_node = get_el_node(data->envv_list, key);
	if(!key_node)
		return (NULL);
	return (key_node->value);
}

t_envv_node	*get_el_node(t_envv_node *envv_list, char *key)
{
	t_envv_node *curr;

	curr = envv_list;
	while (curr)
	{
		if (ft_strncmp(key, curr->key, ft_strlen(key)))
			break ;
		curr = curr->p_link;
	}
	return (curr);
}


//환경 변수 문법을 체크한 뒤, key값만 반환하는 함수
