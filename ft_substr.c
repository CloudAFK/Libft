/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romasant <romasant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 18:13:23 by romasant          #+#    #+#             */
/*   Updated: 2026/10/17 19:00:38 by romasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	counter;

	counter = 0;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	str = malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);
	while (len-- && s[start] != '\0')
	{
		str[counter] = s[start + counter];
		counter++;
	}
	str[counter] = '\0';
	return (str);
}
