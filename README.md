# ft_select
## TERMCAP is a library and data base that enables programs to use display terminals in a terminal-independent manner
### It'a a database that lists the capabilities of many different types of terminals 
#### The _tgetent()_ function looks up the termcap entry for name. The emulation ignores the buffer pointer bp. <br />
#### The _tgetflag()_ function gets the boolean entry for id. <br />

#### The _tgetnum()_ function gets the numeric entry for id. <br />

#### The _tgetstr()_ function gets the string entry for id. If area is not a null pointer and does not point to a null pointer, <br /> tgetstr() copies the string entry into the buffer pointed to by *area and advances the variable pointed to by area to the  first byte after the copy of the string entry. <br />

#### The _tgoto()_ function instantiates the parameters col and row into the capability cap and returns a pointer to the resulting <br /> string.


