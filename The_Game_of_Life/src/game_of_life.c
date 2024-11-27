#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define tmpGotoxy(x, y) (printf("\033[%d;%dH", y, x))
#define customGotoxy(x, y) (move(y, x))

#define MapWidth 82
#define MapHeight 27

#define DeadState (char)0
#define AliveState (char)1
#define BorderState (char)2

#define ClearScreenOffset 2

#define OptionsAmount 6

#define BorderPair 1
#define AlivePair 2

void clearScreen(char macTerminal);
void initializeMap(char* cellStates, char makeDead);
char readMap(char** cellStates);
char shouldBeAlive(char* cellStates, int x, int y);
char nextGeneration(char* cellStates);
void renderState(char currentState);
void renderMap(char* cellStates);
char isFieldEmpty(char* cellStates);
void choiceMenu();
void updateFrameSpeed(float* frameSpeed);

int main() {
    char* cellStates = NULL;
    choiceMenu();
    if (readMap(&cellStates)) {
        float frameSpeed = 2.5f;
        char gameOver = (char)0;

        initscr();
        cbreak();
        nodelay(stdscr, TRUE);
        curs_set(0);
        noecho();

        start_color();
        init_pair(BorderPair, COLOR_WHITE, COLOR_WHITE);
        init_pair(AlivePair, COLOR_GREEN, COLOR_YELLOW);

        stdin = freopen("/dev/tty", "r", stdin);
        while (cellStates && !gameOver) {
            renderMap(cellStates);
            gameOver = (char)(nextGeneration(cellStates) || isFieldEmpty(cellStates));
            updateFrameSpeed(&frameSpeed);

            refresh();
            usleep(155000 * frameSpeed);
        }

        if (gameOver) {
            scanf("%c", &gameOver);
            clearScreen((char)0);
            customGotoxy(0, 0);
            printw("Game Over!");
            refresh();
            scanf("%c", &gameOver);
        }

        endwin();
    } else {
        clearScreen((char)1);
        tmpGotoxy(1, 1);
        printf("Incorrect input");
    }

    if (cellStates) free(cellStates);
    return 0;
}

void clearScreen(char macTerminal) {
    for (int i = 0; i <= MapHeight + ClearScreenOffset; i++) {
        for (int j = 0; j <= MapWidth + ClearScreenOffset; j++) {
            if (!macTerminal) {
                customGotoxy(j, i);
                printw(" ");
            } else {
                tmpGotoxy(j + 1, i + 1);
                printf(" ");
            }
        }
    }
}

void initializeMap(char* cellStates, char makeDead) {
    for (int i = 0; cellStates && i < MapHeight; i++) {
        for (int j = 0; j < MapWidth; j++) {
            if (i == 0 || i == MapHeight - 1 || j == 0 || j == MapWidth - 1)
                *(cellStates + i * MapWidth + j) = BorderState;
            else if (makeDead)
                *(cellStates + i * MapWidth + j) = DeadState;
        }
    }
}

char readMap(char** cellStates) {
    char correctInput = (char)1;
    clearScreen((char)1);
    tmpGotoxy(1, 1);
    *cellStates = (char*)malloc(MapHeight * MapWidth * sizeof(char));

    int tmpVal = 0;
    for (int i = 1; correctInput && *cellStates && i < MapHeight - 1; i++) {
        for (int j = 1; correctInput && j < MapWidth - 1; j++) {
            if (scanf("%d", &tmpVal) < 1 || tmpVal < 0 || tmpVal > 1)
                correctInput = (char)0;
            else
                *(*cellStates + i * MapWidth + j) = (char)tmpVal;
        }
    }
    initializeMap(*cellStates, (char)0);

    return correctInput;
}

char shouldBeAlive(char* cellStates, int x, int y) {
    char ans = (char)1;
    int aliveCounter = 0;

    for (int i = y - 1; i <= y + 1; i++) {
        for (int j = x - 1; j <= x + 1; j++) {
            if (i >= 1 && j >= 1 && i < MapHeight - 1 && j < MapWidth - 1 && (i != y || j != x) &&
                *(cellStates + i * MapWidth + j) == AliveState)
                aliveCounter++;
            else if (i >= MapHeight - 1 && j >= MapWidth - 1 &&
                     *(cellStates + 1 * MapWidth + 1) == AliveState)
                aliveCounter++;
            else if (i <= 0 && j <= 0 &&
                     *(cellStates + (MapHeight - 2) * MapWidth + MapWidth - 2) == AliveState)
                aliveCounter++;
            else if (i >= MapHeight - 1 && j <= 0 &&
                     *(cellStates + 1 * MapWidth + MapWidth - 2) == AliveState)
                aliveCounter++;
            else if (i <= 0 && j >= MapWidth - 1 &&
                     *(cellStates + (MapHeight - 2) * MapWidth + 1) == AliveState)
                aliveCounter++;
            else if (j <= 0 && *(cellStates + i * MapWidth + MapWidth - 2) == AliveState)
                aliveCounter++;
            else if (j >= MapWidth - 1 && *(cellStates + i * MapWidth + 1) == AliveState)
                aliveCounter++;
            else if (i <= 0 && *(cellStates + (MapHeight - 2) * MapWidth + j) == AliveState)
                aliveCounter++;
            else if (i >= MapHeight - 1 && *(cellStates + 1 * MapWidth + j) == AliveState)
                aliveCounter++;
        }
    }

    if ((*(cellStates + y * MapWidth + x) == AliveState && (aliveCounter < 2 || aliveCounter > 3)) ||
        (*(cellStates + y * MapWidth + x) == DeadState && aliveCounter != 3))
        ans = (char)0;

    return ans;
}

char nextGeneration(char* cellStates) {
    char* newCellStates = (char*)malloc(MapWidth * MapHeight * sizeof(char));
    char gameOver = (char)1;

    if (newCellStates) initializeMap(newCellStates, (char)1);

    for (int i = 1; newCellStates && i < MapHeight - 1; i++) {
        for (int j = 1; j < MapWidth - 1; j++) {
            if (shouldBeAlive(cellStates, j, i)) *(newCellStates + i * MapWidth + j) = AliveState;
        }
    }

    for (int i = 0; newCellStates && i < MapHeight; i++) {
        for (int j = 0; j < MapWidth; j++) {
            if (*(cellStates + i * MapWidth + j) != *(newCellStates + i * MapWidth + j)) gameOver = (char)0;

            *(cellStates + i * MapWidth + j) = *(newCellStates + i * MapWidth + j);
        }
    }

    if (newCellStates) free(newCellStates);

    return gameOver;
}

void renderState(char currentState) {
    if (currentState == DeadState)
        printw(" ");
    else if (currentState == AliveState) {
        attron(COLOR_PAIR(AlivePair));
        printw(" ");
        attroff(COLOR_PAIR(AlivePair));
    } else if (currentState == BorderState) {
        attron(COLOR_PAIR(BorderPair));
        printw(" ");
        attroff(COLOR_PAIR(BorderPair));
    }
}

void renderMap(char* cellStates) {
    for (int i = 0; i < MapHeight; i++) {
        for (int j = 0; j < MapWidth; j++) {
            customGotoxy(j, i);
            renderState(*(cellStates + i * MapWidth + j));
        }
    }
}

char isFieldEmpty(char* cellStates) {
    char ans = (char)1;

    for (int i = 0; ans && i < MapHeight; i++) {
        for (int j = 0; ans && j < MapWidth; j++) {
            if (*(cellStates + i * MapWidth + j) == AliveState) ans = (char)0;
        }
    }

    return ans;
}

void choiceMenu() {
    char currentOption = (char)0;
    do {
        clearScreen((char)1);
        tmpGotoxy(1, 1);
        printf("1 - Load Map 1\n");
        printf("2 - Load Map 2\n");
        printf("3 - Load Map 3\n");
        printf("4 - Load Map 4\n");
        printf("5 - Load Map 5\n");
        printf("6 - Load from keyboard\n");
        scanf("%c", &currentOption);
    } while (!(currentOption >= '1' && currentOption <= OptionsAmount + '0'));

    if (currentOption == '1')
        stdin = freopen("Maps/Map1.txt", "r", stdin);
    else if (currentOption == '2')
        stdin = freopen("Maps/Map2.txt", "r", stdin);
    else if (currentOption == '3')
        stdin = freopen("Maps/Map3.txt", "r", stdin);
    else if (currentOption == '4')
        stdin = freopen("Maps/Map4.txt", "r", stdin);
    else if (currentOption == '5')
        stdin = freopen("Maps/Map5.txt", "r", stdin);
    else if (currentOption == '6')
        stdin = freopen("/dev/tty", "r", stdin);
}

void updateFrameSpeed(float* frameSpeed) {
    char chr = getch();

    if ((chr == 'Q' || chr == 'q') && *frameSpeed + *frameSpeed / 2.0 <= 15)
        *frameSpeed += *frameSpeed / 2.0;
    else if ((chr == 'E' || chr == 'e') && *frameSpeed - *frameSpeed / 2.0 >= 0.075)
        *frameSpeed -= *frameSpeed / 2.0;

    flushinp();
}
