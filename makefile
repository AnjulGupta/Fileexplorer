CXX = g++
CXXFLAGS = -Wall -g

FE_project: FE_project.o Normal_mode.o
	$(CXX) $(CXXFLAGS) -o FE_project FE_project.o Normal_mode.o

FE_project.o: FE_project.cpp normal_mode.h
	$(CXX) $(CXXFLAGS) -c FE_project.cpp

Normal_mode.o: Normal_mode.cpp normal_mode.h
	$(CXX) $(CXXFLAGS) -c Normal_mode.cpp
