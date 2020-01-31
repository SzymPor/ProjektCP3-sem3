#pragma once

#include <iostream>

using namespace std;

class MovieInfo {
private:
	int year = 0;
	string Actor;
	string Description;

public:
	void setYear(int y);
	int getYear();

	void setActor(string a);
	string getActor();

	void setDesc(string d);
	string getDesc();

};
