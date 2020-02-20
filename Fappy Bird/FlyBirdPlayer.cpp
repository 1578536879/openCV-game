#include "stdafx.h"
#include "FlyBirdPlayer.h"


FlyBirdPlayer::FlyBirdPlayer()
{
}


FlyBirdPlayer::~FlyBirdPlayer()
{
}

void FlyBirdPlayer::init(IplImage *back) {
	m_birds.push_back(cvLoadImage(".//images//bird0_0.png"));
	m_birds.push_back(cvLoadImage(".//images//bird0_1.png"));
	m_birds.push_back(cvLoadImage(".//images//bird0_2.png"));
	srand(time(0));
	int width = m_birds[0]->width + rand() % (back->width / 2);
	m_point = cvPoint(width, 100);
	if (back != 0) {
		m_backgroundWidth = back->width;
		m_backgorundHeight = back->height;
	}
}

void FlyBirdPlayer::fly(int pos, bool flag) {
	m_onShow++;
	m_onShow = m_onShow % 3;
	if (pos == 0) { /*向下*/
		if (m_point.y + 3 > m_backgorundHeight - m_birds[m_onShow]->height) {
			return;
		}
		if (flag) m_point.y += 1;
		else m_point.y += 3;
	}
	else if (pos == 1) { /*向上*/
		if (m_point.y - 3 < 0) {
			return;
		}
		m_point.y -= 3;
	}
	else if (pos == 2) {/*向左*/
		if (m_point.x - 3 < 0) {
			return;
		}
		m_point.x -= 3;
	}
	else if (pos == 3) {/*向右*/
		if (m_point.x + 3 > m_backgroundWidth - m_birds[m_onShow]->width) {
			return;
		}
		m_point.x += 3;
	}
}

IplImage *FlyBirdPlayer::show(IplImage *back) {
	if (back != 0 && m_birds[m_onShow] != 0) {
		/*if (m_birds[m_onShow]->height + m_point.y > m_backgorundHeight) return;
		if (m_birds[m_onShow]->width + m_point.x > m_backgroundWidth) return;*/
		for (int i = 0; i < m_birds[m_onShow]->height; i++) {
			for (int j = 0; j < m_birds[m_onShow]->width; j++) {
				int r = CV_IMAGE_ELEM(m_birds[m_onShow], uchar, i, j * 3);
				int g = CV_IMAGE_ELEM(m_birds[m_onShow], uchar, i, j * 3 + 1);
				int b = CV_IMAGE_ELEM(m_birds[m_onShow], uchar, i, j * 3 + 2);
				if (!(r == 0 && g == 0 && b == 0)) {
					CV_IMAGE_ELEM(back, uchar, i + m_point.y, (j + m_point.x) * 3) = CV_IMAGE_ELEM(m_birds[m_onShow], uchar, i, j * 3);
					CV_IMAGE_ELEM(back, uchar, i + m_point.y, (j + m_point.x) * 3 + 1) = CV_IMAGE_ELEM(m_birds[m_onShow], uchar, i, j * 3 + 1);
					CV_IMAGE_ELEM(back, uchar, i + m_point.y, (j + m_point.x) * 3 + 2) = CV_IMAGE_ELEM(m_birds[m_onShow], uchar, i, j * 3 + 2);

				}
			}
		}
	}
	return back;
}

int FlyBirdPlayer::abs(int x) {
	if (x < 0) {
		return x * -1;
	}
	else return x;
}

bool FlyBirdPlayer::ifDie(vector<CvPoint> points, vector<IplImage *> obs) {
	int i = 0;
	int top = 10;
	int bottom = 10;
	int left = 30;
	int right = 45;
	for (vector<CvPoint>::iterator it = points.begin(); it != points.end(); it++, i++) {

		if ((*it).y == 0 && m_point.y + top <= obs[i]->height) {
			int a = (*it).x - (m_point.x + left);
			int b = m_point.x + left - (*it).x;
			if (a > 0 && a < m_birds[m_onShow]->width - right) {
				return false;
			}
			if (b > 0 && b < obs[i]->width) {
				return false;
			}
		}
		else if ((*it).y != 0 && m_point.y + m_birds[m_onShow]->height - bottom >= (*it).y) {
			int x = (*it).x - (m_point.x + left);
			int y = m_point.x + left - (*it).x;
			if (x > 0 && x< m_birds[m_onShow]->width - right) {
				return false;
			}
			if (y > 0 && y < obs[i]->width) {
				return false;
			}
		}
	}
	return true;
}