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
# include "colors.h"
# include <signal.h>
# include <sys/ioctl.h>

# define KEY_ESC		27
# define KEY_BACK		127
# define KEY_END 4610843
# define KEY_DELETE		2117294875
# define KEY_RETURN		10
# define KEY_UP			4283163
# define KEY_HOME   4741915
# define KEY_DOWN		4348699
# define KEY_CTRL_A		1
# define KEY_SPACE    32
# define KEY_TAB 9
# define INPUT *(unsigned int *)buff

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

typedef struct    s_lsarg
{
  char            *name;
  int             name_len;
  int             select;
  int             cursor;
  struct s_lsarg  *next;
  struct s_lsarg  *prev;

}                 t_lsarg;

typedef struct      s_select
{
    struct termios  term;
    char            **ret_tab;
    int             count_lines;
    int             enter;
    size_t          max_len;
    int             height;
    int             width;
    struct s_lsarg  *begin;
}                   t_select;

void      tm_printlist(t_select *arg);
int       tm_keyhook(t_select *arg);
void      tm_makelist(char **argv, t_select *arg);
void      tm_signal(void);
void		  get_signal(int i);
void      return_key(t_select *arg);
int       pputchar(int c);
void	    print_return(t_select *arg);
void      resize_window(void);
int       check_size_window(t_select *arg);
t_select  *get_info(void);

void    tm_end_session(t_select *arg);

#endif
