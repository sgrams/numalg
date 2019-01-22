graphics_toolkit ("gnuplot");
format long;
output_precision = 34;
load ../../csv/errors.csv;
load ../../csv/iterative.csv
load ../../csv/precisions.csv
load ../../csv/montecarlo.csv

### All methods compared to Monte Carlo simulation
agent_count = errors(:,1);
abs_results = [errors(:,2), errors(:,3), errors(:,4), errors(:,5), errors(:,6), errors(:,7)];
bar(agent_count, abs_results);
xlim([2.5 20.5]);
ylim([0 0.003]);
ylabel ("error");
xlabel ("agents count");
title  ("All methods compared to Monte Carlo simulation");
legend ("Gauss", "Gauss Improved", "Gauss-Seidel Approx.", "Gauss-Seidel Iterative", "Jacobi Approx.", "Jacobi Iterative", "location","northwest");
print -dpng ../../report/plots/01_abs_all_methods_all_rows.png;

### Execution times of all methods (varied agents)
agent_count = errors(:,1);
time_results = [errors(:,8), errors(:,9), errors(:,10), errors(:,11), errors(:,12), errors(:,13)];
plot(agent_count, time_results, "linewidth", 5);
xlim([3 20]);
ylabel ("time");
xlabel ("agents count")
title ("Execution times of all methods (varied agents)")
legend ("Gauss", "Gauss Improved", "Gauss-Seidel Approx.", "Gauss-Seidel Iterative", "Jacobi Approx.", "Jacobi Iterative", "location","north");
print -dpng ../../report/plots/02_time_execution_all_methods.png;

### Difference of Gauss-Seidel and Jacobi iterative methods
iterations = iterative(1701:1800,2);
abs_results = (iterative(1701:1800,3) - iterative(1701:1800,4));
plot(iterations, abs_results, "linewidth", 5, "k");
xlim([3 1000]);
%ylim([-1 1]);
ylabel ("error");
xlabel ("iterations");
title ("Difference of Gauss-Seidel and Jacobi iterative methods");
legend ("Gauss-Seidel and Jacobi iterative methods difference", "location", "northeast");
print -dpng ../../report/plots/03_abs_iterative_methods_all_rows.png;

### Execution times of iterative methods
iterations = iterative(1701:1800,2);
plot(iterations, iterative(1701:1800,5), "-", "linewidth", 5, iterations, iterative(1701:1800,6), "-", "linewidth", 5);
ylabel ("time");
xlabel ("iterations");
title ("Execution times of iterative methods");
legend ("Gauss-Seidel", "Jacobi", "location", "northwest");

print -dpng ../../report/plots/04_time_iterative_methods_all_rows.png;


### Difference of Gauss-Seidel and Jacobi precision methods
epsi = precisions(273:288,2);
abs_results = (precisions(273:288,3) - precisions(273:288,4));
semilogx(epsi, abs_results, "linewidth", 5);
xlim([0.00000000000001 0.0001])
ylim([-1 1])
ylabel ("error");
xlabel ("precision");
title ("Difference of Gauss-Seidel and Jacobi precision methods");
legend ("Gauss-Seidel and Jacobi precision methods difference", "location", "northwest");
print -dpng ../../report/plots/05_abs_precision_methods_all_rows.png;


### Execution times of precision methods
epsi = precisions(273:288,2);
time_results = [precisions(273:288,5), precisions(273:288,6)];
semilogx(epsi, time_results, "linewidth", 5);
xlim([0.00000000000001 0.0001])
ylabel ("time");
xlabel ("precision");
title ("Execution times of precision methods");
legend ("Gauss-Seidel", "Jacobi", "location", "northwest");
print -dpng ../../report/plots/06_time_precision_methods_all_rows.png;

### Difference of PG and PGS methods
agent_count = errors(:,1);
abs_results = (errors(:,2) - errors(:,3));
plot(agent_count, abs_results, "linewidth", 5, "m");
xlim([3 20]);
ylabel ("error");
xlabel ("agents count");
title  ("Difference of PG and PGS methods");
legend ("Difference of PG and PGS methods", "location","south");
print -dpng ../../report/plots/07_abs_gauss_and_gauss_optimized_all_rows.png;

### Monte Carlo iterations for N=5, error to PGS method
iteration_count = montecarlo(:,1);
abs_results = montecarlo(:,2)
plot(iteration_count, abs_results, "linewidth", 2, "b");
xlim([10 10000]);
ylabel ("error");
xlabel ("iterations count");
title  ("Monte Carlo iterations for N=5, error to PGS method");
legend ("N=5, error to PGS method", "location","north");
print -dpng ../../report/plots/08_abs_gauss_and_montecarlo_iterations_rows.png;
