/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romasant <romasant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 00:14:29 by Cloud             #+#    #+#             */
/*   Updated: 2026/08/03 14:54:00 by romasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
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
	result = ft_isalnum(av[1][0]);
	if (result == 1)
		printf("Le charactere '%c' est alphanumeric !!", av[1][0]);
	else if (result == 0)
		printf("Le charactere '%c' n'est pas alphanumeric !!", av[1][0]);
	return (0);
}
*/