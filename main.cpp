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
};

class FileName:public Movies{
public:
    string txt=".txt";
    string finalname(){
    return(Title+txt);
    }
};

class MovieInfo{
public:
    int year=0;
    string Actor;
    string Description;
    //string Genre;
};

class UserDecisions{
public:
    int choice=0;
    int descchoice=0;
    int NoActors=0;
};

class TempData{
public:
    string del;
    string line;
};

int main()

{
    cout << "Hello there! Welcome to the movie database project!"<<endl;

    char repeat = 'y';
    while( repeat == 'y'){

    FileName FName;
    MovieInfo Info;
    UserDecisions UD;
    TempData Temp;

    cout << "\nWhat would you like to do? \n'1'-add a movie, \n'2'-view info about existing movie, \n'3'-delete a movie entry, \n'4'-view a list of existing movies, \n'5'-exit program.\n";

    cin >> UD.choice;

    cin.ignore();

    switch(UD.choice){

        case 1: //ADD A MOVIE

            {
            cout<<"specify movie title: ";
            getline (cin, FName.Title);

            fstream moviefile;
            moviefile.open(FName.finalname().c_str(), ios::in); //OPEN MOVIE FILE

            if (!moviefile)
            {
            moviefile.close();

            moviefile.open("movielist.txt", ios::app);
            moviefile<<FName.Title<<endl;
            moviefile.close();

            moviefile.open(FName.finalname().c_str(), ios::app);

            cout<<"specify release date: ";
            cin>>Info.year;

            moviefile<<FName.Title<<" ("<<Info.year<<")"<<endl<<endl;

            moviefile<<"Actors:"<<endl;

            cout<<"How many actors would you like to assign to this movie?"<<endl;
            cin>>UD.NoActors;
            cin.ignore();

            cout<<"now, type in the names of chosen actors."<<endl;

            for(int i=0; i<UD.NoActors; i++)
                {
                getline (cin, Info.Actor);
                moviefile<<Info.Actor<<endl;
                }

            cout<<"What about a short description of a movie? (0- no, 1- yes)"<<endl;
            cin>>UD.descchoice;
            cin.ignore();

            if(UD.descchoice==1)
                {
                cout<<"type in your description:"<<endl;
                getline (cin, Info.Description);
                moviefile<<"\nSynopsis:\n"<<Info.Description;
                }

            else if(UD.descchoice==0){break;}

            else{cout<<"So uncivilized. If you can't read, you probably can't write, so no description!!!11!!11";}
            moviefile.close();
            }

            else{cout<<"file already exists, you can view info about it by selecting '2'";}

            break;
            }
        case 2: //VIEW INFO

            {
            cout<<"specify movie title: ";
            getline (cin, FName.Title);

            fstream moviefile;
            moviefile.open(FName.finalname().c_str(), ios::in);

            if (!moviefile)
                {
                cerr << "\nUnable to get info, perhaps the archives are incomplete?";
                }

            else
                {
                cout << "\n" << moviefile.rdbuf();
                }

            moviefile.close();

        break;
            }

        case 3: //DELETE ENTRY

            {
            cout<<"specify movie title to delete: ";
            getline (cin, FName.Title);

            if (remove(FName.finalname().c_str()) !=0)
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
                Temp.del=FName.Title;

                while (getline(in, Temp.line))
                {
                if (Temp.line != Temp.del)
                cout << Temp.line << endl;
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

            if (!moviefile)
                {
                cerr << "Database is empty, you need to add some movies.";
                }

            else
                {
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

        case 5:{return 0;}

        default: cout<<"that's not an allowed choice, restart and try again!"<<endl;

    }

    cout<< "\n\nDo you want to repeat? (y/n):";
    cin>> repeat;
  }

return 0;}
