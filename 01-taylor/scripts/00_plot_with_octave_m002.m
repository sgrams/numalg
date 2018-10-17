graphics_toolkit ("gnuplot");
format long;
output_precision = 32;
load ../output_m2.csv;

### exp(sin(x))
plot (output_m2(:,1), output_m2(:,2),
      output_m2(:,1), output_m2(:,3),
      output_m2(:,1), output_m2(:,4),
      output_m2(:,1), output_m2(:,5),
      output_m2(:,1), output_m2(:,6));

ylabel ("exp(sin(x))");
xlabel ("arguments");
title  ("Plot of exp(sin(x)), M=2");
legend ("func0", "func1", "func2", "func3", "func4");
print -dpng 01_functions_m002.png;

### diffs
plot (output_m2(:,1), abs (output_m2(:,2) - output_m2(:,3)));
ylabel ("abs (func0(x) - func1(x))");
xlabel ("arguments");
title  ("abs (func0(x) - func1(x)), M=2");
legend ("abs (func0(x) - func1(x))");
print -dpng 02_plot_diff_func0-func1_m002.png;

plot (output_m2(:,1), abs (output_m2(:,2) - output_m2(:,4)));
ylabel ("abs (func0(x) - func2(x))");
xlabel ("arguments");
title  ("abs (func0(x) - func2(x)), M=2");
legend ("abs (func0(x) - func2(x))");
print -dpng 03_plot_diff_func0-func2_m002.png;

plot (output_m2(:,1), abs (output_m2(:,2) - output_m2(:,5)));
ylabel ("abs (func0(x) - func3(x))");
xlabel ("arguments");
title  ("abs (func0(x) - func3(x)), M=2");
legend ("abs (func0(x) - func3(x))");
print -dpng 04_plot_diff_func0-func3_m002.png;

plot (output_m2(:,1), abs (output_m2(:,2) - output_m2(:,6)));
ylabel ("abs (func0(x) - func4(x))");
xlabel ("arguments");
title  ("abs (func0(x) - func4(x)), M=2");
legend ("abs (func0(x) - func4(x))");
print -dpng 05_plot_diff_func0-func4_m002.png;


### diffs 2
plot (output_m2(:,1), abs (output_m2(:,3) - output_m2(:,4)));
ylabel ("abs (func1(x) - func2(x))");
xlabel ("arguments");
title  ("abs (func1(x) - func2(x)), M=2");
legend ("abs (func1(x) - func2(x))");
print -dpng 06_plot_diff_func1-func2_m002.png;


plot (output_m2(:,1), abs (output_m2(:,5) - output_m2(:,6)));
ylabel ("abs (func3(x) - func4(x))");
xlabel ("arguments");
title  ("abs (func3(x) - func4(x)), M=2");
legend ("abs (func3(x) - func4(x))");
print -dpng 07_plot_diff_func3-func4_m002.png;
