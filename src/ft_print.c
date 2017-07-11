#include "ft_select.h"
#include "colors.h"


void select_view(t_lsarg *list)
{
  if (list->line == 1 && list->select == 1)
  {
    tputs(tgetstr("us", NULL), 1, pputchar);
    tputs(tgetstr("so", NULL), 1, pputchar);
    ft_putstr_fd(CL_YELLOW, 2);
    ft_putendl_fd(list->name, 2);
    ft_putstr_fd(C_RES, 2);
    tputs(tgetstr("se", NULL), 1, pputchar);
    tputs(tgetstr("ue", NULL), 1, pputchar);
  }
  else if (list->line == 1)
  {

  	tputs(tgetstr("us", NULL), 1, pputchar);
  	ft_putstr_fd(C_YELLOW, 2);
  	ft_putendl_fd(list->name, 2);
  	ft_putstr_fd(C_RES, 2);
  	tputs(tgetstr("ue", NULL), 1, pputchar);
  }
  else if (list->select == 1)
  {
    tputs(tgetstr("so", NULL), 1, pputchar);
  	ft_putstr_fd(C_RED, 2);
  	ft_putendl_fd(list->name, 2);
  	ft_putstr_fd(C_RES, 2);
  	tputs(tgetstr("se", NULL), 1, pputchar);
  }
  else
    ft_putendl_fd(list->name, 2);
}

void tm_printlist(t_select *arg)
{
  t_lsarg *tmp;

  tmp = NULL;
  select_view(arg->begin);
  tmp = arg->begin->next;
  while (tmp != arg->begin)
  {
    select_view(tmp);
    tmp = tmp->next;
  }
}
