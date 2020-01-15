#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <iomanip>
#include <cstdlib>
#include <sstream>


using namespace std;



class Movies{

public:

    string Title;
    string txt=".txt";
    int year=0;
    string Actor;
    string Description;
    string finalname()
    {
    return (Title+txt);
    }
};



int main()

{
    cout << "Hello there! Welcome to the movie database project!"<<endl;

    char repeat = 'y';
    while( repeat == 'y'){

    int choice=0;

    Movies movie;



    cout << "\nWhat would you like to do? \n'1'-add a movie, \n'2'-view info about existing movie, \n'3'-delete a movie entry, \n'4'-view a list of existing movies\n";
    cin >> choice;

    cin.ignore();

    switch(choice){

        case 1: //ADD A MOVIE

            {

            int descchoice=0;

            int NoActors=0;

            cout<<"specify movie title: ";

            getline (cin, movie.Title);

            fstream moviefile;

            moviefile.open(movie.finalname().c_str(), ios::in); //OPEN MOVIE FILE



            if (!moviefile){

            moviefile.close();
            moviefile.open("movielist.txt", ios::app);
            moviefile<<movie.Title<<endl;
            moviefile.close();

            moviefile.open(movie.finalname().c_str(), ios::app);

            cout<<"specify release date: ";

            cin>>movie.year;

            moviefile<<movie.Title<<" ("<<movie.year<<")"<<endl<<endl;

            moviefile<<"Actors:"<<endl;

            cout<<"How many actors would you like to assign to this movie?"<<endl;

            cin>>NoActors;

            cin.ignore();

            cout<<"now, type in the names of chosen actors."<<endl;

            for(int i=0; i<NoActors; i++){

                getline (cin, movie.Actor);

                moviefile<<movie.Actor<<endl;

                }

            cout<<"What about a short description of a movie? (0- no, 1- yes)"<<endl;

            cin>>descchoice;

            cin.ignore();

            if(descchoice==1){

                cout<<"type in your description:"<<endl;

                getline (cin, movie.Description);

                moviefile<<"\nSynopsis:\n"<<movie.Description;

                }

            else if(descchoice==0){break;}

            else{cout<<"So uncivilized. If you can't read, you probably can't write, so no description!!!11!!11";}

            moviefile.close();

            }

            else{cout<<"file already exists, you can view info about it by selecting '2'";}

            break;
            }
        case 2: //VIEW INFO

            {



            cout<<"specify movie title: ";

            getline (cin, movie.Title);

            fstream moviefile;

            moviefile.open(movie.finalname().c_str(), ios::in);

            if (!moviefile) {

                cerr << "Unable to get info, perhaps the archives are incomplete?";

                }

            else{

                cout << moviefile.rdbuf();

            }

            moviefile.close();

        break;

            }

        case 3: //DELETE ENTRY

            {

            cout<<"specify movie title to delete: ";
            getline (cin, movie.Title);
            if (remove(movie.finalname().c_str()) !=0)
            {
                perror("error  deleting the file");
            }
            else
            {
                string del;
                string line;
                ifstream in("movielist.txt");

                if (!in.is_open())
                {
                    cout << "Input file failed to open\n";
                }

                ofstream out("temp.txt");
                del=movie.Title;
                while (getline(in, line))
                {
                if (line != del)
                out << line << endl;
                }
                in.close();
                out.close();
                remove("movielist.txt");
                rename("temp.txt", "movielist.txt");
                puts("file deleted successfully");
            }
        break;
        }

        case 4:
            {

            fstream moviefile;
            moviefile.open("movielist.txt", ios::in);
            if (!moviefile) {

                cerr << "Database is empty, you need to add some movies.";

                }

            else{
                   moviefile.seekg(0, ios::end);
                    if( moviefile.tellg()==0 )
                        {
                        moviefile.close();
                        remove("movielist.txt");
                        cout<<"Database is empty, you need to add some movies.";
                        }
                    else
                        {
                        moviefile.open("movielist.txt", ios::in);
                        moviefile.clear();
                        moviefile.seekg(0, ios::beg);
                        cout<<"Movies already in database:"<<endl;
                        cout << moviefile.rdbuf();
                        }


                }

            moviefile.close();


        break;
        }

        default: cout<<"that's not an allowed choice, restart and try again!"<<endl;

    }
    cout<< "\n\nDo you want to repeat? (y/n):";
    cin>> repeat;
  }

    return 0;

}
