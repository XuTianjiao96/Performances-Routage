SRC=main.cpp topology.cpp routing.cpp calculation.cpp
HDR=topology.h routing.h calculation.h

all:$(SRC) $(HDR)
	g++ -o main $(SRC)
clean:
	rm -f main
