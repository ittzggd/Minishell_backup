/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 20:08:48 by yukim             #+#    #+#             */
/*   Updated: 2022/06/26 17:51:09 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	init_data_stdfd(void);
static void	init_data_termios(void);
static void	init_data_envvlist(char **envp);

void	init_setting(char **envp)
{
	// 현재 원본 stdin, stdout fd를 저장해놓음
	init_data_stdfd();

	// 현재 터미널의 원래 속성을 저장
	init_data_termios();
		
	// 환경변수 목록 받아서, data에 추가
	init_data_envvlist(envp);
}

static void	init_data_stdfd(void)
{
	// 현재 원본 stdin, stdout fd를 저장해놓음
	if (pipe(data.std_fd) < 0)
	{
		data.exit_status = 1;
		exit(data.exit_status);
	}
	close(data.std_fd[0]);
	close(data.std_fd[1]);
	data.std_fd[0] = dup(STDIN_FILENO);
	data.std_fd[1] = dup(STDOUT_FILENO);
}

static void	init_data_termios(void)
{
	// 현재 터미널의 원래 설정된 속성 저장
	tcgetattr(data.std_fd[0], &data.origin_term);
	data.changed_term = data.origin_term;

//	data.changed_term.c_lflag &= ~(ICANON | ECHO); // 이건 ctrl + C 를 사용할 때, echo로 시그널을 출력하지 않도록
	// printf("origin_term c_lflag = %lx\n", data.origin_term.c_lflag);
	// printf("changed_term c_lflag = %lx\n", data.changed_term.c_lflag);
	
	/*TIME 이 0이지만 MIN은 0이 아닐 때.
	이 경우, read는 적어도 큐에 유용한 입력이 MIN 바이트가 될 때까지 기다린다. 
	그 시간동안, read는 요청된 개수의 유용한 문자들을 반환한다. 
	read는 만일 큐에 MIN보다 더 많은 문자가 발생했다면 MIN 문자보다 더 많은 문자를 반환할 수 있다.
	*/
	// data.changed_term.c_cc[VTIME] = 0; // 입력을 무한대로 기다림
	// data.changed_term.c_cc[VMIN] = 1;
	
	// 터미널에 changed_term 속성 적용
	tcsetattr(data.std_fd[0], TCSANOW, &data.changed_term);
}

static void	init_data_envvlist(char **envp)
{
	char	*key;
	char	*value;

	// 환경변수 목록 받아서, data에 추가
	while (*envp)
	{
		init_envp(*envp, &key, &value);
		insert_envv(key, value, TRUE);
		envp++;
	}
	insert_envv("OLDPWD", NULL, TRUE);
}
