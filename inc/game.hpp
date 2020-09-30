/*
 * @Author: BabyXin
 * @Date: 2020-09-21 12:29:21
 * @LastEditTime: 2020-09-22 01:37:06
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /greepy_snake/inc/game.hpp
 */
#include <unistd.h>
#include "iostream"
#include "pthread.h"
#include <termio.h>
enum direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};
enum state
{
    WIN,
    FAIL,
    CONTINUE
};
enum cell
{
    SPACE,
    STAR,
    BLOCK,
    SNAKE
};

static direction head_d;
static direction last_head_d;
class Board
{
private:

    int star_num = 0;
    int block_num = 0;
    int width;
    int height;
    char marker = '*';
    char headmarker = '^';
    cell **mark_board;
    // define by yourself
    void print_line1();                                     // print line with '-'
    void print_line2(int row_line, int head_x, int head_y); // print line with '|' and ' '
public:
    Board(int width, int height);
    void print_board(int head_x, int head_y);
    void mark(int x, int y, cell c);
    void unmark(int x, int y);
    cell getCell(int x, int y);
    bool check_filled(int snake_length);
    void mark_snake(int x, int y);
    void random_star(int snake_length);
    void set_headmarker(direction d);
};

struct Body
{
    int x;
    int y;
    Body(int X, int Y)
    {
        this->x = X;
        this->y = Y;
        this->next = nullptr;
    }
    Body *next;
};

class Snake
{
private:
    direction head_direction; // 脑袋的朝向
    // void readInput(void* args); // 读取输入
public:
    Body *head;
    Body *tail;
    int length;
    Snake(int x, int y, direction d);
    Body *get_next_pos();
    void move(Body &next_pos);
    void grow(Body &next_pos);
    void set_direction(direction d);
};

class Game
{
    static int scanKeyboard();
    static void *readInput(void *args);

private:
    direction get_input_by_keyboard();
    state step(direction d);
    void settle(state game_state);
    void win();
    void fail();

public:
    Board *board;
    Snake *snake;
    Game(int width, int height, int x, int y);
    void run();
};
