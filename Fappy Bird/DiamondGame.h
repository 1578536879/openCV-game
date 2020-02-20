#pragma once
#include "DiamondGamePlayer.h"
#include "DiamondGameTetris.h"
#include"Game.h"
#include <iostream>
#include<opencv2/opencv.hpp>
#include<cstdlib>
#include<fstream>
#include<string>
#include<math.h>
#include<Windows.h>
#include<mmsystem.h>
#include<dsound.h>
#pragma comment(lib,"WINMM.LIB")
using namespace std;
class DiamondGame
{
	int m_socre = 0;
	DiamondGameTetris m_tetris;
	DiamondGamePlayer m_player;
	IplImage *m_back;
	vector<CvPoint> b_points;
	int m_highestScore;
public:
	DiamondGame();
	~DiamondGame();
	void init(bool flag);
	int addEventListener();
	void run(int x);
	void die(IplImage *back);
	void write(IplImage *back);
	void stop(IplImage *b);
};

