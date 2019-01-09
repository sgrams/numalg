graphics_toolkit ("gnuplot");
format long;
output_precision = 34;
load ../../errors.csv;

### test
agent_count = errors(12:13,1);
abs_results = [errors(12:13,2), errors(12:13,3), errors(12:13,4), errors(12:13,5), errors(12:13,6), errors(12:13,7)];
ylabel ("error");
xlabel ("agents count");
plot(agent_count, abs_results);
%ylim([0.108 0.1111]);
%ylim([0.250733 0.250734]);




print -dpng 00_test.png;



### algorithms abs errors all rows
agent_count = errors(:,1);
abs_results = [errors(:,2), errors(:,3), errors(:,4), errors(:,5), errors(:,6), errors(:,7)];
ylabel ("error");
xlabel ("agents count");
bar(agent_count, abs_results);
title  ("Monte Carlo ABS errors all");
legend ("Gauss", "Gauss Improved", "Gauss-Seidel Approx", "Gauss-Seidel Iterative", "Jacobi Iterative", "Jacobi Approx", "location","north");

print -dpng 01_abs_all_methods_all_rows.png;

### algorithms abs errors on last rows
agent_count = errors(12:13,1);
abs_results = [errors(12:13,2), errors(12:13,3), errors(12:13,4), errors(12:13,5), errors(12:13,6), errors(12:13,7)];
ylabel ("error");
xlabel ("agents count");
plot(agent_count, abs_results);
title  ("Monte Carlo ABS errors last rows");
legend ("Gauss", "Gauss Improved", "Gauss-Seidel Approx", "Gauss-Seidel Iterative", "Jacobi Iterative", "Jacobi Approx", "location","northwest");


print -dpng 02_abs_all_methods_last_rows.png;

### time execution based on agents
agent_count = errors(:,1);
time_results = [errors(:,8), errors(:,9), errors(:,10), errors(:,11), errors(:,12), errors(:,13)];
ylabel ("time");
xlabel ("agents count")
plot(agent_count, time_results);


