/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cloud <Cloud@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 00:20:00 by Cloud             #+#    #+#             */
/*   Updated: 2026/08/01 10:34:53 by Cloud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(char *str)
{
	int (i) = 0;
	while (str[i])
		i++;
	return (i);
}
/*
#include <stdio.h>

int	main(int ac, char **av)
{
	(void) ac;
	printf("La size de la chaine est de : %d", ft_strlen(av[1]));
	return (0);
}
*/