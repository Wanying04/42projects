#include <stdio.h>

int	invalid(char *s)
{
	int i = 0;
	int open = 0;
	int close = 0;

	while (s[i])
	{
		if (s[i] == '(')
			open++;
		else if (s[i] == ')')
		{
			if (open > 0)
				open--;
			else
				close++;
		}
		i++;
	}
	return (open + close);
}

void result(char *s, int remove, int delete, int pos)
{
	if (remove == delete && !invalid(s))
	{
		puts(s);
		return ;
	}
	while (s[pos])
	{
		if (s[pos] == '(' || s[pos] == ')')
		{
			char c = s[pos];
			s[pos] = ' ';
			result(s, remove, delete + 1, pos + 1);
			s[pos] = c;
		}
		pos++;
	}
}

int main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	int remove = invalid(av[1]);
	result(av[1], remove, 0, 0);
	return (0);
}

/*Assignment name  : rip
Expected files   : *.c *.h
Allowed functions: puts, write
--------------------------------------------------------------------------------

Escribe un programa que tome como argumento una cadena que contenga solo paréntesis.
Si los paréntesis no están equilibrados (por ejemplo, «()»),
tu programa deberá eliminar el número mínimo de paréntesis para que la expresión quede equilibrada.
Por eliminar nos referimos a sustituirlos por espacios.
A continuación, imprimirás todas las soluciones (puede haber más de una).

El orden de las soluciones no es importante.

Por ejemplo, esto debería funcionar:
$> ./rip '(()' | cat -e
 ()$
( )$
$> ./rip '((()()())())' | cat -e
((()()())())$
$> ./rip '()())()'| cat -e
()() ()$
()( )()$
( ())()$
$> ./rip '(()(()(' | cat -e
(()  ) $
( )( ) $
( ) () $
 ()( ) $*/