graphics_toolkit ("gnuplot");
format long;
output_precision = 32;
load ../output_m4.csv;

### exp(sin(x))
plot (output_m4(:,1), output_m4(:,2),
      output_m4(:,1), output_m4(:,3),
      output_m4(:,1), output_m4(:,4),
      output_m4(:,1), output_m4(:,5),
      output_m4(:,1), output_m4(:,6));

ylabel ("exp(sin(x))");
xlabel ("arguments");
title  ("Plot of exp(sin(x))");
legend ("func0", "func1", "func2", "func3", "func4");
print -dpng 01_functions_m4.png;

### diffs
plot (output_m4(:,1), fabsl (output_m4(:,2) - output_m4(:,3)));
ylabel ("fabsl (func0(x) - func1(x))");
xlabel ("arguments");
title  ("fabsl (func0(x) - func1(x))");
legend ("fabsl (func0(x) - func1(x))");
print -dpng 02_plot_diff_func0-func1_m4.png;

plot (output_m4(:,1), fabsl (output_m4(:,2) - output_m4(:,4)));
ylabel ("fabsl (func0(x) - func2(x))");
xlabel ("arguments");
title  ("fabsl (func0(x) - func2(x))");
legend ("fabsl (func0(x) - func2(x))");
print -dpng 03_plot_diff_func0-func2_m4.png;

plot (output_m4(:,1), fabsl (output_m4(:,2) - output_m4(:,5)));
ylabel ("fabsl (func0(x) - func3(x))");
xlabel ("arguments");
title  ("fabsl (func0(x) - func3(x))");
legend ("fabsl (func0(x) - func3(x))");
print -dpng 04_plot_diff_func0-func3_m4.png;

plot (output_m4(:,1), fabsl (output_m4(:,2) - output_m4(:,6)));
ylabel ("fabsl (func0(x) - func4(x))");
xlabel ("arguments");
title  ("fabsl (func0(x) - func4(x))");
legend ("fabsl (func0(x) - func4(x))");
print -dpng 05_plot_diff_func0-func4_m4.png;


### diffs 2
plot (output_m4(:,1), fabsl (output_m4(:,3) - output_m4(:,4)));
ylabel ("fabsl (func1(x) - func2(x))");
xlabel ("arguments");
title  ("fabsl (func1(x) - func2(x))");
legend ("fabsl (func1(x) - func2(x))");
print -dpng 06_plot_diff_func1-func2_m4.png;


plot (output_m4(:,1), fabsl (output_m4(:,5) - output_m4(:,6)));
ylabel ("fabsl (func3(x) - func4(x))");
xlabel ("arguments");
title  ("fabsq (func3(x) - func4(x))");
legend ("fabsl (func3(x) - func4(x))");
print -dpng 07_plot_diff_func3-func4_m4.png;
