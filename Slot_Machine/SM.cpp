#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <ctime>
using namespace std;

char generateSymbol() {
    const char symbols[] = {'X', '#', '$', '7'};
    int index = rand() % 4; 
    return symbols[index];
}

int determineWinAmount(char symbol1, char symbol2, char symbol3) {
    if (symbol1 == symbol2 && symbol2 == symbol3) {
        if (symbol1 == 'X') {
            return 10;
        } else if (symbol1 == '#') {
            return 25;
        } else if (symbol1 == '$') {
            return 50;
        } else if (symbol1 == '7') {
            return 100;
        }
    }
    return 0;
}
    
int main(){
    string playerOne;
    bool player1_yes = false;
    bool game_running = true;
    int dollars = 10;
    
    cout << "---------------------------" << endl << "Welcome to the Slot Machine" << endl << "---------------------------" << endl;
    cout << "The goal of the game is to get 3 matching symbols on each wheel. Slot machines have a variety of symbols on the wheel." << endl << "For our slot machine, we'll have 4 different possible symbols: 7, $, #, and X." << endl << "Matching each set of symbols should result in the following payouts: " << endl;
    cout << " 777 = 100 dollars" << endl;
    cout << " $$$ = 50 dollars" << endl;
    cout << " ### = 25 dollars" << endl;
    cout << " XXX = 10 dollars" << endl;
    cout << "Would you like to spin the Slot Machine for $1? You have $" << dollars << "." << endl << "Please enter 'Yes' or 'No'." << endl;
    
    while (game_running == true) 
    
    do {
        
    char slot1;
    char slot2;
    char slot3;

    slot1 = generateSymbol();
    slot2 = generateSymbol();
    slot3 = generateSymbol();
        
      getline(cin, playerOne);            
    if (playerOne.size() >= 3) {
        if (dollars < 1) {
            cout << "You have insufficient funds. Game Over" << endl;
            game_running = false; 
    return 0;
        }
        
        else {
            dollars = dollars - 1;
    
    cout << endl << "[" << slot1 << "][" << slot2 << "][" << slot3 << "]" << endl;
    
    int winAmount = determineWinAmount(slot1, slot2, slot3);

        if (winAmount > 0) {
            cout << "You won $" << winAmount << "!" << endl;
            dollars += winAmount;
        } else {
            cout << "No win." << endl;
        }
        
    cout << endl << "You now have $" << dollars << "." << endl << "Would you like to go again?" << endl << "Please enter 'Yes' or 'No'." << endl;
        }
    }
        
    if (playerOne.size() > 0 && playerOne.size() < 3) {    
            player1_yes = true; 
        cout << "Fine, be that way...";
    return 0;
    }
    
} while (player1_yes == false);
    
    return 0;
}
