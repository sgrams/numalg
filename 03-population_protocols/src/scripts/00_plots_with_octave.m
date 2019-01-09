graphics_toolkit ("gnuplot");
format long;
output_precision = 34;
load ../../errors.csv;


### gauss float time

agent_count = errors(:,1);
abs_results = [errors(:,2), errors(:,3), errors(:,4), errors(:,5), errors(:,6), errors(:,7)];
plot(agent_count,abs_results);
ylabel ("error");
xlabel ("agents count");
title  ("Monte Carlo ABS errors");
legend ("Gauss", "Gauss Improved", "Gauss-Seidel Approx", "Gauss-Seidel Iterative", "Jacobi Iterative", "Jacobi Approx", "location","north");

print -dpng 00_gauss.png;