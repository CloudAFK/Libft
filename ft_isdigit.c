/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romasant <romasant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 00:08:41 by Cloud             #+#    #+#             */
/*   Updated: 2026/08/03 14:54:19 by romasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
#include <stdlib.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	(void) ac;
	int	(result) = 0;
	result = ft_isdigit(av[1][0]);
	if (result == 1)
		printf("Le charactere '%c' est un nombre !!", av[1][0]);
	else if (result == 0)
		printf("Le charactere '%c' n'est pas un nombre !!", av[1][0]);
	return (0);
}
*/