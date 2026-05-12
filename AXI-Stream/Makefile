CXX = g++

SYSTEMC_HOME = C:/systemc/systemc-2.3.3

INCLUDES = -I$(SYSTEMC_HOME)/src -I$(SYSTEMC_HOME)/src/tlm_core/include
LIBS = -L$(SYSTEMC_HOME)/build/src/.libs -lsystemc -lpthread

TARGET_BASIC = sim_basic.exe
TARGET_DEMO = sim_demo.exe
TARGET_ADVANCED = sim_advanced.exe

SRC_BASIC = main_basic_example.cpp
SRC_DEMO = main_axi_stream.cpp
SRC_ADVANCED = main_advanced_example.cpp

all: $(TARGET_BASIC) $(TARGET_DEMO) $(TARGET_ADVANCED)

$(TARGET_BASIC):
	$(CXX) $(SRC_BASIC) $(INCLUDES) $(LIBS) -o $(TARGET_BASIC)

$(TARGET_DEMO):
	$(CXX) $(SRC_DEMO) $(INCLUDES) $(LIBS) -o $(TARGET_DEMO)

$(TARGET_ADVANCED):
	$(CXX) $(SRC_ADVANCED) $(INCLUDES) $(LIBS) -o $(TARGET_ADVANCED)

run_basic: $(TARGET_BASIC)
	./$(TARGET_BASIC)

run_demo: $(TARGET_DEMO)
	./$(TARGET_DEMO)

run_advanced: $(TARGET_ADVANCED)
	./$(TARGET_ADVANCED)

clean:
	del /Q *.exe *.vcd 2>nul

.PHONY: all run_basic run_demo run_advanced clean
