/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_donut_one_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:00:00 by user42            #+#    #+#             */
/*   Updated: 2025/05/08 13:52:26 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file donut.c
 * @brief ASCII animation of a rotating 3D donut (torus)
 *
 * This program creates a rotating 3D donut (torus) rendered with ASCII
 * characters in the terminal. It uses trigonometric calculations to project
 * a 3D torus onto a 2D display with simulated lighting effects.
 */

#include <string.h>
#include <stdio.h>
#include <math.h>

/** @brief Terminal screen width */
#define SCREEN_WIDTH 80
/** @brief Terminal screen height */
#define SCREEN_HEIGHT 22
/** @brief Total buffer size (width × height) */
#define BUFFER_SIZE 1760
/** @brief Full circle in radians (2π) */
#define FULL_CIRCLE 6.28
/** @brief Distance of torus from center */
#define DONUT_DIST 2.0
/** @brief View distance (camera Z position) */
#define VIEW_DIST 5.0

/**
 * @brief Stores rotation angles for the donut
 *
 * Controls the orientation of the donut in 3D space
 */
typedef struct s_rotation
{
	float	x;  /**< Rotation around X axis */
	float	y;  /**< Rotation around Y axis */
}	t_rotation;

/**
 * @brief Stores the output and depth buffers
 *
 * Output buffer holds ASCII characters for rendering,
 * while depth buffer tracks Z-depth for hidden surface removal
 */
typedef struct s_buffer
{
	char	output[BUFFER_SIZE];  /**< ASCII character screen buffer */
	float	depth[BUFFER_SIZE];   /**< Z-buffer for depth testing */
}	t_buffer;

/**
 * @brief Stores rendering parameters
 *
 * Contains configuration values that control the appearance and resolution
 */
typedef struct s_render
{
	char	*shades;      /**< ASCII characters for different light levels */
	float	ring_step;    /**< Angular step for inner ring (tube) */
	float	donut_step;   /**< Angular step for outer donut circle */
}	t_render;

/**
 * @brief Main donut animation state
 *
 * Contains all state information for the donut animation
 */
typedef struct s_donut
{
	t_rotation	rot;     /**< Current rotation angles */
	t_buffer	buf;     /**< Output and depth buffers */
	t_render	render;  /**< Rendering configuration */
}	t_donut;

/**
 * @brief Initialize the donut animation state
 *
 * Sets up initial values for rotation, rendering parameters, and buffers
 *
 * @param donut Pointer to donut structure to initialize
 */
void	init_donut(t_donut *donut)
{
	donut->rot.x = 0;
	donut->rot.y = 0;
	/** Characters from darkest to brightest for lighting effect */
	donut->render.shades = ".,-~:;=!*#$@";
	/** Higher values = lower resolution, faster rendering */
	donut->render.ring_step = 0.02;
	donut->render.donut_step = 0.07;
	/** Initialize buffers with empty space and zero depth */
	memset(donut->buf.output, ' ', BUFFER_SIZE);
	memset(donut->buf.depth, 0, BUFFER_SIZE * sizeof(float));
}

/**
 * @brief Clear buffers before rendering a new frame
 *
 * Resets the output buffer to spaces and depth buffer to zeros
 *
 * @param buf Pointer to buffer structure
 */
void	clear_buffers(t_buffer *buf)
{
	memset(buf->output, ' ', BUFFER_SIZE);
	memset(buf->depth, 0, BUFFER_SIZE * sizeof(float));
}

/**
 * @brief Calculate the projected 2D position of a 3D point
 *
 * Uses trigonometric formulas to project a point on the torus surface to
 * screen coordinates. Also calculates the depth (Z) value for z-buffering.
 *
 * @param angle_a Angle around the tube (inner circle)
 * @param angle_b Angle around the torus (outer circle)
 * @param depth Pointer to store the calculated depth value
 * @param rot Current rotation values
 * @return Screen buffer position or -1 if off-screen
 */
int	calc_position(float angle_a, float angle_b, float *depth, t_rotation rot)
{
	float	x_proj;    /* Projected X coordinate */
	float	y_proj;    /* Projected Y coordinate */
	float	radius;    /* Distance from center to current circle point */
	float	temp;      /* Temporary calculation value */
	int		position;  /* Buffer position */

	/* Calculate the circle of the donut at distance DONUT_DIST from center */
	radius = cos(angle_b) + DONUT_DIST;

	/* Calculate Z-coordinate inverse (depth) for projection */
	*depth = 1.0 / (sin(angle_a) * radius * sin(rot.x)
			+ sin(angle_b) * cos(rot.x) + VIEW_DIST);

	/* Calculate intermediate value used in multiple places */
	temp = sin(angle_a) * radius * cos(rot.x)
		- sin(angle_b) * sin(rot.x);

	/* Project 3D coordinates to 2D screen space */
	x_proj = 40 + 30 * *depth * (cos(angle_a) * radius * cos(rot.y)
			- temp * sin(rot.y));
	y_proj = 12 + 15 * *depth * (cos(angle_a) * radius * sin(rot.y)
			+ temp * cos(rot.y));

	/* Check if the point is within screen boundaries */
	position = -1;
	if (y_proj > 0 && y_proj < SCREEN_HEIGHT
		&& x_proj > 0 && x_proj < SCREEN_WIDTH)
	{
		position = (int)x_proj + SCREEN_WIDTH * (int)y_proj;
	}
	return (position);
}

/**
 * @brief Calculate lighting value for a point on the donut
 *
 * Determines how illuminated a point is based on its orientation
 * relative to a fixed light source. Higher values = brighter.
 *
 * @param angle_a Angle around the tube (inner circle)
 * @param angle_b Angle around the torus (outer circle)
 * @param rot Current rotation values
 * @return Light intensity (0-11 range)
 */
int	calc_light(float angle_a, float angle_b, t_rotation rot)
{
	float	light;       /* Calculated light intensity */
	int		light_level; /* Discretized light level */

	/* Calculate dot product between surface normal and light direction */
	light = 8.0 * ((sin(angle_b) * sin(rot.x)
				- sin(angle_a) * cos(angle_b) * cos(rot.x))
			* cos(rot.y) - sin(angle_a) * cos(angle_b) * sin(rot.x)
			- sin(angle_b) * cos(rot.x)
			- cos(angle_a) * cos(angle_b) * sin(rot.y));

	/* Convert to integer and ensure non-negative value */
	light_level = (int)light;
	if (light_level < 0)
	{
		light_level = 0;
	}
	return (light_level);
}

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
void	render_point(float angle_a, float angle_b, t_donut *donut)
{
	int		position;    /* Buffer position */
	int		light;       /* Light level (0-11) */
	float	point_depth; /* Z depth of this point */

	/* Calculate screen position and depth */
	position = calc_position(angle_a, angle_b, &point_depth, donut->rot);
	if (position != -1)
	{
		/* Calculate lighting for this point */
		light = calc_light(angle_a, angle_b, donut->rot);

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
void	render_frame(t_donut *donut)
{
	float	angle_a; /* Current angle around the tube */
	float	angle_b; /* Current angle around the donut */

	/* Clear output and depth buffers */
	clear_buffers(&donut->buf);

	/* Outer loop: iterate around the donut (torus) */
	angle_b = 0;
	while (angle_b < FULL_CIRCLE)
	{
		/* Inner loop: iterate around the tube */
		angle_a = 0;
		while (angle_a < FULL_CIRCLE)
		{
			render_point(angle_a, angle_b, donut);
			angle_a += donut->render.ring_step;
		}
		angle_b += donut->render.donut_step;
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
void	print_frame(t_donut *donut)
{
	int	i;          /* Buffer index */
	int	is_line_end; /* Flag for end of line detection */

	/* Move cursor to home position (top-left corner) */
	printf("\x1b[H");

	/* Output each character in the buffer */
	i = 0;
	while (i < BUFFER_SIZE)
	{
		is_line_end = i % SCREEN_WIDTH;
		if (is_line_end == 0 && i > 0)
		{
			/* Insert newline at end of each screen row */
			putchar('\n');
		}
		else
		{
			/* Print the ASCII character at this position */
			putchar(donut->buf.output[i]);
		}
		i++;
	}
}

/**
 * @brief Update rotation angles for animation
 *
 * Increments the rotation angles to create the spinning effect
 *
 * @param donut Pointer to donut structure
 */
void	update_rotation(t_donut *donut)
{
	donut->rot.x += 0.04; /* X rotation speed */
	donut->rot.y += 0.02; /* Y rotation speed */
}

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
	init_donut(&donut);

	/* Clear the screen using ANSI escape code */
	printf("\x1b[2J");

	/* Animation loop */
	while (1)
	{
		/* Render a new frame */
		render_frame(&donut);

		/* Display the frame */
		print_frame(&donut);

		/* Update rotation for next frame */
		update_rotation(&donut);
	}
	return (0);
}
