#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <ctime>
using namespace std;

void start_sentence() {         // function for cout statement
    cout << "~~~~~~~~~~~~~~~~~~~~~" << endl << "Welcome to Battleship" << endl << "~~~~~~~~~~~~~~~~~~~~~" << endl << " " <<endl;
    return; }
    
    // function that tests the players input to see if it hits a battleship or not, and changes the board accordingly
void displayBoardP(string displayPlayer[][10], int arrayPlayer[][10], int size, string input, int& countPlayerP, bool& playAgainP){

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (input == displayPlayer[i][j]) {
                if (arrayPlayer[i][j] == 1) {
                    displayPlayer[i][j] = "X";    countPlayerP++;  
                    cout << "You hit a spot" << endl << "Go again" << endl; }
                else if (arrayPlayer[i][j] == 0) {
                    displayPlayer[i][j] = "O";    playAgainP = false;   
                    cout << "You did not hit a spot" << endl; } } } } }
                    
    // function that tests the randomized computers picked spot to see if it hits a battleship or not, and changes the board accordingly 
void displayBoardB(string displayBot[][10], int arrayBot[][10], int size, int randomR, int randomC, int& countB, bool& playAgainB){

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if ((randomR == i) && (randomC == j)) {
                if (arrayBot[randomR][randomC] == 1) {
                    displayBot[randomR][randomC] = "X";    countB++;   
                    cout << "The computer hit a spot" << endl << "It has another turn" << endl;}
                else if (arrayBot[randomR][randomC] == 0) {
                    displayBot[randomR][randomC] = "O";    playAgainB = false;     
                    cout << "The computer did not hit a spot" << endl; } } } } }

int main() {
    const int a = 10;   const int b = 10;   // variables for row and column of the display player board 
    const int c = 10;   const int d = 10;   // variables for row and column of the display computer board
    int counterP = 0;   int counterB = 0;   // variables that count the total ships for player and computer
    int randomR;        int randomC;        // variables for randomized row and column for the computers turn 
    string placement;                       // variable for players inputed spot 
    int size;                               // variable that determines how much of the total board is use per difficulty 
    bool play_againP;   bool play_againB;   // variables that allow the computer and player to go again if they guess a spot right
    bool next_turn;                         // variable that separates the turns of the player and computer
    srand(time(0));

    string displayPlayer[a][b] = {{"A1","A2","A3","A4","A5","A6","A7","A8","A9","A10"}, // display board for player 
                            {"B1","B2","B3","B4","B5","B6","B7","B8","B9","B10"},       // player picks spots from this board
                            {"C1","C2","C3","C4","C5","C6","C7","C8","C9","C10"}, 
                            {"D1","D2","D3","D4","D5","D6","D7","D8","D9","D10"}, 
                            {"E1","E2","E3","E4","E5","E6","E7","E8","E9","E10"}, 
                            {"F1","F2","F3","F4","F5","F6","F7","F8","F9","F10"}, 
                            {"G1","G2","G3","G4","G5","G6","G7","G8","G9","G10"}, 
                            {"H1","H2","H3","H4","H5","H6","H7","H8","H9","H10"}, 
                            {"I1","I2","I3","I4","I5","I6","I7","I8","I9","I10"}, 
                            {"J1","J2","J3","J4","J5","J6","J7","J8","J9","J10"}};
    string displayBot[c][d] = {{"A1","A2","A3","A4","A5","A6","A7","A8","A9","A10"},    // display board for computer 
                            {"B1","B2","B3","B4","B5","B6","B7","B8","B9","B10"},       // computer randomly picks spots from this board
                            {"C1","C2","C3","C4","C5","C6","C7","C8","C9","C10"}, 
                            {"D1","D2","D3","D4","D5","D6","D7","D8","D9","D10"}, 
                            {"E1","E2","E3","E4","E5","E6","E7","E8","E9","E10"}, 
                            {"F1","F2","F3","F4","F5","F6","F7","F8","F9","F10"}, 
                            {"G1","G2","G3","G4","G5","G6","G7","G8","G9","G10"}, 
                            {"H1","H2","H3","H4","H5","H6","H7","H8","H9","H10"}, 
                            {"I1","I2","I3","I4","I5","I6","I7","I8","I9","I10"}, 
                            {"J1","J2","J3","J4","J5","J6","J7","J8","J9","J10"}};
                            
    int arrayPlayer[10][10] = {{0,0,0,0,0,0,0,0,0,0},       // battleship placement board for player 
                                {0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0}};
    int arrayBot[10][10] = {{0,0,0,0,0,0,0,0,0,0},          // battleship placement board for computer 
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0}};

    bool game_running = true;   // variable to keep the game running
    string start;               // variable to start the game
    
    start_sentence();                           // function call for welcome statement 
    cout << "Type 'Start' to begin:" << endl;           // game start input 
    cin >> start;
    
    while (start != "Start") {
        cout << "Please retype 'Start' to begin:" << endl;      // while "Start" is not entered the loop will repeat and ask again
        cin >> start; }
    
    if (start == "Start") {
    while (game_running == true) {  // while game_running is true the game will run
                                   // at the end of the code, the bool statement is switched to false to end the loop and the game
    string playerOne;
    bool player1_yes = false;               // variable for the player's name input 
   
    cout << "Enter username: " << endl;
    do {
        getline(cin, playerOne);            // loop that will run while player's name input is 0 or less characters and 11 or more
    if (playerOne.size() >= 11) {
        cout << "Exceeded character limit of 10. Please reenter username: " << endl; }
        
    if (playerOne.size() > 0 && playerOne.size() < 11) {    
            player1_yes = true; }
            
} while (player1_yes == false);
    
    cout << "Welcome " << playerOne << "." << endl;
    cout << "You will play the computer in your selected mode 'Easy' 'Medium' or 'Hard'" << endl;
    
    string difficulty;
    
    // output statements that inform the player of the sizes of battleships and the modes of the game
    cout << endl;
    cout << "Easy mode is a 5x5 board with 4 battleships." << endl;
    cout << "Battle ships sizes:" << endl << "1 x 3 spots battleship" << endl << "2 x 2 spots battleship" << endl;
    cout << "1 x 1 spot battleship" << endl << endl; 
    cout << "Medium mode is a 8x8 board with 4 battleships." << endl;
    cout << "Battle ships sizes:" << endl << "1 x 4 spots battleship" << endl << "2 x 3 spots battleship" << endl;
    cout << "1 x 2 spots battleship" << endl << endl;
    cout << "Hard mode is a 8x8 board with 4 battleships." << endl;
    cout << "Battle ships sizes:" << endl << "1 x 5 spots battleship" << endl << "1 x 4 spots battleship" << endl; 
    cout << "1 x 3 spots battleship" << endl << "1 x 2 spots battleship" << endl << endl;
    // the instructions for the game
    cout << "You will guess a spot where the battleship is located." << endl; 
    cout << "If it hits a battleship, the spot you selected will changed to an X." << endl; 
    cout << "If you do not hit a battleship the spot will change to a O." << endl;
    cout << "If you hit a spot, you may continue to go until you do not hit a spot." << endl;
    cout << "The battleships are not diagonal" << endl << "They are either horizontal or vertical" << endl; 
    cout << "The same rules apply to the computer's turn which will go after yours." << endl;
    cout << "To win you need to hit all the battleships on your board before the computer hits all of it's battleship on it's board." << endl;
    cout << endl; 
    cout << "Please select game difficulty: 'Easy', 'Medium', or 'Hard'" << endl;
    getline(cin, difficulty);
    
        // loops while player input is not one of the modes
    while ((difficulty != "Easy") && (difficulty != "Medium") && (difficulty != "Hard")) {
        cout << "Please reenter game difficulty:" << endl;
        cin >> difficulty; }
    
    if (difficulty == "Easy") {             // start of the easy mode

        int random = rand() % 5;
        if (random == 0) {              // randomly picks a number 0-4 that picks placement of the battleships for the player
            arrayPlayer[0][0] = 1;    arrayPlayer[1][0] = 1;    arrayPlayer[3][4] = 1;  arrayPlayer[2][0] = 1;
            arrayPlayer[2][4] = 1;    arrayPlayer[3][1] = 1;    arrayPlayer[3][2] = 1;  arrayPlayer[0][3] = 1; }
        if (random == 1) {
            arrayPlayer[0][0] = 1;    arrayPlayer[0][1] = 1;    arrayPlayer[0][2] = 1;  arrayPlayer[4][4] = 1;
            arrayPlayer[3][4] = 1;    arrayPlayer[2][1] = 1;    arrayPlayer[2][0] = 1;  arrayPlayer[4][0] = 1; }
        if (random == 2) {
            arrayPlayer[2][1] = 1;    arrayPlayer[2][2] = 1;    arrayPlayer[2][3] = 1;  arrayPlayer[0][3] = 1;
            arrayPlayer[0][4] = 1;    arrayPlayer[3][4] = 1;    arrayPlayer[3][3] = 1;  arrayPlayer[4][2] = 1; }
        if (random == 3) {
            arrayPlayer[2][2] = 1;    arrayPlayer[3][2] = 1;    arrayPlayer[4][2] = 1;  arrayPlayer[4][4] = 1;
            arrayPlayer[4][3] = 1;    arrayPlayer[0][3] = 1;    arrayPlayer[1][3] = 1;  arrayPlayer[4][0] = 1; }
        if (random == 4) {
            arrayPlayer[2][2] = 1;    arrayPlayer[2][1] = 1;    arrayPlayer[2][3] = 1;  arrayPlayer[4][0] = 1;
            arrayPlayer[4][2] = 1;    arrayPlayer[4][1] = 1;    arrayPlayer[2][0] = 1;  arrayPlayer[3][4] = 1; }

        int random2 = rand() % 5;
        if (random2 == 0) {             // randomly picks a number from 0-4 that picks placement of battleships for the computer
            arrayBot[4][3] = 1;     arrayBot[4][4] = 1;     arrayBot[4][2] = 1;     arrayBot[0][1] = 1;
            arrayBot[1][1] = 1;     arrayBot[3][1] = 1;     arrayBot[4][1] = 1;     arrayBot[0][3] = 1; }
        if (random2 == 1) {
            arrayBot[0][0] = 1;     arrayBot[1][0] = 1;     arrayBot[2][0] = 1;     arrayBot[4][0] = 1;
            arrayBot[4][1] = 1;     arrayBot[2][3] = 1;     arrayBot[2][4] = 1;     arrayBot[4][4] = 1; }
        if (random2 == 2) {
            arrayBot[0][4] = 1;     arrayBot[0][3] = 1;     arrayBot[0][2] = 1;     arrayBot[4][0] = 1;
            arrayBot[4][1] = 1;     arrayBot[0][0] = 1;     arrayBot[1][0] = 1;     arrayBot[4][4] = 1; }
        if (random2 == 3) {
            arrayBot[1][1] = 1;     arrayBot[2][1] = 1;     arrayBot[3][1] = 1;     arrayBot[4][4] = 1;
            arrayBot[4][3] = 1;     arrayBot[3][3] = 1;     arrayBot[2][3] = 1;     arrayBot[0][2] = 1; }
        if (random2 == 4) {
            arrayBot[3][1] = 1;     arrayBot[2][1] = 1;     arrayBot[1][1] = 1;     arrayBot[2][4] = 1;
            arrayBot[2][3] = 1;     arrayBot[0][1] = 1;     arrayBot[0][2] = 1;     arrayBot[3][3] = 1; }
            
           
            cout << "This is your battleship board" << endl;
            
        for (int z = 0; z < 25; z++) {      // loop will run 25 times max for player and computer, there are 25 spots on player and computers board 
            size = 5;
            next_turn = false;
            play_againP = true;
    
                for (int i = 0; i < size; i++) {        // outputs board for player based on size, size is 5 for 5x5 board for easy
                    for (int j = 0; j < size; j++) {
                        cout << displayPlayer[i][j] << "\t";   }
                    cout << endl;   }
                    
                        cout << "It is your turn to go" << endl;
                        cout << "Please select a new spot" << endl << endl;
        do {
            cin >> placement;  // loops while a spot is not a spot on the board, prevents against a non real spot 
            while ((placement != "A1") && (placement != "A2") && (placement != "A3") && (placement != "A4") && (placement != "A5") 
	            && (placement != "B1") && (placement != "B2") && (placement != "B3") && (placement != "B4") 
	            && (placement != "B5") && (placement != "C1") && (placement != "C2") && (placement != "C3") 
	            && (placement != "C4") && (placement != "C5") && (placement != "D1") && (placement != "D2") 
	            && (placement != "D3") && (placement != "D4") && (placement != "D5") && (placement != "E1") 
	            && (placement != "E2") && (placement != "E3") && (placement != "E4") && (placement != "E5")) {
	                cout << "That spot does not exist" << endl;
	                cout << "Enter a new spot" << endl;   
	                cin >> placement; }
	                // prevents against a non real spot and a spot that has already been selected 
	    while ((placement != displayPlayer[0][0]) && (placement != displayPlayer[0][1]) && (placement != displayPlayer[0][2])
		 && (placement != displayPlayer[0][3]) && (placement != displayPlayer[0][4]) && (placement != displayPlayer[1][0])
		 && (placement != displayPlayer[1][1]) && (placement != displayPlayer[1][2]) && (placement != displayPlayer[1][3]) 
		 && (placement != displayPlayer[1][4]) && (placement != displayPlayer[2][0]) && (placement != displayPlayer[2][1])
		 && (placement != displayPlayer[2][2]) && (placement != displayPlayer[2][3]) && (placement != displayPlayer[2][4]) 
		 && (placement != displayPlayer[3][0]) && (placement != displayPlayer[3][1]) && (placement != displayPlayer[3][2])
		 && (placement != displayPlayer[3][3]) && (placement != displayPlayer[3][4]) && (placement != displayPlayer[4][0]) 
		 && (placement != displayPlayer[4][1]) && (placement != displayPlayer[4][2]) && (placement != displayPlayer[4][3])
		 && (placement != displayPlayer[4][4])) {
	        if ((placement == "A1") || (placement == "A2") || (placement == "A3") || (placement == "A4") || 
	            (placement == "A5") || (placement == "B1") || (placement == "B2") || (placement == "B3") || (placement == "B4") || 
	            (placement == "B5") || (placement == "C1") || (placement == "C2") || (placement == "C3") || (placement == "C4") ||
                (placement == "C5") || (placement == "D1") || (placement == "D2") || (placement == "D3") || (placement == "D4") ||
                (placement == "D4") || (placement == "E1") || (placement == "E2") || (placement == "E3") || (placement == "E4") || 
                (placement == "E5")) {
                        cout << "You have already selected that spot" << endl;
                        cout << "Pick another spot" << endl; }
            else {
                cout << "That spot does not exist" << endl;
                cout << "Pick another spot" << endl; }
	            cin >> placement; }

        displayBoardP(displayPlayer, arrayPlayer, size, placement, counterP, play_againP); 
        // function call that checks the spots for battleships and changes them
                
                    cout << "Your new board looks like this" << endl;
                    
                    for (int i = 0; i < size; i++) {            // outputs board for player based on size, size is 5 for 5x5 board for easy
                        for (int j = 0; j < size; j++) {
                            cout << displayPlayer[i][j] << "\t"; }
                                cout << endl;   }
                                
                    cout << endl;
        
            if (counterP == 8) { play_againP = false; } // when all the player's battleships are hit the player turn loop will end
        
        } while (play_againP == true);  // when a spot is wrong the bool statement will switch and the turn will end
      
      if (counterP == 8) {      // when all the battleships are hit for the player the loop mode will break and the player wins
            cout << "This is your winning board" << endl << "You beat the computer: You win the game!";     break; }
            // winner is declared
      
        do {    if (play_againP == false) {                 // prevents the computers turn from overriding the players turn
                next_turn = true;   play_againB = true; }   // the code cannot move to computers turn until players turn ends 
        } while (next_turn == false);                   
        
        cout << "________________________________________" << endl << endl;     
        // splits up the computer and players turn
        
        cout << "It is the computer's turn now" << endl << endl; 
        
        do {
                        
            randomR = rand() % 5;       // random number generator for column and row that determines the computer's placement
            randomC = rand() % 5;
            
            // loops while the randomized placement has not already been selected by the computer 
                while ((displayBot[randomR][randomC] == "X") || (displayBot[randomR][randomC] == "O")) {
                    randomR = rand() % 5;
                    randomC = rand() % 5; }
                
        displayBoardB(displayBot, arrayBot, size, randomR, randomC, counterB, play_againB);
        // function call to check the computers board for a battleship hit and if it does change it 
        
                for (int i = 0; i < size; i++) {        // output computers board based on size, size is 5 for 5x5 board for easy 
                    for (int j = 0; j < size; j++) {
                        cout << displayBot[i][j] << "\t"; }
                            cout << endl; }
                            
                cout << "This was the computer's turn" << endl << endl; 
                
                        
                if (counterB == 8) { play_againB = false; }     // ends the turn loop when all battleships are hit for computer 
                
        } while (play_againB == true); // when a spot is wrong the bool statement will switch and the turn will end
        
        cout << "________________________________________" << endl << endl;     
        // splits up the computer and players turn
    
        if (counterB == 8) {        // when all the battleships are hit for the computer the mode will end and the computer wins
            cout << "The computer beat you: You lost the game:(";   break; } } }
            // winner is declared

    else if (difficulty == "Medium") {  // start of the medium mode
        
        int random = rand() % 5; 
            if (random == 0) {      // randomly picks a number 0-4 that picks placement of the battleships for the player
                arrayPlayer[6][7] = 1;  arrayPlayer[6][6] = 1;  arrayPlayer[6][5] = 1;  arrayPlayer[6][4] = 1;  
                arrayPlayer[4][2] = 1;  arrayPlayer[4][3] = 1;  arrayPlayer[4][1] = 1;  arrayPlayer[4][6] = 1;  
                arrayPlayer[4][7] = 1;  arrayPlayer[4][5] = 1;  arrayPlayer[0][4] = 1;  arrayPlayer[0][5] = 1; }
            if (random == 1) {
                arrayPlayer[2][2] = 1;  arrayPlayer[3][2] = 1;  arrayPlayer[4][2] = 1;  arrayPlayer[5][2] = 1;  
                arrayPlayer[0][7] = 1;  arrayPlayer[0][6] = 1;  arrayPlayer[0][5] = 1;  arrayPlayer[1][1] = 1;  
                arrayPlayer[1][2] = 1;  arrayPlayer[1][3] = 1;  arrayPlayer[7][0] = 1;  arrayPlayer[7][1] = 1; }
            if (random == 2) {
                arrayPlayer[0][2] = 1;  arrayPlayer[1][2] = 1;  arrayPlayer[2][2] = 1;  arrayPlayer[3][2] = 1;  
                arrayPlayer[5][4] = 1;  arrayPlayer[5][3] = 1;  arrayPlayer[5][2] = 1;  arrayPlayer[0][7] = 1;  
                arrayPlayer[0][6] = 1;  arrayPlayer[0][5] = 1;  arrayPlayer[0][1] = 1;  arrayPlayer[1][1] = 1; }
        if (random == 3) {
                arrayPlayer[2][3] = 1;  arrayPlayer[2][4] = 1;  arrayPlayer[2][5] = 1;  arrayPlayer[2][6] = 1;  
                arrayPlayer[5][0] = 1;  arrayPlayer[5][1] = 1;  arrayPlayer[5][2] = 1;  arrayPlayer[1][1] = 1;  
                arrayPlayer[1][2] = 1;  arrayPlayer[1][3] = 1;  arrayPlayer[6][5] = 1;  arrayPlayer[7][5] = 1; }
        if (random == 4) {
                arrayPlayer[5][7] = 1;  arrayPlayer[5][6] = 1;  arrayPlayer[5][5] = 1;  arrayPlayer[5][4] = 1;  
                arrayPlayer[1][0] = 1;  arrayPlayer[1][1] = 1;  arrayPlayer[1][2] = 1;  arrayPlayer[0][5] = 1;  
                arrayPlayer[0][4] = 1;  arrayPlayer[0][3] = 1;  arrayPlayer[6][2] = 1;  arrayPlayer[6][1] = 1; }
        
        int random2 = rand() % 5;
        if (random2 == 0) {         // randomly picks a number from 0-4 that picks placement of battleships for the computer
            arrayBot[5][7] = 1; arrayBot[5][6] = 1; arrayBot[5][5] = 1; arrayBot[5][4] = 1; arrayBot[1][0] = 1; 
            arrayBot[1][1] = 1; arrayBot[1][2] = 1; arrayBot[0][5] = 1; arrayBot[0][4] = 1; arrayBot[0][3] = 1;
            arrayBot[6][2] = 1; arrayBot[6][1] = 1; }
        if (random2 == 1) {
            arrayBot[4][3] = 1; arrayBot[3][3] = 1; arrayBot[2][3] = 1; arrayBot[1][3] = 1; arrayBot[2][5] = 1;
            arrayBot[3][5] = 1; arrayBot[4][5] = 1; arrayBot[4][0] = 1; arrayBot[3][0] = 1; arrayBot[2][0] = 1;
            arrayBot[7][6] = 1; arrayBot[7][5] = 1; }
        if (random2 == 2) {
            arrayBot[1][0] = 1; arrayBot[2][0] = 1; arrayBot[3][0] = 1; arrayBot[4][0] = 1; arrayBot[2][4] = 1;
            arrayBot[3][4] = 1; arrayBot[4][4] = 1; arrayBot[1][1] = 1; arrayBot[1][2] = 1; arrayBot[1][3] = 1;
            arrayBot[3][7] = 1; arrayBot[4][7] = 1; }
        if (random2 == 3) {
            arrayBot[7][1] = 1; arrayBot[7][2] = 1; arrayBot[7][3] = 1; arrayBot[7][4] = 1; arrayBot[5][4] = 1;
            arrayBot[5][3] = 1; arrayBot[5][2] = 1; arrayBot[1][2] = 1; arrayBot[2][2] = 1; arrayBot[3][2] = 1;
            arrayBot[3][6] = 1; arrayBot[2][6] = 1; }
        if (random2 == 4) {
            arrayBot[0][3] = 1; arrayBot[1][3] = 1; arrayBot[2][3] = 1; arrayBot[3][3] = 1; arrayBot[1][5] = 1;
            arrayBot[2][5] = 1; arrayBot[3][5] = 1; arrayBot[0][1] = 1; arrayBot[1][1] = 1; arrayBot[2][1] = 1;
            arrayBot[6][5] = 1; arrayBot[6][6] = 1; }
        
                cout << "This is your battleship board" << endl;
                
        for (int z = 0; z < 64; z++) {      // loop will run 64 times max for player and computer, there are 64 spots on player and computers board 
            size = 8;
            next_turn = false;
            play_againP = true;
    
                for (int i = 0; i < size; i++) {        // outputs board for player based on size, size is 8 for 8x8 board for medium
                    for (int j = 0; j < size; j++) {
                        cout << displayPlayer[i][j] << "\t";   }
                            cout << endl;   }
                            
                cout << "It is your turn to go" << endl;
                cout << "Please select a new spot" << endl << endl;
                
        do {        // loops while a spot is not a spot on the board, prevents against a non real spot 
            cin >> placement;
        while ((placement != "A1") && (placement != "A2") && (placement != "A3") && (placement != "A4") && (placement != "A5") && 
            (placement != "A6") && (placement != "A7") && (placement != "A8") && (placement != "B1") && (placement != "B2") && 
            (placement != "B3") && (placement != "B4") && (placement != "B5") && (placement != "B6") && (placement != "B7") && 
            (placement != "B8") && (placement != "C1") && (placement != "C2") && (placement != "C3") && (placement != "C4") && 
            (placement != "C5") && (placement != "C6") && (placement != "C7") && (placement != "C8") && (placement != "D1") && 
            (placement != "D2") && (placement != "D3") && (placement != "D4") && (placement != "D5") && (placement != "D6") && 
            (placement != "D7") && (placement != "D8") && (placement != "E1") && (placement != "E2") && (placement != "E3") && 
            (placement != "E4") && (placement != "E5") && (placement != "E6") && (placement != "E7") && (placement != "E8") && 
            (placement != "F1") && (placement != "F2") && (placement != "F3") && (placement != "F4") && (placement != "F5") && 
            (placement != "F6") && (placement != "F7") && (placement != "F8") && (placement != "G1") && (placement != "G2") && 
            (placement != "G3") && (placement != "G4") && (placement != "G5") && (placement != "G6") && (placement != "G7") && 
            (placement != "G8") && (placement != "H1") && (placement != "H2") && (placement != "H3") && (placement != "H4") && 
            (placement != "H5") && (placement != "H6") && (placement != "H7") && (placement != "H8") && (placement != "I1") && 
            (placement != "I2") && (placement != "I3") && (placement != "I4") && (placement != "I5") && (placement != "I6") && 
            (placement != "I7") && (placement != "I8") && (placement != "J1") && (placement != "J2") && (placement != "J3") && 
            (placement != "J4") && (placement != "J5") && (placement != "J6") && (placement != "J7") && (placement != "J8")) {
	            cout << "That spot does not exist" << endl;
	            cout << "Enter a new spot" << endl;   
	            cin >> placement; }
	        // prevents against a non real spot and a spot that has already been selected 
	    while ((placement != displayPlayer[0][0]) && (placement != displayPlayer[0][1]) && (placement != displayPlayer[0][2])
		    && (placement != displayPlayer[0][3]) && (placement != displayPlayer[0][4]) && (placement != displayPlayer[0][5])
		    && (placement != displayPlayer[0][6]) && (placement != displayPlayer[0][7]) && (placement != displayPlayer[1][0]) 
		    && (placement != displayPlayer[1][1]) && (placement != displayPlayer[1][2]) && (placement != displayPlayer[1][3]) 
		    && (placement != displayPlayer[1][4]) && (placement != displayPlayer[1][5]) && (placement != displayPlayer[1][6]) 
		    && (placement != displayPlayer[1][7]) && (placement != displayPlayer[2][0]) && (placement != displayPlayer[2][1])
		    && (placement != displayPlayer[2][2]) && (placement != displayPlayer[2][3]) && (placement != displayPlayer[2][4])
		    && (placement != displayPlayer[2][5]) && (placement != displayPlayer[2][6]) && (placement != displayPlayer[2][7])
		    && (placement != displayPlayer[3][0]) && (placement != displayPlayer[3][1]) && (placement != displayPlayer[3][2])
		    && (placement != displayPlayer[3][3]) && (placement != displayPlayer[3][4]) && (placement != displayPlayer[3][5]) 
		    && (placement != displayPlayer[3][6]) && (placement != displayPlayer[3][7]) && (placement != displayPlayer[4][0])
		    && (placement != displayPlayer[4][1]) && (placement != displayPlayer[4][2]) && (placement != displayPlayer[4][3])
		    && (placement != displayPlayer[4][4]) && (placement != displayPlayer[4][5]) && (placement != displayPlayer[4][6])
		    && (placement != displayPlayer[4][7]) && (placement != displayPlayer[5][0]) && (placement != displayPlayer[5][1])
		    && (placement != displayPlayer[5][2]) && (placement != displayPlayer[5][3]) && (placement != displayPlayer[5][4])
		    && (placement != displayPlayer[5][5]) && (placement != displayPlayer[5][6]) && (placement != displayPlayer[5][7])
		    && (placement != displayPlayer[6][0]) && (placement != displayPlayer[6][1]) && (placement != displayPlayer[6][2])
		    && (placement != displayPlayer[6][3]) && (placement != displayPlayer[6][4]) && (placement != displayPlayer[6][5])
		    && (placement != displayPlayer[6][6]) && (placement != displayPlayer[6][7]) && (placement != displayPlayer[7][0])
		    && (placement != displayPlayer[7][1]) && (placement != displayPlayer[7][2]) && (placement != displayPlayer[7][3])
		    && (placement != displayPlayer[7][4]) && (placement != displayPlayer[7][5]) && (placement != displayPlayer[7][6])
		    && (placement != displayPlayer[7][7])) {
	          if ((placement != "A1") || (placement != "A2") || (placement != "A3") || (placement != "A4") || (placement != "A5")|| 
                (placement != "A6") || (placement != "A7") || (placement != "A8") || (placement != "B1") || (placement != "B2") ||
                (placement != "B3") || (placement != "B4") || (placement != "B5") || (placement != "B6") || (placement != "B7") ||
                (placement != "B8") || (placement != "C1") || (placement != "C2") || (placement != "C3") || (placement != "C4") || 
                (placement != "C5") || (placement != "C6") || (placement != "C7") || (placement != "C8") || (placement != "D1") || 
                (placement != "D2") || (placement != "D3") || (placement != "D4") || (placement != "D5") || (placement != "D6") || 
                (placement != "D7") || (placement != "D8") || (placement != "E1") || (placement != "E2") || (placement != "E3") || 
                (placement != "E4") || (placement != "E5") || (placement != "E6") || (placement != "E7") || (placement != "E8") || 
                (placement != "F1") || (placement != "F2") || (placement != "F3") || (placement != "F4") || (placement != "F5") || 
                (placement != "F6") || (placement != "F7") || (placement != "F8") || (placement != "G1") || (placement != "G2") || 
                (placement != "G3") || (placement != "G4") || (placement != "G5") || (placement != "G6") || (placement != "G7") || 
                (placement != "G8") || (placement != "H1") || (placement != "H2") || (placement != "H3") || (placement != "H4") || 
                (placement != "H5") || (placement != "H6") || (placement != "H7") || (placement != "H8") || (placement != "I1") || 
                (placement != "I2") || (placement != "I3") || (placement != "I4") || (placement != "I5") || (placement != "I6") || 
                (placement != "I7") || (placement != "I8") || (placement != "J1") || (placement != "J2") || (placement != "J3") || 
                (placement != "J4") || (placement != "J5") || (placement != "J6") || (placement != "J7") || (placement != "J8")){
                        cout << "You have already selected that spot" << endl;
                        cout << "Pick another spot" << endl; }
                else {
                        cout << "That spot does not exist" << endl;
                        cout << "Pick another spot" << endl; }
	                    cin >> placement; }
	        
	    displayBoardP(displayPlayer, arrayPlayer, size, placement, counterP, play_againP);
	    // function call that checks the spots for battleships and changes them
                        
                cout << "Your new board looks like this" << endl;
                
                for (int i = 0; i < size; i++) {        // outputs board for player based on size, size is 8 for 8x8 board for medium
                    for (int j = 0; j < size; j++) {
                        cout << displayPlayer[i][j] << "\t"; }
                            cout << endl;   }
                        
                            cout << endl; 
        
            if (counterP == 12) { play_againP = false; } // when all the player's battleships are hit the player turn loop will end
        
        } while (play_againP == true); // when a spot is wrong the bool statement will switch and the turn will end
        
        
        if (counterP == 12) { // when all the battleships are hit for the player the loop mode will break and the player wins
            cout << "This is your winning board" << endl << "You beat the computer: You win the game!";     break; }
            // winner is declared
            
            do {    if (play_againP == false) {             // prevents the computers turn from overriding the players turn
                next_turn = true;   play_againB = true; }   // the code cannot move to computers turn until players turn ends
            } while (next_turn == false);
        
                    cout << "____________________________________________________________" << endl << endl;  
                    // splits up the computer and players turn
                
                    cout << "It is the computer's turn now" << endl << endl; 
        
        do {
	      
        randomR = rand() % 8;   // random number generator for column and row that determines the computer's placement
        randomC = rand() % 8;
        
        // loops while the randomized placement has not already been selected by the computer 
            while ((displayBot[randomR][randomC] == "X") || (displayBot[randomR][randomC] == "O")) {
                randomR = rand() % 8;
                randomC = rand() % 8; }
            
        displayBoardB(displayBot, arrayBot, size, randomR, randomC, counterB, play_againB);
        // function call to check the computers board for a battleship hit and if it does change it
                    
                for (int i = 0; i < size; i++) {            // output computers board based on size, size is 8 for 8x8 board for medium
                    for (int j = 0; j < size; j++) {
                        cout << displayBot[i][j] << "\t"; }
                            cout << endl; }
            
            cout << "This was the computer's turn" << endl << endl;
        
        if (counterB == 12) { play_againB = false; }    // ends the turn loop when all battleships are hit for computer 
        
        } while (play_againB == true); // when a spot is wrong the bool statement will switch and the turn will end
        
        cout << "____________________________________________________________" << endl << endl;  
        // splits up the computer and players turn
        
            if (counterB == 12) {   // when all the battleships are hit for the computer the mode will end and the computer wins
                cout << "The computer beat you: You lost the game:(";   break; } } }
                // winner is declared
    
    else if (difficulty == "Hard") {    // start of the hard mode
        
        int random = rand() % 5;
            if (random == 0) {      // randomly picks a number 0-4 that picks placement of the battleships for the player
                arrayPlayer[7][2] = 1;    arrayPlayer[7][3] = 1;    arrayPlayer[7][4] = 1;    arrayPlayer[7][5] = 1;    
                arrayPlayer[7][6] = 1;    arrayPlayer[4][2] = 1;    
                arrayPlayer[5][2] = 1;    arrayPlayer[3][2] = 1;    arrayPlayer[7][2] = 1;    arrayPlayer[9][2] = 1;    
                arrayPlayer[9][3] = 1;    arrayPlayer[9][4] = 1;    
                arrayPlayer[0][0] = 1;    arrayPlayer[1][0] = 1; }
            if (random == 1) {
                arrayPlayer[3][9] = 1;    arrayPlayer[3][8] = 1;    arrayPlayer[3][7] = 1;    arrayPlayer[3][6] = 1;    
                arrayPlayer[3][5] = 1;    arrayPlayer[1][4] = 1;
                arrayPlayer[1][5] = 1;    arrayPlayer[1][6] = 1;    arrayPlayer[1][7] = 1;    arrayPlayer[6][8] = 1;    
                arrayPlayer[7][8] = 1;    arrayPlayer[8][8] = 1;    
                arrayPlayer[7][4] = 1;    arrayPlayer[8][4] = 1; }
            if (random == 2) {
                arrayPlayer[5][2] = 1;    arrayPlayer[6][2] = 1;    arrayPlayer[7][2] = 1;    arrayPlayer[8][2] = 1;    
                arrayPlayer[9][2] = 1;    arrayPlayer[4][0] = 1;
                arrayPlayer[5][0] = 1;    arrayPlayer[3][7] = 1;    arrayPlayer[4][7] = 1;    arrayPlayer[5][7] = 1;    
                arrayPlayer[4][9] = 1;    arrayPlayer[3][9] = 1;
                arrayPlayer[2][9] = 1;    arrayPlayer[1][9] = 1; }
            if (random == 3) {
                arrayPlayer[5][5] = 1;    arrayPlayer[5][6] = 1;    arrayPlayer[5][7] = 1;    arrayPlayer[5][8] = 1;    
                arrayPlayer[5][9] = 1;    arrayPlayer[2][1] = 1;
                arrayPlayer[3][1] = 1;    arrayPlayer[4][1] = 1;    arrayPlayer[5][1] = 1;    arrayPlayer[9][4] = 1;    
                arrayPlayer[9][3] = 1;    arrayPlayer[9][2] = 1;
                arrayPlayer[2][9] = 1;    arrayPlayer[3][9] = 1; }
            if (random == 4) {
                arrayPlayer[3][4] = 1;    arrayPlayer[4][4] = 1;    arrayPlayer[5][4] = 1;    arrayPlayer[6][4] = 1;    
                arrayPlayer[7][4] = 1;    arrayPlayer[4][7] = 1;
                arrayPlayer[5][7] = 1;    arrayPlayer[6][7] = 1;    arrayPlayer[7][7] = 1;    arrayPlayer[9][0] = 1;    
                arrayPlayer[9][1] = 1;    arrayPlayer[9][2] = 1;
                arrayPlayer[2][8] = 1;    arrayPlayer[2][9] = 1; }

        int random2 = rand() % 5;
            if (random2 == 0) {         // randomly picks a number from 0-4 that picks placement of battleships for the computer
                arrayBot[5][7] = 1; arrayBot[4][7] = 1; arrayBot[3][7] = 1; arrayBot[2][7] = 1; arrayBot[1][7] = 1;
                arrayBot[8][9] = 1; arrayBot[8][8] = 1; arrayBot[8][7] = 1; arrayBot[8][6] = 1; arrayBot[3][0] = 1;
                arrayBot[3][1] = 1; arrayBot[3][2] = 1; arrayBot[1][4] = 1; arrayBot[2][4] = 1; }
            if (random2 == 1) {
                arrayBot[3][1] = 1; arrayBot[4][1] = 1; arrayBot[5][1] = 1; arrayBot[6][1] = 1; arrayBot[7][1] = 1; 
                arrayBot[4][7] = 1; arrayBot[5][7] = 1; arrayBot[6][7] = 1; arrayBot[7][7] = 1; arrayBot[7][9] = 1;
                arrayBot[8][9] = 1; arrayBot[9][9] = 1; arrayBot[1][2] = 1; arrayBot[2][2] = 1; }
            if (random2 == 2) {
                arrayBot[7][3] = 1; arrayBot[7][2] = 1; arrayBot[7][1] = 1; arrayBot[7][4] = 1; arrayBot[7][5] = 1;
                arrayBot[6][7] = 1; arrayBot[7][7] = 1; arrayBot[8][7] = 1; arrayBot[9][7] = 1; arrayBot[0][0] = 1;
                arrayBot[0][1] = 1; arrayBot[0][2] = 1; arrayBot[3][3] = 1; arrayBot[4][3] = 1; }
            if (random2 == 3) {
                arrayBot[9][9] = 1; arrayBot[8][9] = 1; arrayBot[7][9] = 1; arrayBot[6][9] = 1; arrayBot[5][9] = 1;
                arrayBot[4][4] = 1; arrayBot[5][4] = 1; arrayBot[6][4] = 1; arrayBot[7][4] = 1; arrayBot[9][0] = 1; 
                arrayBot[9][1] = 1; arrayBot[9][2] = 1; arrayBot[3][8] = 1; arrayBot[2][8] = 1; }
            if (random2 == 4) {
                arrayBot[1][8] = 1; arrayBot[2][8] = 1; arrayBot[3][8] = 1; arrayBot[4][8] = 1; arrayBot[5][8] = 1;
                arrayBot[4][1] = 1; arrayBot[3][1] = 1; arrayBot[2][1] = 1; arrayBot[1][1] = 1; arrayBot[8][3] = 1;
                arrayBot[8][2] = 1; arrayBot[8][1] = 1; arrayBot[8][0] = 1; arrayBot[9][0] = 1; }
    
                    cout << "This is your battleship board" << endl;
                    
            for (int z = 0; z < 100; z++) { // loop will run 100 times max for player and computer, there are 100 spots on player and computers board 
                size = 10;
                next_turn = false;
                play_againP = true;
                    
                    for (int i = 0; i < size; i++) {    // outputs board for player based on size, size is 10 for 10x10 board for hard
                        for (int j = 0; j < size; j++) {
                            cout << displayPlayer[i][j] << "\t";   }
                                cout << endl;   }
                                
                        cout << "It is your turn to go" << endl;
                        cout << "Please select a new spot" << endl << endl;
                
        do {        // loops while a spot is not a spot on the board, prevents against a non real spot 
                    cin >> placement;
        while ((placement != "A1") && (placement != "A2") && (placement != "A3") && (placement != "A4") && (placement != "A5") && 
            (placement != "A6") && (placement != "A7") && (placement != "A8") && (placement != "A9") && (placement != "A10") && 
            (placement != "B1") && (placement != "B2") && (placement != "B3") && (placement != "B4") && (placement != "B5") && 
            (placement != "B6") && (placement != "B7") && (placement != "B8") && (placement != "B9") && (placement != "B10") && 
            (placement != "C1") && (placement != "C2") && (placement != "C3") && (placement != "C4") && (placement != "C5") && 
            (placement != "C6") && (placement != "C7") && (placement != "C8") && (placement != "C9") && (placement != "C10") && 
            (placement != "D1") && (placement != "D2") && (placement != "D3") && (placement != "D4") && (placement != "D5") && 
            (placement != "D6") && (placement != "D7") && (placement != "D8") && (placement != "D9") && (placement != "D10") && 
            (placement != "E1") && (placement != "E2") && (placement != "E3") && (placement != "E4") && (placement != "E5") && 
            (placement != "E6") && (placement != "E7") && (placement != "E8") && (placement != "E9") && (placement != "E10") &&
            (placement != "F1") && (placement != "F2") && (placement != "F3") && (placement != "F4") && (placement != "F5") && 
            (placement != "F6") && (placement != "F7") && (placement != "F8") && (placement != "F9") && (placement != "F10") && 
            (placement != "G1") && (placement != "G2") && (placement != "G3") && (placement != "G4") && (placement != "G5") && 
            (placement != "G6") && (placement != "G7") && (placement != "G8") && (placement != "G9") && (placement != "G10") && 
            (placement != "H1") && (placement != "H2") && (placement != "H3") && (placement != "H4") && (placement != "H5") && 
            (placement != "H6") && (placement != "H7") && (placement != "H8") && (placement != "H9") && (placement != "H10") && 
            (placement != "I1") && (placement != "I2") && (placement != "I3") && (placement != "I4") && (placement != "I5") && 
            (placement != "I6") && (placement != "I7") && (placement != "I8") && (placement != "I9") && (placement != "I10") && 
            (placement != "J1") && (placement != "J2") && (placement != "J3") && (placement != "J4") && (placement != "J5") && 
            (placement != "J6") && (placement != "J7") && (placement != "J8") && (placement != "J9") && (placement != "J10")) {
	                cout << "That spot does not exist" << endl;
	                cout << "Enter a new spot" << endl;   
	                cin >> placement; }
	             // prevents against a non real spot and a spot that has already been selected    
	      while ((placement != displayPlayer[0][0]) && (placement != displayPlayer[0][1]) && (placement != displayPlayer[0][2])
		    && (placement != displayPlayer[0][3]) && (placement != displayPlayer[0][4]) && (placement != displayPlayer[0][5])
		    && (placement != displayPlayer[0][6]) && (placement != displayPlayer[0][7]) && (placement != displayPlayer[0][8]) 
		    && (placement != displayPlayer[0][9]) && (placement != displayPlayer[1][0]) && (placement != displayPlayer[1][1]) 
		    && (placement != displayPlayer[1][2]) && (placement != displayPlayer[1][3]) && (placement != displayPlayer[1][4]) 
		    && (placement != displayPlayer[1][5]) && (placement != displayPlayer[1][6]) && (placement != displayPlayer[1][7])
		    && (placement != displayPlayer[1][8]) && (placement != displayPlayer[1][9]) && (placement != displayPlayer[2][0]) 
		    && (placement != displayPlayer[2][1]) && (placement != displayPlayer[2][2]) && (placement != displayPlayer[2][3])
		    && (placement != displayPlayer[2][4]) && (placement != displayPlayer[2][5]) && (placement != displayPlayer[2][6]) 
		    && (placement != displayPlayer[2][7]) && (placement != displayPlayer[2][8]) && (placement != displayPlayer[2][9])
		    && (placement != displayPlayer[3][0]) && (placement != displayPlayer[3][1]) && (placement != displayPlayer[3][2])
		    && (placement != displayPlayer[3][3]) && (placement != displayPlayer[3][4]) && (placement != displayPlayer[3][5]) 
		    && (placement != displayPlayer[3][6]) && (placement != displayPlayer[3][7]) && (placement != displayPlayer[3][8]) 
		    && (placement != displayPlayer[3][9]) && (placement != displayPlayer[4][0]) && (placement != displayPlayer[4][1]) 
		    && (placement != displayPlayer[4][2]) && (placement != displayPlayer[4][3]) && (placement != displayPlayer[4][4]) 
		    && (placement != displayPlayer[4][5]) && (placement != displayPlayer[4][6]) && (placement != displayPlayer[4][7])
		    && (placement != displayPlayer[4][8]) && (placement != displayPlayer[4][9]) && (placement != displayPlayer[5][0]) 
		    && (placement != displayPlayer[5][1]) && (placement != displayPlayer[5][2]) && (placement != displayPlayer[5][3]) 
		    && (placement != displayPlayer[5][4]) && (placement != displayPlayer[5][5]) && (placement != displayPlayer[5][6]) 
		    && (placement != displayPlayer[5][7]) && (placement != displayPlayer[5][8]) && (placement != displayPlayer[5][9]) 
		    && (placement != displayPlayer[6][0]) && (placement != displayPlayer[6][1]) && (placement != displayPlayer[6][2]) 
		    && (placement != displayPlayer[6][3]) && (placement != displayPlayer[6][4]) && (placement != displayPlayer[6][5]) 
		    && (placement != displayPlayer[6][6]) && (placement != displayPlayer[6][7]) && (placement != displayPlayer[6][8]) 
		    && (placement != displayPlayer[6][9]) && (placement != displayPlayer[7][0]) && (placement != displayPlayer[7][1]) 
		    && (placement != displayPlayer[7][2]) && (placement != displayPlayer[7][3]) && (placement != displayPlayer[7][4]) 
		    && (placement != displayPlayer[7][5]) && (placement != displayPlayer[7][6]) && (placement != displayPlayer[7][7])
		    && (placement != displayPlayer[7][8]) && (placement != displayPlayer[7][9]) && (placement != displayPlayer[8][0])
		    && (placement != displayPlayer[8][1]) && (placement != displayPlayer[8][2]) && (placement != displayPlayer[8][3]) 
		    && (placement != displayPlayer[8][4]) && (placement != displayPlayer[8][5]) && (placement != displayPlayer[8][6])
		    && (placement != displayPlayer[8][7]) && (placement != displayPlayer[8][8]) && (placement != displayPlayer[8][9])
		    && (placement != displayPlayer[9][0]) && (placement != displayPlayer[9][1]) && (placement != displayPlayer[9][2])
		    && (placement != displayPlayer[9][3]) && (placement != displayPlayer[9][4]) && (placement != displayPlayer[9][5])
		    && (placement != displayPlayer[9][6]) && (placement != displayPlayer[9][7]) && (placement != displayPlayer[9][8])
		    && (placement != displayPlayer[9][9])) {
		     if ((placement != "A1") || (placement != "A2") || (placement != "A3") || (placement != "A4") || (placement != "A5") ||
              (placement != "A6") || (placement != "A7") || (placement != "A8") || (placement != "A9") || (placement != "A10") || 
              (placement != "B1") || (placement != "B2") || (placement != "B3") || (placement != "B4") || (placement != "B5") ||
              (placement != "B6") || (placement != "B7") || (placement != "B8") || (placement != "B9") || (placement != "B10") || 
              (placement != "C1") || (placement != "C2") || (placement != "C3") || (placement != "C4") || (placement != "C5") || 
              (placement != "C6") || (placement != "C7") || (placement != "C8") || (placement != "C9") || (placement != "C10") || 
              (placement != "D1") || (placement != "D2") || (placement != "D3") || (placement != "D4") || (placement != "D5") || 
              (placement != "D6") || (placement != "D7") || (placement != "D8") || (placement != "D9") || (placement != "D10") || 
              (placement != "E1") || (placement != "E2") || (placement != "E3") || (placement != "E4") || (placement != "E5") || 
              (placement != "E6") || (placement != "E7") || (placement != "E8") || (placement != "E9") || (placement != "E10") ||
              (placement != "F1") || (placement != "F2") || (placement != "F3") || (placement != "F4") || (placement != "F5") || 
              (placement != "F6") || (placement != "F7") || (placement != "F8") || (placement != "F9") || (placement != "F10") || 
              (placement != "G1") || (placement != "G2") || (placement != "G3") || (placement != "G4") || (placement != "G5") || 
              (placement != "G6") || (placement != "G7") || (placement != "G8") || (placement != "G9") || (placement != "G10") || 
              (placement != "H1") || (placement != "H2") || (placement != "H3") || (placement != "H4") || (placement != "H5") || 
              (placement != "H6") || (placement != "H7") || (placement != "H8") || (placement != "H9") || (placement != "H10") || 
              (placement != "I1") || (placement != "I2") || (placement != "I3") || (placement != "I4") || (placement != "I5") || 
              (placement != "I6") || (placement != "I7") || (placement != "I8") || (placement != "I9") || (placement != "I10") || 
              (placement != "J1") || (placement != "J2") || (placement != "J3") || (placement != "J4") || (placement != "J5") || 
              (placement != "J6") || (placement != "J7") || (placement != "J8") || (placement != "J9") || (placement != "J10")) {
                        cout << "You have already selected that spot" << endl;
                        cout << "Pick another spot" << endl; }
                else {
                        cout << "That spot does not exist" << endl;
                        cout << "Pick another spot" << endl; }
		                cin >> placement; }
		     
        displayBoardP(displayPlayer, arrayPlayer, size, placement, counterP, play_againP);
        // function call that checks the spots for battleships and changes them
                        
                    cout << "Your new board looks like this" << endl;
                    
                        for (int i = 0; i < size; i++) {    // outputs board for player based on size, size is 10 for 10x10 board for hard
                            for (int j = 0; j < size; j++) {
                                cout << displayPlayer[i][j] << "\t"; }
                                    cout << endl;   }
                                    
                                    cout << endl;
        
            if (counterP == 14) { play_againP = false; } // when all the player's battleships are hit the player turn loop will end
        
        } while (play_againP == true); // when a spot is wrong the bool statement will switch and the turn will end
            
        if (counterP == 14) { // when all the battleships are hit for the player the loop mode will break and the player wins
            cout << "This is your winning board" << endl << "You beat the computer: You win the game!";     break; }
            // winner is declared
            
            do {    if (play_againP == false) {             // prevents the computers turn from overriding the players turn
                next_turn = true;   play_againB = true; }   // the code cannot move to computers turn until players turn ends
            } while (next_turn == false);
            
        cout << "________________________________________________________________________________" << endl << endl; 
        // splits up the computer and players turn
            
            cout << "It is the computer's turn now" << endl << endl;
            
            do {
                
        randomR = rand() % 10;      // random number generator for column and row that determines the computer's placement
        randomC = rand() % 10;
        
        // loops while the randomized placement has not already been selected by the computer 
            while ((displayBot[randomR][randomC] == "X") || (displayBot[randomR][randomC] == "O")) {
                randomR = rand() % 10;
                randomC = rand() % 10; }
                
        displayBoardB(displayBot, arrayBot, size, randomR, randomC, counterB, play_againB);
        // function call to check the computers board for a battleship hit and if it does change it
                
                
            for (int i = 0; i < size; i++) {            // output computers board based on size, size is 10 for 10x10 board for hard
                for (int j = 0; j < size; j++) {
                    cout << displayBot[i][j] << "\t"; }
                        cout << endl; }
            
            cout << "This was the computer's turn" << endl << endl; 
                        
                if (counterB == 14) { play_againB = false; }  // ends the turn loop when all battleships are hit for computer 
                
        } while (play_againB == true); // when a spot is wrong the bool statement will switch and the turn will end
        
        cout << "________________________________________________________________________________" << endl << endl; 
        // splits up the computer and players turn
    
        if (counterB == 14) {   // when all the battleships are hit for the computer the mode will end and the computer wins
            cout << "The computer beat you: You lost the game:(";   break; } } }
            // winner is declared
            
    game_running = false; } }
    // when the player or the computer wins and the turn and modes are broken through breaks, the code will move to this line 
    // this line switches the bool statement game_running to false and the game ends
    
   return 0; }
