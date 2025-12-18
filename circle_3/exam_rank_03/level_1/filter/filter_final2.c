#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int	main(int ac, char **av)
{
	char	buffer[99999];
	int		i = 0;
	int		leido = 1;
	int		j;
	int		len;

	if (ac != 2)
		return (1);
	len = strlen(av[1]);
	while (leido > 0)
		leido = read(0, &buffer[i++], 1);
	buffer[--i] = 0;
	i = 0;
	while (buffer[i])
	{
		j = 0;
		while (buffer[i + j] && av[1][j] && buffer[i + j] == av[1][j])
			j++;
		if (j == len)
		{	
			while (j--)
			{	
				write(1, "*", 1);
				i++;
			}
		}
		else
			write(1, &buffer[i++], 1);
	}
	return (0);
}

/*Assignment name: filter
Expected files: filter.c
Allowed functions: read, write, strlen, memmem, memmove, malloc, calloc,
realloc, free, printf, fprintf, stdout, stderr, perror
--------------------------------------------------------------------------------

Escribe un programa que tome un único argumento.

Tu programa leerá desde stdin y escribirá todo el contenido leído en stdout,
excepto que cada aparición de s debe ser reemplazada por “*” (tantas como la
longitud de s). Tu programa se probará con tamaños de búfer aleatorios,
utilizando una función de lectura personalizada.

Por lo tanto, el búfer establecido en tu programa se llenará con un
número diferente de caracteres en cada nueva llamada.

Por ejemplo:

./filter bonjour
will behave in the same way as:
sed 's/bonjour/ ******* /g'

./filter abc
will behave in the same way as:
sed's/abc/ *** /g'

En términos más generales, su programa debe ser equivalente al script de shell filter.sh
presente en este directorio (puede comparar su programa con él).

En caso de error durante una lectura o un malloc, debe escribir «Error: » seguido del
mensaje de error en stderr y devolver 1.

Si el programa se llama sin argumentos, con un argumento vacío o con varios
argumentos, debe devolver 1.

Por ejemplo, esto debería funcionar:

$> echo 'abcdefaaaabcdeabcabcdabc' | ./filter abc | cat -e
***defaaa***de******d***$
$> echo 'ababcabababc' | ./filter ababc | cat -e
*****ab*****$
$>

NOTAS:
memmem includes:
				#define _GNU_SOURCE
				#include <string.h>

perror includes:
				#include <errno.h>

read includes:
				#include <fcntl.h>*/