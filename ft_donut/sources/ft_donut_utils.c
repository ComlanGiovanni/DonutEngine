/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_donut_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:57:15 by gicomlan          #+#    #+#             */
/*   Updated: 2025/05/08 13:57:16 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_donut_utils.c
 * @brief Utility functions for the ft_donut project
 */

#include <unistd.h>
#include "ft_donut.h"

/**
 * @brief Write a character to standard output
 *
 * @param c Character to write
 */
void	ft_putchar(char c)
{
	write(1, &c, 1);
}

/**
 * @brief Fill memory with a constant byte
 *
 * @param s Memory area to fill
 * @param c Value to set (converted to unsigned char)
 * @param n Number of bytes to fill
 */
void	ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			index;

	ptr = (unsigned char *)s;
	index = 0;
	while (index < n)
	{
		ptr[index] = (unsigned char)c;
		index++;
	}
}

/**
 * @brief Move cursor to home position (top-left corner)
 *
 * Uses ANSI escape sequence
 */
void	ft_cursor_home(void)
{
	write(1, "\x1b[H", 3);
}

/**
 * @brief Clear the terminal screen
 *
 * Uses ANSI escape sequence
 */
void	ft_clear_screen(void)
{
	write(1, "\x1b[2J", 4);
}
