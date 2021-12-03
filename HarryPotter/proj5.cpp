#include "Game.h"
#include "Hero.h"
#include "Lqueue.cpp"
#include "Villain.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>

#include "windows.h"
#define _CRTDBG_MAP_ALLOC //to get more details
#include <stdlib.h>  
#include <crtdbg.h>   //for malloc and free

using namespace std;

int main() {

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    srand(time(NULL)); //Do not use srand anywhere else
    Game myGame("proj5_data.txt");
    myGame.LoadFile();
    myGame.MainMenu();
    return 0;
}

/*
int main(int argc, char* argv[]) {
    srand(time(NULL)); //Do not use srand anywhere else
    if (argc < 2) {
        cout << "You are missing a data file." << endl;
        cout << "Expected usage ./proj5 proj5_data.txt" << endl;
        cout << "File 1 should be a file with a wizards" << endl;
        return 0;
    }
    Game myGame(argv[1]);
    myGame.LoadFile();
    myGame.MainMenu();
    return 0;
}
*/
