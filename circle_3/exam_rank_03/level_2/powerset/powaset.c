#include <stdlib.h>
#include <stdio.h>

int	*nums;			//array para guardar los num pasados como argumentos
int	target;			//numero objetivo sumando los enteros
int	actual[100];	//almacena temporalmente el subconjunto que estamos construyendo

void	powerset(int p_num, int size, int p_act, int suma)
{
	if (suma == target)		//si ya encontre la solucion
	{
		int	i = 0;
		while (i < p_act)
		{
			if (i > 0)		//imprimir el resultado
				printf(" ");
			printf("%d", actual[i++]);
		}
		printf("\n");
		return;
	}
	if (p_num >= size)		//si ya no quedan numeros por explorar
		return;
	powerset(p_num + 1, size, p_act, suma);
	actual[p_act] = nums[p_num];
	powerset(p_num + 1, size, p_act + 1, suma + nums[p_num]);
}
//p_num = posicion en el array nums[]
//size = cuantos numeros hay
//p_act = numeros que llevo en el subconjunto actual
//suma = cuanto suman los numeros que llevo

int	main(int ac, char **av)
{
	int	p_num = 0;
	if (ac < 3)				//valida argumentos
		return (1);
	target = atoi(av[1]);	//guarda el primer argv ya convertido a int
	if (!(nums = malloc(sizeof(int) * (ac - 2))))
		return (1);			//reserva memoria para los numeros
	while (p_num < ac - 2)	//rellena el array nums
	{						//con los argv ya convertidos a int
		nums[p_num] = atoi(av[p_num + 2]);
		p_num++;
	}//llama a la funcion recursiva
	powerset(0, ac - 2, 0, 0);	//0 = pos0, empieza al inicio, ac-2 = size, 
	free(nums);				//0 = subconjunto vacio, 0 = suma inicial
	return (0);
}
