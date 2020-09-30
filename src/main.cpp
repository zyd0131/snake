/*
 * @Author: your name
 * @Date: 2020-09-21 12:29:21
 * @LastEditTime: 2020-09-22 01:29:21
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /greepy_snake/src/main.cpp
 */
#include "game.hpp"

int main(int argc, char const *argv[])
{
    Game game(10, 10, 5, 5);
    game.board->mark(2, 5, STAR);
    game.board->mark(9, 5, STAR);
    game.run();
    // int count=0;
    // while (true)
    // {
    //     system("clear");
    //     game.board->random_star(count);
    //     game.board->print_board();
    //     count++;
    //     usleep(20000);
    // }

    return 0;
}
