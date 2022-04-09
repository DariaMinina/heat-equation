#ifndef gnu_print_h
#define gnu_print_h

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Dot  //класс для вывода результата с помощью точек
{
private:
    double x;
    double y;
public:
    Dot(){};
    Dot(double xx, double yy): x(xx), y(yy) {};
    double get_x(){return x;};
    double get_y(){return y;};
    friend ostream& operator<< (ostream &out, Dot &dot)
    {
        out << dot.get_x() << " " << dot.get_y();
        return out;
    };
    
};

class Gnu_visual
{
private:
    vector<Dot> dots;
    vector<string> color;
    int II;
    int JJ;
    int n;
public:
    Gnu_visual();
    ~Gnu_visual(){ /*outfile.close(); */};
    void build_figure(int, int);
    int data_transfer(double *, double, double, int);
    
};

Gnu_visual::Gnu_visual()
{

    cout << "set terminal gif animate delay 100 font \"Arial,10\" ## как выводим\n";
    cout << "set encoding utf8\n\n";
    cout << "set xrange [-2 : 20] noreverse writeback ## диапазон по x\n";
    cout << "set yrange [-2 : 10] noreverse writeback ## диапазон по y\n";
    cout << "set grid ""\n";
    cout << "set format x ""\n";
    cout << "set format y ""\n";
    cout << "set ytics 1\n";
    cout << "set xtics 1\n";
    cout << "set size ratio -1\n";
    cout << "set grid\n";
    cout << "set output \"heat_equation.gif\"\n";
    cout << "unset key\n";
    cout << "set title \"Heat equation\"\n\n";
    cout << "# define a palette with an exact number of colors\n";
    cout << "set palette maxcolors 5\n";
    cout << "set palette model RGB defined ( \\" << endl;;
    cout << "  0 \"blue\", \\" << endl;
    cout << "  1 \"green\", \\" << endl;
    cout << "  2 \"yellow\", \\" << endl;
    cout << "  3 \"orange\", \\" << endl;
    cout << "  4 \"red\")\n\n\n";
    cout << "# Define palette labels, the range matches the number of colors defined above\n";
    cout << "set cbrange [0:5]\n";
    cout << "set cbtics offset 0,+4 ( \\" << endl;
    cout << "  '110' 0, \\" << endl;
    cout << "  '120' 1, \\" << endl;
    cout << "  '170' 2, \\" << endl;
    cout << "  '195' 3, \\" << endl;
    cout << "  '200' 4, \\" << endl;
    cout << "  '' 5)\n\n\n";
    cout << "# define a function to map strings to palette indices\n";
    cout << "map_color(string) = ( \\" << endl;
    cout << "  string eq 'color1' ? 0 : \\" << endl;
    cout << "  string eq 'color2' ? 1 : \\" << endl;
    cout << "  string eq 'color3' ? 2 : \\" << endl;
    cout << "  string eq 'color4' ? 3 : \\" << endl;
    cout << "  string eq 'color5' ? 4 : \\" << endl;
    cout << "  5)\n\n";

}

void Gnu_visual::build_figure(int I, int J)
{
	II = I;
	JJ = J;
    cout << "set arrow from 0,0 to "<< I << ",0 nohead\n";
    cout << "set arrow from 0,0 to 0," << J << " nohead\n";
    cout << "set arrow from 0,"<< J << " to "<< J << "," << J << " nohead\n";
    cout << "set arrow from "<< J << "," << J << " to " << I << ",0 nohead\n";
    
}

int Gnu_visual::data_transfer(double *x, double hx, double hy, int N)
{
    cout << "plot '-' using 1:2:(map_color(stringcolumn(3))) notitle with points pointtype 5 pointsize 1 palette\n";
    
    double middle_I; 
    int node_number;

    middle_I = II;
    node_number = 0;

    n = N;

    for (double j = 0; j <= JJ; j = j + hy) {
        for (double i = 0; i <= middle_I; i = i + hx) {
            dots.push_back(Dot(i, j));
            if (x[node_number] >= 195 && x[node_number] <= 200) {
                color.push_back("color5");
            } else if (x[node_number] >= 130 && x[node_number] <= 200) {
                color.push_back("color4");
            } else if (x[node_number] >= 120 && x[node_number] <= 200) {
                color.push_back("color3");
            } else if (x[node_number] >= 110 && x[node_number] <= 200) {
                color.push_back("color2");
            } else {
                color.push_back("color1");
            }
            node_number++;
        }
        
        middle_I = middle_I - hx;
    }

    for (int i = 0; i < n; i++){
        cout << dots[i] << " " << color[i] << "\n";
    }
    cout << "EOD" << endl;
                
    return 0;
};

#endif /* gnu_print_h */

