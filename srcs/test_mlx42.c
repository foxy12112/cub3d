// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   test_mlx42.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/03/20 10:29:23 by psostari          #+#    #+#             */
// /*   Updated: 2025/03/20 10:29:26 by psostari         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../MLX42/MLX42.h"
// #include <stdio.h>
// #include <stdlib.h>

// void hook(void* param)
// {
// 	(void)param;

// }

// int main(void)
// {
// 	mlx_t* mlx = mlx_init(800, 600, "Hello MLX42", true);
// 	if (!mlx)
// 	{
// 		fprintf(stderr, "Error initializing MLX42\n");
// 		return (1);
// 	}

// 	mlx_loop_hook(mlx, &hook, NULL);
// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (0);
// }
