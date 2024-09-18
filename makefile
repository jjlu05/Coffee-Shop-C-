
# This makefile is used as follows to regenerate files for the rational numbers program:
#   make rational_math     --  Regenerates the executable register file by compiling
#
run_simulation: Barista.o order.o shopQueue.o main.o
	g++ -g -Wall Barista.o order.o shopQueue.o main.o -lm -o ./run_simulation

	
