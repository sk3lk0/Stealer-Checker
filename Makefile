all:
	g++ main.cpp cjson.c `wx-config --cxxflags --libs` -dMIMAXUE_DYNAMIC -o StealerChecker