/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cloud <Cloud@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 23:44:15 by Cloud             #+#    #+#             */
/*   Updated: 2026/08/01 00:08:13 by Cloud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}
/*
#include <stdlib.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	int	(result) = 0;
	(void) ac;
	result = ft_isalpha(av[1][0]);
	if (result == 1)
		printf("Le charactere '%c' est une lettre !!", av[1][0]);
	else if (result == 0)
		printf("Le charactere '%c' n'est pas une lettre !!", av[1][0]);
	return (0);
}
*/