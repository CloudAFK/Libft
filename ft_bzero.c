/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romasant <romasant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 14:53:52 by romasant          #+#    #+#             */
/*   Updated: 2026/08/03 14:53:52 by romasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	size_t (i) = 0;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	str[] = "Hello, World!";
	size_t	i;

	printf("Avant bzero : \"%s\"\n", str);

	ft_bzero(str, 5);

	printf("Après bzero (affichage caractère par caractère) :\n");

	for (i = 0; i < sizeof(str); i++)
	{
		if (str[i] == '\0')
			printf("\\0 ");
		else
			printf("%c ", str[i]);
	}
	printf("\n");

	return (0);
}
*/