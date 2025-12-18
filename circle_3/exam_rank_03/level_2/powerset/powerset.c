#include <stdio.h>
#include <stdlib.h>

int	*nums;
int target;
int actual[100];

void	powaset(int p_num, int size, int p_act, int suma)
{
	if (suma == target)
	{
		int i = 0;
		while (i < p_act)
		{
			if (i > 0)
				printf(" ");
			printf("%d", actual[i++]);
		}
		printf("\n");
		return;
	}
	if (p_num >= size)
		return;
	powaset(p_num + 1, size, p_act, suma);
	actual[p_act] = nums[p_num];
	powaset(p_num + 1, size, p_act + 1, suma + nums[p_num]);
}

int	main(int ac, char **av)
{
	int i = 0;
	if (ac < 3 || !(nums = malloc(sizeof(int) * (ac - 2))))
		return (1);
	target = atoi(av[1]);
	while (i < ac - 2)
	{
		nums[i] = atoi(av[i + 2]);
		i++;
	}
	powaset(0, ac - 2, 0, 0);
	free(nums);
	return(0);
}

/*contador para recorrer los argumentos y llenar el array nums
av1 es un string, lo convertimos a int y lo guardamos en target
reservo memoria para nums, reservo - 2 porque no necesito reservar para el ejecutor ni para el target
mientras i sea menos que el numero de argumentos
almaceno en nums cada argumento
llamo a la funcion recursiva
pos_num = 0; size = ac-2; p_act; suma = 0;
libero memoria
salgo

Assignment name  : powerset
Expected files   : *.c *.h
Allowed functions: atoi, printf, fprintf, malloc, calloc, realloc, free, stdout,
write
--------------------------------------------------------------------------------

Escribe un programa que tome como argumento un entero n seguido de un conjunto s de
enteros distintos.
Tu programa debe mostrar todos los subconjuntos de s cuya suma de elementos sea n.

El orden de las líneas no es importante, pero el orden de los elementos en un subconjunto sí lo es:
debe coincidir con el orden en el conjunto inicial s.
De esta manera, no debe haber duplicados (por ejemplo: «1 2» y «2 1»).

Por ejemplo, utilizando el comando ./powerset 5 1 2 3 4 5,
esta salida es válida:
1 4
2 3
5
esta salida es válida:
2 3
5
1 4
pero esta no:
4 1
3 2
5

En caso de error de malloc, tu programa se cerrará con el código 1.
No realizaremos pruebas con conjuntos no válidos (por ejemplo, «1 1 2»).
Pista: el subconjunto vacío es un subconjunto válido de cualquier conjunto. Se mostrará como una línea vacía.

Por ejemplo, esto debería funcionar:
$> ./powerset 3 1 0 2 4 5 3 | cat -e
3$
0 3$
1 2$
1 0 2$
$> ./powerset 12 5 2 1 8 4 3 7 11 | cat -e
8 4$
1 11$
1 4 7$
1 8 3$
2 3 7$
5 7$
5 4 3$
5 2 1 4$
$> ./powerset 0 1 -1 | cat -e
$
1 -1$
$> ./powerset 7 3 8 2 | cat -e

// Other tests:
$> ./powerset 100 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 | cat -e
...
$> ./powerset -1 1 2 3 4 5 -10 | cat -e
...
$> ./powerset 0 -1 1 2 3 -2 | cat -e
...
$> ./powerset 13 65 23 3 4 6 7 1 2 | cat -e
...
$> ./powerset 10 0 1 2 3 4 5 6 7 8 9 | cat -e
...*/