#include <bits/stdc++.h>
#include "graphics.h"
#include <mmsystem.h>
#include <stdio.h>
#include <climits>
#include <queue>
#include <vector>

using namespace std;

const int CELL_SIZE = 18;
const int DIAMOND = 4;
const int EMPTY = 0;
const int BODY = 1;
const int APPLE = 2;
const int WALL = 3;

int counterscore = 0;
int displaycounter = 0;
vector<int> Scores;

char arr[100000];
char arrsc[100000];
long long speed = 5000000;

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

int board[38][35] =
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

    readimagefile("package/apple.ico",left , top, left + 16, top + 16);
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
    for(int i=1; i<34; ++i)
    {
        for(int j=1; j<34; ++j)
        {
            if(board[4][25] || !board[4][25])
                board[4][25] = 2;
            board[i][j] = 0;
        }
    }
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
    for(int i=0; i<=2; i++)
    {
        snakeBody.push(loc);
        board[loc.r][loc.c] = 1;
        loc.r += 1;
    }
}

void drawbar(int x,int y,int x1,int y1)
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
    if(++counterscore)
    {
        speed -= 70000;
    }
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

void gameover();

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
        if(ch == 's' || ch == 'S')
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

void start()
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

void end()
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
    outtextxy(160, 450, "Press \"ESC\" To Close");
    settextstyle(GOTHIC_FONT,HORIZ_DIR,1);
    outtextxy(110, 490, "Press \"SPACE\" To Play Again");
    settextstyle(GOTHIC_FONT,HORIZ_DIR,1);
    outtextxy(130, 530, "Press \"H\" To Display Scores");

    /*----------------------------------------*/

    setcolor(RGB(69,217,253));
    setfillstyle(SOLID_FILL,RGB(69,217,253));
    settextstyle(3,HORIZ_DIR,1);
    outtextxy(280,570,"Powered by");
    settextstyle(GOTHIC_FONT,HORIZ_DIR,5);
    outtextxy(235,590,"CAST");
}



void CounterScore()
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

void score()
{
    ofstream out,ou;
    out.open("package/Scores.txt",ios::app|ios::out);
    ou.open("bin/Debug/package/Scores.txt",ios::app|ios::out);
    setcolor(WHITE);
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    sprintf(arr,"Score : %d",counterscore);
    outtextxy(245,400,arr);
    out<<counterscore<<endl;
    ou<<counterscore<<endl;
    displaycounter++;
    ou.close();
    out.close();
}

void ScoreDisplay()
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
    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);
    outtextxy(60,60,"Note : If the total number Scores greater than 17,");
    outtextxy(130,90,"the all Scores will be Cleared |^_^|");

    /*----------------------------------------*/

    setbkcolor(RGB(8,23,42));
    setcolor(RGB(239,37,97));
    setfillstyle(SOLID_FILL,RGB(239,37,97));
    settextstyle(GOTHIC_FONT,HORIZ_DIR,2);
    outtextxy(60,130,"Scores :");


    /*----------------------------------------*/

    setcolor(RGB(69,217,253));
    setfillstyle(SOLID_FILL,RGB(69,217,253));
    settextstyle(GOTHIC_FONT,HORIZ_DIR,2);
    outtextxy(320,135,"High Score : ");

    /*----------------------------------------*/

    setcolor(RGB(255,217,0));
    setfillstyle(SOLID_FILL,RGB(255,217,0));
    settextstyle(GOTHIC_FONT,HORIZ_DIR,2);
    outtextxy(160, 500, "Press \"ESC\" To Close");
    settextstyle(GOTHIC_FONT,HORIZ_DIR,1);
    outtextxy(110, 540, "Press \"SPACE\" To Play Again");

    /*----------------------------------------*/

    setcolor(RGB(69,217,253));
    setfillstyle(SOLID_FILL,RGB(69,217,253));
    settextstyle(3,HORIZ_DIR,1);
    outtextxy(280,570,"Powered by");
    settextstyle(GOTHIC_FONT,HORIZ_DIR,5);
    outtextxy(235,590,"CAST");
}

bool DeleteScores()
{
    int scor;
    Scores.clear();
    ifstream in,n;
    in.open("package/Scores.txt");
    n.open("bin/Debug/package/Scores.txt");
    if(in)
    {
        while(!in.eof())
        {
            in>>scor;
            Scores.push_back(scor);
        }
        in.close();
    }
    else if(n)
    {
        while(!n.eof())
        {
            n>>scor;
            Scores.push_back(scor);
        }
        n.close();
    }
    if(Scores.size() > 17)
    {
        /*int st1,st2;

        st1 = remove("package/Scores.txt");
        st2 = remove("bin/Debug/package/Scores.txt");

        if(st1==0 && st2==0)
            cout<<"\nFile Deleted Successfully!"<<endl;
        else
            cout<<"\nError Occurred!"<<endl;*/
        in.open("package/Scores.txt", std::ofstream::out | std::ofstream::trunc);
        n.open("bin/Debug/package/Scores.txt", std::ofstream::out | std::ofstream::trunc);
        return false;
    }
    return true;
}

void DisplayScores()
{
    int scores,max=0;
    ifstream in,n;
    in.open("package/Scores.txt");
    n.open("bin/Debug/package/Scores.txt");
    int y=150;
    if(in)
    {
        if(DeleteScores())
        {
            while(in>>scores)
            {
                setcolor(WHITE);
                settextstyle(BOLD_FONT,HORIZ_DIR,3);
                sprintf(arrsc,"  >> %d",scores);
                outtextxy(80,y,arrsc);
                y+=20;
                if(max<scores)
                {
                    max = scores;
                }
                setcolor(WHITE);
                settextstyle(BOLD_FONT,HORIZ_DIR,3);
                sprintf(arrsc,"%d",max);
                outtextxy(500,135,arrsc);

            }
        }
        in.close();
    }
    else if(n)
    {
        if(DeleteScores())
        {
            while(n>>scores)
            {
                setcolor(WHITE);
                settextstyle(BOLD_FONT,HORIZ_DIR,3);
                sprintf(arrsc,"  >> %d",scores);
                outtextxy(80,y,arrsc);
                y+=20;
                if(max<scores)
                {
                    max = scores;
                }
                setcolor(WHITE);
                settextstyle(BOLD_FONT,HORIZ_DIR,3);
                sprintf(arrsc,"%d",max);
                outtextxy(500,135,arrsc);
            }
        }
        n.close();
    }
}

int main( )
{
    initwindow(35 * CELL_SIZE, 38 * CELL_SIZE);
    /// sndPlaySound("package/Snake Music.wav",SND_ASYNC|SND_LOOP);
    GameOver = false;
    drawBoard();
    start();
    setcolor(WHITE);
    getch();
    drawbar(20,20,613,613);
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
        if(gameTimer % speed == 0)
        {
            moveSnake();
            CounterScore();
        }
        gameTimer++;
        checkkeyInput();
    }
    while(! kbhit());
    closegraph();
}

void play_again()
{
    counterscore = 0;
    speed = 5000000;
    while(!snakeBody.empty())
    {
        snakeBody.pop();
    }
    initwindow(35 * CELL_SIZE, 38 * CELL_SIZE);
    GameOver = false;
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
        if(gameTimer % speed == 0)
        {
            moveSnake();
            CounterScore();
        }
        gameTimer++;
        checkkeyInput();
    }
    while(! kbhit());
    closegraph();

}

void gameover()
{
    GameOver = true;
    PlaySound("package/game_over_sound.wav",NULL,SND_ASYNC);
    drawbar(18,18,613,613);
    end();
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
            }
            else if(int(ch) == 72 || int(ch) == 104) /// 72 | 104 To Press H | h
            {
                ScoreDisplay();
                DisplayScores();
            }
        }
    }
}
