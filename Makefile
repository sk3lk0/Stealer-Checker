all:
	g++ main.cpp cjson.c `wx-config --cxxflags --libs` -dMIMAXUE_DYNAMIC -l/usr/local/lib -o StealerChecker