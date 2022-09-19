#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

const double NEARZERO = 1.0e-10;       // interpretation of "zero"

using vec    = vector<double>;         // vector
using matrix = vector<vec>;            // matrix (=collection of (row) vectors)

// Prototypes
void print( string title, const vec &V );
void print( string title, const matrix &A );
vec matrixTimesVector( const matrix &A, const vec &V );
vec vectorCombination( double a, const vec &U, double b, const vec &V );
double innerProduct( const vec &U, const vec &V );
double vectorNorm( const vec &V );
vec conjugateGradientSolver( const matrix &A, const vec &B );


//======================================================================


int main()
{
	int N = 117;	
	//matrix A(N + 1);
	vec b(N);
   //matrix A = { { 4, 1 }, { 1, 3 } };
   //A.reserve(N + 1);
   //vec b = { 1, 2 };
   //b.reserve(N + 1);
   //vector < vector <int> > a(n, vector <int> (m) ); // Объявление вектора на n строк по m элементов 
   matrix A(N, vec(N));
   cout << A.size() << " " << b.size() << endl;
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
    	for (int j = 0; j < N; j++) {
    		A[i][j] = 1.0e-9;
    		//cout << A[i][j] << endl;
    	}
      b[i] = 1.0e-9;
      //cout << b[i] << endl;

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


   vec X = conjugateGradientSolver(A, b);

   //cout << "Solves AX = B\n";
   //print( "\nA:", A );
   //print( "\nB:", B );
   print( "\nX:", X );
   print( "\nCheck AX:", matrixTimesVector( A, X ) );
}


//======================================================================


void print( string title, const vec &V )
{
   cout << title << '\n';

   int n = V.size();           
   for ( int i = 0; i < n; i++ )
   {
      double x = V[i];   if ( abs( x ) < NEARZERO ) x = 0.0;
      cout << x << '\t';
   }
   cout << '\n';
}


//======================================================================


void print( string title, const matrix &A )
{
   cout << title << '\n';

   int m = A.size(), n = A[0].size();                      // A is an m x n matrix
   for ( int i = 0; i < m; i++ )
   {
      for ( int j = 0; j < n; j++ )
      {
         double x = A[i][j];   if ( abs( x ) < NEARZERO ) x = 0.0;
         cout << x << '\t';
      }
      cout << '\n';
   }
}


//======================================================================


vec matrixTimesVector( const matrix &A, const vec &V )     // Matrix times vector
{
   int n = A.size();
   vec C( n );
   for ( int i = 0; i < n; i++ ) C[i] = innerProduct( A[i], V );
   return C;
}


//======================================================================


vec vectorCombination( double a, const vec &U, double b, const vec &V )        // Linear combination of vectors
{
   int n = U.size();
   vec W( n );
   for ( int j = 0; j < n; j++ ) W[j] = a * U[j] + b * V[j];
   return W;
}


//======================================================================


double innerProduct( const vec &U, const vec &V )          // Inner product of U and V
{
   return inner_product( U.begin(), U.end(), V.begin(), 0.0 );
}


//======================================================================


double vectorNorm( const vec &V )                          // Vector norm
{
   return sqrt( innerProduct( V, V ) );
}


//======================================================================


vec conjugateGradientSolver( const matrix &A, const vec &B )
{
   double TOLERANCE = 1.0e-10;

   int n = A.size();
   vec X( n, 0.0 );

   vec R = B;
   vec P = R;
   int k = 0;

   while ( k < n )
   {
      vec Rold = R;                                         // Store previous residual
      vec AP = matrixTimesVector( A, P );

      double alpha = innerProduct( R, R ) / max( innerProduct( P, AP ), NEARZERO );
      X = vectorCombination( 1.0, X, alpha, P );            // Next estimate of solution
      R = vectorCombination( 1.0, R, -alpha, AP );          // Residual 

      if ( vectorNorm( R ) < TOLERANCE ) break;             // Convergence test

      double beta = innerProduct( R, R ) / max( innerProduct( Rold, Rold ), NEARZERO );
      P = vectorCombination( 1.0, R, beta, P );             // Next gradient
      k++;
   }

   return X;
}