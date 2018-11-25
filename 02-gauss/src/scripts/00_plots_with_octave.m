graphics_toolkit ("fltk");
format long;
output_precision = 32;
load ../float_tests.csv;
load ../double_tests.csv;
load ../mytype_tests.csv;

### gauss float time
matrix_size_float = float_tests(:,1);
time_results_float = [float_tests(:,8), float_tests(:,9), float_tests(:,10)];
plot(matrix_size_float,time_results_float);
ylabel ("time[s]");
xlabel ("matrix size");
title  ("float time execution plot");
legend ("float standard", "float partial gauss", "float full gauss","location","north");

print -dpng ../plots/00_float_plot_time.png;

### gauss double time
matrix_size_double = double_tests(:,1);
time_results_double = [double_tests(:,8), double_tests(:,9), double_tests(:,10)];
plot(matrix_size_double,time_results_double);
ylabel ("time [s]");
xlabel ("matrix size");
title  ("double time execution plot");
legend ("double standard", "double partial gauss", "double full gauss","location","north");

print -dpng ../plots/01_double_plot_time.png;

### gauss mytype time
matrix_size_mytype = mytype_tests(:,1);
time_results_mytype = [mytype_tests(:,8), mytype_tests(:,9), mytype_tests(:,10)];
plot(matrix_size_mytype,time_results_mytype);
ylabel ("time [s]");
xlabel ("matrix size");
title  ("mytype time execution bar");
legend ("mytype standard", "mytype partial gauss", "mytype full gauss","location","north");

print -dpng ../plots/02_mytype_plot_time.png;


### abs float
abs_result_float = [float_tests(:,2), float_tests(:,3), float_tests(:,4)];
plot(matrix_size_float,abs_result_float);
ylabel ("abs");
xlabel ("matrix size");
title  ("float abs error");
legend ("float standard", "float partial gauss", "float full gauss","location","north");

print -dpng ../plots/03_float_plot_abs.png;

### abs double
abs_result_double = [double_tests(:,2), double_tests(:,3), double_tests(:,4)];
plot(matrix_size_double,abs_result_double);
ylabel ("abs");
xlabel ("matrix size");
title  ("double abs error");
legend ("double standard", "double partial gauss", "double full gauss","location","north");

print -dpng ../plots/04_double_plot_abs.png;

### rel float
rel_result_float = [float_tests(:,5), float_tests(:,6), float_tests(:,7)];
plot(matrix_size_float,rel_result_float);
ylabel ("relative error");
xlabel ("matrix size");
title  ("float relative error");
legend ("float standard", "float partial gauss", "float full gauss","location","north");

print -dpng ../plots/05_float_plot_rel.png;

### rel double
rel_result_double = [double_tests(:,5), double_tests(:,6), double_tests(:,7)];
plot(matrix_size_double,abs_result_double);
ylabel ("relative error");
xlabel ("matrix size");
title  ("double relative error");
legend ("double standard", "double partial gauss", "double full gauss","location","north");

print -dpng ../plots/06_double_plot_rel.png;