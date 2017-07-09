/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tm_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <alcornea@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 01:21:34 by alcornea          #+#    #+#             */
/*   Updated: 2017/07/08 13:51:41 by alcornea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
	ICANON - canonical input processing mode, terminal input is processed in lines terminated by newline, no input can be read
	if the entire line is not been typed, canonical input mode provides input editing facilities, within the current line of text,
	gives the user a way to edit input line by line;
	NON canonical input don't permit erase and kill to be performed;
	ECHO - if this bit is set, echoing of input characters back to the terminal is enabled;

	VMIN/VTIME - able to insure that we could efficiently capture all data sent in one burst without risk of inter-message overlap
	Ex: "ESC [ A" => Up arrow in order to say if it's only a esc key or it's up arrow we timed the time pressing;

	The operating system return from the read() system call when either the user buffer is full or when  the end of file has been reached,
	from the terminal to see when we done reading we use vmin and vtime;
	internal time is started when a character arrive and counts up to tenths of sec, resets when a new data arrives;


*/
static void sig_stop(void)
{
	t_select *tm;
	char s[2];

	tm = NULL;
	tm = tm_stock(tm, 1);
	s[0] = tm->term.c_cc[VSUSP];
	s[1] = 0;
	tm->term.c_lflag &= ~(ICANON | ECHO);
	signal(SIGTSTP, SIG_DFL);
	tm_clear();
	tcsetattr(0, 0, &(tm->term));
	tputs(tgetstr("te", NULL)), 1, ft_pputchar);
	tputs(tgetstr("ve", NULL)), 1, ft_pputchar);
	ioctl(0, TIOCSTI, s);
}

static void sig_cont(void)
{
	t_select *tm;

	tm = NULL;
	tm = tm_stock(tm, 1);
	tm->term.c_lflag &= ~(ICANON | ECHO);
	tm->term.c_cc[VMIN] = 1;
	tm->term.c_cc[VTIME] = 0;
	tcsetattr(0, 0, &(tm->term));
	tputs(tgetstr("ti", NULL)), 1, ft_pputchar);
	tputs(tgetstr("ve", NULL)), 1, ft_pputchar);
	signal(SIGTSTP, get_signal);
	re_size();
	check_size(tm);
}

/*
** SIGCONT : discard signal, continue after sig_top ;
** SIGTSTP : stop process, stop signal generated from keyboard ;
** SIGWINCH : discard signal, window size change ;
*/

void get_signal(int i)
{
	t_select *tm;

  tm = NULL;
	if (i == SIGCONT)
		sig_cont();
	else if (i == SIGTSTP)
		sig_stop();
	else if (i == SIGWINCH)
		sig_size();
	else
    {
	    tm = tm_stock(tm, 1);
	    tm_endtm(tm);
	    exit(0);
    }
}

void tm_signal(void)
{
	int i;

	i = 1;
	while (i < 32)
	{
		signal(i, get_signal;
		i++;
	}
}
