#pragma once
#ifndef UPDATE_DATAPLAYERS_H
#define UPDATE_DATAPLAYERS_H 

#include "BaseData.h"
#include "File_History.h"
#include <algorithm>

using namespace std;

void update_data1(int sco, int heart_game, string inputText)
{
	char c;
	int lines = 1;
	fstream f1("Data1.txt");
	f1.get(c);
	while (f1)
	{
		while (f1 && c != '\n')
		{
			f1.get(c);
		}
		lines++;
		f1.get(c);
	}
	f1.close();
	//cout << lines << " ";
	fstream f2("Data1.txt");
	Player* players = new Player[lines];
	int p = 0;
	int diem, o, scs;
	if (lines > 1)
	{
		int pos1, pos2;
		while (!f2.eof())
		{
			pos1 = pos2 = 0;
			string s;
			string s2 = "";
			getline(f2, s);
			diem = 0;
			o = p + 1;
			scs = 0;
			while (o >= 10)
			{
				scs++;
				o /= 10;
			}

			for (int i = 3 + scs; i < s.length(); i++)
			{
				if (s[i] >= '0' && s[i] <= '9')
				{
					pos1 = i;
					break;
				}
				s2 += s[i];
			}
			if (s2.length() > 1)
			{
				s2.pop_back();
				players[p].init_name(s2);
				diem = (int(char(s[pos1]) - '0')) * 100;
				players[p].init_score(diem);
				pos2 = pos1 + 4;
				if (s[pos1 + 1] == ' ') pos2 = pos1 + 2;
				players[p].init_heart(int(char(s[pos2]) - '0'));
				if (s[pos2 + 2] == 't') players[p].init_win("true");
				else players[p].init_win("false");
				p++;
			}
		}
		f2.close();
	}
	players[p].init_name(inputText);
	players[p].init_score(sco);
	players[p].init_heart(heart_game);
	players[p].init_win("false");
	sort(players, players + lines, sort_data);
	for (int i = 0; i < lines; i++)
	{
		players[i].print();
	}
	ofstream f4("Data1.txt", ios::out | ios::trunc);
	for (int i = 0; i < lines; i++)
	{
		if (i > 0) f4 << '\n';
		f4 << i + 1 << ". " << players[i].get_name() << " " << players[i].get_score() << " "
			<< players[i].get_heart() << " " << players[i].get_win();
	}
	f4.close();
	delete[]players;
}

void update_data2(int sco, int heart_game, string inputText)
{
	char c;
	int lines = 1;
	fstream f1("Data2.txt");
	f1.get(c);
	while (f1)
	{
		while (f1 && c != '\n')
		{
			f1.get(c);
		}
		lines++;
		f1.get(c);
	}
	f1.close();
	//cout << lines << " ";
	fstream f2("Data2.txt");
	Player* players = new Player[lines];
	int p = 0;
	int diem, o, scs;
	if (lines > 1)
	{
		int pos1, pos2;
		while (!f2.eof() && f2 )
		{
			string s;
			string s2 = "";
			getline(f2, s);
			diem = 0;
			o = p + 1;
			scs = 0;
			while (o >= 10)
			{
				scs++;
				o /= 10;
			}

			for (int i = 3 + scs; i < s.length(); i++)
			{
				if (s[i] >= '0' && s[i] <= '9')
				{
					pos1 = i;
					break;
				}
				s2 += s[i];
			}
			if (s2.length() > 1)
			{
				s2.pop_back();
				players[p].init_name(s2);
				diem = (int(char(s[pos1]) - '0')) * 100;
				players[p].init_score(diem);
				pos2 = pos1 + 4;
				if (s[pos1 + 1] == ' ') pos2 = pos1 + 2;
				players[p].init_heart(int(char(s[pos2]) - '0'));
				if (s[pos2 + 2] == 't') players[p].init_win("true");
				else players[p].init_win("false");
				p++;
			}
		}
		f2.close();
	}
	players[p].init_name(inputText);
	players[p].init_score(sco);
	players[p].init_heart(heart_game);
	players[p].init_win("false");
	sort(players, players + lines, sort_data);
	for (int i = 0; i < lines; i++)
	{
		players[i].print();
	}
	ofstream f4("Data2.txt", ios::out | ios::trunc);
	for (int i = 0; i < lines; i++)
	{
		if (i > 0) f4 << '\n';
		f4 << i + 1 << ". " << players[i].get_name() << " " << players[i].get_score() << " "
			<< players[i].get_heart() << " " << players[i].get_win();
	}
	f4.close();
	delete[]players;
}

void update_big_data(int sco, int heart_game, string inputText, string Victory)
{
	char c;
	int lines = 1;
	fstream f1("Big_Data.txt");
	f1.get(c);
	while (f1)
	{
		while (f1 && c != '\n')
		{
			f1.get(c);
		}
		lines++;
		f1.get(c);
	}
	f1.close();
	//cout << lines << " ";
	fstream f2("Big_Data.txt");
	Player* players = new Player[lines];
	int p = 0;
	int diem, o, scs;
	if (lines > 1)
	{
		int pos1, pos2;
		while (!f2.eof())
		{
			pos1 = pos2 = 0;
			string s;
			string s2 = "";
			getline(f2, s);
			diem = 0;
			o = p + 1;
			scs = 0;
			while (o >= 10)
			{
				scs++;
				o /= 10;
			}

			for (int i = 3 + scs; i < s.length(); i++)
			{
				if (s[i] >= '0' && s[i] <= '9')
				{
					pos1 = i;
					break;
				}
				s2 += s[i];
			}
			if (s2.length() > 1)
			{
				s2.pop_back();
				players[p].init_name(s2);
				diem = (int(char(s[pos1]) - '0')) * 100;
				players[p].init_score(diem);
				pos2 = pos1 + 4;
				if (s[pos1 + 1] == ' ') pos2 = pos1 + 2;
				players[p].init_heart(int(char(s[pos2]) - '0'));
				if (s[pos2 + 2] == 't') players[p].init_win("true");
				else players[p].init_win("false");
				p++;
			}
		}
		f2.close();
	}
	players[p].init_name(inputText);
	players[p].init_score(sco);
	players[p].init_heart(heart_game);
	players[p].init_win(Victory);
	sort(players, players + lines, sort_data);
	for (int i = 0; i < lines; i++)
	{
		players[i].print();
	}
	ofstream f4("Big_Data.txt", ios::out | ios::trunc);
	for (int i = 0; i < lines; i++)
	{
		if (i > 0) f4 << '\n';
		f4 << i + 1 << ". " << players[i].get_name() << " " << players[i].get_score() << " "
			<< players[i].get_heart() << " " << players[i].get_win();
	}
	f4.close();
	delete[]players;
}

#endif // !UPDATE_DATAPLAYERS_H
