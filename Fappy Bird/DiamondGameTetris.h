#pragma once
#include <iostream>
#include<opencv2/opencv.hpp>
#include<stdlib.h>
using namespace std;
class DiamondGameTetris
{
	int m_map[15][12];
	int m_nowShape;
	int m_preShape;
	int m_preBird;
	int m_bird;
	vector<IplImage* > m_birds;
	IplImage *m_background;
public:
	DiamondGameTetris();
	~DiamondGameTetris();
	void init();
	IplImage * show(IplImage * back);
	void compose(CvPoint point, IplImage *bird, IplImage * back);
	bool ifMove(vector<CvPoint> points, int x);
	void insert(vector<CvPoint> points);
	int getShape();
	int getBird();
	bool ifDie();
	void eliminate(int x);
	int ifEliminate();
	IplImage* forecast(IplImage *back);
	bool ifChange(vector<CvPoint> b_points);
};

