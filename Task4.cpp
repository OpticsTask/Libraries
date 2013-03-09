#include "stdafx.h"
#include "Task2-7.h"
#include <math.h>

int FunLib::Round(double value)
{
	if (value > 0)
		return (int) (value + 0.5);
	else
		return (int) (value - 0.5);
} 

double** FunLib::RotateMatrix(double **matrix, int N, double angle)
{
	double coord_x, coord_y;// координаты текущего вектора (x,y)
	// Создаем преобразованную матрицу
	double **matrixRotate = new double* [N];
	for(int i = 0; i < N; i++)
	{
		matrixRotate[i] = new double[N];
	}

	for(int i = 0; i < N; i++)//не нужно, это только для отладки
	{
		for(int j = 0; j < N; j++)//не нужно, это только для отладки
		{
			matrixRotate[i][j] = 0;
		}//не нужно, это только для отладки
	}

	int center = (N - 1) / 2;
	double angleRad = angle * L_PI / 180;
	double sinValue = sin(angleRad);
	double cosValue = cos(angleRad);

	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			// поворачиваем вектор (i - (N - 1), j - (N - 1)) на угол angle
			coord_x = (i - center) * cosValue + (j - center) * sinValue;
			coord_y = - (i - center) * sinValue + (j - center) * cosValue;
			//printf("(%0.2f, %0.2f)", coordinates[0], coordinates[1]);
			// Округляем координаты вектора
			coord_x = Round(coord_x);
			coord_y = Round(coord_y);
			// Проверяем, не выходим ли за границы массива
			if ( !((abs(coord_x) > center) || (abs(coord_y) > center)) )
			{
				coord_x  = coord_x  + center;
				coord_y  = coord_y  + center;

				matrixRotate[(int) coord_x ][ (int) coord_y] += matrix[i][j];
			}
		}
	}
	return matrixRotate;
}
