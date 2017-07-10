/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tm_endtm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <alcornea@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 01:20:35 by alcornea          #+#    #+#             */
/*   Updated: 2017/07/08 01:20:37 by alcornea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void tm_endtm(t_select *tm)
{
	tm->term.c_lflag |= (ICANON | ECHO); //enabling back the bits
	tcsetattr(0, 0, &(tm->term));
	tputs(tgetstr("te", NULL), 1, pputchar);
	tputs(tgetstr("ve", NULL), 1, pputchar); //enable the cursor
	(tm->select) ? print_list(tm) : (0); // check to print only if a arg was selected 
}
