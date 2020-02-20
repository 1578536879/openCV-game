#pragma once
#include <opencv2\opencv.hpp>
#include<iostream>
#include <string>
#include<vector>
#include<stdlib.h>
#include<math.h>
using namespace std;
class FlyBirdPlayer
{
	vector<IplImage *> m_birds;
	int m_backgroundWidth = 0;
	int m_backgorundHeight = 0;
	int m_onShow = 0;
	CvPoint m_point;
public:
	FlyBirdPlayer();
	~FlyBirdPlayer();
	void init(IplImage * back);
	void compose(IplImage * back);
	IplImage *show(IplImage *back);
	void fly(int pos, bool flag);
	bool ifDie(vector<CvPoint> points, vector<IplImage * > obs);
	int abs(int x);
};

