/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 17:00:28 by ojessi            #+#    #+#             */
/*   Updated: 2019/07/19 19:18:32 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*int 	main(void)
{
	int		A;
	int		B;
	int		i;
	double	a, b, x, y, t, n = 15;
	printf("Mandelbrot Set\n");
	for (B = 0; B <= 4 * n; B++)
	{
		b = 2 - (B / n);
		for (A = 0; A <= 4 * n; A++)
		{
			a = -2 + (A / n);
			x = 0;
			y = 0;
			for (i = 1; i <= 100; i++)
			{
				t = x;
				x = (x * x) - (y * y) + a;
				y = (2 * t * y) + b;
				if ((x * x) + (y * y) > 4)
				{
					if (i >= 0 && i <= 1)
						printf("%d", i - 1);
					else
						printf("%d", i);
					break;
				}
			}
			if (i == 101)
				printf(".");
			else
				printf(" ");
		}
		printf("\n");
	}
	return (0);
}*/

int		main(void)
{
	int		i, n = 100;
	double	x0, y0, t;
	
	
	for (int y = 0; y < 100; y++)//Проход по всем значениям Y
	{
		for (int x = 0; x < 100; x++)//Проход по всем значениям X
		{
			i = 0;//Обнуляем количество итерация для аждой точи
			x0 = 0;//Ставим начальные значения для точки
			y0 = 0;
			while (i < n)
			{
				t = x0;//Запоминаем значения для того чтобы потом правильно посчитать Y0
				x0 = (x0 * x0) - (y0 * y0) + (-3 + (x / 10.));//Считаем X0n+1
				y0 = (2 * x0 * y0) + (3 - (y / 10.));//Считаем Y0n+1
				if ((x0 * x0) + (y0 * y0) > 4)//Сравниваем модуль числа
				{
					if (i >= 0 && i <= 1)
						printf("%d", i);
					else
						printf("%d", i);
					break;//Перестаем считать итерации для точи, которая вышла за пределы 2
				}
					i++;//Увеличиваем итерации в цикле
			}
			if (n != i)//Если точа вышла раньше чем дошла до границы итерации, то печатаем значени на котором она вышла
				printf(" ");
			else if (i == n)
				printf(".");//Иначе печатаем 0
		}
		printf("\n");//Делаем перенос строки
	}
	return (0);
}