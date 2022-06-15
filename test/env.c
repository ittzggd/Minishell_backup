/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 09:59:43 by hejang            #+#    #+#             */
/*   Updated: 2022/06/15 20:55:57 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*remove_quote(char *quote_str)
{
	char	*ret;
	int		ret_len;
	int		i;

	i = 0;
	ret_len = 0;
	while (quote_str[i])
	{
		if (!is_quote(quote_str[i]))
			ret_len++;
		i++;
	}
	if (ret_len == ft_strlen(quote_str))
		return (quote_str);
	ret = (char *)malloc(sizeof(char) * (ret_len + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while(*quote_str)
	{
		if(!is_quote(*quote_str))
		{
			ret[i] = *quote_str;
			i++;
		}
		quote_str++;
	}
	ret[i] = '\0';
	return (ret);
}

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
	if (ft_strncmp(&token[j], "$", -1)) // $
		return ;
	else if (token[j] && (token[j] == '$' && token[j + 1] == '\"')) // $"USER" => 치환 안하는 경우
	{
		data->plexer->pptokens[i] = remove_quote(&token[j + 1]);
		if(token)
			free(token);
		return ;
	}
	else if (ft_strncmp(&token[j], "\"$\"", 3)) // "$"USER, "$" => 치환 안하는 경우
	{
		data->plexer->pptokens[i] = remove_quote(&token[j]);
		if(token)
			free(token);
		return ;
	}
	else if (ft_strncmp(&token[j], "$?", -1)) // 
	{
	// 	data->plexer->pptokens[i] = ft_itoa(data->exit_status);
		return ;
	}
	else if(ft_strncmp(data->plexer->pptokens[i - 1], "<<", -1))
		return ;
	// echo "$PATH"hello => $PATH가 get_envv로 치환한 뒤 strjoin
	while (token[j] && (token[j] == '$' || (token[j] == '\"' && token[j + 1] == '$')))
		j++;
	key_len = 0;
	// while (token[j - 2] == '\"' && token[j + key_len] != '\"')  // echo $USER"hello
	// 	key_len++;
	while (token[j + key_len] && token[j + key_len] != '\"')
		key_len++;
	key = (char *)malloc(key_len + 1);
	if (key)
	{
		ft_strlcpy(key, &token[j], key_len + 1);
	// 알고보니 strlcpy에서는 dst를 할당해서 return 해주지 않는다는 사실,,, 할당해주는거로 바꿔봐야겟금,,,널가드를 lcpy에 추가했는데 맞느지 머르겟슴...아는게 멀까....
		argv = get_envv(data, key);
		if(key)
			free(key);
		if (token[j + key_len + 1] == '\0')
			data->plexer->pptokens[i] = argv;
		else
			data->plexer->pptokens[i] = ft_strjoin(argv, &token[j + key_len + 1]);
		if(token)
			free(token);
	}
}

void	insert_envv(t_data *data, char *key, char *value, int init_flag) // export시 환경변수 설정
{
	t_envv_node	element;
	t_envv_node	*is_exist;
	t_envv_node	*new;
	
	// if (data->envv_list)
		is_exist = get_el_node(data->envv_list, key);
	// else
	// 	is_exist = NULL;
	if (is_exist)
	{
		if (is_exist->value)
			free(is_exist->value);
		is_exist->value = ft_strdup(value);
	}
	else
	{
		element.key = key;
		element.value = value;
		element.init_flag = init_flag;
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

	// if(!envv_list)
	// 	return (NULL);
	curr = envv_list;
	while (curr)
	{
		if (ft_strncmp(key, curr->key, ft_strlen(key)))
			break ;
		curr = curr->p_link;
	}
	return (curr);
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
		ft_strlcpy(*key, input, p_equal - input + 1);
		*value = ft_strdup(p_equal + 1);
		if (!(*value))
			return (ERROR);
	}
	else
	{
		*key = input;
		*value = NULL;
	}
	return (init_flag);
}
