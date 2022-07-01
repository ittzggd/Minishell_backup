/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 09:59:43 by hejang            #+#    #+#             */
/*   Updated: 2022/07/01 19:42:14 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

// char	*remove_quote(char *quote_str)
// {
// 	char	*ret;
// 	int		ret_len;
// 	int		i;

// 	i = 0;
// 	ret_len = 0;
// 	while (quote_str[i])
// 	{
// 		if (!is_quote(quote_str[i]))
// 			ret_len++;
// 		i++;
// 	}
// 	if (ret_len == ft_strlen(quote_str))
// 		return (quote_str);
// 	ret = (char *)malloc(sizeof(char) * (ret_len + 1));
// 	if (!ret)
// 		return (NULL);
// 	i = 0;
// 	while(*quote_str)
// 	{
// 		if(!is_quote(*quote_str))
// 		{
// 			ret[i] = *quote_str;
// 			i++;
// 		}
// 		quote_str++;
// 	}
// 	ret[i] = '\0';
// 	return (ret);
// }

// 환경변수를 비교하여 교체
void	replace_env_to_value(int i)
{
	/*
	strncmp로 환경변수 목록에서 찾아오기 => get_env함수 존재
	$와 괄호를 제외한 문자열구하기 = name
	원래 환경변수 $()문자열 free!
	data.ptype[i] = T_WORD
	return (new env)  혹은 data.pptokens[i] = new env
	*/



	char	*key;
	char	*token;
	char	*argv;
	int		j;
	int		key_len;

	token = data.lexer.pptokens[i]; // $USER 혹은 "$USER"
	
	j = 0;
	if (ft_strncmp(token, "$", -1)) // $
		return ;
	else if (token[j] && (token[j] == '$' && token[j + 1] == '\"')) // $"USER" => 치환 안하는 경우
	{
		data.lexer.pptokens[i] = remove_quote(&token[j + 1]);
		if(token)
			free(token);
		return ;
	}
	else if (ft_strncmp(token, "\"$\"", 3)) // "$"USER, "$" => 치환 안하는 경우
	{
		data.lexer.pptokens[i] = remove_quote(&token[j]);
		if(token)
			free(token);
		return ;
	}
	else if (ft_strncmp(&(token[j]), "$?", -1)) // 
	{
	// 	data.lexer.pptokens[i] = ft_itoa(data.exit_status);
		return ;
	}
	else if(ft_strncmp(data.lexer.pptokens[i - 1], "<<", -1))
		return ;
	// echo "$PATH"hello => $PATH가 get_envv로 치환한 뒤 strjoin
	while (token[j] && (token[j] == '$' || (token[j] == '\"' && token[j + 1] == '$')))
		j++;
	// while (token[j - 2] == '\"' && token[j + key_len] != '\"')  // echo $USER"hello
	// 	key_len++;
	key_len = 0;
	while (token[j + key_len])
	{
		if (!ft_is_alpha(token[j + key_len]) && (token[j + key_len] != '_') \
				&& !ft_is_digit(token[j + key_len]) && (token[j + key_len] != '?'))
			break ;
		key_len++;
	}
	key = (char *)malloc(sizeof(char) * (key_len + 1));
	if (key)
	{
		ft_strlcpy(key, &token[j], key_len + 1);
		argv = get_envv(key);

		if(key)
			free(key);
		if (token[j + key_len] == '\0')
		{
			data.lexer.pptokens[i] = argv;
		}
		else
		{
			data.lexer.pptokens[i] = ft_strjoin(argv, &token[j + key_len]);
		}
		if(token)
			free(token);
	}
}

void	insert_envv(char *key, char *value, int init_flag) // export시 환경변수 설정
{
	t_envv_node	element;
	t_envv_node	*is_exist;
	t_envv_node	*new;
	char		*tmp;
	
	is_exist = get_el_node(data.envv_list, key);
	if (is_exist)
	{
		tmp = is_exist->value;
		is_exist->value = ft_strdup(value);
		if (tmp)
			free(tmp);
	}
	else
	{
		element.key = key;
		element.value = value;
		element.init_flag = init_flag;
		new = ft_lstnew(element);
		ft_lstadd_back(new);
		data.envv_cnt++;
	}
}

char	*get_envv(char *key)
{
	t_envv_node *key_node;
	char		*ret;

	key_node = get_el_node(data.envv_list, key);
	if(!key_node)
		return (NULL);
	ret = ft_strdup(key_node->value);
	return (ret);
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


// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   env.c                                              :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/06/02 09:59:43 by hejang            #+#    #+#             */
// /*   Updated: 2022/07/01 15:04:53 by yukim            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "./include/minishell.h"

// void	replace_env_to_value(int i)
// {
// 	char	*key;
// 	char	*token;
// 	char	*argv;
// 	int		j;
// 	int		key_len;

// 	token = data.lexer.pptokens[i];
// 	j = 0;
// 	if (check_env(token, i, j) == TRUE)
// 		return ;
// 	while (token[j] && (token[j] == '$'
// 			|| (token[j] == '\"' && token[j + 1] == '$')))
// 		j++;
// 	key_len = 0;
// 	while (token[j + key_len] && token[j + key_len] != '\"')
// 		key_len++;
// 	key = ft_calloc(key_len + 1, sizeof(char));
// 	if (!key)
// 		ft_error("replace_env_to_value : allocation failed\n");
// 	if (key)
// 		get_value(key, token, key_len, i, j);
// }

// void	insert_envv(char *key, char *value, int init_flag)
// {
// 	t_envv_node	element;
// 	t_envv_node	*is_exist;
// 	t_envv_node	*new;

// 	is_exist = get_el_node(data.envv_list, key);
// 	if (is_exist)
// 	{
// 		if (is_exist->value)
// 			free(is_exist->value);
// 		is_exist->value = ft_strdup(value);
// 	}
// 	else
// 	{
// 		element.key = key;
// 		element.value = value;
// 		element.init_flag = init_flag;
// 		new = ft_lstnew(element);
// 		ft_lstadd_back(new);
// 		data.envv_cnt++;
// 	}
// }

// char	*get_envv(char *key)
// {
// 	t_envv_node	*key_node;

// 	key_node = get_el_node(data.envv_list, key);
// 	if (!key_node)
// 		return (NULL);
// 	return (key_node->value);
// }

// t_envv_node	*get_el_node(t_envv_node *envv_list, char *key)
// {
// 	t_envv_node	*curr;

// 	curr = envv_list;
// 	while (curr)
// 	{
// 		if (ft_strncmp(key, curr->key, ft_strlen(key)))
// 			break ;
// 		curr = curr->p_link;
// 	}
// 	return (curr);
// }

// int	init_envp(char *input, char **key, char **value)
// {
// 	int		i;
// 	int		init_flag;
// 	char	*p_equal;

// 	init_flag = FALSE; // 220701 added : maybe NUll is user init? or auto setting? distinguish
// 	p_equal = ft_strchr(input, '=');
// 	if (p_equal)
// 	{
// 		init_flag = TRUE;
// 		*key = ft_calloc(p_equal - input + 1, sizeof(char));
// 		if(!*key)
// 			ft_error("init_envp : allocation failed");
// 		ft_strlcpy(*key, input, p_equal - input + 1);
// 		*value = ft_strdup(p_equal + 1);
// 	}
// 	else
// 	{
// 		*key = input;
// 		*value = NULL;
// 	}
// 	return (init_flag);
// }
