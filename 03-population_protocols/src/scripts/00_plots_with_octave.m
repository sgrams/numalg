graphics_toolkit ("gnuplot");
format long;
output_precision = 34;
load ../../errors.csv;
load ../../iterative.csv
load ../../precisions.csv

### algorithms abs errors all rows
agent_count = errors(:,1);
abs_results = [errors(:,2), errors(:,3), errors(:,4), errors(:,5), errors(:,6), errors(:,7)];
bar(agent_count, abs_results);
xlim([19.5 30.5]);
ylim([0 0.02]);
ylabel ("error");
xlabel ("agents count");
title  ("Monte Carlo ABS errors all");
legend ("Gauss", "Gauss Improved", "Gauss-Seidel Approx", "Gauss-Seidel Iterative", "Jacobi Approx", "Jacobi Iterative", "location","northwest");

print -dpng ../../report/plots/01_abs_all_methods_all_rows.png;


### algorithms abs errors all rows
agent_count = errors(:,1);
plot(agent_count, errors(:,2), errors(:,3), "--", "linewidth", 5);
ylabel ("error");
xlabel ("agents count");
title  ("Monte Carlo ABS errors Gauss & Gauss Optimized");
legend ("Gauss", "Gauss Improved", "location","northwest");

print -dpng ../../report/plots/01_abs_all_methods_gauss.png;

agent_count = errors(:,1);
plot(agent_count, errors(:,4), errors(:,5), "linewidth", 5);
ylabel ("error");
xlabel ("agents count");
title  ("Monte Carlo ABS errors Gauss-Seidel Approx & Gauss-Seidel Iterative");
legend ("Gauss-Seidel Approx", "Gauss-Seidel Iterative", "location","northwest");

print -dpng ../../report/plots/01_abs_all_methods_gauss_seidel.png;

agent_count = errors(:,1);
plot(agent_count, errors(:,6), errors(:,7), "linewidth", 5);
ylabel ("error");
xlabel ("agents count");
title  ("Monte Carlo ABS errors Jacobi Approx & Jacobi Iterative");
legend ("Jacobi Approx", "Jacobi Iterative", "location","northwest");

print -dpng ../../report/plots/01_abs_all_methods_jacobi.png;


### time execution based on agents
agent_count = errors(:,1);
time_results = [errors(:,8), errors(:,9), errors(:,10), errors(:,11), errors(:,12), errors(:,13)];
plot(agent_count, time_results, "linewidth", 5);
xlim([3 50]);
ylabel ("time");
xlabel ("agents count")
title ("Time execution for all methods")
legend ("Gauss", "Gauss Improved", "Gauss-Seidel Approx", "Gauss-Seidel Iterative", "Jacobi Approx", "Jacobi Iterative", "location","north");

print -dpng ../../report/plots/02_time_execution_all_methods.png;

### abs iterative jacobi, seidel
iterations = iterative(1701:1800,2);
abs_results = (iterative(1701:1800,3) - iterative(1701:1800,4));
plot(iterations, abs_results, "linewidth", 5);
ylabel ("error");
xlabel ("iterations");
title ("ABS difference of Gauss-Seidel and Jacobi iterative");
legend ("Gauss-Seidel and Jacobi diff", "location", "northwest");

print -dpng ../../report/plots/03_abs_iterative_methods_all_rows.png;

### time execution iterative methods based on iterations
iterations = iterative(1701:1800,2);
plot(iterations, iterative(1701:1800,5), "-", "linewidth", 5, iterations, iterative(1701:1800,6), "-", "linewidth", 5);
ylabel ("time");
xlabel ("iterations");
title ("Time execution iterative methods");
legend ("Gauss-Seidel", "Jacobi", "location", "northwest");

print -dpng ../../report/plots/04_time_iterative_methods_all_rows.png;


### abs precision jacobi, seidel
epsi = precisions(847:863,2);
abs_results = (precisions(847:863,3) - precisions(847:863,4));
semilogx(epsi, abs_results, "linewidth", 5);
ylabel ("error");
xlabel ("precision");
title ("ABS difference of Gauss-Seidel and Jacobi precisions");
legend ("Gauss Seidel and Jacobi diff", "location", "northwest");

print -dpng ../../report/plots/05_abs_precision_methods_all_rows.png;


### time precision jacobi, seidel
epsi = precisions(847:863,2);
time_results = [precisions(847:863,5), precisions(847:863,6)];
semilogx(epsi, time_results, "linewidth", 5);
ylabel ("time");
xlabel ("precision");
title ("Time execution precisions methods");
legend ("Gauss-Seidel", "Jacobi", "location", "northeast");

print -dpng ../../report/plots/06_time_precision_methods_all_rows.png;

 ###abs gauss and gauss optimized
 agent_count = errors(:,1);
 abs_results = (errors(:,2) - errors(:,3));
 plot(agent_count, abs_results, "linewidth", 5);
 xlim([10 50]);
 ylabel ("error");
 xlabel ("agents count");
 title  ("ABS Gauss and Gauss Optimized difference");
 legend ("ABS Gauss and Gauss Optimized diff", "location","south");

 print -dpng ../../report/plots/07_abs_gauss_and_gauss_optimized_all_rows.png;













