/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:13:44 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/11/27 11:34:37 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strlen(const char *s)
{
	int	count;

	if (s == NULL)
		return (-1);
	count = 0;
	while (s[count])
		count++;
	return (count);
}

int	ft_write(const char *s)
{
	int	i;

	if (s == NULL)
		return (-1);
	i = 0;
	while (s[i])
	{
		write(1, &(s[i]), 1);
		i++;
	}
	return (i);
}
