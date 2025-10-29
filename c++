#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int WIDTH = 40;
const int HEIGHT = 20;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

class SnakeGame {
private:
    bool gameOver;
    int x, y; // Head position
    int fruitX, fruitY;
    int score;
    Direction dir;
    vector<pair<int, int>> tail;

public:
    SnakeGame() {
        gameOver = false;
        dir = STOP;
        x = WIDTH / 2;
        y = HEIGHT / 2;
        score = 0;
        srand(time(0));
        generateFruit();
    }

    void generateFruit() {
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
    }

    void draw() {
        system("cls"); // Clear screen
        
        // Top border
        for (int i = 0; i < WIDTH + 2; i++)
            cout << "#";
        cout << endl;

        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (j == 0)
                    cout << "#"; // Left border

                if (i == y && j == x)
                    cout << "O"; // Snake head
                else if (i == fruitY && j == fruitX)
                    cout << "F"; // Fruit
                else {
                    bool printTail = false;
                    for (int k = 0; k < tail.size(); k++) {
                        if (tail[k].first == j && tail[k].second == i) {
                            cout << "o";
                            printTail = true;
                        }
                    }
                    if (!printTail)
                        cout << " ";
                }

                if (j == WIDTH - 1)
                    cout << "#"; // Right border
            }
            cout << endl;
        }

        // Bottom border
        for (int i = 0; i < WIDTH + 2; i++)
            cout << "#";
        cout << endl;

        cout << "Score: " << score << endl;
        cout << "Controls: W=Up, A=Left, S=Down, D=Right, X=Exit" << endl;
    }

    void input() {
        if (_kbhit()) {
            switch (_getch()) {
                case 'a':
                case 'A':
                    if (dir != RIGHT) dir = LEFT;
                    break;
                case 'd':
                case 'D':
                    if (dir != LEFT) dir = RIGHT;
                    break;
                case 'w':
                case 'W':
                    if (dir != DOWN) dir = UP;
                    break;
                case 's':
                case 'S':
                    if (dir != UP) dir = DOWN;
                    break;
                case 'x':
                case 'X':
                    gameOver = true;
                    break;
            }
        }
    }

    void logic() {
        // Move tail
        if (!tail.empty()) {
            tail.insert(tail.begin(), make_pair(x, y));
            tail.pop_back();
        }

        // Move head
        switch (dir) {
            case LEFT:
                x--;
                break;
            case RIGHT:
                x++;
                break;
            case UP:
                y--;
                break;
            case DOWN:
                y++;
                break;
            default:
                break;
        }

        // Check wall collision
        if (x >= WIDTH) x = 0;
        else if (x < 0) x = WIDTH - 1;
        if (y >= HEIGHT) y = 0;
        else if (y < 0) y = HEIGHT - 1;

        // Check self collision
        for (int i = 0; i < tail.size(); i++) {
            if (tail[i].first == x && tail[i].second == y)
                gameOver = true;
        }

        // Check fruit collision
        if (x == fruitX && y == fruitY) {
            score += 10;
            generateFruit();
            tail.push_back(make_pair(0, 0));
        }
    }

    void run() {
        cout << "=== SNAKE GAME ===" << endl;
        cout << "Press any key to start..." << endl;
        _getch();

        while (!gameOver) {
            draw();
            input();
            logic();
            Sleep(100); // Game speed
        }

        cout << "\nGame Over!" << endl;
        cout << "Final Score: " << score << endl;
        cout << "Press any key to exit..." << endl;
        _getch();
    }
};

int main() {
    SnakeGame game;
    game.run();
    return 0;
}
