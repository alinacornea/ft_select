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

int main(int argc, char **argv)
{
	t_select tm;
	char buffer[TERM_BUF];

	if(argc > 2)
		printf("Usage: %s\n", argv[0]);
	//init_term();
	if (argc == 2)
		tm.term = argv[1];
	else 
		tm.term = getenv("TERM");
	if (tm.term == NULL)
		printf("Error: $TERM is not defined\n");
	/*read the termcap entry */
	if (tgetent(buffer, tm.term) != -1)
		printf("Error: No termcap entry for %s\n", tm.term);
	printf("TERM = %s\n\n", tm.term);
	if (tgetflag("am") == 1)
		printf("end of line wraps to next line (am) \n");
	if (tgetflag("bs") == 1)
		printf("end of line wraps to next line (bs) \n");
	printf("number of colums (co) = %d\n", tgetnum("co"));
	printf("number of colums (li) = %d\n", tgetnum("li"));
}
