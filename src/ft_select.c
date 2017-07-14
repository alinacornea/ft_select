/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <alcornea@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 14:38:23 by alcornea          #+#    #+#             */
/*   Updated: 2017/07/08 13:49:32 by alcornea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_lsarg		*tm_init_list(void)
{
	t_lsarg	*tmp;

	tmp = ft_memalloc(sizeof(t_lsarg));
	tmp->name = NULL;
	tmp->select = 0;
	tmp->cursor = 0;
	tmp->name_len = 0;
	tmp->next = NULL;
	tmp->prev = NULL;
	return (tmp);
}

/*
** get_selected() and return_key() functions will return the selected lines.
** ret_tab variable will memorize all of them and after the session wil end wil
** print them out.
*/

static void	get_selected(t_select *arg, int count)
{
	int		i;
	t_lsarg	*tmp;

	i = 0;
	tmp = NULL;
	arg->ret_tab = (char **)malloc(sizeof(char*) * (count + 1));
	if (arg->begin->select == 1)
	{
		arg->ret_tab[i] = ft_strdup(arg->begin->name);
		free(arg->begin->name);
		i++;
	}
	tmp = arg->begin->next;
	while (tmp != arg->begin)
	{
		if (tmp->select == 1)
		{
			arg->ret_tab[i] = ft_strdup(tmp->name);
			free(tmp->name);
			i++;
		}
		tmp = tmp->next;
	}
	tmp->name = NULL;
	arg->ret_tab[i] = 0;
}

void		return_key(t_select *arg)
{
	int		count_sel_lines;
	t_lsarg	*tmp;

	arg->enter = 1;
	count_sel_lines = 0;
	if (arg->begin->select == 1)
		count_sel_lines++;
	tmp = arg->begin->next;
	while (tmp != arg->begin)
	{
		if (tmp->select == 1)
			count_sel_lines++;
		tmp = tmp->next;
	}
	get_selected(arg, count_sel_lines);
}

static void	create_list(t_select *arg, t_lsarg *ls)
{
	t_lsarg	*tmp;

	if (arg->begin == NULL)
	{
		ls->prev = ls;
		ls->next = ls;
		arg->begin = ls;
		ls->cursor = 1;
	}
	else
	{
		tmp = arg->begin->prev;
		tmp->next = ls;
		ls->next = arg->begin;
		ls->prev = tmp;
		arg->begin->prev = ls;
	}
}

/*
** tm_makelist() will create the list based on the arguments introduced
** using the t_select and t_lasarg structs;
** name-len will be using in order to find out the window size;
*/

void		tm_makelist(char **argv, t_select *arg, int argc)
{
	int		i;
	t_lsarg	*tmp;

	i = 1;
	arg->count_lines = argc;
	while (argv[i])
	{
		tmp = tm_init_list();
		tmp->name = ft_strdup(argv[i]);
		tmp->name_len = ft_strlen(tmp->name);
		create_list(arg, tmp);
		i++;
	}
}
