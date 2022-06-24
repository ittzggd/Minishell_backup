/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 20:08:48 by yukim             #+#    #+#             */
/*   Updated: 2022/06/24 21:21:22 by hejang           ###   ########.fr       */
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

	data.changed_term.c_lflag &= ~(ICANON | ECHO); // 이건 ctrl + C 를 사용할 때, echo로 시그널을 출력하지 않도록
	printf("origin_term c_lflag = %lx\n", data.origin_term.c_lflag);
	printf("changed_term c_lflag = %lx\n", data.changed_term.c_lflag);
	
	data.changed_term.c_cc[VTIME] = 0; // 입력을 무한대로 기다림
	data.changed_term.c_cc[VMIN] = 1;
	
	// 터미널 속성값 - c_lflag
	// - ISIG 플래그 : signal을 받아들인다. 
	// 	이 플래그가 on되어 있다면 INTR, QUIT, 등과 같은 특수 문자를 받아들임.
	// - ICANON 플래그 : 이 플래그가 on되면 정규모드로 입력이 이루어진다.
	

	// ctrl + c 구현 사항 : print a new prompt on a newline.
	// 만약에 ISIG 플래그가 on되어 있다면,
	// ctrl + C 문자를 입력시 포그라운드 프로세스에 SIGINT가 발생
	// data.changed_term.c_cc[VINTR] = VINTR;
	
	// ctrl + d 구현 사항 : exit the shell.
	// 만약에 ICANON 플래그가 on되어 있고 EOF가 발생하면,
	// 읽기 대기중인 모든 문자들은 개행 문자를 만나지 않아도 바로 프로세스로 전달
	// data.changed_term.c_cc[VEOF] = VEOF;
	
	// ctrl-\ 구현 사항 : do nothing.
	// ISIG 플래그가 On되어 있고 ctrl + \ 문자가 입력되면,
	// SIGQUIT 시그널이 발생한다.
	// data.changed_term.c_cc[VQUIT] = VQUIT;

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