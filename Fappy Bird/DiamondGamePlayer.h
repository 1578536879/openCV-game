#pragma once
#include <iostream>
#include<opencv2/opencv.hpp>
#include<stdlib.h>
using namespace std;
class DiamondGamePlayer
{
	int m_player[3][3];
	int m_playerX[3][3];
	int m_playerY[3][3];
	int judge[2][3];//无用
	int x;//无用
	//vector<CvPoint> m_points;
	int m_shape;
	int m_bird;
	vector<IplImage *> m_birds;
public:
	DiamondGamePlayer();
	~DiamondGamePlayer();
	void init(int x, int y);
	void newShape();
	void compose(CvPoint point, IplImage *bird, IplImage *back);
	IplImage *showPalyer(IplImage *back);
	void move(int x);
	void swap(int &a, int &b);
	vector<CvPoint> getPosition();
	void changeShape();
	vector<CvPoint> getChangePoints();
};

