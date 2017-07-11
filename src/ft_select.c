#include "ft_select.h"
/*
  NOTE: In order to search termcap library, compile ussing "-ltermcap" or "-ltermlib"
*/


int pputchar(int c)
{
	return (write(2, &c, 1));
}

t_lsarg *tm_init_list(void)
{
  t_lsarg *tmp;

  tmp = (t_lsarg *)malloc(sizeof(t_lsarg));
  tmp->name = NULL;
  tmp->select = 0;
  tmp->line = 0;
  tmp->len = 0;
  tmp->next = NULL;
  tmp->prev = NULL;
  return (tmp);
}

/*
  Setting terminal (noncanonical mode):
  1.Look up the description of the terminal type in use, using tgetent() and tgetent()
  2.Get the parrameters (key pressed immediately by the user) using tcgetattr()
  3.Setting the terminal into nonconincal mode, allows to set how many characters should be read
    before input is given to the program. (&= ~ICANON) unset a flag using bit mask operation;
    ICANON - "line editing" mode, terminal buffers line at a time;
    ECHO - controls wheter input is immediately re-echoed as output;
  4.Set buffer size to 1 byte and time wait to 0 sec, (VMIN, VTIME)
  5.Set the attributes of the terminal making change immediately;
  6.Extract information we will use using tgetstr(), tputs();
*/

int tm_set_terminal(t_select *arg)
{

  if ((tgetent(NULL, getenv("TERM"))) < 1)
    printf("Specify a terminal type with `setenv TERM <yourtype>'.\n");
  if ((tcgetattr(0, &(arg->term))) == -1)
    return (0);
  arg->term.c_lflag &= ~(ICANON | ECHO);
  arg->term.c_cc[VMIN] = 1;
  arg->term.c_cc[VTIME] = 0;
  arg->height = tgetnum("li");
  arg->width = tgetnum("co");
  printf("%d %d\n", arg->height, arg->width);
  if ((tcsetattr(0, 0, &(arg->term))) == -1)
    return (0);
  tputs(tgetstr("ti", NULL), 1, pputchar);
  tputs(tgetstr("vi", NULL), 1, pputchar);
  return(1);
}

void	print_return(t_select *arg)
{
	int		i;

	i = 0;
	while (arg->ret_tab[i])
	{
		ft_putstr(arg->ret_tab[i]);
		if (arg->ret_tab[i + 1])
			ft_putchar(32);
		i++;
	}
}

/*
  create the list of the arguments
*/

void push_list(t_select *arg, t_lsarg *ls)
{
  t_lsarg *tmp;

  if (arg->begin == NULL)
  {
    ls->prev = ls;
    ls->next = ls;
    arg->begin = ls;
    ls->line = 1;
  }
  else{
    tmp = arg->begin->prev;
    tmp->next = ls;
    ls->next = arg->begin;
    ls->prev = tmp;
    arg->begin->prev = ls;
  }
}
void tm_makelist(char **argv, t_select *arg)
{
  int i;
  t_lsarg *tmp;

  i = 1;
  while (argv[i])
  {
    tmp = tm_init_list();
    tmp->name = ft_strdup(argv[i]);
    tmp->len = ft_strlen(tmp->name);
    push_list(arg, tmp);
    i++;
  }
  arg->count[LINE] = i;
}

int main(int argc, char **argv)
{
  t_select *arg = NULL;

  arg = ft_memalloc(sizeof(t_select));
  if (argc < 2)
    printf("Usage: ./ft_select [arg1] [arg2] [arg3] ...");
  // tm_signal();
  if (!tm_set_terminal(arg))
    printf("Setting terminal failed\n");
  if (argc >=2)
  {
    tputs(tgetstr("cl", NULL), 1, pputchar);
    tm_makelist(argv, arg);
    tm_printlist(arg);
    while (1)
    {
      if(!tm_keyhook(arg))
        break;
    }
  }
  /*tm_end_session();
  "ve" -return cursor to normal;
  "te" - output the string when exit, finish "ti"
  */
  arg->term.c_lflag |= (ICANON | ECHO); // | return 1 all the time except when 0, 0
  tcsetattr(0, 0, &(arg->term));
  tputs(tgetstr("te", NULL), 1, pputchar);
  tputs(tgetstr("ve", NULL), 1, pputchar);
  if(arg->ret_tab)
   print_return(arg);
  return (0);
}
