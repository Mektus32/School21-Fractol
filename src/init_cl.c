/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 19:11:48 by ojessi            #+#    #+#             */
/*   Updated: 2019/07/29 20:34:39 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_change_params(t_fractol *frac)
{
	frac->cl->ret = clEnqueueWriteBuffer(frac->cl->command_queue,
	frac->cl->zoom, CL_TRUE, 0, sizeof(cl_double), &frac->zoom, 0, NULL, NULL);
	frac->cl->ret = clEnqueueWriteBuffer(frac->cl->command_queue,
	frac->cl->movey, CL_TRUE, 0, sizeof(cl_double), &frac->movey, 0, NULL,
	NULL);
	frac->cl->ret = clEnqueueWriteBuffer(frac->cl->command_queue,
	frac->cl->movex, CL_TRUE, 0, sizeof(cl_double), &frac->movex, 0, NULL,
	NULL);
	frac->cl->ret = clEnqueueWriteBuffer(frac->cl->command_queue,
	frac->cl->iterations, CL_TRUE, 0, sizeof(cl_int), &frac->iterations, 0,
	NULL, NULL);
	frac->cl->ret = clEnqueueWriteBuffer(frac->cl->command_queue,
	frac->cl->choise, CL_TRUE, 0, sizeof(cl_int), &frac->choise, 0, NULL, NULL);
	frac->cl->ret = clEnqueueWriteBuffer(frac->cl->command_queue,
	frac->cl->color, CL_TRUE, 0, sizeof(cl_int), &frac->color, 0, NULL, NULL);
	frac->cl->ret = clEnqueueWriteBuffer(frac->cl->command_queue,
	frac->cl->fracx0, CL_TRUE, 0, sizeof(cl_double), &frac->x0, 0, NULL, NULL);
	frac->cl->ret = clEnqueueWriteBuffer(frac->cl->command_queue,
	frac->cl->fracy0, CL_TRUE, 0, sizeof(cl_double), &frac->y0, 0, NULL, NULL);
	frac->cl->ret = clEnqueueWriteBuffer(frac->cl->command_queue,
	frac->cl->p, CL_TRUE, 0, sizeof(cl_int), &frac->p, 0, NULL, NULL);
}

void	ft_choise_frac(t_fractol *frac)
{
	ft_change_params(frac);
	if (frac->numfrac == 1)
	{
		ft_set_kernel_mandelbrot(frac->cl);
		frac->cl->ret = clEnqueueNDRangeKernel(frac->cl->command_queue,
		frac->cl->mandelbrot, 1, NULL, frac->cl->global_work_size, NULL, 0,
		NULL, NULL);
	}
	else if (frac->numfrac == 2)
	{
		ft_set_kernel_julia(frac->cl);
		frac->cl->ret = clEnqueueNDRangeKernel(frac->cl->command_queue,
		frac->cl->julia, 1, NULL, frac->cl->global_work_size, NULL, 0,
		NULL, NULL);
	}
	ft_next_choise_frac(frac);
	frac->cl->ret = clEnqueueReadBuffer(frac->cl->command_queue,
	frac->cl->img_data, CL_TRUE, 0, sizeof(int) * WIDTH * HEIGHT,
	frac->image->img_data, 0, NULL, NULL);
	mlx_put_image_to_window(frac->mlx_ptr, frac->win_ptr, frac->image->img_ptr,
	0, 0);
	ft_print_menu(frac);
}

void	ft_create_kernels(t_cl *cl)
{
	cl->mandelbrot = clCreateKernel(cl->program, "mandelbrot", &cl->ret);
	cl->julia = clCreateKernel(cl->program, "julia", &cl->ret);
	cl->ship = clCreateKernel(cl->program, "ship", &cl->ret);
	cl->mandelbrot_x = clCreateKernel(cl->program, "mandelbrot_x", &cl->ret);
	cl->img_data = clCreateBuffer(cl->context, CL_MEM_READ_WRITE, WIDTH * HEIGHT
	* sizeof(cl_int), NULL, &cl->ret);
	cl->zoom = clCreateBuffer(cl->context, CL_MEM_READ_WRITE, sizeof(cl_double),
	NULL, &cl->ret);
	cl->movey = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
	sizeof(cl_double), NULL, &cl->ret);
	cl->movex = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
	sizeof(cl_double), NULL, &cl->ret);
	cl->iterations = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
	sizeof(cl_int), NULL, &cl->ret);
	ft_next_create_kernels(cl);
}

void	ft_get_cl(t_cl *cl)
{
	int		fd;

	cl->ret = clGetPlatformIDs(1, &cl->platform_id, &cl->ret_num_platforms);
	cl->ret = clGetDeviceIDs(cl->platform_id, CL_DEVICE_TYPE_GPU, 1,
			&cl->device_id, &cl->ret_num_devices);
	cl->context = clCreateContext(NULL, 1, &cl->device_id, NULL, NULL,
			&cl->ret);
	cl->command_queue = clCreateCommandQueue(cl->context, cl->device_id, 0,
			&cl->ret);
	if ((fd = open(FILENAME, O_RDONLY)) < 0)
	{
		write(1, "File Error\n", 11);
		exit(0);
	}
	lstat(FILENAME, &cl->stats);
	cl->source_size = cl->stats.st_size;
	cl->source_str = (char*)malloc(sizeof(char) * (cl->source_size + 1));
	cl->source_str[cl->source_size] = '\0';
	read(fd, cl->source_str, cl->source_size);
	close(fd);
	cl->program = clCreateProgramWithSource(cl->context, 1,
	(const char**)&cl->source_str, (const size_t*)&cl->source_size, &cl->ret);
	cl->ret = clBuildProgram(cl->program, 1, &cl->device_id, NULL, NULL, NULL);
}

void	ft_init_cl(t_fractol *frac)
{
	frac->cl->global_work_size[0] = WIDTH * HEIGHT;
	ft_get_cl(frac->cl);
	ft_create_kernels(frac->cl);
	ft_choise_frac(frac);
}
