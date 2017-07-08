/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <alcornea@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 14:37:29 by alcornea          #+#    #+#             */
/*   Updated: 2017/07/07 15:29:14 by alcornea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

// int main(int argc, char **argv)
// {
// 	t_select tm;
// 	char buffer[TERM_BUF];
//
// 	if(argc > 2)
// 		printf("Usage: %s\n", argv[0]);
// 	//init_term();
// 	if (argc == 2)
// 		tm.term = argv[1];
// 	else
// 		tm.term = getenv("TERM");
// 	if (tm.term == NULL)
// 		printf("Error: $TERM is not defined\n");
// 	/*read the termcap entry */
// 	if (tgetent(buffer, tm.term) != -1)
// 		printf("Error: No termcap entry for %s\n", tm.term);
// 	printf("TERM = %s\n\n", tm.term);
// 	if (tgetflag("am") == 1)
// 		printf("end of line wraps to next line (am) \n");
// 	if (tgetflag("bs") == 1)
// 		printf("end of line wraps to next line (bs) \n");
// 	printf("number of colums (co) = %d\n", tgetnum("co"));
// 	printf("number of colums (li) = %d\n", tgetnum("li"));
// }

static void sig_cont(void)
{
	t_select *tm;

	tm = NULL;
	tm = tm_stock(tm, 1);
	tm->term.c
}
void get_signal(int i)
{
	if (i == SIGCONT)
		sig_cont();
	else if (i == SIGTSTP)
		sig_stop();
	else if (i == SIGWINCH)
		sig_size();
	else
		sig_end();
}

void tm_signal(void)
{
	int i;

	i = 1;
	while (i < 32)
	{
		signal(i, get_signal)
		i++;
	}
}
int tm_init(t_select *tm)
{
	struct winsize win;

	if ((t_getent(NULL, getenv("TERM")) < 1) ||
	(tcgetattr(0, &(tm->term)) == -1))
		return (0);
	// tm->term.c_lflag
	tm->term.c_cc[VMIN] = 1;
	tm->term.c_cc[VTIME] = 0;
	tm->col = win.ws_col;
	tm->row = win.ws_row;
	if (tcsetattr(0, 0, &(tm->term)) == -1)
		return (0);
	tputs(tgetstr("ti", NULL), 1, ft_putchar);
	tputs(tgetstr("vi", NULL), 1, ft_putchar);
	return (1);
}

int main(int argc, char **argv)
{
	t_select tm;

	tm_signal();
	tm_init(&tm);
	(argc >= 2) ? tm_select(argv, &tm);
	(!tm_end(&tm)) ? (-1) : (0);
	return (0);
}
