/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <alcornea@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 14:38:23 by alcornea          #+#    #+#             */
/*   Updated: 2017/07/08 13:49:32 by alcornea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
#define FT_SELECT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <termcap.h>
# include <term.h>
# include "libft.h"
# include <sys/ioctl.h>

# define TERM_BUF 2048
# define KEY_ASCII(c)	(c)
# define KEY_ESC		27
# define KEY_BACK		127
# define KEY_DELETE		2117294875
# define KEY_RETURN		10
# define KEY_UP			4283163
# define KEY_HOME   4741915
# define KEY_DOWN		4348699
# define KEY_CTRL_A		1
# define KEY_SPACE    32
# define BUFFER *(unsigned int *)buffer
/*
ID meaning:
vs enhance the cursor
vi cursor visible
ve cursor to normal
us underline mode
ue top underlying
ti special mode for terminal
te finish ti
is initialize the terminal for each login session
*/

typedef struct s_list
{
  char *arg;
  int len;
  int select;
  int line;
  struct s_list *next;
  struct s_list *prev;

} t_list;

typedef struct s_select
{
    struct termios term;
    char          *name;
    // char *term;
    int col;
    int row;
    int select;
    t_list *list;


}              t_select;


int     pputchar(int c);
void    get_signal(int i);
void    tm_clear(void);
void parse_arg(char **argv, t_select *tm);
void tm_endtm(t_select *tm);
int tm_keyhook(t_select *tm);

#endif
