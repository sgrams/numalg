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

semilogy(matrix_size, all_time, "linewidth", 4);
ylabel ("time");
xlabel ("matrix size");
title ("calculation time execution");
legend ("G", "G\\_SPARSE    ", "GS\\_1E-10", "GS\\_EIGEN", "LU\\_EIGEN", "location", "northwest");

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
title ("generate time execution");
legend ("G", "G\\_SPARSE    ", "GS\\_1E-10", "GS\\_EIGEN", "LU\\_EIGEN", "location", "northwest");

print -dpng ../../report/plots/02_gen_time_execution_all_methods.png;

###calc sparse abs error
gauss_sparse_abs = gauss_sparse(3:60,4);
seidel_eigen_abs = gs_eigen(3:60,4);
lu_eigen_abs = lu_eigen(3:60,4);
sparse_abs = [(gauss_sparse_abs), (seidel_eigen_abs), (lu_eigen_abs)];

plot(matrix_size, sparse_abs, "linewidth", 4);
ylabel ("abs error");
xlabel ("matrix size");
title ("calculation sparse methods abs error");
legend ("G\\_SPARSE    ", "GS\\_EIGEN", "LU\\_EIGEN", "location", "northwest");

print -dpng ../../report/plots/03_calc_abs_error_sparse_methods.png;

###calc norm abs error
gauss_abs = gauss(3:60,4);
seidel_1e10_abs = gs_1e10(3:60,4);
lu_eigen_abs = lu_eigen(3:60,4);
stanard_abs = [(gauss_abs), (seidel_1e10_abs)];

plot(matrix_size, stanard_abs, "linewidth", 4);
ylabel ("abs error");
xlabel ("matrix size");
title ("calculation standard methods abs error");
legend ("G  ","GS\\_1E-10   ", "location", "northwest");

print -dpng ../../report/plots/04_calc_abs_error_standard_methods.png;


###gen sparse abs error
gen_gauss_sparse_abs = gauss_sparse(3:60,8);
gen_seidel_eigen_abs = gs_eigen(3:60,8);
gen_lu_eigen_abs = lu_eigen(3:60,8);
gen_sparse_abs = [(gen_gauss_sparse_abs), (gen_seidel_eigen_abs), (gen_lu_eigen_abs)];

plot(matrix_size, gen_sparse_abs, "linewidth", 4);
ylabel ("abs error");
xlabel ("matrix size");
title ("generate sparse methods abs error");
legend ("G\\_SPARSE    ", "GS\\_EIGEN", "LU\\_EIGEN", "location", "northwest");

print -dpng ../../report/plots/05_gen_abs_error_sparse_methods.png;

###gen standard abs error
gen_gauss_abs = gauss(3:60,8);
gen_seidel_1e10_abs = gs_1e10(3:60,8);
gen_standard_abs = [(gen_gauss_abs), (gen_seidel_1e10_abs)];

plot(matrix_size, gen_standard_abs, "linewidth", 4);
ylabel ("abs error");
xlabel ("matrix size");
title ("generate standard methods abs error");
legend ("G", "GS\\_1E-10    ", "location", "northwest");

print -dpng ../../report/plots/06_gen_abs_error_standard_methods.png;








