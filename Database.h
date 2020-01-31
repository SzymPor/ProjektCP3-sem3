#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <list>

#include "FileName.h"
#include "MovieInfo.h"

using namespace std;

class Database
{
private:
	string sTemp;
	string del;
	string line;
	int nTemp;
	int checktrue = 1900;
	int checkactors = 0;

	FileName fn;
	MovieInfo mi;

public:
	void AddMovie();
	void ViewMovieInfo();
	void ViewMovieList();
	void DeleteMovie();
};

