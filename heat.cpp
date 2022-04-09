#include <iostream>
#include <cmath>
#include "gnu_print.hpp"
//#include "csv_print.hpp"

using namespace std;

const int N = 117;  // N = 117, 425

double* gauss(double A[N][N], double b[N], int n) {

  double *x;
  x = new double[n];
  double d, s;

	for (int k = 0; k < N; k++) // прямой ход
	{
		for (int j = k + 1; j < N; j++)
		{		
			d = A[j][k] / A[k][k]; // формула (1)

			for (int i = k; i < N; i++)
			{
				A[j][i] = A[j][i] - d * A[k][i]; // формула (2)

			}
			b[j] = b[j] - d * b[k]; // формула (3)
		}
	}
	for (int k = N - 1; k >= 0; k--) // обратный ход
	{
		d = 0;

		for (int j = k + 1; j < N; j++)
		{
			s = A[k][j] * x[j]; // формула (4)
			d = d + s; // формула (4)
		}
		x[k] = (b[k] - d) / A[k][k]; // формула (4)
	}

  return x;
}

int main(){

	double A[N][N]; // матрица для значений каждого узла
	double b[N]; //вектор свободных переменных
	double *x; //решение
	int l1 = 16; // длина фигуры по оси x
	int l2 = 8; // длина фигуры по оси y
	double T1 = 200; // граничное условие (ГУ) для грани слева
	double T2 = 100; // ГУ для грани снизу и сверху


	const double hx = 1; // шаг сетки по оси x // 1, 0.5
	const double hy = 1; // шаг сетки по оси y / 1, 0.5

	// количество узлов (максимальное) по каждой из оси
	const int I = l1 / hx; 
	const int J = l2 / hy;

	//cout << I << " " << J << endl;

	// примем начальные значения в матрице и в векторе b равными нулю
	for (int i = 0; i < N; i++)
	{
    	for (int j = 0; j < N; j++)
        	A[i][j] = 0;
        	b[i] = 0;
	}

	// нижние ГУ
	for(int i = 0; i <= I; i++) {
		A[i][i] = 1;
		b[i] = T2;
	}


	int I_node = I + 1; // задание промежуточных значений
	int k = 1; 
	int I_node_old = 0;

	while (I_node < N - J - 1) { // внутренние узлы по оси икс

		for (int i = I_node + 1; i < I_node + I - k; i++) {
			A[i][i - 1] = 1 * hy * hy; // левый узел
			A[i][i] = - 2 * hy * hy - 2 * hx * hx; // центральный узел
			A[i][i + 1] = 1 * hy * hy; // правый узел
			A[i][i - I_node] = 1 * hx * hx; // нижний узел
			A[i][i + I_node - 1] = 1 * hx * hx; // верхний узел
		}


		A[I_node][I_node] = 1; // левые ГУ
		b[I_node] = T1; 

		I_node_old = I_node;
		I_node = I_node + I - k + 1; // шаг по узлам

		A[I_node - 1][I_node_old - 3] = 1;
		A[I_node - 1][I_node - 1] = -1;
		b[I_node - 1] = 40 * sqrt(hx * hx + hy * hy);
		
		k++;
	}

	// верхние ГУ
	for(int i = N - J - 1; i < N; i++) {
		A[i][i] = 1;
		b[i] = T2;
	}

	A[0][0] = 1; // значение нулевого узла примем равным значению ГУ левой грани
	b[0] = T1;

	A[N - J - 1][N - J - 1] = 1; // значение верхнего левого узла примем = ГУ левой грани
	b[N - J - 1] = T1;

	x = gauss(A, b, N);

  Gnu_visual gnu;
  gnu.build_figure(l1, l2);
  gnu.data_transfer(x, hx, hy, N);
 
  /*
  Csv_visual csv;
  csv.data_transfer(x, N);
  */

	return 0;

}
