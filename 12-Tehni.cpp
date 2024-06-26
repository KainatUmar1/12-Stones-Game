#include<iostream>
#include<conio.h>
#include<fstream>
#include<math.h>
#include<iomanip>
#include<windows.h>
using namespace std;

#define DBLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGREY 7
#define DARKGREY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define DWHITE 15

void getRowColbyLeftClick(int& rpos, int& cpos)
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD Events;
    INPUT_RECORD InputRecord;
    SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
    do
    {
        ReadConsoleInput(hInput, &InputRecord, 1, &Events);
        if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
            rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
            break;
        }
    } while (true);
}
void gotoRowCol(int rpos, int cpos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = cpos;
    scrn.Y = rpos;
    SetConsoleCursorPosition(hOuput, scrn);
}
void SetClr(int clr)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}

enum colour { Blue, Red };
struct position
{
    int ri, ci;
};

void init(char**& B, int& dim, string Ns[], int& turn)
{
    ifstream rdr("Text.txt");
    rdr >> dim;
    B = new char* [dim];
    for (int ri = 0; ri < dim; ri++)
        B[ri] = new char[dim];

    for (int ri = 0; ri < dim; ri++)
    {
        for (int ci = 0; ci < dim; ci++)
            rdr >> B[ri][ci];
    }
    cout << "Enter Name of 1st player : ";
    cin >> Ns[0];
    cout << "Enter Name of 2nd player : ";
    cin >> Ns[1];
    turn = Blue;
}

bool isRed(char p)
{
    if (p == '*')
        return true;
    return false;
}

bool isBlue(char p)
{
    if (p == 'O')
        return true;
    return false;
}

bool isMyPiece(char sym, int  turn)
{
    if (turn == RED)
        return isRed(sym);
    return isBlue(sym);
}

void selectPos(position& p, int dim)
{
    cout << "\n\nGive Coordinate(A1:E5): ";
    int d;
    char c;
    cin >> c >> d;
    c = toupper(c);
    p.ri = d - 1;
    p.ci = c - 'A';
}

bool isValidSrc(char** B, int dim, position sc, int turn)
{
    if (sc.ri < 0 || sc.ri >= dim || sc.ci < 0 || sc.ci >= dim)
        return false;
    return (isMyPiece(B[sc.ri][sc.ci], turn));
}

bool isValidDes(char** B, int dim, position dc, int turn)
{
    if (dc.ri < 0 || dc.ri >= dim || dc.ci < 0 || dc.ci >= dim)
        return false;
    return (!(isMyPiece(B[dc.ri][dc.ci], turn)));
}

void updateBoard(char** B, position& sc, position& dc)
{
    char p = B[sc.ri][sc.ci];
    B[dc.ri][dc.ci] = p;
    B[sc.ri][sc.ci] = '-';
}

void changeTurn(int &turn)
{
    if (turn == Blue)
        turn = Red;
    else
        turn = Blue;
}

void Turn(string Ns,int turn)
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
    if (turn == Blue)
        SetClr(9);
    else
        SetClr(12);
    cout << Ns << "`s Turn";
}

void Board(char** B, int row, int col, int para, int a, int b)
{
    for (int i = 0; i < para; i++)
    {
        if (i == 0)
        {
            gotoRowCol(row, col++);
            if (B[a][b] == '*')
                SetClr(4);
            if (B[a][b] == 'O')
                SetClr(1);
            cout << B[a][b] ;
        }
        else
        {
            gotoRowCol(row, col++);
            SetClr(14);
            cout << '-';
        }
    }

    for (int i = 0; i < para; i++)
    {
        if (i==0)
        {
            gotoRowCol(row++, col);
            if (B[a][b] == '*')
                SetClr(4);
            if (B[a][b] == 'O')
                SetClr(1);
            cout << B[a][b];
        }
        else
        {
            gotoRowCol(row++, col);
            SetClr(14);
            cout << '|';
        }
    }

    for (int i = 0; i < para; i++)
    {
        if (i==0)
        {
            gotoRowCol(row, col--);
            if (B[a][b] == '*')
                SetClr(4);
            if (B[a][b] == 'O')
                SetClr(1);
            cout << B[a][b];
        }
        else
        {
            gotoRowCol(row, col--);
            SetClr(14);
            cout << '-';
        }
    }

    for (int i = 0; i < para; i++)
    {
        if (i == 0)
        {
            gotoRowCol(row--, col);
            if (B[a][b] == '*')
                SetClr(4);
            if (B[a][b] == 'O')
                SetClr(1);
            cout << B[a][b];
        }
        else
        {
            gotoRowCol(row--, col);
            SetClr(14);
            cout << '|';
        }
    }
}

void printBoard(char** B, int dim)
{
    system("cls");
    for (int r = 0; r < 40; r++)
    {
        for (int c = 0; c < 40; c++)
        {
            if (r == c)
            {
                gotoRowCol(r,c);
                SetClr(14);
                cout << "\\";
            }
            if (c == (40 - r))
            {
                gotoRowCol(r, c);
                SetClr(14);
                cout << "/";
            }
        }
    }
    for (int r = 0; r < 20; r++)
    {
        for (int c = 0; c < 20; c++)
        {
            if (c == (20-r))
            {
                gotoRowCol(r, c);
                SetClr(14);
                cout << "/";
            }
        }
    }
    for (int c = 0; c < 20; c++)
    {
        for (int r = 20; r <= 40; r++)
        {
            if (r == (20 + c))
            {
                gotoRowCol(r, c);
                SetClr(14);
                cout << "\\";
            }
        }
    }
    for (int r = 20,p=0; r < 40; r++,p++)
    {
        for (int c = 0; c <= 40; c++)
        {
            if (c ==40-p && r==20+p)
            {
                gotoRowCol(r, c);
                SetClr(14);
                cout << "/";
            }
        }
    }
    for (int r = 0; r < 20; r++)
    {
        for (int c = 20; c <= 40; c++)
        {
            if (c == (20 + r))
            {
                gotoRowCol(r, c);
                SetClr(14);
                cout << "\\";
            }
        }
    }
    for (int r = 0; r < dim-1; r++)
    {
        for (int c = 0; c < dim - 1; c++)
        {
            Board(B, r * 10, c * 10, 10, r, c);
        }
    }

}

bool isDiagonalPathClrL2R(char** B, position sc, position dc)
{
    if (sc.ri < dc.ri)
    {
        int Dr = dc.ri - sc.ri - 1;
        for (int i = 1; i <= Dr; i++)
        {
            if (B[sc.ri + i][sc.ci + i] != '-')
                return false;
        }
        return true;
    }
    else
    {
        int Dr = sc.ri - dc.ri - 1;
        for (int i = 1; i <= Dr; i++)
        {
            if (B[sc.ri - i][sc.ci - 1] != '-')
                return false;
        }
        return true;
    }
}

bool isDiagonalPathClrR2L(char** B, position sc, position dc)
{
    if (sc.ri < dc.ri)
    {
        int Dr = dc.ri - sc.ri - 1;
        for (int i = 1; i <= Dr; i++)
        {
            if (B[sc.ri + i][sc.ci - i] != '-')
                return false;
        }
        return true;
    }
    else
    {
        int Dr = sc.ri - dc.ri - 1;
        for (int i = 1; i <= Dr; i++)
        {
            if (B[sc.ri - i][sc.ci + 1] != '-')
                return false;
        }
        return true;
    }
}

int main()
{
    char** B;
    string Ns[2];
    position sc, dc;
    int dim = 0, turn = 0;

    init(B, dim, Ns, turn);
    cout << endl << endl << endl << endl;
    printBoard(B, dim);
    while (true)
    {
        cout << endl << endl << endl << endl << endl;
        Turn(Ns[turn],turn);
        do
        {
            do
            {
                selectPos(sc, dim);
                if (!isValidSrc(B, dim, sc, turn))
                    cout << "Invalid Source selection...!!!";
            } while (!isValidSrc(B, dim, sc, turn));
            selectPos(dc, dim);
            if (!isValidDes(B, dim, sc, turn))
                cout << "Invalid Destination selection...!!!";
        } while (!isValidDes(B, dim, dc, turn));
        system("cls");
        updateBoard(B, sc, dc);
        printBoard(B, dim);
        changeTurn(turn);
    }
    return _getch();
}
