#include <iostream>

#include "Database.h"

using namespace std;

int main()
{
	cout << "Hello there! Welcome to the movie database project!" << endl;
	Database db;

	char repeat = 'y';
	while (repeat == 'y') {

		char choice;

		cout << "\nWhat would you like to do? \n'1'-add a movie, \n'2'-view info about a specific, existing movie, \n'3'-delete a movie entry, \n'4'-view a list of all existing movies, \n'5'-exit program.\n";

		cin >> choice;
		cin.ignore();

		switch (choice) {

		case '1': //ADD A MOVIE

		{
			db.AddMovie();
			break;
		}
		case '2': //VIEW INFO

		{
			db.ViewMovieInfo();
			break;
		}

		case '3': //DELETE ENTRY

		{
			db.DeleteMovie();
			break;
		}

		case '4':

		{
			db.ViewMovieList();
			break;
		}

		case '5': { return 0; }

		default: cout << "that's not an allowed choice, restart and try again!" << endl;

		}

		cout << "\n\nDo you want to start again? (y/n):";
		cin >> repeat;
	}
	return 0;
}
