#pragma once
#ifndef  FILE_HISTORY_H
#define FILE_HISTORY_H

#include "BaseData.h"

using namespace std;
// su dung ma nguyen de dem so dong trong file
// https://nguyenvanhieu.vn/dem-so-dong-so-ky-tu-trong-file-text-su-dung-c/
class Player
{
private:
    string name;
    int heart;
    string win;
    int Map_game;
    int score;
public:
    Player()
    {
        string name = "";
        heart = 0;
        score = 0;
        Map_game = 1;
        win = "";
    }
    string get_name()
    {
        return name;
    }
    int get_heart()
    {
        return heart;
    }
    string get_win()
    {
        return win;
    }
    int get_Map_game()
    {
        return Map_game;
    }
    int get_score()
    {
        return score;
    }
    void init_name(string _name)
    {
        name = _name;
    }
    void init_heart(int x)
    {
        heart = x;
    }
    void init_win(string x)
    {
        win = x;
    }
    void init_Map_game(int x)
    {
        Map_game = x;
    }
    void init_score(int x)
    {
        score = x;
    }
    int get_length()
    {
        return name.length();
    }
    friend bool sort_data(Player a, Player b);
    void print()
    {
        cout << name << " " << score << " " << heart << " " << win << '\n';
    }
};

bool sort_data(Player a, Player b)
{
    return((a.win > b.win) || (a.win == b.win && a.score > b.score)
        || (a.win == b.win && a.score == b.score && a.heart > b.heart )
        || (a.win == b.win && a.heart == b.heart && a.score == b.score && a.name < b.name));
}

#endif // ! FILE_HISTORY_H


