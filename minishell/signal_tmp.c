#include "./include/minishell.h"

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		data.exit_status = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sigquit_handler(int signum)
{
	int	size;

	size = ft_strlen(rl_line_buffer);
	if (signum == SIGQUIT)
	{
		if (size == 0)
		{
			rl_on_new_line();
			rl_redisplay();
		}
		if (size != 0)
		{
			printf("\nQuit: 3\n");
			//free_env(g_sh.env);
			exit(131);
		}
	}
}

void	hdoc_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		exit(1);
	}
}

void	exec_sigint(int signum)
{
	(void)signum;
	ft_error_message("\n", 130);
	//ft_putstr_fd("\n", 2);
	rl_on_new_line();
	exit(130);
}

void	exec_sigquit(int signum)
{
	(void)signum;
	ft_error_message("\n", 131);
	//ft_putstr_fd("Quit: 3\n", 2);
	exit(131);
}
