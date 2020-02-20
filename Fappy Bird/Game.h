#pragma once
#include<iostream>
#include<opencv2/opencv.hpp>
#include"DiamondGame.h"
#include"FlyBirdGame.h"
using namespace std;
class Game
{
	IplImage *openVoice;
	IplImage *closeVoice;
	IplImage *back;
public:
	Game();
	~Game();
	void init();
	void compose(IplImage *back, IplImage *voice);
	void show();
};

