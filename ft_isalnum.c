/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cloudking <cloudking@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:12:34 by cloudking         #+#    #+#             */
/*   Updated: 2026/10/03 16:23:38 by cloudking        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if (((c >= 65 && c <= 90)
			|| (c >= 97 && c <= 122))
		|| (c >= 48 && c <= 57))
		return (1);
	return (0);
}

/*
#include <stdio.h>

int	main(int ac, char **av)
{
	(void) ac;
	printf("Si 1 => alphanumerique\nSinon =>
	non alphanumerique\n\n Resultat : %d", ft_isalnum(av[1][0]));
	return (0);
}
*/