/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:53:06 by ahakki            #+#    #+#             */
/*   Updated: 2025/02/05 21:19:36 by ahakki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_abs(int a)
{
	return ((a >= 0) * a + (a < 0) * -a);
}

int	ft_max(int a, int b)
{
	return ((a >= b) * a + (a < b) * b);
}
