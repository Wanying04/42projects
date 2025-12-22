#include <stdio.h>
#include <stdlib.h>

int	*nums;
int	target;
int	actual[100];

void	powerset(int p_num, int	amount, int p_act, int sum)
{
	if (sum == target)
	{
		int	i = 0;
		while (i < p_act)
		{
			if (i > 0)
				printf(" ");
			printf("%d", actual[i++]);
		}
		printf("\n");
		return;
	}
	if (p_num >= amount)
		return;
	powerset(p_num + 1, amount, p_act, sum);
	actual[p_act] = nums[p_num];
	powerset(p_num + 1, amount, p_act + 1, sum + num[p_num]);
}

int	main(int ac, char **av)
{
	int	i = 0;

	if (ac < 3 || !(nums = malloc(sizeof(int) * (ac - 2))))
		return 1;
	target = atoi(av[1]);
	while (i < ac - 2)
		nums[i] = atoi(av[2 + (i++)]);
	powerset(0, ac - 2, 0, 0);
	free(nums);
	return 0;
}


#include <stdio.h>
#include <stdlib.h>

int	*nums;
int	target;
int	actual[100];

void	powerset(int p_num, int amount, int p_act, int sum)
{
	if (sum == target)
	{
		int	i = 0;
		while (i < p_act)
		{
			if (i > 0)
				printf(" ");
			printf("%d", actual[i++]);
		}
		printf("\n");
		return;
	}
	if (p_num >= amount)
		return;
	powerset(p_num + 1, amount, p_act, sum);
	actual[p_act] = nums[p_num];
	powerset(p_num + 1, amount, p_act + 1, sum + nums[p_num]);
}

int	main(int ac, char **av)
{
	int	i = 0;

	if (ac < 3 || !(nums = malloc(sizeof(int) * (ac - 2))))
		return 1;
	target = atoi(av[1]);
	while (i < ac - 2)
		nums[i] = atoi(av[2 + (i++)]);
	powerset(0, ac - 2, 0, 0);
	free(nums);
	return 0;
}
