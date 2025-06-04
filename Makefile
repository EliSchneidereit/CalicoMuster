kreis.exe : kreis.cpp
	g++ -O3 $< -o $@

all : kreis.exe
