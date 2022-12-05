#include "FEHLCD.h"
#include "FEHRandom.h"
#include <stdio.h>

class BoardState;

void drawHome();
void showPlayGame();
void showStats();
void showInstruc();
void showCredits();

void drawBoard(int[10][20]);
bool checkTouch(int, int, int, int);
void drawButton(char[], int, int, int, int);
void generatePieceCoordinates(int, int[8]);

// Class for board state
// This class represents the board and the current active piece
class BoardState {
    public:
        // The board with all the set pieces
        int setBoard[10][20];

        // The active piece and its location
        int activePiece[8];

        // The type of the active piece
        int activePieceType;

        // The rotation level of the active piece
        int rotation;


        /*
        Constructor
        */
        BoardState() {
            // Create the setBoard of empty space
            for (int i = 0; i < 10; i ++) {
                for (int j = 0; j < 20; j++) {
                    setBoard[i][j] = 0;
                }
            }

            // Default values for type and rotation
            activePieceType = 0;
            rotation = 0;
        }


        /*
        Generates an active piece
        */
        void generatePiece() {

            // Set rotation to 0
            rotation = 0;

            // Use random to generate 1 of 7 pieces
            activePieceType = (Random.RandInt() / 4681) + 1;

            // Use generated piece to create coordinates of piece
            generatePieceCoordinates(activePieceType, activePiece);
        }


        /*
        Applies gravity to piece
        Moves based off of current level and tick
        takes in int tick and int level
        Returns whether piece hit bottom
        */
        bool applyGravity(int tick, int level) {

            // Check if gravity is applied current tick
            if (tick % ((10-level) * 5) == 0) {
                // Check if piece is touching bottom of board
                for (int i = 1; i < 8; i += 2) {
                    if (activePiece[i] == 19) {
                        return true;
                    }
                }
                // Check if piece is touching another piece below
                for (int i = 0; i < 8; i += 2) {
                    if (setBoard[activePiece[i]][activePiece[i+1]+1] != 0) {
                        return true;
                    }
                }

                // If piece isn't touching anything below, make piece move down
                for (int i = 1; i < 8; i += 2) {
                    activePiece[i]++;
                }
            }

            return false;
        }


        /*
        Move piece left of right depending on user input
        takes int direction for left for right
        */
        void movePiece(int direction) {
            // Variable to determine if there is space to move the piece
            bool moveable = true;

            // Loop through to check if the piece is moveable based on if each block in piece is gonna collide
            for (int i = 0; i < 8; i += 2) {

                // Check left
                if (direction == 1) {
                    // Check if collid with border
                    if (activePiece[i] == 0) {
                        moveable = false;
                    }

                    // Check if collid with other piece
                    else if (setBoard[activePiece[i]-1][activePiece[i+1]] != 0) {
                        moveable = false;
                    }
                }

                // Check right
                else {
                    // Check if collid with border
                    if (activePiece[i] == 10) {
                        moveable = false;
                    }

                    // Check if collider with other piece
                    else if (setBoard[activePiece[i]+1][activePiece[i+1]] != 0) {
                        moveable = false;
                    }
                }
            }

            // Move piece based of direction by increamenting or decrementing all y values
            if (moveable) {
                if (direction == 1) {
                    activePiece[0] -= 1;
                    activePiece[2] -= 1;
                    activePiece[4] -= 1;
                    activePiece[6] -= 1;
                }
                else {
                    activePiece[0] += 1;
                    activePiece[2] += 1;
                    activePiece[4] += 1;
                    activePiece[6] += 1;
                }
            }
        }


        /*
        Move piece downwards
        */
        void moveDown() {

            bool moveable = true;

            // Loop through to check if the piece is moveable based on if each block in piece is gonna collide
            for (int i = 1; i < 8; i += 2) {
                // Check if piece collides with bottom
                if (activePiece[i] == 19) {
                    moveable = false;
                }

                // Check if piece collides with other piece
                else if (setBoard[activePiece[i-1]][activePiece[i]+1] != 0) {
                    moveable = false;
                }
            }

            // Move piece by increamenting all Y values of the piece
            if (moveable) {
                for (int i = 1; i < 8; i += 2) {
                    activePiece[i] += 1;
                }
            }
        }


        /*
        Rotates piece clockwise
        */
        void rotatePiece() {

            // Int array to represent where the piece should end up
            int resultPosition[8];

            // 2D array of the movements for all rotations

            // I piece rotation
            int rotateI[4][8] = {
                {2, 0, 1, 1, 0, 2, -1, 3},
                {-2, 0, -1, -1, 0, -2, 1, -3},
                {2, 0, 1, 1, 0, 2, -1, 3},
                {-2, 0, -1, -1, 0, -2, 1, -3}
            };

            // J piece rotation
            int rotateJ[4][8] = {
                {2, 1, 1, 0, 0, 1, -1, 2},
                {0, 1, 1, 0, 0, -1, -1, -2},
                {-2, 1, -1, 2, 0, 1, 1, 0},
                {0, -3, -1, -2, 0, -1, 1, 0}
            };

            // L piece rotation
            int rotateL[4][8] = {
                {0, 3, -1, 2, 0, 1, 1, 0},
                {-2, -1, -1, -2, 0, -1, 1, 0},
                {0, -1, 1, 0, 0, 1, -1, 2},
                {2, -1, 1, 0, 0, -1, -1, -2}
            };

            // O piece rotation
            int rotateO[4][8] = {
                {0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0}
            };

            // S piece rotation
            int rotateS[4][8] = {
                {-1, 0, 0, 1, 1, 0, 2, 1},
                {1, 0, 0, -1, -1, 0, -2, -1},
                {-1, 0, 0, 1, 1, 0, 2, 1},
                {1, 0, 0, -1, -1, 0, -2, -1}
            };

            // T piece rotation
            int rotateT[4][8] = {
                {1, 1, 1, -1, 0, 0, -1, 1},
                {-1, 1, 1, 1, 0, 0, -1, -1},
                {-1, -1, -1, 1, 0, 0, 1, -1},
                {1, -1, -1, -1, 0, 0, 1, 1,}
            };

            // Z piece rotation
            int rotateZ[4][8] = {
                {1, 0, 0, 1, -1, 0, -2, 1},
                {-1, 0, 0, -1, 1, 0, 2, -1},
                {1, 0, 0, 1, -1, 0, -2, 1},
                {-1, 0, 0, -1, 1, 0, 2, -1}
            };

            // create result array by adding rotation change array to piece array
            for (int i = 0; i < 8; i++) {
                // Switch depending on piece type
                switch (activePieceType) {
                    case 1:
                        resultPosition[i] = activePiece[i] + rotateI[rotation][i];
                        break;
                    case 2:
                        resultPosition[i] = activePiece[i] + rotateJ[rotation][i];
                        break;
                    case 3:
                        resultPosition[i] = activePiece[i] + rotateL[rotation][i];
                        break;
                    case 4:
                        resultPosition[i] = activePiece[i] + rotateO[rotation][i];
                        break;
                    case 5:
                        resultPosition[i] = activePiece[i] + rotateS[rotation][i];
                        break;
                    case 6:
                        resultPosition[i] = activePiece[i] + rotateT[rotation][i];
                        break;
                    case 7:
                        resultPosition[i] = activePiece[i] + rotateZ[rotation][i];
                        break;
                }
            }

            bool rotationSuccess = true;

            // Check if result position if valid
            for (int i = 0; i < 8; i += 2) {
                // Check if piece is out of box
                if (resultPosition[i] < 0 || resultPosition[i] > 9) {
                    rotationSuccess = false;
                }
                if (resultPosition[i+1] < 0 || resultPosition[i] > 19) {
                    rotationSuccess = false;
                }

                // Check if piece will collide with existing piece
                if (setBoard[resultPosition[i]][resultPosition[i+1]] != 0) {
                    rotationSuccess = false;
                }
            }


            // Change piece position
            if (rotationSuccess) {
              for (int i = 0; i < 8; i++) {
                  activePiece[i] = resultPosition[i];
              }

              // Increment rotation
              rotation++;
              rotation %= 4;
            }

        }

        /*
        Clear completed lines in the board
        return score earned
        */
        int checkLineClear(int level) {

            int linesCleared = 0;
            bool rowCleared = true;

            // Loop through the rows starting at the bottom
            int row = 19;
            while (row >= 0 && linesCleared < 4) {
                rowCleared = true;

                // loop through all values in that row to see if it is completed
                for (int i = 0; i < 10; i++) {
                    if (setBoard[i][row] != 0) {
                        rowCleared = false;
                    }
                }

                // If row is completed
                if (rowCleared) {
                    linesCleared++;
                    // If not top row, move pieces from row above down a level
                    if (row != 0) {
                        for (int i = 0; i < 10; i++) {
                            setBoard[i][row] = setBoard[i][row-1];
                        }
                    }
                    // If it is top row, set row to empty
                    else {
                      for (int i = 0; i < 10; i++) {
                          setBoard[i][row] = 0;
                      }
                    }
                }
                // If line not complete, check line above
                else {
                    row++;
                }

            }

            // Return score based off of level and lines cleared
            int scoreGained = 10 * (linesCleared * ( 1.0 + (0.5 * linesCleared))) * (1.0 + (0.5 * level));

            return scoreGained;

        }

};

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

    // Create boardState
    BoardState boardState;

    // Board representing what gets displayed to the screen
    int displayBoard[10][20];

    // Int representing current level
    int level = 1;

    // Int representing current tick
    int tick = 0;

    // Create inital piece
    boardState.generatePiece();

    // Loop for the game
    bool gameCont = true;

    while (gameCont) {
        // Increament tick
        tick++;

        // Apply gravity to current piece
        // If true, piece tick ground
        // Rotation gets reset to 0
        if (boardState.applyGravity(tick, level)) {
            for (int i = 0; i < 8; i += 2) {
                boardState.setBoard[boardState.activePiece[i]][boardState.activePiece[i+1]] = boardState.activePieceType;
            }
            boardState.generatePiece();
        }

        // Check lines cleared
        boardState.checkLineClear(level);

        // Combine activepiece with board to make the display board
        for (int i = 0; i < 10; i ++) {
            for (int j = 0; j < 20; j++) {
                displayBoard[i][j] = boardState.setBoard[i][j];
            }
        }
        for (int i = 0; i < 8; i += 2) {
            displayBoard[boardState.activePiece[i]][boardState.activePiece[i+1]] = boardState.activePieceType;
        }

        // redraw the board
        LCD.Clear();
        drawBoard(displayBoard);

        // Draw Back button
        drawButton("BACK", 250, 25, 60, 30);

        // Draw control buttons
        drawButton("L", 200, 100, 25, 25);
        drawButton("R", 250, 100, 25, 25);
        drawButton("D", 225, 125, 25, 25);
        drawButton("r", 225, 75, 25, 25);

        // Check left, right, down, and rotate buttons
        if (checkTouch(200,225,100,125)) {
            boardState.movePiece(1);
        }
        else if (checkTouch(250, 275, 100, 125)) {
            boardState.movePiece(2);
        }
        else if (checkTouch(225, 250, 125, 150)) {
            boardState.moveDown();
        }
        else if (checkTouch(225, 250, 75, 100)) {
            boardState.rotatePiece();
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

/*
Main
*/
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

void generatePieceCoordinates(int type, int n[8]) {
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
            n[2] = 5; n[3] = 1;
            n[4] = 4; n[5] = 1;
            n[6] = 3; n[7] = 1;
            break;

        // O piece
        case 4:
            n[0] = 4; n[1] = 0;
            n[2] = 5; n[3] = 0;
            n[4] = 4; n[5] = 1;
            n[6] = 5; n[7] = 1;
            break;

        // S piece
        case 5:
            n[0] = 5; n[1] = 0;
            n[2] = 4; n[3] = 0;
            n[4] = 4; n[5] = 1;
            n[6] = 3; n[7] = 1;
            break;

        // T piece
        case 6:
            n[0] = 4; n[1] = 0;
            n[2] = 3; n[3] = 1;
            n[4] = 4; n[5] = 1;
            n[6] = 5; n[7] = 1;
            break;

        // Z piece
        case 7:
            n[0] = 3; n[1] = 0;
            n[2] = 4; n[3] = 0;
            n[4] = 4; n[5] = 1;
            n[6] = 5; n[7] = 1;
            break;
    }

}
