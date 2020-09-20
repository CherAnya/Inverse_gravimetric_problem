#include <iostream>
#include <fstream> 
#include <math.h>
#include <conio.h>

using namespace std;

#define M 1000  
#define N 1000  
#define K 7
#define A 0.0007 //параметр регуляризации

float past[K][K];
float present[K][K];

double f(double x, double y, double s1, double t1, double z)
{
	return (1 / sqrt((x - s1) * (x - s1) + (y - t1) * (y - t1) + z * z)) - (1 / sqrt((x - s1) * (x - s1) + (y - t1) * (y - t1) + 1210000));     //для нахождения gridn
}

int main(int argc, char* argv[])
{
	float s[K] = {-3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0};
	float t[K] = { -3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0 };
	float grid[K][K] = { {	-0.755435,	-0.696257,	-0.642266,	-0.619078,	-0.642266,	-0.696257,	-0.755436	},
						{	-0.696257,	-0.59059,	-0.468554,	-0.405612,	-0.468554,	-0.59059,	-0.696256	},
						{	-0.642266,	-0.468554,	-0.185227,	0.0273407,	-0.185226,	-0.468554,	-0.642266	},
						{	-0.619078,	-0.405613,	0.0273403,	0.743134,	0.027342,	-0.405612,	-0.619078	},
						{	-0.642266,	-0.468554,	-0.185227,	0.0273407,	-0.185226,	-0.468554,	-0.642266	},
						{	-0.696257,	-0.59059,	-0.468554,	-0.405612,	-0.468554,	-0.59059,	-0.696256	},
						{	-0.755436,	-0.696257,	-0.642266,	-0.619078,	-0.642266,	-0.696257,	-0.755436	} };
	double gridn = 0.0;  
	double x0 = 0.0;
	double y0 = 0.0;
	double x1 = 0.0;
	double y1 = 0.0;
	double g = 0.370; //скачок плотности
	int i = 0;
	int j = 0;
	double a = 0.0;
	double b = 0.0;
	double c = 0.0;
	double d = 0.0; //пределы интегрирования x(a,b), y(c,d)
	double dx = 0.0;
	double dy = 0.0;

	for (int i1 = 0; i1 < K; i1++) {
		for (int j1 = 0; j1 < K; j1++) {
			past[i1][j1] = 1100;
		}
	}

	int iter = 0;
	float maxdiff = 0;

	ofstream out("Out.txt");
	do {
		for (int i1 = 0; i1 < K; i1++)
		{
			for (int j1 = 0; j1 < K; j1++)
			{
				a = s[i1] - 1.0;
				b = s[i1] + 1.0;
				c = t[j1] - 1.0;
				d = t[j1] + 1.0;
				dx = (b - a) / M;
				dy = (d - c) / N;
				for (i = 1, x0 = a; i < M + 1; i++)
				{
					x1 = x0 + dx;
					for (j = 1, y0 = c; j < N + 1; j++)
					{
						y1 = y0 + dy;
						gridn += f((x0 + x1) / 2., (y0 + y1) / 2., s[i1], t[j1], past[i1][j1]); 
						y0 = y1;
					}
					x0 = x1;
				}
				gridn *= dx * dy;
				gridn *= g;
				present[i1][j1] = past[i1][j1] / (1 + past[i1][j1] * A * (grid[i1][j1] - gridn));
				maxdiff = grid[i1][j1] - gridn;
				past[i1][j1] = present[i1][j1];
				cout << present[i1][j1] << endl;
				out << s[i1] << " " << t[j1] << " " << present[i1][j1] << endl;
			}
		}
	} while (maxdiff > 0.0001);
	out.close();

	cin.get();
	return 0;
}