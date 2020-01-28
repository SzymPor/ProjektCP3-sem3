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
};

class UserDecisions{
public:
    char choice;
    char descchoice;
    int NoActors=0;
};

class TempData{
public:
    string del;
    string line;
    int checktrue=0;
    int checkactors=0;
};


class AddMovie:public FileName, public MovieInfo, public UserDecisions, public TempData{
public:
    void AddAMovie(){
            cout<<"specify movie title: ";
            getline (cin, Title);

            fstream moviefile;
            moviefile.open(finalname().c_str(), ios::in);
        try{
            if (!moviefile)
            {
            moviefile.close();

            moviefile.open("movielist.txt", ios::app);
            moviefile<<Title<<endl;
            moviefile.close();

            moviefile.open(finalname().c_str(), ios::app);

            cout<<"specify release year in [YYYY] format: ";
            cin>>year;

            checktrue=1900;

            while(checktrue>1877){
            if (year>1877){
            moviefile<<Title<<" ("<<year<<")"<<endl<<endl;
            checktrue=1200;
            }
            else{
            cout<<"Are you sure about that? First movie ever was created in 1878. Correct yourself:"<<endl;
            cin>>year;
            checktrue=year;}
            }

            cout<<"How many actors would you like to assign to this movie?"<<endl;

            cin>>NoActors;
            cin.ignore();

            checkactors=2;

            while(checkactors>=0){

            if(NoActors>0){
            moviefile<<"Actors:"<<endl;
            cout<<"now, type in the names of chosen actors."<<endl;

            for(int i=0; i<NoActors; i++)
                {
                getline (cin, Actor);
                moviefile<<Actor<<endl;
                }
            checkactors=-2;
            }

            else if(NoActors==0) {cout<<"No actors added"<<endl<<endl;}
            else{cout<<"well, how do you suppose to add a negative number of actors? Correct yourself:"<<endl;
            cin>>NoActors;
            checkactors=NoActors;
            NoActors++;}
            }

            cout<<"What about a short description of a movie? (0- no, 1- yes)"<<endl;
            cin>>descchoice;
            cin.ignore();

            if(descchoice=='1')
                {
                cout<<"type in your description:"<<endl;
                getline (cin, Description);
                moviefile<<"\nSynopsis:\n"<<Description;
                }

            else if(descchoice=='0'){cout<<"file left without description"<<endl;}

            else{cout<<"So uncivilized. If you can't read, you probably can't write, so no description!!!11!!11";}
            moviefile.close();
            }

            else{throw "file already exists, you can view info about it by selecting '2'";}}
            catch (const char* msg) {
                cerr << msg << endl;
            }
}
};

class ViewInfo: public FileName{
public:
    void ViewMovieInfo(){
            cout<<"specify movie title: ";
            getline (cin, Title);

            fstream moviefile;
            moviefile.open(finalname().c_str(), ios::in);

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
};

class Delete:public FileName, public TempData{
public:
    void DeleteEntry(){
            cout<<"specify movie title to delete: ";
            getline (cin, Title);

            if (remove(finalname().c_str()) !=0)
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
                del=Title;

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
    }
};

class ViewList{
public:
    void ViewMovieList(){
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
    }
};

int main()
{
    cout << "Hello there! Welcome to the movie database project!"<<endl;

    char repeat = 'y';
    while( repeat == 'y'){

    ViewList VList;
    Delete Del;
    ViewInfo View;
    AddMovie Add;
    UserDecisions UD;

    cout << "\nWhat would you like to do? \n'1'-add a movie, \n'2'-view info about a specific, existing movie, \n'3'-delete a movie entry, \n'4'-view a list of all existing movies, \n'5'-exit program.\n";

    cin >> UD.choice;
    cin.ignore();

    switch(UD.choice){

        case '1': //ADD A MOVIE

            {
            Add.AddAMovie();
            break;
            }
        case '2': //VIEW INFO

            {
            View.ViewMovieInfo();
            break;
            }

        case '3': //DELETE ENTRY

            {
            Del.DeleteEntry();
            break;
        }

        case '4':

            {
            VList.ViewMovieList();
            break;
        }

        case '5':{return 0;}

        default: cout<<"that's not an allowed choice, restart and try again!"<<endl;

    }

    cout<< "\n\nDo you want to start again? (y/n):";
    cin>> repeat;
  }
return 0;}
