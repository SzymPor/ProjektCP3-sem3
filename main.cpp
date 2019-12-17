#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <iomanip>
#include <sstream>
using namespace std;

class Movies{
public:
    string Title;
    int year=0;
    string Actor;
    string Description;
};

int main()
{
    string txt=".txt";
    string finalname;
    int choice=0;
    Movies movie;
    cout << "Hello there! Welcome to the movie database project!"<<endl;
    cout << "What would you like to do? ('1'-add a movie, '2'-view info about existing movie, '3'-delete a movie entry)";
    cin >> choice;
    cin.ignore();
    switch(choice){
        case 1:
            {
            int descchoice=0;
            int NoActors=0;
            cout<<"specify movie title: ";
            getline (cin, movie.Title);
            fstream moviefile;
            finalname=movie.Title+txt;
            moviefile.open(finalname.c_str(), ios::in); //OPEN MOVIE FILE

            if (!moviefile){
            moviefile.close();
            moviefile.open(finalname.c_str(), ios::app);
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
        case 2:
            {

            cout<<"specify movie title: ";
            getline (cin, movie.Title);
            fstream moviefile;
            finalname=movie.Title+txt;
            moviefile.open(finalname.c_str(), ios::in);
            if (!moviefile) {
                cerr << "Unable to get info, perhaps the archives are incomplete?";
                }
            else{
                cout << moviefile.rdbuf();
            }
            moviefile.close();
        break;
            }
        case 3:
            {
            cout<<"nothing yet";
        break;
            }
        default:
            cout<<"that's not an allowed choice, restart and try again!"<<endl;
    }




    return 0;
}
