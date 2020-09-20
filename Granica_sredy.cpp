#include <iostream>
#include <fstream> 
#include <math.h>
#include <conio.h>

using namespace std;

#define M 1000  //количество разбиений по Х
#define N 1000  //количество разбиений по У

double f(double x, double y, double s1, double t1)
{
	return (1 / sqrt((x - s1) * (x - s1) + (y - t1) * (y - t1) + (x * x + y * y))) - (1 / sqrt((x - s1) * (x - s1) + (y - t1) * (y - t1) + 1210000));     //функция 
}

int main(int argc, char* argv[])
{
	double integral = 0.0;  //начальное значение интеграла
	double x0 = 0.0;
	double y0 = 0.0;
	double x1 = 0.0;
	double y1 = 0.0;
	double s = 0.0;
	double t = 0.0;
	double g = 0.370; //скачок плотности
	int i = 0;
	int j = 0;
	double a = 0.0;
	double b = 0.0;
	double c = 0.0;
	double d = 0.0; //пределы интегрирования по х(a,b), y(c,d)
	double dx = 0.0;
	double dy = 0.0;

	//расчет гравитационного поля; запись в файл
	ofstream out("Out_pole.txt");
	for (s = -3.0; s < 4.0; s++)
	{
		for (t = -3.0; t < 4.0; t++)
		{
			a = s - 1.0;
			b = s + 1.0;
			c = t - 1.0;
			d = t + 1.0;
			dx = (b - a) / M;
			dy = (d - c) / N;
			for (i = 1, x0 = a; i < M + 1; i++)
			{
				x1 = x0 + dx;
				for (j = 1, y0 = c; j < N + 1; j++)
				{
					y1 = y0 + dy;
					integral += f((x0 + x1) / 2., (y0 + y1) / 2., s, t); //накопление интегральной суммы
					y0 = y1;
				}
				x0 = x1;
			}
			integral *= dx * dy;
			integral *= g;
			cout << "I = " << integral << endl; //результат
			//out << "{" << s << ", " << t << ", " << integral << "}, " << endl;
			out << integral << endl;
		}
	}
	out.close();

	cin.get();
	return 0;
}