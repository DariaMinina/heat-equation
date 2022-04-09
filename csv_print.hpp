#ifndef csv_print_h
#define csv_print_h

#include <iostream>

using namespace std;

class Csv_visual
{
public:
    Csv_visual(){};
    ~Csv_visual(){ /*outfile.close(); */};
    int data_transfer(double *, int);  
};

int Csv_visual::data_transfer(double *x, int N)
{
    cout << "Номер_узла,значение_температуры\n";
    for (int i = 0; i < N; i++)
        cout << i << "," << x[i] << endl;
    return 0;
}

#endif 
