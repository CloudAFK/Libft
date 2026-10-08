/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romasant <romasant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 18:59:13 by romasant          #+#    #+#             */
/*   Updated: 2026/10/08 22:25:51 by romasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t counter_str;
	size_t	last_index;

	counter_str = 0;
	last_index = 0;
	while (s[counter_str])
	{
		if (c == s[counter_str] && !s[counter_str])
			last_index = counter_str;
		counter_str++;
	}
	if (c == '\0')
		return ((char *)s);
	if (!s[counter_str] && last_index != 0)
			return ((char *)s);
	return (NULL);
}

#include <stdio.h>

int	main(int ac, char **av)
{
	(void) ac;
	char	*str;
	char	c;
	char	*result;

	str = av[1];
	c = av[2][0];
	result = ft_strrchr(str, c);
	if (result == NULL)
	{
		printf("Aucune occurence trouve pour %c\n", c);
		return (0);
	}
	printf("%s\n", result);
	return (0);
}
