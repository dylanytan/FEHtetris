#include "FEHLCD.h"

void drawHome();
void showPlayGame();
void showStats();
void showInstruc();
void showCredits();

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
    LCD.DrawRectangle(20,50,100,30);
    LCD.WriteAt("Play",25,60);
    LCD.DrawRectangle(20,100,100,30);
    LCD.WriteAt("Stats",25,110);
    LCD.DrawRectangle(20,150,100,30);
    LCD.WriteAt("Instruc",25,160);
    LCD.DrawRectangle(20,200,100,30);
    LCD.WriteAt("Credits",25,210);   

    int userSelection = 0;
    float touchX, touchY;
    float trashX, trashY;
    while (userSelection == 0) {
        LCD.Update();
        while(!LCD.Touch(&touchX,&touchY)) {}
        while(LCD.Touch(&trashX, &trashY)) {}

        if (touchX >= 20 && touchX <= 120 && touchY >= 50 && touchY <= 80) {
            userSelection = 1;
        }
        else if (touchX >= 20 && touchX <= 120 && touchY >= 100 && touchY <= 130) {
            userSelection = 2;
        }
        else if (touchX >= 20 && touchX <= 120 && touchY >= 150 && touchY <= 180) {
            userSelection = 3;
        }
        else if (touchX >= 20 && touchX <= 120 && touchY >= 200 && touchY <= 230) {
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

    // Back Button
    drawButton("BACK", 250, 25, 60, 30);

    // Loop for the game
    bool gameCont = true;

    while (gameCont) {
        if (checkTouch(250, 310, 25, 55)) {
            gameCont = false;
        }
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
    LCD.DrawRectangle(250,25,60,30);
    LCD.WriteAt("BACK",255, 30);

    // Wait until back pressed
    bool found = false;
    float touchX, touchY, trashX, trashY;
    while (!found) {
        LCD.Update();
        while(!LCD.Touch(&touchX,&touchY)) {}
        while(LCD.Touch(&trashX, &trashY)) {}

        if (touchX >= 250 && touchX <= 310 && touchY >= 25 && touchY <= 55) {
            found = true;
        }
    }

    drawHome();
    while (true) {
        LCD.Update();
    }
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

    // Wait until back pressed
    bool found = false;
    float touchX, touchY, trashX, trashY;
    while (!found) {
        LCD.Update();
        while(!LCD.Touch(&touchX,&touchY)) {}
        while(LCD.Touch(&trashX, &trashY)) {}

        if (touchX >= 250 && touchX <= 310 && touchY >= 25 && touchY <= 55) {
            found = true;
        }
    }

    drawHome();
    while (true) {
        LCD.Update();
    }
}

void showCredits() {
    LCD.Clear();
    LCD.WriteLine("Made by Rishi and Dylan");

    // Back Button
    LCD.DrawRectangle(250,25,60,30);
    LCD.WriteAt("BACK",255, 30);

    // Wait until back pressed
    bool found = false;
    float touchX, touchY, trashX, trashY;
    while (!found) {
        LCD.Update();
        while(!LCD.Touch(&touchX,&touchY)) {}
        while(LCD.Touch(&trashX, &trashY)) {}

        if (touchX >= 250 && touchX <= 310 && touchY >= 25 && touchY <= 55) {
            found = true;
        }
    }

    drawHome();
    while (true) {
        LCD.Update();
    }
}

int main()
{
    
    drawHome();

    while (true) {
        LCD.Update();
    }
    return 0;
}

bool checkTouch(int x1, int x2, int y1, int y2) {
    float touchX, touchY;
    if (LCD.Touch(&touchX, &touchY)) {
        if (touchX >= x1 && touchX <= x2 && touchY >= y1 && touchY <= y2) {
            return true;
        }
    }
    return false;
    
}

void drawButton(char text[], int x, int y, int w, int h) {
    LCD.DrawRectangle(x, y ,w, h);
    LCD.WriteAt(text, x + 5, y + 5);
}