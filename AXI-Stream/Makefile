CXX = g++
SYSTEMC_HOME = C:/systemc/systemc-2.3.3
INCLUDES = -I$(SYSTEMC_HOME)/src -I$(SYSTEMC_HOME)/src/tlm_core/include
LIBS = -L$(SYSTEMC_HOME)/build/src/.libs -lsystemc -lpthread

all: sim.exe

sim.exe: main.cpp axi_stream.h
	$(CXX) main.cpp $(INCLUDES) $(LIBS) -o sim.exe

run: sim.exe
	./sim.exe

clean:
	del /Q *.exe 2>nul

.PHONY: all run clean