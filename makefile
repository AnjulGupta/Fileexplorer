CXX = g++
CXXFLAGS = -Wall -g

FE_project: FE_project.o Normal_mode.o LS_cmd.o
	$(CXX) $(CXXFLAGS) -o FE_project FE_project.o Normal_mode.o LS_cmd.o

FE_project.o: FE_project.cpp normal_mode.h 
	$(CXX) $(CXXFLAGS) -c FE_project.cpp 

Normal_mode.o: Normal_mode.cpp normal_mode.h LS_cmd.h
	$(CXX) $(CXXFLAGS) -c Normal_mode.cpp LS_cmd.cpp

LS_cmd.o: LS_cmd.cpp LS_cmd.h
	$(CXX) $(CXXFLAGS) -c LS_cmd.cpp