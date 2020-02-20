#pragma once
#include <opencv2\opencv.hpp>
#include<iostream>
#include <string>
#include<vector>
#include<stdlib.h>
#include<Windows.h>
#include<mmsystem.h>
#include<dsound.h>
#pragma comment(lib,"WINMM.LIB")
using namespace std;
class FlyBirdObstacle
{
	vector<IplImage *> m_obstacles;
	vector<CvPoint> m_points;
	vector<IplImage *> m_upObs;
	vector<IplImage *> m_downObs;
	int m_backWidth;
	int m_backHeight;
public:
	FlyBirdObstacle();
	~FlyBirdObstacle();
	void init(IplImage *back);
	void move();
	void compose(CvPoint points, IplImage *back, IplImage *obs);
	IplImage *show(IplImage *back);
	vector<IplImage *>getObs();
	vector<CvPoint >getPoints();
};

