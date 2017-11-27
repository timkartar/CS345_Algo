set xlabel "Input Size"
set ylabel "Running time( MiliSeconds )"
set terminal png
set output 'incr_loop1.png'
f(x) = m*x + b
fit f(x) 'loop_data' using 1:2 via m,b
plot 'loop_data' using 1:2 title 'Randomised Incremental Algo Runtime' pt 6 ps 2, f(x) title 'line fit for O(n) algo'

set output 'brute1.png'
f(x) = a*x**4 + b
fit f(x) 'brute_data' using 1:2 via a,b
plot 'brute_data' using 1:2 title 'Brute Force Algo Runtime' pt 4 ps 2, f(x) title 'fit for O(n^4) algo'

set output 'combine_loop1.png'
g(x) = m*x + c
fit g(x) 'loop_data' using 1:2 via m,c
plot 'brute_data' using 1:2 title 'Brute Force Algo Runtime' pt 6 ps 2, f(x) title 'fit for O(n^4) algo', 'loop_data' using 1:2 title 'Randomised Incremental Algo Runtime' pt 4 ps 2, g(x) title 'line fit for O(n) algo'
