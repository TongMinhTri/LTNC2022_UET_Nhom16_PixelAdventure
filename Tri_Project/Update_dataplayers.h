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
	int max_name = 0;
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
	int diem;
	if (lines > 0)
	{
		int pos1, pos2;
		int space1;
		while (!f2.eof())
		{
			pos1 = pos2 = 0;
			string s;
			string s2 = "";
			getline(f2, s);
			diem = 0;
			for (int i = 3; i < s.length(); i++)
			{
				if (s[i] != ' ')
				{
					space1 = i;
					break;
				}
			}
			for (int i = space1; i < s.length(); i++)
			{
				if ((s[i] >= '1' && s[i] <= '9' || (s[i] == '0' && s[i + 1] == ' '))
					&& s[i + 3] == ' ' && s[i + 4] >= '0' && s[i + 4] <= '9' && (s[i + 6] == 'f' || s[i + 6] == 't'))
				{
					pos1 = i;
					break;
				}
			}
			for (int i = space1; i < pos1 - 1; i++)
			{
				s2 += s[i];
			}
			if (s2.length() > 1)
			{
				players[p].init_name(s2);
				diem = (int(char(s[pos1]) - '0')) * 100;
				players[p].init_score(diem);
				pos2 = pos1 + 4;
				players[p].init_heart(int(char(s[pos2]) - '0'));
				if (s[pos2 + 2] == 't') players[p].init_win("true");
				else players[p].init_win("false");
				p++;
			}
			if (s2.length() > max_name) max_name = s2.length();
		}
		f2.close();
	}
	int o, scs, minus_scs = 0;
	o = lines;
	scs = 0;
	while (o >= 10)
	{
		scs++;
		o /= 10;
	}
	players[p].init_name(inputText);
	players[p].init_score(sco);
	players[p].init_heart(heart_game);
	players[p].init_win("false");
	if (inputText.length() > max_name) max_name = inputText.length();
	sort(players, players + lines, sort_data);
	/*for (int i = 0; i < lines; i++)
	{
		players[i].print();
	}*/
	ofstream f4("Data1.txt", ios::out | ios::trunc);
	for (int i = 0; i < lines; i++)
	{
		if (i > 0) f4 << '\n';
		f4 << i + 1 << ". ";
		o = i + 1;
		minus_scs = 0;
		while (o >= 10)
		{
			minus_scs++;
			o /= 10;
		}
		for (int j = 1; j <= max_name - players[i].get_length() + scs - minus_scs; j++)
		{
			f4 << " ";
		}
		f4 << players[i].get_name() << " " << players[i].get_score();
		if (players[i].get_score() == 0) f4 << "   ";
		else f4 << " ";
		f4 << players[i].get_heart() << " " << players[i].get_win();
	}
	f4.close();
	cout << max_name << '\n';
	delete[]players;
}

void update_data2(int sco, int heart_game, string inputText)
{
	char c;
	int lines = 1;
	int max_name = 0;
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
	int diem;
	if (lines > 0)
	{
		int pos1, pos2;
		int space1;
		while (!f2.eof())
		{
			pos1 = pos2 = 0;
			string s;
			string s2 = "";
			getline(f2, s);
			diem = 0;
			for (int i = 3; i < s.length(); i++)
			{
				if (s[i] != ' ')
				{
					space1 = i;
					break;
				}
			}
			for (int i = space1; i < s.length(); i++)
			{
				if ((s[i] >= '1' && s[i] <= '9' || (s[i] == '0' && s[i + 1] == ' '))
					&& s[i + 3] == ' ' && s[i + 4] >= '0' && s[i + 4] <= '9' && (s[i + 6] == 'f' || s[i + 6] == 't'))
				{
					pos1 = i;
					break;
				}
			}
			for (int i = space1; i < pos1 - 1; i++)
			{
				s2 += s[i];
			}
			if (s2.length() > 1)
			{
				players[p].init_name(s2);
				diem = (int(char(s[pos1]) - '0')) * 100;
				players[p].init_score(diem);
				pos2 = pos1 + 4;
				players[p].init_heart(int(char(s[pos2]) - '0'));
				if (s[pos2 + 2] == 't') players[p].init_win("true");
				else players[p].init_win("false");
				p++;
			}
			if (s2.length() > max_name) max_name = s2.length();
		}
		f2.close();
	}
	int o, scs, minus_scs = 0;
	o = lines;
	scs = 0;
	while (o >= 10)
	{
		scs++;
		o /= 10;
	}
	players[p].init_name(inputText);
	players[p].init_score(sco);
	players[p].init_heart(heart_game);
	players[p].init_win("false");
	if (inputText.length() > max_name) max_name = inputText.length();
	sort(players, players + lines, sort_data);
	/*for (int i = 0; i < lines; i++)
	{
		players[i].print();
	}*/
	ofstream f4("Data2.txt", ios::out | ios::trunc);
	for (int i = 0; i < lines; i++)
	{
		if (i > 0) f4 << '\n';
		f4 << i + 1 << ". ";
		o = i + 1;
		minus_scs = 0;
		while (o >= 10)
		{
			minus_scs++;
			o /= 10;
		}
		for (int j = 1; j <= max_name - players[i].get_length() + scs - minus_scs; j++)
		{
			f4 << " ";
		}
		f4 << players[i].get_name() << " " << players[i].get_score();
		if (players[i].get_score() == 0) f4 << "   ";
		else f4 << " ";
		f4 << players[i].get_heart() << " " << players[i].get_win();
	}
	f4.close();
	cout << max_name << '\n';
	delete[]players;
}

void update_big_data(int sco, int heart_game, string inputText, string Victory)
{
	char c;
	int lines = 1;
	int max_name = 0;
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
	int diem;
	if (lines > 0)
	{
		int pos1, pos2;
		int space1;
		while (!f2.eof())
		{
			pos1 = pos2 = 0;
			string s;
			string s2 = "";
			getline(f2, s);
			diem = 0;
			for (int i = 3; i < s.length(); i++)
			{
				if (s[i] != ' ')
				{
					space1 = i;
					break;
				}
			}
			for (int i = space1; i < s.length(); i++)
			{
				if ((s[i] >= '1' && s[i] <= '9' || (s[i] == '0' && s[i + 1] == ' '))
					&& s[i + 3] == ' ' && s[i + 4] >= '0' && s[i + 4] <= '9' && (s[i + 6] == 'f' || s[i + 6] == 't'))
				{
					pos1 = i;
					break;
				}
			}
			for (int i = space1; i < pos1 - 1; i++)
			{
				s2 += s[i];
			}
			if (s2.length() > 1)
			{
				players[p].init_name(s2);
				diem = (int(char(s[pos1]) - '0')) * 100;
				players[p].init_score(diem);
				pos2 = pos1 + 4;
				players[p].init_heart(int(char(s[pos2]) - '0'));
				if (s[pos2 + 2] == 't') players[p].init_win("true");
				else players[p].init_win("false");
				p++;
			}
			if (s2.length() > max_name) max_name = s2.length();
		}
		f2.close();
	}
	int o, scs, minus_scs = 0;
	o = lines;
	scs = 0;
	while (o >= 10)
	{
		scs++;
		o /= 10;
	}
	players[p].init_name(inputText);
	players[p].init_score(sco);
	players[p].init_heart(heart_game);
	players[p].init_win(Victory);
	if (inputText.length() > max_name) max_name = inputText.length();
	sort(players, players + lines, sort_data);
	/*for (int i = 0; i < lines; i++)
	{
		players[i].print();
	}*/
	ofstream f4("Big_Data.txt", ios::out | ios::trunc);
	for (int i = 0; i < lines; i++)
	{
		if (i > 0) f4 << '\n';
		f4 << i + 1 << ". ";
		o = i + 1;
		minus_scs = 0;
		while (o >= 10)
		{
			minus_scs++;
			o /= 10;
		}
		for (int j = 1; j <= max_name - players[i].get_length() + scs - minus_scs; j++)
		{
			f4 << " ";
		}
		f4 << players[i].get_name() << " " << players[i].get_score();
		if (players[i].get_score() == 0) f4 << "   ";
		else f4 << " ";
		f4 << players[i].get_heart() << " " << players[i].get_win();
	}
	f4.close();
	cout << max_name << '\n';
	delete[]players;
}

#endif // !UPDATE_DATAPLAYERS_H
