/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azulbukh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 19:22:01 by azulbukh          #+#    #+#             */
/*   Updated: 2018/03/22 19:28:04 by azulbukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int c;

	c = 0;
	if (!s || !f || !*s || !*f)
		return ;
	while (*s)
	{
		f(c, s);
		c++;
		s++;
	}
}