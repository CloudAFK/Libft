/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cloud <Cloud@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 10:36:41 by Cloud             #+#    #+#             */
/*   Updated: 2026/08/03 14:44:00 by Cloud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*
#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	(void) ac;
	int	result;
	result = ft_isascii(atoi(av[1]));
	if (result == 1)
		printf("Le char '%s' est un char Ascii", av[1]);
	else
		printf("Le char '%s' n'est pas un char Ascii", av[1]);
	return (0);
}
*/