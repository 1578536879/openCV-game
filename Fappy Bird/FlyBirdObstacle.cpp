#include "stdafx.h"
#include "FlyBirdObstacle.h"


FlyBirdObstacle::FlyBirdObstacle()
{
	m_upObs.push_back(cvLoadImage("./images/mini_pipe_down.png", 1));
	m_upObs.push_back(cvLoadImage("./images/short_pipe_down.png", 1));
	m_downObs.push_back(cvLoadImage("./images/short_pipe_up.png", 1));
	m_downObs.push_back(cvLoadImage("./images/mini_pipe_up.png", 1));
}


FlyBirdObstacle::~FlyBirdObstacle()
{
}

void FlyBirdObstacle::init(IplImage *back) {
	srand(time(0));
	int len = rand() % 2;
	if (len == 1) {
		m_obstacles.push_back(m_upObs[rand() % 2]);
		m_points.push_back(cvPoint(back->width, 0));
	}
	len = rand() % 2;
	if (len == 1) {
		m_obstacles.push_back(m_downObs[rand() % 2]);
		m_points.push_back(cvPoint(back->width, back->height - m_obstacles[m_obstacles.size() - 1]->height));
	}
	m_backHeight = back->height;
	m_backWidth = back->width;

}

void FlyBirdObstacle::move() {
	int i = 0;
	bool flag1 = true, flag2 = true;
	int del[20] = { -1 };
	int len = 0;
	for (vector<CvPoint>::iterator it = m_points.begin(); it != m_points.end(); it++, i++) {
		(*it).x -= 1;
		if ((*it).x <= -1 * m_obstacles[i]->width) {
			del[len] = i;
			len++;
		}
		if ((*it).x > m_backWidth - m_obstacles[i]->width - 10 - rand() % 40) {
			if ((*it).y == 0) {
				flag1 = false;
			}
			else {
				flag2 = false;
			}
		}
	}
	for (int i = 0; i < len; i++) {
		m_points.erase(m_points.begin() + i);
		m_obstacles.erase(m_obstacles.begin() + i);
	}
	srand(time(0));
	int buf = rand() % 10;
	if (buf == 0 && flag1) {
		m_obstacles.push_back(m_upObs[rand() % 2]);
		m_points.push_back(cvPoint(m_backWidth, 0));
	}
	buf = rand() % 8;
	if (buf == 0 && flag2) {
		m_obstacles.push_back(m_downObs[rand() % 2]);
		m_points.push_back(cvPoint(m_backWidth, m_backHeight - m_obstacles[m_obstacles.size() - 1]->height));
	}
}

void FlyBirdObstacle::compose(CvPoint point, IplImage *back, IplImage *obs) {
	if (back) {
		if (point.x >= m_backWidth) return;
		for (int i = 0; i < obs->height; i++) {
			for (int j = 0; j < obs->width; j++) {

				if (j + point.x < 0) {
					continue;
				}
				if (j + point.x > m_backWidth) {
					continue;
					cout << (j + point.x) << endl;
				}
				int r = CV_IMAGE_ELEM(obs, uchar, i, j * 3);
				int g = CV_IMAGE_ELEM(obs, uchar, i, j * 3 + 1);
				int b = CV_IMAGE_ELEM(obs, uchar, i, j * 3 + 2);
				//if (!(r == 0 && g == 0 && b == 0)) {
				CV_IMAGE_ELEM(back, uchar, i + point.y, (j + point.x) * 3) = r;
				CV_IMAGE_ELEM(back, uchar, i + point.y, (j + point.x) * 3 + 1) = g;
				CV_IMAGE_ELEM(back, uchar, i + point.y, (j + point.x) * 3 + 2) = b;
				//}
			}
		}
	}
}

IplImage *FlyBirdObstacle::show(IplImage *back) {
	int i = 0;
	for (vector<CvPoint>::iterator it = m_points.begin(); it != m_points.end(); it++, i++) {

		compose((*it), back, m_obstacles[i]);
	}
	return back;
}

vector<IplImage *> FlyBirdObstacle::getObs() {
	return m_obstacles;
}

vector<CvPoint> FlyBirdObstacle::getPoints() {
	return m_points;
}