C_FLAGS=-O3 -lm -std=c++23 -Wall

all:		gauss dy yd

gauss:		gauss.cc
			g++ gauss.cc -o gauss ${C_FLAGS} 

dy:			dy.cc
			g++ dy.cc -o dy ${C_FLAGS}

yd:			yd.cc
			g++ yd.cc -o yd ${C_FLAGS}
