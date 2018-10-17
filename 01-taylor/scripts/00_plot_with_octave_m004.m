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
title  ("Plot of exp(sin(x)), M=4");
legend ("func0", "func1", "func2", "func3", "func4");
print -dpng 01_functions_m004.png;

### diffs
plot (output_m4(:,1), abs (output_m4(:,2) - output_m4(:,3)));
ylabel ("abs (func0(x) - func1(x))");
xlabel ("arguments");
title  ("abs (func0(x) - func1(x)), M=4");
legend ("abs (func0(x) - func1(x))");
print -dpng 02_plot_diff_func0-func1_m004.png;

plot (output_m4(:,1), abs (output_m4(:,2) - output_m4(:,4)));
ylabel ("abs (func0(x) - func2(x))");
xlabel ("arguments");
title  ("abs (func0(x) - func2(x)), M=4");
legend ("abs (func0(x) - func2(x))");
print -dpng 03_plot_diff_func0-func2_m004.png;

plot (output_m4(:,1), abs (output_m4(:,2) - output_m4(:,5)));
ylabel ("abs (func0(x) - func3(x))");
xlabel ("arguments");
title  ("abs (func0(x) - func3(x)), M=4");
legend ("abs (func0(x) - func3(x))");
print -dpng 04_plot_diff_func0-func3_m004.png;

plot (output_m4(:,1), abs (output_m4(:,2) - output_m4(:,6)));
ylabel ("abs (func0(x) - func4(x))");
xlabel ("arguments");
title  ("abs (func0(x) - func4(x)), M=4");
legend ("abs (func0(x) - func4(x))");
print -dpng 05_plot_diff_func0-func4_m004.png;


### diffs 2
plot (output_m4(:,1), abs (output_m4(:,3) - output_m4(:,4)));
ylabel ("abs (func1(x) - func2(x))");
xlabel ("arguments");
title  ("abs (func1(x) - func2(x)), M=4");
legend ("abs (func1(x) - func2(x))");
print -dpng 06_plot_diff_func1-func2_m004.png;


plot (output_m4(:,1), abs (output_m4(:,5) - output_m4(:,6)));
ylabel ("abs (func3(x) - func4(x))");
xlabel ("arguments");
title  ("abs (func3(x) - func4(x)), M=4");
legend ("abs (func3(x) - func4(x))");
print -dpng 07_plot_diff_func3-func4_m004.png;
