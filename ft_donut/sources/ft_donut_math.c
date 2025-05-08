/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_donut_math.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:58:20 by gicomlan          #+#    #+#             */
/*   Updated: 2025/05/08 13:58:22 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_donut_math.c
 * @brief Mathematical calculations for 3D projection
 */

#include "ft_donut.h"

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
int	ft_calc_position(float angle_a, float angle_b, float *depth, t_rotation rot)
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
int	ft_calc_light(float angle_a, float angle_b, t_rotation rot)
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
