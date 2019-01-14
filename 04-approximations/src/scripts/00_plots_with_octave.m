graphics_toolkit ("gnuplot");
format long;
output_precision = 34;
load ../../csv/gauss.csv;
load ../../csv/gauss_plus.csv;
load ../../csv/gauss_minus.csv;
load ../../csv/gauss_sparse.csv
load ../../csv/gauss_sparse_plus.csv
load ../../csv/gauss_sparse_minus.csv
load ../../csv/gs_1e10.csv
load ../../csv/gs_1e10_plus.csv
load ../../csv/gs_1e10_minus.csv
load ../../csv/gs_eigen.csv
load ../../csv/gs_eigen_plus.csv
load ../../csv/gs_eigen_minus.csv
load ../../csv/lu_eigen.csv
load ../../csv/lu_eigen_plus.csv





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

##########################################plus######################minus

###calc gauss plus minus
gauss_time = gauss(3:60,3);
gauss_approx = gauss(3:60,2);
gauss_plus_approx = gauss_plus(3:60,2);
gauss_minus_approx = gauss_minus(3:60,2);
gauss_all = [(gauss_time), (gauss_approx), (gauss_plus_approx), (gauss_minus_approx)];

plot(matrix_size, gauss_all, "linewidth", 4);
ylabel ("time");
xlabel ("matrix size");
title ("CALC GAUSS");
legend("real\\_time", "approximation", "approximation (+1)", "approximation (-1)", "location", "northwest");

print -dpng ../../report/plots/07_calc_gauss_plus_minus_time.png;

###gen gauss plus minus
gen_gauss_time = gauss(3:60,7);
gen_gauss_approx = gauss(3:60,6);
gen_gauss_plus_approx = gauss_plus(3:60,6);
gen_gauss_minus_approx = gauss_minus(3:60,6);
gen_gauss_all = [(gen_gauss_time), (gen_gauss_approx), (gen_gauss_plus_approx), (gen_gauss_minus_approx)];

plot(matrix_size, gen_gauss_all, "linewidth", 4);
ylabel ("time");
xlabel ("matrix size");
title ("GEN GAUSS");
legend("real\\_time", "approximation", "approximation (+1)", "approximation (-1)", "location", "northwest");

print -dpng ../../report/plots/08_gen_gauss_plus_minus_time.png;

###calc gauss sparse plus minus
gauss_sparse_time = gauss_sparse(3:60,3);
gauss_sparse_approx = gauss_sparse(3:60,2);
gauss_sparse_plus_approx = gauss_sparse_plus(3:60,2);
gauss_sparse_minus_approx = gauss_sparse_minus(3:60,2);
gauss_sparse_all = [(gauss_sparse_time), (gauss_sparse_approx), (gauss_sparse_plus_approx), (gauss_sparse_minus_approx)];

plot(matrix_size, gauss_sparse_all, "linewidth", 4);
ylabel ("time");
xlabel ("matrix size");
title ("CALC G\\_SPARSE");
legend("real\\_time", "approximation", "approximation (+1)", "approximation (-1)", "location", "northwest");

print -dpng ../../report/plots/09_calc_gauss_sparse_plus_minus_time.png;

###gen gauss sparse plus minus
gen_gauss_sparse_time = gauss_sparse(3:60,7);
gen_gauss_sparse_approx = gauss_sparse(3:60,6);
gen_gauss_sparse_plus_approx = gauss_sparse_plus(3:60,6);
gen_gauss_sparse_minus_approx = gauss_sparse_minus(3:60,6);
gen_gauss_sparse_all = [(gen_gauss_sparse_time), (gen_gauss_sparse_approx), (gen_gauss_sparse_plus_approx), (gen_gauss_sparse_minus_approx)];

plot(matrix_size, gen_gauss_sparse_all, "linewidth", 4);
ylabel ("time");
xlabel ("matrix size");
title ("GEN G\\_SPARSE");
legend("real\\_time", "approximation", "approximation (+1)", "approximation (-1)", "location", "northwest");

print -dpng ../../report/plots/10_gen_gauss_sparse_plus_minus_time.png;

###calc gauss 1e10 plus minus
gauss_1e10_time = gs_1e10(3:60,3);
gauss_1e10_approx = gs_1e10(3:60,2);
gauss_1e10_plus_approx = gs_1e10_plus(3:60,2);
gauss_1e10_minus_approx = gs_1e10_minus(3:60,2);
gauss_1e10_all = [(gauss_1e10_time), (gauss_1e10_approx), (gauss_1e10_plus_approx), (gauss_1e10_minus_approx)];

plot(matrix_size, gauss_1e10_all, "linewidth", 4);
ylabel ("time");
xlabel ("matrix size");
title ("CALC GS\\_1E-10");
legend("real\\_time", "approximation", "approximation (+1)", "approximation (-1)", "location", "northwest");

print -dpng ../../report/plots/11_calc_gauss_1e10_plus_minus_time.png;

###calc gauss 1e10 plus minus
gen_gauss_1e10_time = gs_1e10(3:60,7);
gen_gauss_1e10_approx = gs_1e10(3:60,6);
gen_gauss_1e10_plus_approx = gs_1e10_plus(3:60,6);
gen_gauss_1e10_minus_approx = gs_1e10_minus(3:60,6);
gen_gauss_1e10_all = [(gen_gauss_1e10_time), (gen_gauss_1e10_approx), (gen_gauss_1e10_plus_approx), (gen_gauss_1e10_minus_approx)];

plot(matrix_size, gen_gauss_1e10_all, "linewidth", 4);
ylabel ("time");
xlabel ("matrix size");
title ("GEN GS\\_1E-10");
legend("real\\_time", "approximation", "approximation (+1)", "approximation (-1)", "location", "northwest");

print -dpng ../../report/plots/12_calc_gauss_1e10_plus_minus_time.png;

###calc gauss eigen plus minus
gs_eigen_time = gs_eigen(3:60,3);
gs_eigen_approx = gs_eigen(3:60,2);
gs_eigen_plus_approx = gs_eigen_plus(3:60,2);
gs_eigen_minus_approx = gs_eigen_minus(3:60,2);
gs_eigen_all = [(gs_eigen_time), (gs_eigen_approx), (gs_eigen_plus_approx), (gs_eigen_minus_approx)];

plot(matrix_size, gs_eigen_all, "linewidth", 4);
ylabel ("time");
xlabel ("matrix size");
title ("CALC GS\\_EIGEN");
legend("real\\_time", "approximation", "approximation (+1)", "approximation (-1)", "location", "northwest");

print -dpng ../../report/plots/13_calc_gauss_eigen_plus_minus_time.png;

###gen gauss eigen plus minus
gen_gs_eigen_time = gs_eigen(3:60,7);
gen_gs_eigen_approx = gs_eigen(3:60,6);
gen_gs_eigen_plus_approx = gs_eigen_plus(3:60,6);
gen_gs_eigen_minus_approx = gs_eigen_minus(3:60,6);
gen_gs_eigen_all = [(gen_gs_eigen_time), (gen_gs_eigen_approx), (gen_gs_eigen_plus_approx), (gen_gs_eigen_minus_approx)];

plot(matrix_size, gen_gs_eigen_all, "linewidth", 4);
ylabel ("time");
xlabel ("matrix size");
title ("GEN GS\\_EIGEN");
legend("real\\_time", "approximation", "approximation (+1)", "approximation (-1)", "location", "northwest");

print -dpng ../../report/plots/14_gen_gauss_eigen_plus_minus_time.png;

###calc lu eigen plus minus
lu_eigen_time = lu_eigen(3:60,3);
lu_eigen_approx = lu_eigen(3:60,2);
lu_eigen_plus_approx = lu_eigen_plus(3:60,2);
lu_eigen_all = [(lu_eigen_time), (lu_eigen_approx), (lu_eigen_plus_approx)];

plot(matrix_size, lu_eigen_all, "linewidth", 4);
ylabel ("time");
xlabel ("matrix size");
title ("CALC LU\\_EIGEN");
legend("real\\_time", "approximation", "approximation (+1)", "location", "northwest");

print -dpng ../../report/plots/15_calc_lu_eigen_plus_minus_time.png;

###gen lu eigen plus minus
gen_lu_eigen_time = lu_eigen(3:60,7);
gen_lu_eigen_approx = lu_eigen(3:60,6);
gen_lu_eigen_plus_approx = lu_eigen_plus(3:60,6);
gen_lu_eigen_all = [(gen_lu_eigen_time), (gen_lu_eigen_approx), (gen_lu_eigen_plus_approx)];

plot(matrix_size, gen_lu_eigen_all, "linewidth", 4);
ylabel ("time");
xlabel ("matrix size");
title ("GEN LU\\_EIGEN");
legend("real\\_time", "approximation", "approximation (+1)", "location", "northwest");

print -dpng ../../report/plots/16_gen_lu_eigen_plus_minus_time.png;









