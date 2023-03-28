/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:29:45 by sbocanci          #+#    #+#             */
/*   Updated: 2023/03/28 14:24:51 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	uc;
	char			*last;

	last = NULL;
	uc = c;
	while (*s != '\0')
	{
		if (*s == uc)
			last = ((char *)s);
		s++;
	}
	if (uc == '\0')
		return ((char *)s);
	return (last);
}
