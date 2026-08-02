/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cloudking <cloudking@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 13:41:27 by cloudking         #+#    #+#             */
/*   Updated: 2026/08/02 14:22:38 by cloudking        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_n;
	unsigned char	*src_n;

	size_t(i) = 0;
	dest_n = (unsigned char *)dest;
	src_n = (unsigned char *)src;
	while (i < n)
	{
		dest_n[i] = src_n[i];
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>

int main(void)
{
	char dest[6];
	char *src;

	src = "Hello";
	ft_memcpy(dest, src, sizeof(3));
	printf("Voici la nouvelle chaine : %s", dest);

}
*/