/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <alcornea@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 14:37:29 by alcornea          #+#    #+#             */
/*   Updated: 2017/07/08 17:41:20 by alcornea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <string.h>

/*
**	tgetent - loads the entry for name
**	tgetflag - gets the boolean entry for id or 0 if it's not available
** 	tgetnum - gets the numeric entry for the id or -1 if it's not available
**	tgetstr - return the string for the id or 0 if it's not available
**	tputs - to output the returned string
**	tgoto - intantiates the parameters into the gien capability, than it's passed to tputs;

**	tcsetattr - setting the termios structure
**	tcgetattr - function copies the parameters associeted with the terminal
	int tcsetattr(int fd, int optional action, const struct termios *termios_p);
	itn tcgetattr(int fd, struct termios *termios_p)

**	bs - backspace when contrl_h
**	am - automargin capability
**	co#80 - 80 colums
**	li#24 - 24 lines
**	up = ^K up cabability, move the cursor up one line;
**	cl = ^Z clear the screen;
**	ho=^^ move the cursor Home (upper-left corner)
**	nd=^L non destructive space capability, move the cursor one space to the right without changing the tesx
**	c_lflag - member of the struct terminos, control higher-level aspects of input prossesing.
**	VMIN - specifies the minimum number of bytes that must be available in the input queue in order for read to return
	VTIME - specifies how long to wait for input before returning, in units of 0.1 seconds
**
*/

int pputchar(int c)
{
	return (write(2, &c, 1));
}

void tm_clear(void)
{
	tputs(tgetstr("cl", NULL), 1, pputchar);
}


// int check_size(t_select *tmp)
// {
// 	struct winsize win;

// 	/*need to check for the screen size and if will be to small to display an error and clear te screen
// 	ioctl (fd, TIOCGWINSZ, &win) if it's less than zero
// 	*/
// }

void tm_select(char **argv, t_select *tm)
{
	tm_clear();
	parse_arg(argv, tm);
	print_list(tm);
	check_size(tm);
	// while (1)
	// {
	// 	if (!tm_keyhook(tm))
	// 		return (0);
	// }
}
/*
	term.c_lflag --> local modes
	term.c_iflag --> input modes
	term.c_oflag --> output modes
	term.c_cflag --> control modes
	term.c_cc 	 --> special characters
	cursor_invisible  civis  vi   make cursor invisible

	int ioctl(int fd, unsigned long request, ...); control device
	fd - open file descriptor;
	win.ws_col; win.ws_row;
	minsize width: 6; height: 2


*/

int tm_init(t_select *tm)
{
	struct winsize win;

	if ((tcgetattr(0, &(tm->term))) == -1) //call tcgetattr to get the current mode of the particular device ,
	// and store the result modify only the one we are in interesed in and store theem with tcsetattr
		return (0);
	tm->term.c_lflag &= ~(ICANON | ECHO); //disable line editing immediately canonical mode
	printf("%lx %x %x\n", tm->term.c_lflag, ICANON, ECHO);
	tm->term.c_cc[VMIN] = 1;
	tm->term.c_cc[VTIME] = 0;
	ioctl(0, TIOCGWINSZ, &win); //get the size of the window;
	tm->col = win.ws_col;
	tm->row = win.ws_row;
	if (tcsetattr(0, 0, &(tm->term)) == -1)
		return (0);
	tputs(tgetstr("ti", NULL), 1, pputchar);
	tputs(tgetstr("ve", NULL), 1, pputchar);
	return (1);
}

int main(int argc, char **argv)
{
	t_select tm;

	(void)argv;
	(argc < 2) ? printf("Introduce the parameters\n") : (0);
	tm_signal();
	if ((tgetent(NULL, getenv("TERM"))) < 1)
		printf("Check terminal name\n");
	(!tm_init(&tm)) ? (printf("Initialing terminal failed\n")) : (0);
	(argc >= 2) ? tm_select(argv, &tm) : (0);
	tm_endtm(&tm);
	return (0);
}
