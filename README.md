# heat-equation
Решение стационарной задачи теплопроводности Методом конечных разностей (МКР) для пластины в форме трапеции

**heat.cpp** - файл, в котором реализован МКР, то есть: наложены ГУ, составлена система линейных алгебраических уравнений (СЛАУ), учитаны размеры пластины, задано количество узлов и шаг сетки. СЛАУ решена с помощью метода Гаусса.

**gnu_print.hpp** - описан класс и его методы, для представления данных в файле .plt (под словом "данные" понимается значения температур в узлах). 
**csv_print.hpp** - вывод данных в формате .csv.

Перенаправив результат работы программы в файл **heat.plt**, получим файл, который можно передать gnuplot для представления данных на графике.
**heat_equation.gif** - файл с визуализированными данными (результат работы gnuplot)

Перенаправив результат работы программы в файл **data.csv**, получим значения температур в формате таблицы (1 столбец - номер узла, 2 столбец - значение температуры)

Корректно запускать файлы таким образом:

1. g++ heat.cpp -std=c++11
2. ./a.out > heat.plt (или ./a.out > data117.csv)
3. gnuplot heat.plt
4. open heat_equation.gif

Для быстрого запуска разработан скрипт **script_heat**, в нем реализованы все пункты выше.

bash script_heat

Результат для 425 узлов:


<img width="610" alt="heat" src="https://user-images.githubusercontent.com/87333725/162577106-9b66aa59-48e6-4bd7-ab08-088965fdf8e1.png">

