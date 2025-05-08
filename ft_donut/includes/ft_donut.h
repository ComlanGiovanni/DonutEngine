/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_donut.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:55:48 by gicomlan          #+#    #+#             */
/*   Updated: 2025/05/08 14:13:25 by gicomlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DONUT_H
# define FT_DONUT_H

# include <math.h>
# include <stddef.h>

/** @brief Terminal screen width */
# define SCREEN_WIDTH 80
/** @brief Terminal screen height */
# define SCREEN_HEIGHT 22
/** @brief Total buffer size (width × height) */
# define BUFFER_SIZE 1760
/** @brief Full circle in radians (2π) */
/** @brief Full circle in radians (2π) */
# define FULL_CIRCLE 6.28
/** @brief Distance of torus from center */
# define DONUT_DIST 2.0
/** @brief View distance (camera Z position) */
# define VIEW_DIST 5.0

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
	float   main_circle_step;  /* Step size for the main circle (was donut_step) */
	//float	donut_step;   /**< Angular step for outer donut circle */
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

/* Utility functions (ft_donut_utils.c) */
void	ft_putchar(char c);
void	ft_memset(void *s, int c, size_t n);
void	ft_cursor_home(void);
void	ft_clear_screen(void);

/* Initialization functions (ft_donut_init.c) */
void	ft_init_donut(t_donut *donut);
void	ft_clear_buffers(t_buffer *buf);

/* Mathematical calculations (ft_donut_math.c) */
int		ft_calc_position(float angle_a, float angle_b, float *depth,
			t_rotation rot);
int		ft_calc_light(float angle_a, float angle_b, t_rotation rot);

/* Rendering functions (ft_donut_render.c) */
void	ft_render_point(float angle_a, float angle_b, t_donut *donut);
void	ft_render_frame(t_donut *donut);
void	ft_print_frame(t_donut *donut);
void	ft_update_rotation(t_donut *donut);

#endif
