/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:35:59 by daniel-esca       #+#    #+#             */
/*   Updated: 2025/04/16 12:36:19 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "../minirt.h"

// ft_hit_cylinder.c
void	init_cylinder_cal(t_cylinder *cylinder, t_ray *ray, t_cy_data *d);
float	ft_hit_caps(t_cylinder *cylinder, t_cy_data *d, float result, int i);
void	cy_calc(t_cylinder *cylinder, t_ray *ray, t_cy_data *d);
void	ft_init_data(t_cylinder *cylinder, t_cy_data *d);
void	ft_hit_cylinder(t_cylinder *cylinder, t_ray *ray, bool *hit);

// ft_hit_sphere.c
void	ft_hit_sphere(t_sphere *sphere, t_ray *ray, bool *hit);

// ft_light_utils.c
t_vec3	ft_difuse_light(t_light *light, t_hit *hit);
int		ft_shadow(t_image *image, t_hit	*hit);
t_vec3	ft_light_point(t_light *light, t_hit *hit, t_vec3 color);

// ft_maths2.c
t_vec3	ft_vec3(double a, double b, double c);
double	ft_len_sqr(t_vec3 v);
double	ft_len(t_vec3 v);
t_vec3	ft_float_to_vec3(double a);

// ft_maths3.c
t_vec3	ft_clamp(t_vec3 color);
t_vec3	ft_normalice(t_vec3 vec);
t_vec3	ft_scale(t_vec3 value, double scale);

// ft_cuadratic.c
t_vec2	ft_cuadratic(double a, double b, double c);

// ft_maths.c
double	ft_dot(t_vec3 a, t_vec3 b);
t_vec3	ft_cross(t_vec3 a, t_vec3 b);
double	ft_length_squared(t_vec3 vec);
t_vec3	ft_norm(t_vec3 v);

// ft_per_pixel.c
int		ft_hit_anything(t_image *image, t_ray *ray);
t_vec3	ft_per_pixel(t_image *image, t_vec2 coord);

// ft_operations.c
t_vec3	ft_add(t_vec3 a, t_vec3 b);
t_vec3	ft_sub(t_vec3 a, t_vec3 b);
t_vec3	ft_mult(t_vec3 a, t_vec3 b);
double	safe_divide(double a, double b);
t_vec3	ft_divide(t_vec3 a, t_vec3 b);

// ft_render.c
void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
int		ft_convert_rgba(t_vec3 color);
void	ft_init_camera(t_image *image);
void	ft_create_render(t_mlx *data, t_image *image);

// ft_color_utils.c
int		check_rgb(int color);
t_vec3	ft_scale_color(t_vec3 color, double f);
t_vec3	ft_adjust_color(t_vec3 color, t_vec3 adjuster);

// ft_hit_plane.c
void	ft_hit_plane(t_plane *plane, t_ray *ray, bool *hit);

#endif
