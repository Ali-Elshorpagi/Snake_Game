#include <bits/stdc++.h>
#include "graphics.h"
#include <mmsystem.h>  /// To Make Us Use Sounds
#include <stdio.h>    /// To Use sprintf Func To Show Score
#include <climits>
#include <queue>

using namespace std;

const int CELL_SIZE = 18;
const int DIAMOND = 4;
const int EMPTY = 0;
const int BODY = 1;
const int APPLE = 2;
const int WALL = 3;

int counterscore = 0; /// Score Counter
char arr[100000];     /// To sprintf

bool GameOver = false;

enum Directions {UP, DOWN, LEFT, RIGHT};
Directions SnakeDirection = DOWN;

struct Location
{
    int r ;
    int c ;
};

bool isFireStarted;
Location fireLocation;
Directions fireDirection;

queue <Location> snakeBody;

int board[38][35] = /// We Increase The Array To Show The score Under The Game
{
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},

};
void drawWall(int row,int col)
{
    int left = col*CELL_SIZE;
    int top = row*CELL_SIZE;
    int right = left + CELL_SIZE;
    int bottom = top + CELL_SIZE;
    setfillstyle(SOLID_FILL, RGB(81,91,212));
    bar(left, top, right, bottom);
    setcolor(BLACK);
    setlinestyle(SOLID_LINE,1, NORM_WIDTH);
    line(left+0 ,top+9 ,left+18,top+9);
    line(left+12,top+0 ,left+12,top+9);
    line(left+4 ,top+9 ,left+4 ,bottom);
    line(left ,bottom,right ,bottom);
    line(left ,top ,right ,top);
}
void drawApple(int row,int col)
{
    int left = col*CELL_SIZE;
    int top = row*CELL_SIZE;

    readimagefile("package/apple.ico",left , top, left + 16, top + 16);  /// We Use an anthor icon That's more realistic
}

void erasefire(int row,int col)
{
    int left = col*CELL_SIZE;
    int top = row*CELL_SIZE;

    setfillstyle(SOLID_FILL, BLACK  );
    bar(left, top, left+18, top+18);
}

void drawFire(int row,int col)
{
    int left = col*CELL_SIZE;
    int top = row*CELL_SIZE;
    setfillstyle(SOLID_FILL, LIGHTCYAN);
    bar(left+2, top+2, left+15, top+15);
}

void eraseSnakeBody(int row,int col)
{
    int left = col*CELL_SIZE;
    int top = row*CELL_SIZE;

    setfillstyle(SOLID_FILL, BLACK  );
    bar(left, top, left+18, top+18);
}

void drawSnakeBody(int row,int col)
{
    int left = col*CELL_SIZE;
    int top = row*CELL_SIZE;
    setfillstyle(SOLID_FILL, YELLOW);
    bar(left+1, top+1, left+16, top+16);
}
void drawBoard()
{
    for(int row=0; row<38; row++)
    {
        for(int col=0; col<35; col++)
        {
            switch(board[row][col])
            {
            case BODY:
                drawSnakeBody(row,col);
                break;
            case APPLE:
                drawApple(row,col);
                break;
            case WALL:
                drawWall(row,col);
                break;
            }
        }
    }
}

void initSnake()
{
    Location loc;
    loc.r = 6;
    loc.c = 15;
    for(int i=0; i<=3; i++)
    {
        snakeBody.push(loc);
        board[loc.r][loc.c] = 1;
        loc.r += 1;
    }
}

void drawbar(int x,int y,int x1,int y1)  /// We Make a func within name "drawbar" To Hide Game before star and after game over
{
    setcolor(BLACK);
    setfillstyle(SOLID_FILL,BLACK);
    bar(x,y,x1,y1);
    floodfill(x+1,y+1, BLACK);
}

Location getNextfire()
{
    Location nextFireLoc = fireLocation;
    switch(fireDirection)
    {
    case UP:
        nextFireLoc.r -= 1;
        break;
    case DOWN:
        nextFireLoc.r += 1;
        break;
    case LEFT:
        nextFireLoc.c -= 1;
        break;
    case RIGHT:
        nextFireLoc.c += 1;
        break;
    }
    return nextFireLoc;

}

Location getNextHead()
{
    Location head = snakeBody.back();
    switch(SnakeDirection)
    {
    case UP:
        head.r -= 1;
        break;
    case DOWN:
        head.r += 1;
        break;
    case LEFT:
        head.c -= 1;
        break;
    case RIGHT:
        head.c += 1;
        break;
    }
    return head;
}

void generatenextapple()
{
    int r,c;
    do
    {
        r = rand() % 35;
        c = rand() % 35;
    }
    while(board[r][c] != EMPTY);
    counterscore++;   /// We Put the counter here because when the snake eat the apple the score increase dynamic
    board[r][c] = APPLE;
    drawApple(r,c);
}

void moveSnakeToNestlocation(Location nextHead)
{
    snakeBody.push(nextHead);
    drawSnakeBody(nextHead.r, nextHead.c);
    board[nextHead.r][nextHead.c] = 1;

    Location tail = snakeBody.front();
    snakeBody.pop();
    eraseSnakeBody(tail.r, tail.c);
    board[tail.r][tail.c] = 0;
}

void moveandgrowsanke(Location nextHead)
{
    snakeBody.push(nextHead);
    drawSnakeBody(nextHead.r, nextHead.c);
    board[nextHead.r][nextHead.c] = 1;
}

void gameover();  /// We Put the head of func "gameover" To allow us use the func that under it && Proto type

void moveSnake()
{
    Location nextHead = getNextHead();
    switch(board[nextHead.r][nextHead.c])
    {
    case EMPTY:
        moveSnakeToNestlocation(nextHead);
        break;
    case APPLE:
        PlaySound(TEXT("package/apple-crunch.wav") ,NULL,SND_ASYNC);
        moveandgrowsanke(nextHead);
        generatenextapple();
        break;
    case WALL:
    case BODY:
        gameover();
        break;
    }

}


void changeSnakeDirection(char ch)
{
    switch(ch)
    {
    case KEY_UP:
        SnakeDirection = UP;
        break;
    case KEY_DOWN:
        SnakeDirection = DOWN;
        break;
    case KEY_LEFT:
        SnakeDirection = LEFT;
        break;
    case KEY_RIGHT:
        SnakeDirection = RIGHT;
        break;
    }

}

void startFire()
{
    isFireStarted = true;
    fireLocation = getNextHead();
    fireDirection = SnakeDirection;
    drawFire(fireLocation.r,fireLocation.c);

}

void stopFire()
{
    isFireStarted = false;
    erasefire(fireLocation.r,fireLocation.c);

}

void moveFire()
{
    if (isFireStarted)
    {
        Location nextFireLoc = getNextfire();
        if (nextFireLoc.r > 34 || nextFireLoc.r < 1 || nextFireLoc.c > 34 || nextFireLoc.c < 1)
        {
            stopFire();
        }
        drawFire(nextFireLoc.r,nextFireLoc.c);
        erasefire(fireLocation.r,fireLocation.c);
        fireLocation = nextFireLoc;
    }

}

void checkkeyInput()
{
    char ch;
    if(kbhit())
    {
        ch = getch();
        if(ch == 0)
        {
            ch = getch();
            changeSnakeDirection(ch);
        }
        if (ch == 32)
        {
            if(!isFireStarted)
            {
                startFire();
            }
        }
        if(ch == 's' || ch == 'S')    /// Please Read the within name "README"
        {
            sndPlaySound("package/snake_sound.wav",SND_ASYNC|SND_LOOP);
        }
        if(ch == 'n' || ch == 'N')
        {
            sndPlaySound("package/H_1.wav",SND_ASYNC|SND_LOOP);
        }
        if(ch == 't' || ch == 'T')
        {
            sndPlaySound("package/H_2.wav",SND_ASYNC|SND_LOOP);
        }
        if(ch == 'z' || ch == 'Z')
        {
            sndPlaySound("package/H_3.wav",SND_ASYNC|SND_LOOP);
        }
    }
}

void start()   /// We make this func To Show The Start
{
    setcolor(RGB(8,23,42));
    setfillstyle(SOLID_FILL,RGB(8,23,42));
    bar(18,18,613,666);

    /*----------------------------------------*/

    setcolor(RGB(230,230,230));
    setfillstyle(SOLID_FILL,RGB(230,230,230));
    bar(33,33,598,651);

    /*----------------------------------------*/

    setcolor(RGB(8,23,42));
    setfillstyle(SOLID_FILL,RGB(8,23,42));
    bar(48,48,583,636);

    /*----------------------------------------*/

    setbkcolor(RGB(8,23,42));
    setcolor(RGB(239,37,97));
    setfillstyle(SOLID_FILL,RGB(239,37,97));
    settextstyle(GOTHIC_FONT,HORIZ_DIR,9);
    outtextxy(80,70,"Snake");

    /*----------------------------------------*/

    readimagefile("package/snake.jpg",60,165,440,365);

    /*----------------------------------------*/

    setcolor(RGB(69,217,253));
    setfillstyle(SOLID_FILL,RGB(69,217,253));
    settextstyle(GOTHIC_FONT,HORIZ_DIR,8);
    outtextxy(220,160,"Game");

    /*----------------------------------------*/

    setcolor(RGB(255,217,0));
    setfillstyle(SOLID_FILL,RGB(255,217,0));
    settextstyle(GOTHIC_FONT,HORIZ_DIR,3);
    outtextxy(115,400,"Ali Abdulsalam Elshorpagi");
    outtextxy(140,450,"Amr Sameh Mohamed");

    /*----------------------------------------*/

    setcolor(WHITE);
    setfillstyle(SOLID_FILL,WHITE);
    settextstyle(GOTHIC_FONT,HORIZ_DIR,3);
    outtextxy(140,570,"Press any key to start");
}

void end()   /// We make this func To Show The End
{
    setcolor(RGB(8,23,42));
    setfillstyle(SOLID_FILL,RGB(8,23,42));
    bar(18,18,613,666);

    /*----------------------------------------*/

    setcolor(RGB(230,230,230));
    setfillstyle(SOLID_FILL,RGB(230,230,230));
    bar(33,33,598,651);

    /*----------------------------------------*/

    setcolor(RGB(8,23,42));
    setfillstyle(SOLID_FILL,RGB(8,23,42));
    bar(48,48,583,636);

    /*----------------------------------------*/

    setbkcolor(RGB(8,23,42));
    setcolor(RGB(239,37,97));
    setfillstyle(SOLID_FILL,RGB(239,37,97));
    settextstyle(GOTHIC_FONT,HORIZ_DIR,9);
    outtextxy(80,70,"Game");

    /*----------------------------------------*/

    readimagefile("package/snake.jpg",60,165,440,365);

    /*----------------------------------------*/

    setcolor(RGB(69,217,253));
    setfillstyle(SOLID_FILL,RGB(69,217,253));
    settextstyle(GOTHIC_FONT,HORIZ_DIR,9);
    outtextxy(240,160,"Over");

    /*----------------------------------------*/

    setcolor(RGB(255,217,0));
    setfillstyle(SOLID_FILL,RGB(255,217,0));
    settextstyle(GOTHIC_FONT,HORIZ_DIR,2);
    outtextxy(150, 450, "Press \"ESC\" TO Close");
    settextstyle(GOTHIC_FONT,HORIZ_DIR,1);
    outtextxy(95, 490, "Press \"SPACE\" TO Play Again..:)");

    /*----------------------------------------*/

    setcolor(RGB(69,217,253));
    setfillstyle(SOLID_FILL,RGB(69,217,253));
    settextstyle(3,HORIZ_DIR,1);
    outtextxy(280,570,"Powered by");
    settextstyle(GOTHIC_FONT,HORIZ_DIR,5);
    outtextxy(235,590,"CAST");
}



void CounterScore()   /// We make this func To Show score and who made the game into the game
{
    drawbar(18,630,613,666);
    setbkcolor(BLACK);
    setcolor(WHITE);
    settextstyle(BOLD_FONT,HORIZ_DIR,1);
    outtextxy(370,640,"Powerd by: ");
    settextstyle(GOTHIC_FONT,HORIZ_DIR,3);
    outtextxy(480,637,"CAST");
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    sprintf(arr,"Score : %d",counterscore);
    outtextxy(50,637,arr);
}

void score()   /// We make this func to show the Score in game over screan
{
    setcolor(WHITE);
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    sprintf(arr,"Score : %d",counterscore);
    outtextxy(245,400,arr);
}

int main( )
{
    initwindow(35 * CELL_SIZE, 38 * CELL_SIZE);
    /// sndPlaySound("package/Snake Music.wav",SND_ASYNC|SND_LOOP);    /// WE add this line to play  a music during game
    GameOver = false;
    int i=0;
    if(i==0)  /// we add this if to make starting and stop after that
    {
        drawBoard();
        start();
        setcolor(WHITE);
        getch();
        drawbar(20,20,613,613);
        i++;
    }
    initSnake();
    drawBoard();
    int gameTimer = 0;
    while(! GameOver )
    {
        if(gameTimer == INT_MAX)
        {
            gameTimer = 0;
        }
        if(gameTimer % 2000000 == 0)
        {
            moveFire();
        }
        if(gameTimer % 5000000 == 0)
        {
            moveSnake();
            CounterScore();
        }
        gameTimer++;
        checkkeyInput();
    }
    while(! kbhit());
    closegraph( );
}

void play_again()
{
    counterscore = 0;
    while(!snakeBody.empty())
    {
        snakeBody.pop();
    }
    initwindow(35 * CELL_SIZE, 38 * CELL_SIZE);
    GameOver = false;
    int i=0;
    if(i==0)
    {
        drawBoard();
        start();
        setcolor(WHITE);
        getch();
        drawbar(20,20,613,613);
        i++;
    }
    initSnake();
    drawBoard();
    int gameTimer = 0;
    while(! GameOver )
    {
        if(gameTimer == INT_MAX)
        {
            gameTimer = 0;
        }
        if(gameTimer % 2000000 == 0)
        {
            moveFire();
        }
        if(gameTimer % 5000000 == 0)
        {
            moveSnake();
            CounterScore();
        }
        gameTimer++;
        checkkeyInput();
    }
    while(! kbhit());
    closegraph( );
}

void gameover()
{
    GameOver = true;
    PlaySound("package/game_over_sound.wav",NULL,SND_ASYNC);  /// we add this sound of game over
    drawbar(18,18,613,613);   /// this function of drawbar that we explain above
    end(); /// this function of end that we explain above
    score();
    char ch;
    while(true)
    {
        ch = getch();
        if(kbhit)
        {
            if(int(ch) == 27 ) /// 27 to press a ESC
            {
                closegraph();
            }
            else if(int(ch) == 32)  /// 32 To press a SPACE
            {
                play_again();
                //outtextxy(100, 530, "Wait Next Version, friend |^_^|");
            }
        }
    }
}
