all:
	g++ main.cpp cjson.c `wx-config --cxxflags --libs` -o StealerChecker