graphics_toolkit ("gnuplot");
format long;
output_precision = 32;
load ../output_m16.csv;

### exp(sin(x))
plot (output_m16(:,1), output_m16(:,2),
      output_m16(:,1), output_m16(:,3),
      output_m16(:,1), output_m16(:,4),
      output_m16(:,1), output_m16(:,5),
      output_m16(:,1), output_m16(:,6));

ylabel ("exp(sin(x))");
xlabel ("arguments");
title  ("Plot of exp(sin(x)), M=16");
legend ("func0", "func1", "func2", "func3", "func4");
print -dsvg 01_functions_m016.svg;

### diffs
plot (output_m16(:,1), abs (output_m16(:,2) - output_m16(:,3)));
ylabel ("abs (func0(x) - func1(x))");
xlabel ("arguments");
title  ("abs (func0(x) - func1(x)), M=16");
legend ("abs (func0(x) - func1(x))");
print -dsvg 02_plot_diff_func0-func1_m016.svg;

plot (output_m16(:,1), abs (output_m16(:,2) - output_m16(:,4)));
ylabel ("abs (func0(x) - func2(x))");
xlabel ("arguments");
title  ("abs (func0(x) - func2(x)), M=16");
legend ("abs (func0(x) - func2(x))");
print -dsvg 03_plot_diff_func0-func2_m016.svg;

plot (output_m16(:,1), abs (output_m16(:,2) - output_m16(:,5)));
ylabel ("abs (func0(x) - func3(x))");
xlabel ("arguments");
title  ("abs (func0(x) - func3(x)), M=16");
legend ("abs (func0(x) - func3(x))");
print -dsvg 04_plot_diff_func0-func3_m016.svg;

plot (output_m16(:,1), abs (output_m16(:,2) - output_m16(:,6)));
ylabel ("abs (func0(x) - func4(x))");
xlabel ("arguments");
title  ("abs (func0(x) - func4(x)), M=16");
legend ("abs (func0(x) - func4(x))");
print -dsvg 05_plot_diff_func0-func4_m016.svg;
