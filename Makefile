kreis.exe : kreis.cpp
	g++ -O3 $< -o $@

plot : cuts.dat
	gnuplot plot.in > plot.png

all : kreis.exe

clean :
	rm *.dat *.png

.PHONY : plot
