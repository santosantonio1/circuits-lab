all:		gauss

gauss:		gauss.cc
			g++ gauss.cc -o gauss -O3 -lm 
