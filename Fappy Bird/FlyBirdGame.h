#pragma once
#include"FlyBirdPlayer.h"
#include"FlyBirdObstacle.h"
#include"Game.h"
#include<iostream>
#include<vector>
#include<stdlib.h>
#include<opencv2/opencv.hpp>
#include<math.h>
#include<fstream>
#include<time.h>
using namespace std;
class FlyBirdGame
{
	FlyBirdObstacle m_obs;
	FlyBirdPlayer m_player;
	IplImage *m_back;
	double m_dis = 0;
	double m_highestSocre;
public:
	FlyBirdGame();
	~FlyBirdGame();
	void init(bool voice);
	void run();
	void die(IplImage *b);
};

