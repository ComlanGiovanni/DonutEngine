/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:55:32 by gicomlan          #+#    #+#             */
/*   Updated: 2025/05/08 13:55:41 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.c
 * @brief Main entry point for ft_donut ASCII animation
 */

#include "ft_donut.h"

/**
 * @brief Main program entry point
 *
 * Initializes the donut and runs the animation loop
 *
 * @return 0 on successful execution
 */
int	main(void)
{
	t_donut	donut; /* Main animation state */

	/* Initialize the donut state */
	ft_init_donut(&donut);

	/* Clear the screen using ANSI escape code */
	ft_clear_screen();

	/* Animation loop */
	while (1)
	{
		/* Render a new frame */
		ft_render_frame(&donut);

		/* Display the frame */
		ft_print_frame(&donut);

		/* Update rotation for next frame */
		ft_update_rotation(&donut);
	}
	return (0);
}
