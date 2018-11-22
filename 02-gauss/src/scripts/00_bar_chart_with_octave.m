graphics_toolkit ("gnuplot");
format long;
output_precision = 32;
load ../float_tests.csv;
load ../double_tests.csv;
load ../mytype_tests.csv;

### time
matrix_size = float_tests(:,1);
time_results = [float_tests(:,8), float_tests(:,9), float_tests(:,10), double_tests(:,8), double_tests(:,9), double_tests(:,10), mytype_tests(:,8), mytype_tests(:,9), mytype_tests(:,10)];
bar(matrix_size,time_results);
ylabel ("time");
xlabel ("matrix size");
title  ("time execution bars");
legend ("float standard", "float partial gauss", "float full gauss", "double standard", "double partial gauss", "double full gauss", "mytype standard", "mytype partial gauss", "mytype full gauss");

print -dpng 01_plot_time.png;

### abs
abs_error = [float_tests(:,2), float_tests(:,3), float_tests(:,4), double_tests(:,2), double_tests(:,3), double_tests(:,4), mytype_tests(:,2), mytype_tests(:,3), mytype_tests(:,4)];
bar(matrix_size,abs_error);
ylabel ("abs error value");
xlabel ("matrix size");
title ("abs error bars");
legend ("float standard", "float partial gauss", "float full gauss", "double standard", "double partial gauss", "double full gauss", "mytype standard", "mytype partial gauss", "mytype full gauss");

### relative
rel_error = [float_tests(:,5), float_tests(:,6), float_tests(:,7), double_tests(:,5), double_tests(:,6), double_tests(:,7), mytype_tests(:,5), mytype_tests(:,6), mytype_tests(:,7)];
bar(matrix_size,rel_error);
ylabel ("relative error value");
xlabel ("matrix size");
title ("relative error bars");
legend ("float standard", "float partial gauss", "float full gauss", "double standard", "double partial gauss", "double full gauss", "mytype standard", "mytype partial gauss", "mytype full gauss");



