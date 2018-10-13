/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_whitespace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolgin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 18:07:07 by avolgin           #+#    #+#             */
/*   Updated: 2017/11/12 18:08:35 by avolgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_is_whitespace(char c)
{
	if (c == '\n' || c == '\v' || c == '\t')
		return (1);
	else if (c == '\f' || c == ' ' || c == '\r')
		return (1);
	else
		return (0);
}
