/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <alcornea@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 14:38:23 by alcornea          #+#    #+#             */
/*   Updated: 2017/07/08 13:49:32 by alcornea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
  Signal are sofware interrups, ctrl+c process is sending  s signal to kill the process
  SIGCONT continue if stopped
  SIGSTOP stop process
  SIGTSTP stop typed at terminal
  SIGINT interrupt from keyboard
  SIGTERM termination signal
  SIGWINCH window resize
*/
//
#include "ft_select.h"

static	void	sig_stop(void)
{
	t_select	*arg;
	char	cp[2];

	arg = NULL;
	cp[0] = arg->term.c_cc[VSUSP];
	cp[1] = 0;
  arg->mod = 0;
	arg->term.c_lflag |= (ICANON | ECHO); //set icanon anfd echo back
	signal(SIGTSTP, SIG_DFL);
	tputs(tgetstr("cl", NULL), 1, pputchar);
	tcsetattr(0, 0, &(arg->term));
	tputs(tgetstr("te", NULL), 1, pputchar);
	tputs(tgetstr("ve", NULL), 1, pputchar);
	ioctl(0, TIOCSTI, cp);
}

static void		sig_cont(void)
{
	t_select *arg;

	arg = NULL;
	arg->term.c_lflag &= ~(ICANON | ECHO);
	arg->term.c_cc[VMIN] = 1;
	arg->term.c_cc[VTIME] = 0;
  arg->mod = 0;
	tcsetattr(0, 0, &(arg->term));
	tputs(tgetstr("ti", NULL), 1, pputchar);
	tputs(tgetstr("vi", NULL), 1, pputchar);
	signal(SIGTSTP, get_signal);
	// resize();
	// ft_check_size(arg);
}

void			get_signal(int i)
{
	t_select *arg;

	arg = NULL;
	if (i == SIGCONT)
		sig_cont();
	else if (i == SIGTSTP) //control z
		sig_stop();
	// else if (i == SIGWINCH)
	// 	resize();
	else
	{
	  tm_end_session(arg);
		exit(0);
	}
}

void			tm_signal(void)
{
	int i;

	i = 1;
	while (i < 32)
	{
		signal(i, get_signal);
		i++;
	}
}

// #include<stdio.h>
// #include<signal.h>
// #include<unistd.h>
//
// void sig_handler(int signo)
// {
//     if (signo == SIGUSR1)
//         printf("received SIGUSR1\n");
//     else if (signo == SIGKILL)
//         printf("received SIGKILL\n");
//     else if (signo == SIGINT)
//         printf("received SIGINT\n");
//     else if (signo == SIGSTOP)
//         printf("received SIGSTOP\n");
// }
//
// int main(void)
// {
//     if (signal(SIGUSR1, sig_handler) == SIG_ERR)
//         printf("\ncan't catch SIGUSR1\n");
//     if (signal(SIGKILL, sig_handler) == SIG_ERR)
//         printf("\ncan't catch SIGKILL\n");
//     if (signal(SIGSTOP, sig_handler) == SIG_ERR)
//         printf("\ncan't catch SIGSTOP\n");
//     while(1)
//         sleep(1);
//     return 0;
// }
