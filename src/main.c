/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <alcornea@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 14:38:23 by alcornea          #+#    #+#             */
/*   Updated: 2017/07/08 13:49:32 by alcornea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
  NOTE: In order to search termcap library, compile ussing "-ltermcap" or "-ltermlib"
*/

int pputchar(int c)
{
	return (write(1, &c, 1));
}

/*
** Setting terminal (noncanonical mode):
**
** 1. Look up the description of the terminal type in use, using tgetent() and tgetent()
** 2. Get the parrameters (key pressed immediately by the user) using tcgetattr()
** 3. Setting the terminal into nonconincal mode, allows to set how many characters should be read
**  before input is given to the program. (&= ~ICANON) unset a flag using bit mask operation;
**  ICANON - "line editing" mode, terminal buffers line at a time;
**  ECHO - controls wheter input is immediately re-echoed as output;
** 4. Set buffer size to 1 byte and time wait to 0 sec, (VMIN, VTIME)
** 5. Set the attributes of the terminal making change immediately;
** 6. Extract information we will use using tgetstr(), tputs();
*/

int tm_set_terminal(t_select *arg)
{
	struct winsize win;

  if ((tgetent(NULL, getenv("TERM"))) < 1)
    printf("Specify a terminal type with `setenv TERM <yourtype>'.\n");
  if ((tcgetattr(0, &(arg->term))) == -1)
    return (0);
  arg->term.c_lflag &= ~(ICANON | ECHO);
  arg->term.c_cc[VMIN] = 1;
  arg->term.c_cc[VTIME] = 0;
	ioctl(0, TIOCGWINSZ, &win);
  arg->height= win.ws_row;
  arg->width = win.ws_col;
  if ((tcsetattr(0, 0, &(arg->term))) == -1)
    return (0);
  tputs(tgetstr("ti", NULL), 1, pputchar);
  tputs(tgetstr("vi", NULL), 1, pputchar);
  return(1);
}

/*
** End terminal session:
**
** Setting terminal back to canonical mode using bit mask operator |
** "ve" - return cursor to normal;
** "te" - output the string when exit, finish "ti";
*/

void tm_end_session(t_select *arg)
{
	arg->term.c_lflag |= (ICANON | ECHO); // | return 1 all the time except when 0, 0
	tcsetattr(0, 0, &(arg->term));
	tputs(tgetstr("te", NULL), 1, pputchar);
	tputs(tgetstr("ve", NULL), 1, pputchar);
	(arg->ret_tab) ?	print_return(arg) : (0);
}

int main(int argc, char **argv)
{
  t_select *arg;

	tm_signal();
  arg = get_info();
  if (argc < 2)
    ft_printf("Usage: ./ft_select [arg1] [arg2] [arg3] ...\n");
  if (!tm_set_terminal(arg))
    ft_printf("Setting terminal failed\n");
  if (argc >=2)
  {
    tputs(tgetstr("cl", NULL), 1, pputchar);
    tm_makelist(argv, arg);
    tm_printlist(arg);
		check_size_window(arg);
    while (1)
    {
      if(!tm_keyhook(arg))
        break;
    }
  }
	tm_end_session(arg);
  return (0);
}
