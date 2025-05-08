/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_donut_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:59:01 by gicomlan          #+#    #+#             */
/*   Updated: 2025/05/08 14:00:44 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_donut_render.c
 * @brief Rendering functions for the donut animation
 */

#include "ft_donut.h"

/**
 * @brief Render a single point on the donut
 *
 * Calculates position and lighting for one point and updates
 * the buffer if this point is visible (passes z-buffer test)
 *
 * @param angle_a Angle around the tube (inner circle)
 * @param angle_b Angle around the torus (outer circle)
 * @param donut Pointer to donut structure
 */
void	ft_render_point(float angle_a, float angle_b, t_donut *donut)
{
	int		position;    /* Buffer position */
	int		light;       /* Light level (0-11) */
	float	point_depth; /* Z depth of this point */

	/* Calculate screen position and depth */
	position = ft_calc_position(angle_a, angle_b, &point_depth, donut->rot);
	if (position != -1)
	{
		/* Calculate lighting for this point */
		light = ft_calc_light(angle_a, angle_b, donut->rot);

		/* Z-buffer test: only render if this point is closer than existing */
		if (point_depth > donut->buf.depth[position])
		{
			donut->buf.depth[position] = point_depth;
			donut->buf.output[position] = donut->render.shades[light];
		}
	}
}

/**
 * @brief Render a complete frame of the donut
 *
 * Iterates through all points on the donut surface and renders each one,
 * sampling the surface with steps defined in the render configuration.
 *
 * @param donut Pointer to donut structure
 */
void    ft_render_frame(t_donut *donut)
{
    float   tube_angle;      /* Angle around the tube (was angle_a) */
    float   main_angle;      /* Angle around the main circle (was angle_b) */

    ft_clear_buffers(&donut->buf);

    /* Outer loop: iterate around the main circle of the torus */
    main_angle = 0;
    while (main_angle < FULL_CIRCLE)
    {
        /* Inner loop: iterate around the tube cross-section */
        tube_angle = 0;
        while (tube_angle < FULL_CIRCLE)
        {
            ft_render_point(tube_angle, main_angle, donut);
            tube_angle += donut->render.tube_step;
        }
        main_angle += donut->render.main_circle_step;
    }
}

/**
 * @brief Print the current frame to the terminal
 *
 * Outputs the ASCII characters in the buffer to create the donut image.
 * Uses ANSI escape codes to position cursor at top-left before drawing.
 *
 * @param donut Pointer to donut structure
 */
void	ft_print_frame(t_donut *donut)
{
	int	buffer_index;  /* Current position in buffer */
	int	is_line_end;   /* Flag for end of line detection */

	/* Move cursor to home position (top-left corner) */
	ft_cursor_home();

	/* Output each character in the buffer */
	buffer_index = 0;
	while (buffer_index < BUFFER_SIZE)
	{
		is_line_end = buffer_index % SCREEN_WIDTH;
		if (is_line_end == 0 && buffer_index > 0)
		{
			/* Insert newline at end of each screen row */
			ft_putchar('\n');
		}
		else
		{
			/* Print the ASCII character at this position */
			ft_putchar(donut->buf.output[buffer_index]);
		}
		buffer_index++;
	}
}

/**
 * @brief Update rotation angles for animation
 *
 * Increments the rotation angles to create the spinning effect
 *
 * @param donut Pointer to donut structure
 */
void	ft_update_rotation(t_donut *donut)
{
	donut->rot.x += 0.04; /* X rotation speed */
	donut->rot.y += 0.02; /* Y rotation speed */
}
