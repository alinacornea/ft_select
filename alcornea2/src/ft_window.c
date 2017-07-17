/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <alcornea@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 14:38:23 by alcornea          #+#    #+#             */
/*   Updated: 2017/07/08 13:49:32 by alcornea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	resize_window(void)
{
	int				colums;
	t_select		*arg;
	struct winsize	win;

	arg = NULL;
	arg = get_info();
	colums = arg->count_lines / arg->height + 1;
	ioctl(0, TIOCGWINSZ, &win);
	arg->width = win.ws_col;
	arg->height = win.ws_row;
	tputs(tgetstr("cl", NULL), 1, pputchar);
	if (colums < arg->width && arg->width > 20)
		tm_printlist(arg);
	else
		ft_printf(C_RED"it's too smalll!!\n"C_RES);
}

void	position_cursor(t_select *arg, char *buff)
{
	t_lsarg	*tmp;

	tmp = arg->begin;
	while (tmp->cursor != 1)
		tmp = tmp->next;
	tmp->cursor = 0;
	(INPUT == KEY_HOME) ? (arg->begin->cursor = 1) :
	(arg->begin->prev->cursor = 1);
}
