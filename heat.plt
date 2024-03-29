set terminal gif animate delay 100 font "Arial,10" ## как выводим
set encoding utf8

set xrange [-2 : 20] noreverse writeback ## диапазон по x
set yrange [-2 : 10] noreverse writeback ## диапазон по y
set grid 
set format x 
set format y 
set ytics 1
set xtics 1
set size ratio -1
set grid
set output "heat_equation.gif"
unset key
set title "Heat equation"

# define a palette with an exact number of colors
set palette maxcolors 5
set palette model RGB defined ( \
  0 "blue", \
  1 "green", \
  2 "yellow", \
  3 "orange", \
  4 "red")


# Define palette labels, the range matches the number of colors defined above
set cbrange [0:5]
set cbtics offset 0,+4 ( \
  '110' 0, \
  '120' 1, \
  '170' 2, \
  '195' 3, \
  '200' 4, \
  '' 5)


# define a function to map strings to palette indices
map_color(string) = ( \
  string eq 'color1' ? 0 : \
  string eq 'color2' ? 1 : \
  string eq 'color3' ? 2 : \
  string eq 'color4' ? 3 : \
  string eq 'color5' ? 4 : \
  5)

set arrow from 0,0 to 16,0 nohead
set arrow from 0,0 to 0,8 nohead
set arrow from 0,8 to 8,8 nohead
set arrow from 8,8 to 16,0 nohead
plot '-' using 1:2:(map_color(stringcolumn(3))) notitle with points pointtype 5 pointsize 1 palette
0 0 color5
1 0 color1
2 0 color1
3 0 color1
4 0 color1
5 0 color1
6 0 color1
7 0 color1
8 0 color1
9 0 color1
10 0 color1
11 0 color1
12 0 color1
13 0 color1
14 0 color1
15 0 color1
16 0 color1
0 1 color5
1 1 color4
2 1 color3
3 1 color2
4 1 color1
5 1 color1
6 1 color1
7 1 color1
8 1 color1
9 1 color1
10 1 color1
11 1 color1
12 1 color1
13 1 color1
14 1 color1
15 1 color1
0 2 color5
1 2 color4
2 2 color4
3 2 color3
4 2 color2
5 2 color1
6 2 color1
7 2 color1
8 2 color1
9 2 color1
10 2 color1
11 2 color1
12 2 color1
13 2 color1
14 2 color1
0 3 color5
1 3 color4
2 3 color4
3 3 color3
4 3 color2
5 3 color1
6 3 color1
7 3 color1
8 3 color1
9 3 color1
10 3 color1
11 3 color1
12 3 color1
13 3 color1
0 4 color5
1 4 color4
2 4 color4
3 4 color3
4 4 color2
5 4 color1
6 4 color1
7 4 color1
8 4 color1
9 4 color1
10 4 color1
11 4 color1
12 4 color1
0 5 color5
1 5 color4
2 5 color4
3 5 color3
4 5 color2
5 5 color1
6 5 color1
7 5 color1
8 5 color1
9 5 color1
10 5 color1
11 5 color1
0 6 color5
1 6 color4
2 6 color4
3 6 color3
4 6 color1
5 6 color1
6 6 color1
7 6 color1
8 6 color1
9 6 color1
10 6 color1
0 7 color5
1 7 color4
2 7 color3
3 7 color2
4 7 color1
5 7 color1
6 7 color1
7 7 color1
8 7 color1
9 7 color1
0 8 color5
1 8 color1
2 8 color1
3 8 color1
4 8 color1
5 8 color1
6 8 color1
7 8 color1
8 8 color1
EOD
