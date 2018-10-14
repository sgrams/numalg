graphics_toolkit ("gnuplot")
load ../output.csv
plot (output(:,1), output(:,4))
ylabel ("absolute error")
xlabel ("arguments")
title  ("function 1 / function 0 absolute error")
print -dpng output.png
