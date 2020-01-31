#pragma once

#include <iostream>

using namespace std;

class FileName
{
private:
	string title;
	string ext = ".txt";
public:
	string getTitle();
	void setTitle(string _title);

	string getFinalName();
};

