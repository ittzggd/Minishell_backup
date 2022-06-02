/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 09:59:43 by hejang            #+#    #+#             */
/*   Updated: 2022/06/02 13:47:25 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"



// 환경변수를 비교하여 교체
void	replace_env(int i, t_data *data)
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
		argv = getenv(key);
		free(token);
		free(key);
		data->plexer->pptokens[i] = argv;
	}
}

//환경 변수 문법을 체크한 뒤, key값만 반환하는 함수
