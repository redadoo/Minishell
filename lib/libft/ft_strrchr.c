/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:43:11 by evocatur          #+#    #+#             */
/*   Updated: 2023/09/18 16:18:21 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ischarfind;

	ischarfind = NULL;
	if (s != NULL)
	{
		while (*s)
		{
			if (*s == (char)c)
				ischarfind = (char *)s;
			s++;
		}
	}
	if ((char)c == *s)
		ischarfind = (char *)s;
	return (ischarfind);
}
