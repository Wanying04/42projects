/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:26:46 by wtang             #+#    #+#             */
/*   Updated: 2025/06/19 19:39:59 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	max(int* tab, unsigned int len)
{
	int	max;
	unsigned int	i;

	if (len == 0)
		return (0);
	max = tab[0]; //should be AFTER len == 0, otherwise SEGMENTATION FAULT; better use index
	i = 1;
	while (i < len)
	{
		if (tab[i] > max)
			max = tab[i];
		i++;
	}
	return (max);
}
