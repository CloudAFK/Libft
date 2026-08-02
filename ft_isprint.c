/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 11:00:36 by Cloud             #+#    #+#             */
/*   Updated: 2026/08/01 13:55:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	return (c >= 0 && c <= 127);
}
#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	(void) ac;
	int	(result) = ft_isprint(atoi(av[1]));
	if (result == 1)
		printf("Le char '%s' est printable", av[1]);
	else
		printf("Le char '%s' n'est pas printable", av[1]);
	return (0);
}