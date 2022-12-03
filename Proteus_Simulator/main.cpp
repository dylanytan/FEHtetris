#include "FEHLCD.h"
#include "FEHRandom.h"
#include <stdio.h>

void drawHome();
void showPlayGame();
void showStats();
void showInstruc();
void showCredits();

void drawBoard(int[10][20]);
void generatePiece(int, int[8]);
bool applyGravity(int[8], int[10][20], int, int);
void movePiece(int[8], int, int[10][20]);
void moveDown(int[8], int[10][20]);

bool checkTouch(int, int, int, int);
void drawButton(char[], int, int, int, int);

/*
DRAW HOME
*/
void drawHome() {
    LCD.Clear();

    // Displays starting screen
    LCD.WriteLine("TETRIS");
    LCD.SetFontColor(LIGHTGOLDENRODYELLOW);
    drawButton("PLAY",20,50,100,30);
    drawButton("Stats",20,100,100,30);
    drawButton("Instruc", 25, 150, 100, 30);
    drawButton("Credits",20,200,100,30); 

    int userSelection = 0;
    while (userSelection == 0) {
        LCD.Update();

        if (checkTouch(20,120,50,80)) {
            userSelection = 1;
        }
        else if (checkTouch(20,120,100,130)) {
            userSelection = 2;
        }
        else if (checkTouch(20,120,150,180)) {
            userSelection = 3;
        }
        else if (checkTouch(20,120,200,230)) {
            userSelection = 4;
        }
    }
    LCD.Clear();
    switch(userSelection) {
        case 1:
            showPlayGame();
            break;
        case 2:
            showStats();
            break;
        case 3:
            showInstruc();
            break;
        case 4:
            showCredits();
            break;
    }
}


/*
PLAY GAME
*/
void showPlayGame() {
    LCD.Clear();
    LCD.WriteLine("Play Game Here!!!");

    // Board of set pieces
    int setBoard[10][20];

    // The array represting to position of the activePiece
    int activePieceLocation[8];

    // Int representing the type of the active piece
    int activePieceType;

    // Board representing what gets displayed to the screen
    int displayBoard[10][20];

    // Int representing current level
    int level = 1;

    // Int representing current tick
    int tick = 0;

    // Create the empty board that the game is played on
    for (int i = 0; i < 10; i ++) {
        for (int j = 0; j < 20; j++) {
            setBoard[i][j] = 0;
            displayBoard[i][j] = 0;
        }
    }

    // Create inital piece
    activePieceType = (Random.RandInt() / 4681) + 1;
    generatePiece(activePieceType, activePieceLocation);

    // Loop for the game
    bool gameCont = true;

    while (gameCont) {
        // Increament tick
        tick++;

        // Apply gravity to current piece
        // If true, piece tick ground and piece gets moved onto setBoard and new piece gets created
        if (applyGravity(activePieceLocation, setBoard, tick, level)) {
            for (int i = 0; i < 8; i += 2) {
                setBoard[activePieceLocation[i]][activePieceLocation[i+1]] = activePieceType;
            }
            activePieceType = (Random.RandInt() / 4681) + 1;
            generatePiece(activePieceType, activePieceLocation);
        }

        // Combine activepiece with board to make the display board
        for (int i = 0; i < 10; i ++) {
            for (int j = 0; j < 20; j++) {
                displayBoard[i][j] = setBoard[i][j];
            }
        }
        for (int i = 0; i < 8; i += 2) {
            displayBoard[activePieceLocation[i]][activePieceLocation[i+1]] = activePieceType;
        }

        // redraw the board with a back button
        LCD.Clear();
        drawButton("BACK", 250, 25, 60, 30);
        drawBoard(displayBoard);

        // Draw left button
        drawButton("L", 200, 100, 25, 25);
        drawButton("R", 250, 100, 25, 25);
        drawButton("D", 225, 125, 25, 25);

                
        // Check left, right, down buttons
        if (checkTouch(200,225,100,125)) {
            movePiece(activePieceLocation, 1, setBoard);
        }
        else if (checkTouch(250, 275, 100, 125)) {
            movePiece(activePieceLocation, 2, setBoard);
        }
        else if (checkTouch(225, 250, 125, 150)) {
            moveDown(activePieceLocation, setBoard);
        }
        


        // Check back button touch
        if (checkTouch(250, 310, 25, 55)) {
            gameCont = false;
        }

        LCD.Update();
    }

    drawHome();
    while (true) {
        LCD.Update();
    }
}

void showStats() {
    LCD.Clear();
    LCD.WriteLine("HIGH SCORES:");
    LCD.WriteLine(" ");
    LCD.WriteLine("1.   Ava: 5000");
    LCD.WriteLine("2.   Bob: 4000");
    LCD.WriteLine("3.   Carl: 3000");
    LCD.WriteLine("4.   Daisy: 2000");
    LCD.WriteLine("5.   Ellen: 1000");

    // Back Button
    drawButton("BACK",250,25,60,30);

    // Wait until back pressed
    bool found = false;
    while (!found) {
        LCD.Update();
        if (checkTouch(250,310,25,55)) {
            found = true;
        }
    }

    drawHome();
}

void showInstruc() {
    LCD.Clear();
    LCD.WriteLine("INSTRUCTIONS:");
    LCD.WriteLine(" ");
    LCD.WriteLine(" ");
    LCD.WriteLine("Move falling pieces to fill the grid");
    LCD.WriteLine("Filled rows in the grids will clear out and give points");
    LCD.WriteLine("Press the left and right buttons to move the active piece");
    LCD.WriteLine("Press the rotate buttons to rotate the active piece");

    // Back Button
    LCD.DrawRectangle(250,25,60,30);
    LCD.WriteAt("BACK",255, 30);

    // Back Button
    drawButton("BACK",250,25,60,30);

    // Wait until back pressed
    bool found = false;
    while (!found) {
        LCD.Update();
        if (checkTouch(250,310,25,55)) {
            found = true;
        }
    }

    drawHome();
}

void showCredits() {
    LCD.Clear();
    LCD.WriteLine("Made by Rishi and Dylan");

    // Back Button
    drawButton("BACK",250,25,60,30);

    // Wait until back pressed
    bool found = false;
    while (!found) {
        LCD.Update();

        // Check Back button
        if (checkTouch(250,310,25,55)) {
            found = true;
        }
    }

    drawHome();
}

int main()
{
    
    drawHome();

    while (true) {
        LCD.Update();
    }
    return 0;
}

// Function that returns if a certain area is currently being touched
bool checkTouch(int x1, int x2, int y1, int y2) {
    float touchX, touchY;
    if (LCD.Touch(&touchX, &touchY)) {
        if (touchX >= x1 && touchX <= x2 && touchY >= y1 && touchY <= y2) {
            return true;
        }
    }
    return false;
    
}

// Function to draw button with certain size at given location
void drawButton(char text[], int x, int y, int w, int h) {
    LCD.DrawRectangle(x, y ,w, h);
    LCD.WriteAt(text, x + 5, y + 5);
}

// Draw a board of different colored blocks 
void drawBoard(int board[10][20]) {
    // Constant values about board
    int leftBuffer = 50;
    int topBuff = 20;
    int width = 10;

    // Create outline of board
    LCD.SetFontColor(GRAY);
    LCD.DrawRectangle(leftBuffer,topBuff, width * 10, width * 20);

    // loop through all the values of the 
    for (int i = 0; i < 10; i++ ){
        for (int j = 0; j < 20; j++) {
            int color = board[i][j];
            if (color != 0) {
                switch(color) {
                    case 1:
                        LCD.SetFontColor(DARKTURQUOISE);
                        break;
                    case 2:
                        LCD.SetFontColor(ROYALBLUE);
                        break;
                    case 3:
                        LCD.SetFontColor(ORANGE);
                        break;
                    case 4:
                        LCD.SetFontColor(GOLD);
                        break;
                    case 5:
                        LCD.SetFontColor(LIME);
                        break;
                    case 6:
                        LCD.SetFontColor(MEDIUMPURPLE);
                        break;
                    case 7:
                        LCD.SetFontColor(INDIANRED);
                        break;
                }
                LCD.DrawRectangle(leftBuffer + (i * width), topBuff + (j * width), width, width);
            }
            

        }
    }
}

void generatePiece(int type, int n[8]) {
    // Switch depending on the type of tetromino being created
    // modity array n co contain the values of the coordinates of the piece
    switch (type) {
        // I piece
        case 1:
            n[0] = 3; n[1] = 0;
            n[2] = 4; n[3] = 0;
            n[4] = 5; n[5] = 0;
            n[6] = 6; n[7] = 0;
            break;

        // J piece
        case 2:
            n[0] = 3; n[1] = 0;
            n[2] = 3; n[3] = 1;
            n[4] = 4; n[5] = 1;
            n[6] = 5; n[7] = 1;
            break;

        // L piece
        case 3:
            n[0] = 5; n[1] = 0;
            n[2] = 3; n[3] = 1;
            n[4] = 4; n[5] = 1;
            n[6] = 5; n[7] = 1;
            break;

        // O piece
        case 4:
            n[0] = 4; n[1] = 0;
            n[2] = 5; n[3] = 0;
            n[4] = 4; n[5] = 1;
            n[6] = 5; n[7] = 1;
            break;

        // Z piece
        case 5:
            n[0] = 4; n[1] = 0;
            n[2] = 5; n[3] = 0;
            n[4] = 3; n[5] = 1;
            n[6] = 4; n[7] = 1;
            break;

        // T piece
        case 6:
            n[0] = 4; n[1] = 0;
            n[2] = 3; n[3] = 1;
            n[4] = 4; n[5] = 1;
            n[6] = 5; n[7] = 1;
            break;

        // S piece
        case 7:
            n[0] = 3; n[1] = 0;
            n[2] = 4; n[3] = 0;
            n[4] = 4; n[5] = 1;
            n[6] = 5; n[7] = 1;
            break;
    }

}

bool applyGravity(int pieceLocation[8], int setBoard[10][20], int tick, int level) {

    // Check if gravity is applied current tick
    if (tick % ((10-level) * 5) == 0) {
        // Check if piece is touching bottom of board
        for (int i = 1; i < 8; i += 2) {
            if (pieceLocation[i] == 19) {
                return true;
            }
        }
        // Check if piece is touching another piece below
        for (int i = 0; i < 8; i += 2) {
            if (setBoard[pieceLocation[i]][pieceLocation[i+1]+1] != 0) {
                return true;
            }
        }

        // If piece isn't touching anything below, make piece move down
        for (int i = 1; i < 8; i += 2) {
            pieceLocation[i]++;
        }
    }

    return false;
}

void movePiece(int piece[8], int direction, int board[10][20]) {
    // Variable to determine if there is space to move the piece
    bool moveable = true;
    
    // Loop through to check if the piece is loopable
    for (int i = 0; i < 8; i += 2) {
        if (direction == 1) {
            if (piece[i] == 0) {
                moveable = false;
            }
            else if (board[piece[i]-1][piece[i+1]] != 0) {
                moveable = false;
            }
        }
        else {
            if (piece[i] == 10) {
                moveable = false;
            }
            else if (board[piece[i]+1][piece[i+1]] != 0) {
                moveable = false;
            }
        }
    }

    if (moveable) {
        if (direction == 1) {
            piece[0] -= 1;
            piece[2] -= 1;
            piece[4] -= 1;
            piece[6] -= 1;
        }
        else {
            piece[0] += 1;
            piece[2] += 1;
            piece[4] += 1;
            piece[6] += 1;
        }
    }
}

void moveDown(int piece[8], int board[10][20]) {
    bool moveable = true;
    for (int i = 1; i < 8; i += 2) {
        if (piece[i] == 19) {
            moveable = false;
        }
        else if (board[piece[i-1]][piece[i]+1] != 0) {
            moveable = false;
        }
    }
    if (moveable) {
        for (int i = 1; i < 8; i += 2) {
            piece[i] += 1;
        }
    }
}