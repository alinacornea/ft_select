/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <alcornea@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 14:38:23 by alcornea          #+#    #+#             */
/*   Updated: 2017/07/07 15:04:28 by alcornea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
#define FT_SELECT_H

# include <stdio.h>
# include <stdlib.h>
# include <curses.h>
# include <termcap.h>
# include <term.h>

# define TERM_BUF 2048
# define KEY_ASCII(c)	(c)
# define KEY_ESC		27
# define KEY_BACK		127
# define KEY_DELETE		2117294875
# define KEY_RETURN		10
# define KEY_END		4607771
# define KEY_UP			4283163
# define KEY_LEFT		4479771
# define KEY_RIGHT		4414235
# define KEY_DOWN		4348699
# define KEY_CTRL_A		1
# define KEY_CTRL_E		5

typedef struct s_select
{
    struct termios term;
    char          *name;
    int col;
    int row;
    

}              t_select;

#endif
