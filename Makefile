CXX = g++

SYSTEMC_HOME = C:/systemc/systemc-2.3.3

INCLUDES = -I$(SYSTEMC_HOME)/src
LIBS = -L$(SYSTEMC_HOME)/build/src/.libs -lsystemc

TARGET = sim.exe

SRC = main_fsm.cpp

all:
	$(CXX) $(SRC) $(INCLUDES) $(LIBS) -o $(TARGET)

run:
	./$(TARGET)

clean:
	del /Q *.exe *.vcd 2>nul