/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_donut_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:57:54 by gicomlan          #+#    #+#             */
/*   Updated: 2025/05/08 14:13:45 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_donut_init.c
 * @brief Initialization functions for the ft_donut project
 */

#include "ft_donut.h"

/**
 * @brief Initialize the donut animation state
 *
 * Sets up initial values for rotation, rendering parameters, and buffers
 *
 * @param donut Pointer to donut structure to initialize
 */
void	ft_init_donut(t_donut *donut)
{
	donut->rot.x = 0;
	donut->rot.y = 0;
	/** Characters from darkest to brightest for lighting effect */
	donut->render.shades = ".,-~:;=!*#$@";
	/** Higher values = lower resolution, faster rendering */
	donut->render.ring_step = 0.02;
	donut->render.main_circle_step = 0.07;
	/** Initialize buffers with empty space and zero depth */
	ft_memset(donut->buf.output, ' ', BUFFER_SIZE);
	ft_memset(donut->buf.depth, 0, BUFFER_SIZE * sizeof(float));
}

/**
 * @brief Clear buffers before rendering a new frame
 *
 * Resets the output buffer to spaces and depth buffer to zeros
 *
 * @param buf Pointer to buffer structure
 */
void	ft_clear_buffers(t_buffer *buf)
{
	ft_memset(buf->output, ' ', BUFFER_SIZE);
	ft_memset(buf->depth, 0, BUFFER_SIZE * sizeof(float));
}
