all:
	g++ main.cpp `wx-config --cxxflags --libs` -o StealerChecker