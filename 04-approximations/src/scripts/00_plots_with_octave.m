graphics_toolkit ("gnuplot");
format long;
output_precision = 34;
load ../../csv/gauss.csv;
load ../../csv/gauss_sparse.csv
load ../../csv/gs_1e10.csv
load ../../csv/gs_eigen.csv
load ../../csv/lu_eigen.csv


###all methods calc execution time

matrix_size = gauss(3:60,1);

gauss_time = gauss(3:60,3);
gauss_sparse_time = gauss_sparse(3:60,3);
seidel_1e10_time = gs_1e10(3:60,3);
seidel_eigen_time = gs_eigen(3:60,3);
lu_eigen_time = lu_eigen(3:60,3);
all_time = [(gauss_time), (gauss_sparse_time), (seidel_1e10_time), (seidel_eigen_time), (lu_eigen_time)];

plot(matrix_size, all_time, "linewidth", 4);
ylabel ("time");
xlabel ("matrix size");
title ("Calculation time execution");
legend ("Gauss", "Gauss-Sparse", "Gauss-Seidel 1e-10", "Gauss-Seidel-Sparse 1e-10", "SparseLU", "location", "northwest");

print -dpng ../../report/plots/01_calc_time_execution_all_methods.png;

###all methods gen execution time
gen_gauss_time = gauss(3:60,7);
gen_gauss_sparse_time = gauss_sparse(3:60,7);
gen_seidel_1e10_time = gs_1e10(3:60,7);
gen_seidel_eigen_time = gs_eigen(3:60,7);
gen_lu_eigen_time = lu_eigen(3:60,7);
gen_all_time = [(gen_gauss_time), (gen_gauss_sparse_time), (gen_seidel_1e10_time), (gen_seidel_eigen_time), (gen_lu_eigen_time)];

plot(matrix_size, gen_all_time, "linewidth", 4);
ylabel ("time");
xlabel ("matrix size");
title ("Generate time execution");
legend ("Gauss", "Gauss-Sparse", "Gauss-Seidel 1e-10", "Gauss-Seidel-Sparse 1e-10", "SparseLU", "location", "northwest");

print -dpng ../../report/plots/02_gen_time_execution_all_methods.png;

###calc all methods abs error
gauss_abs = gauss(3:60,4);
gauss_sparse_abs = gauss_sparse(3:60,4);
seidel_1e10_abs = gs_1e10(3:60,4);
seidel_eigen_abs = gs_eigen(3:60,4);
lu_eigen_abs = lu_eigen(3:60,4);
all_time = [(gauss_abs), (gauss_sparse_abs), (seidel_1e10_abs), (seidel_eigen_abs), (lu_eigen_abs)];

plot(matrix_size, all_time, "linewidth", 4);
ylabel ("abs error");
xlabel ("matrix size");
title ("Calculation abs error");
legend ("Gauss", "Gauss-Sparse", "Gauss-Seidel 1e-10", "Gauss-Seidel-Sparse 1e-10", "SparseLU", "location", "northwest");

print -dpng ../../report/plots/03_calc_abs_error_all_methods.png;

###calc all methods rel error
gauss_rel = gauss(3:60,5);
gauss_sparse_rel = gauss_sparse(3:60,5);
seidel_1e10_rel = gs_1e10(3:60,5);
seidel_eigen_rel = gs_eigen(3:60,5);
lu_eigen_rel = lu_eigen(3:60,5);
all_time = [(gauss_rel), (gauss_sparse_rel), (seidel_1e10_rel), (seidel_eigen_rel), (lu_eigen_rel)];

plot(matrix_size, all_time, "linewidth", 4);
ylabel ("rel error");
xlabel ("matrix size");
title ("Calculation rel error");
legend ("Gauss", "Gauss-Sparse", "Gauss-Seidel 1e-10", "Gauss-Seidel-Sparse 1e-10", "SparseLU", "location", "northeast");

print -dpng ../../report/plots/04_calc_rel_error_all_methods.png;







