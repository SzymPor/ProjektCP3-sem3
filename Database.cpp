#include "Database.h"


void Database::AddMovie() {
	cout << "specify movie title: ";
	getline(cin, sTemp);
	fn.setTitle(sTemp);

	fstream moviefile;
	moviefile.open(fn.getFinalName().c_str(), ios::in);
	try {
		if (!moviefile)
		{
			moviefile.close();

			moviefile.open("movielist.txt", ios::app);
			moviefile << fn.getTitle() << endl;
			moviefile.close();

			moviefile.open(fn.getFinalName().c_str(), ios::app);

			cout << "specify release year in [YYYY] format: ";
			cin >> nTemp;
			mi.setYear(nTemp);

			while (checktrue > 1877) {
				if (mi.getYear() > 1877) {
					moviefile << fn.getTitle() << " (" << mi.getYear() << ")" << endl << endl;
					checktrue = 1200;
				}
				else {
					cout << "Are you sure about that? First movie ever was created in 1878. Correct yourself:" << endl;
					cin >> nTemp;
					mi.setYear(nTemp);
					checktrue = nTemp;
				}
			}

			cout << "How many actors would you like to assign to this movie?" << endl;
			int NoActors = 0;
			cin >> NoActors;
			cin.ignore();

			checkactors = 2;

			while (checkactors >= 0) {

				if (NoActors > 0) {
					moviefile << "Actors:" << endl;
					cout << "now, type in the names of chosen actors." << endl;

					for (int i = 0; i < NoActors; i++)
					{
						string a;
						getline(cin, a);
						mi.setActor(a);

						moviefile << mi.getActor() << endl;
					}
					checkactors = -2;
				}

				else if (NoActors == 0) { cout << "No actors added" << endl << endl; }
				else {
					cout << "well, how do you suppose to add a negative number of actors? Correct yourself:" << endl;
					cin >> NoActors;
					checkactors = NoActors;
					NoActors++;
				}
			}

			cout << "What about a short description of a movie? (0- no, 1- yes)" << endl;
			char descchoice;
			cin >> descchoice;
			cin.ignore();

			if (descchoice == '1')
			{
				cout << "type in your description:" << endl;
				getline(cin, sTemp);
				mi.setDesc(sTemp);
				moviefile << "\nSynopsis:\n" << mi.getDesc();
			}

			else if (descchoice == '0') { cout << "file left without description" << endl; }

			else { cout << "So uncivilized. If you can't read, you probably can't write, so no description!!!11!!11"; }
			moviefile.close();
		}

		else { throw "file already exists, you can view info about it by selecting '2'"; }
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}
}

void Database::ViewMovieInfo() {
	cout << "specify movie title: ";
	getline(cin, sTemp);
	fn.setTitle(sTemp);

	fstream moviefile;
	moviefile.open(fn.getFinalName().c_str(), ios::in);

	if (!moviefile)
	{
		cerr << "\nUnable to get info, perhaps the archives are incomplete?";
	}

	else
	{
		cout << "\n" << moviefile.rdbuf();
	}

	moviefile.close();
}

void Database::DeleteMovie() {
	cout << "specify movie title to delete: ";
	getline(cin, sTemp);
	fn.setTitle(sTemp);

	if (remove(fn.getFinalName().c_str()) != 0)
	{
		perror("error  deleting the file");
	}

	else
	{
		ifstream in("movielist.txt");

		if (!in.is_open())
		{
			cout << "Input file failed to open\n";
		}

		ofstream out("temp.txt");
		del = fn.getTitle();

		while (getline(in, line))
		{
			if (line != del)
				out << line << endl;
		}

		in.close();
		out.close();
		try {
			if (remove("movielist.txt")) {
				throw "Error occurred while trying to remove the file.";
			}

			if (rename("temp.txt", "movielist.txt")) {
				throw "Error occurred while trying to swap the files.";
			}
		}
		catch (const char* msg) {
			cerr << msg << endl;
		}
		puts("File deleted successfully.");
	}
}

void Database::ViewMovieList() {
	fstream moviefile;
	moviefile.open("movielist.txt", ios::in);

	if (!moviefile)
	{
		cerr << "Database is empty, you need to add some movies.";
	}

	else
	{
		moviefile.seekg(0, ios::end);

		if (moviefile.tellg() == 0)
		{
			moviefile.close();
			remove("movielist.txt");
			cout << "Database is empty, you need to add some movies.";
		}

		else
		{
			moviefile.open("movielist.txt", ios::in);
			moviefile.clear();
			moviefile.seekg(0, ios::beg);
			cout << "Movies already in database:" << endl;
			cout << moviefile.rdbuf();
		}
	}

	moviefile.close();
}
