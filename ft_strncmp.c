/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cloud <Cloud@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 14:44:14 by Cloud             #+#    #+#             */
/*   Updated: 2026/08/03 14:44:14 by Cloud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t (i) = 0;
	while ((s1[i] || s2[i]) && i <= n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>

int main(int ac, char **av)
{
    (void) ac;
    printf("Voici la difference en ASCII des
    deux chaines : %d", ft_strncmp(av[1], av[2], 3));
    return (0);
}
*/