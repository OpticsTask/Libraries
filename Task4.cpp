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
	double coord_x, coord_y;// ���������� �������� ������� (x,y)
	// ������� ��������������� �������
	double **matrixRotate = new double* [N];
	for(int i = 0; i < N; i++)
	{
		matrixRotate[i] = new double[N];
	}

	for(int i = 0; i < N; i++)//�� �����, ��� ������ ��� �������
	{
		for(int j = 0; j < N; j++)//�� �����, ��� ������ ��� �������
		{
			matrixRotate[i][j] = 0;
		}//�� �����, ��� ������ ��� �������
	}

	int center = (N - 1) / 2;
	double angleRad = angle * L_PI / 180;
	double sinValue = sin(angleRad);
	double cosValue = cos(angleRad);

	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			// ������������ ������ (i - (N - 1), j - (N - 1)) �� ���� angle
			coord_x = (i - center) * cosValue + (j - center) * sinValue;
			coord_y = - (i - center) * sinValue + (j - center) * cosValue;
			//printf("(%0.2f, %0.2f)", coordinates[0], coordinates[1]);
			// ��������� ���������� �������
			coord_x = Round(coord_x);
			coord_y = Round(coord_y);
			// ���������, �� ������� �� �� ������� �������
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
