graphics_toolkit ("gnuplot");
format long;
output_precision = 32;
load ../output_m24.csv;

### exp(sin(x))
plot (output_m24(:,1), output_m24(:,2),
      output_m24(:,1), output_m24(:,3),
      output_m24(:,1), output_m24(:,4),
      output_m24(:,1), output_m24(:,5),
      output_m24(:,1), output_m24(:,6));

ylabel ("exp(sin(x))");
xlabel ("arguments");
title  ("Plot of exp(sin(x)), M=24");
legend ("func0", "func1", "func2", "func3", "func4");
print -dpng 01_functions_m024.png;

### diffs
plot (output_m24(:,1), abs (output_m24(:,2) - output_m24(:,3)));
ylabel ("abs (func0(x) - func1(x))");
xlabel ("arguments");
title  ("abs (func0(x) - func1(x)), M=24");
legend ("abs (func0(x) - func1(x))");
print -dpng 02_plot_diff_func0-func1_m024.png;

plot (output_m24(:,1), abs (output_m24(:,2) - output_m24(:,4)));
ylabel ("abs (func0(x) - func2(x))");
xlabel ("arguments");
title  ("abs (func0(x) - func2(x)), M=24");
legend ("abs (func0(x) - func2(x))");
print -dpng 03_plot_diff_func0-func2_m024.png;

plot (output_m24(:,1), abs (output_m24(:,2) - output_m24(:,5)));
ylabel ("abs (func0(x) - func3(x))");
xlabel ("arguments");
title  ("abs (func0(x) - func3(x)), M=24");
legend ("abs (func0(x) - func3(x))");
print -dpng 04_plot_diff_func0-func3_m024.png;

plot (output_m24(:,1), abs (output_m24(:,2) - output_m24(:,6)));
ylabel ("abs (func0(x) - func4(x))");
xlabel ("arguments");
title  ("abs (func0(x) - func4(x)), M=24");
legend ("abs (func0(x) - func4(x))");
print -dpng 05_plot_diff_func0-func4_m024.png;


### diffs 2
plot (output_m24(:,1), abs (output_m24(:,3) - output_m24(:,4)));
ylabel ("abs (func1(x) - func2(x))");
xlabel ("arguments");
title  ("abs (func1(x) - func2(x)), M=24");
legend ("abs (func1(x) - func2(x))");
print -dpng 06_plot_diff_func1-func2_m024.png;


plot (output_m24(:,1), abs (output_m24(:,5) - output_m24(:,6)));
ylabel ("abs (func3(x) - func4(x))");
xlabel ("arguments");
title  ("abs (func3(x) - func4(x)), M=24");
legend ("abs (func3(x) - func4(x))");
print -dpng 07_plot_diff_func3-func4_m024.png;
