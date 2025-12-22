#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

typedef struct
{
	float x, y;
} City;

float	calculate_distance(City a, City b)
{
	float	dx = a.x - b.x;
	float	dy = a.y - b.y;
	return sqrtf(dx * dx + dy * dy);
}

float	calculate_total_distance(City *cities, int *path, int n)
{
	float	total = 0.0f;
	int	i;

	while (i < n -1)
	{
		total += calculate_distance(cities[path[i]])
	}
}