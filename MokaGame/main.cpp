#include "Game.h"
#include "ctime"



// Remove SDL main hook on Windows
#ifdef _WIN32
#  undef main
#endif

using namespace std;

void termin(){
    cout<<"Blad z dupy"<<endl;
    exit(0);
}

void (*old_terminate)() = set_terminate(termin);

int main(int argc, char* argv[]){
try{
  //srand (static_cast <unsigned> (time(0)));
  argc = 1;
  Game gra;
  gra.startGame();
  //lalalala ddd
}
catch(...)
{
    cout<<"Jakis blad"<<endl;
}
return 0;
}



