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

#include "ft_select.h"

/*
**  SIGCONT continue if stopped
**  SIGSTOP stop process
**  SIGTSTP suspend process (VSUSP, default ctrl-Z, value 18)
**  SIGINT interrupt from keyboard (VINTR, default ctrl-C)
**  SIGTERM termination signal
**  SIGWINCH window resize
**	SIGQUIT (VQUIT, default ctrl-\, value 3)
**	SIGKILL kill the process (value 9)
** 	TIOCSTI Insert the given byte in the input queue.
**	VSUSP suspending the characters
*/

t_select *get_info(void)
{
	static t_select *arg;

	if (arg == NULL)
		arg = ft_memalloc(sizeof(t_select));
	return (arg);
}

static	void	sig_stop(void)
{
	t_select	*arg = NULL;
	char	cp[2];

	arg = get_info();
	cp[0] = arg->term.c_cc[VSUSP];
	cp[1] = 0;
	arg->term.c_lflag |= (ICANON | ECHO); //set icanon and echo back
	signal(SIGTSTP, SIG_DFL);
	tputs(tgetstr("cl", NULL), 1, pputchar);
	tcsetattr(0, 0, &(arg->term));
	tputs(tgetstr("te", NULL), 1, pputchar);
	tputs(tgetstr("ve", NULL), 1, pputchar);
	// ioctl(0, TIOCSTI, cp);
}

static void		sig_cont(void)
{
	t_select *arg = NULL;

	arg = get_info();
	arg->term.c_lflag &= ~(ICANON | ECHO);
	arg->term.c_cc[VMIN] = 1;
	arg->term.c_cc[VTIME] = 0;
	tcsetattr(0, 0, &(arg->term));
	tputs(tgetstr("ti", NULL), 1, pputchar);
	tputs(tgetstr("vi", NULL), 1, pputchar);
	signal(SIGTSTP, get_signal);
	// resize_window();
	// check_size_window(arg);
}

void			get_signal(int i)
{
	t_select *arg;

	arg = get_info();
	if (i == SIGCONT)
		sig_cont();
	else if (i == SIGTSTP)
		sig_stop();
	// else if (i == SIGWINCH)
	// 	resize_window();
	else
	{
		tputs(tgetstr("cl", NULL), 1, pputchar);
		tm_end_session(arg);
		(i == SIGSTOP) ? signal(SIGSTOP, SIG_DFL) : (0);
	}
}

void			tm_signal(void)
{
	signal(SIGTSTP, &get_signal);
	signal(SIGINT, &get_signal);
	signal(SIGWINCH, &get_signal);
	signal(SIGTERM, &get_signal);
	signal(SIGCONT, &get_signal);
	signal(SIGQUIT, &get_signal);
	signal(SIGKILL, &get_signal);
}
