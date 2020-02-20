#include "stdafx.h"
#include "DiamondGameTetris.h"


DiamondGameTetris::DiamondGameTetris()
{
}


DiamondGameTetris::~DiamondGameTetris()
{
}

void DiamondGameTetris::init() {
	char file[] = ".//img//bird0_0.png";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			sprintf_s(file, ".//img//bird%d_%d.png", i, j);
			m_birds.push_back(cvLoadImage(file, 1));
		}
	}
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 12; j++) {
			m_map[i][j] = -1;
		}
	}
	srand(time(0));
	m_preShape = rand() % 6;
	m_preBird = rand() % m_birds.size();
	m_nowShape = m_preShape;
	m_bird = m_preBird;
	m_preShape = rand() % 6;
	m_preBird = rand() % m_birds.size();
}

void DiamondGameTetris::compose(CvPoint point, IplImage *bird, IplImage * back) {
	if (back != NULL) {
		for (int i = 0; i < bird->height; i++) {
			for (int j = 0; j < bird->width; j++) {
				int r = CV_IMAGE_ELEM(bird, uchar, i, j * 3);
				int g = CV_IMAGE_ELEM(bird, uchar, i, j * 3 + 1);
				int b = CV_IMAGE_ELEM(bird, uchar, i, j * 3 + 2);
				if (!(r == 0 && g == 0 && b == 0)) {
					CV_IMAGE_ELEM(back, uchar, i + point.y, (j + point.x) * 3) = r;
					CV_IMAGE_ELEM(back, uchar, i + point.y, (j + point.x) * 3 + 1) = g;
					CV_IMAGE_ELEM(back, uchar, i + point.y, (j + point.x) * 3 + 2) = b;
				}
			}
		}
	}
}

IplImage *DiamondGameTetris::forecast(IplImage *back) {
	int x = 500;
	int y = 120;
	if (m_preShape == 0) {
		compose(CvPoint(x, y), m_birds[m_preBird], back);
		compose(CvPoint(x + m_birds[m_preBird]->width, y), m_birds[m_preBird], back);
		compose(CvPoint(x, y + m_birds[m_preBird]->height), m_birds[m_preBird], back);
		compose(CvPoint(x + m_birds[m_preBird]->width, y + m_birds[m_preBird]->height), m_birds[m_preBird], back);
	}
	else if (m_preShape == 1) {
		compose(CvPoint(x, y), m_birds[m_preBird], back);
		compose(CvPoint(x + m_birds[m_preBird]->width, y), m_birds[m_preBird], back);
		compose(CvPoint(x + m_birds[m_preBird]->width, y + m_birds[m_preBird]->height), m_birds[m_preBird], back);
		compose(CvPoint(x + m_birds[m_preBird]->width * 2, y + m_birds[m_preBird]->height), m_birds[m_preBird], back);
	}
	else if (m_preShape == 2) {
		compose(CvPoint(x + m_birds[m_preBird]->width * 2, y), m_birds[m_preBird], back);
		compose(CvPoint(x, y + m_birds[m_preBird]->height), m_birds[m_preBird], back);
		compose(CvPoint(x + m_birds[m_preBird]->width, y + m_birds[m_preBird]->height), m_birds[m_preBird], back);
		compose(CvPoint(x + m_birds[m_preBird]->width * 2, y + m_birds[m_preBird]->height), m_birds[m_preBird], back);
	}
	else if (m_preShape == 3) {
		compose(CvPoint(x + m_birds[m_preBird]->width, y), m_birds[m_preBird], back);
		compose(CvPoint(x + m_birds[m_preBird]->width, y + m_birds[m_preBird]->height), m_birds[m_preBird], back);
		compose(CvPoint(x + m_birds[m_preBird]->width, y + m_birds[m_preBird]->height * 2), m_birds[m_preBird], back);
	}
	else if (m_preShape == 4) {
		compose(CvPoint(x, y + m_birds[m_preBird]->height), m_birds[m_preBird], back);
		compose(CvPoint(x + m_birds[m_preBird]->width, y), m_birds[m_preBird], back);
		compose(CvPoint(x + m_birds[m_preBird]->width, y + m_birds[m_preBird]->height), m_birds[m_preBird], back);
		compose(CvPoint(x + m_birds[m_preBird]->width * 2, y + m_birds[m_preBird]->height), m_birds[m_preBird], back);
	}
	else if (m_preShape == 5) {
		compose(CvPoint(x + m_birds[m_preBird]->width, y + m_birds[m_preBird]->height), m_birds[m_preBird], back);
	}
	return back;
}

IplImage *DiamondGameTetris::show(IplImage *back) {
	cvCopy(forecast(back), back);
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 12; j++) {
			if (m_map[i][j] != -1) {
				int x, y;
				if (i == 0 && j != 0) {
					x = m_birds[m_map[i][j]]->width * j - 10 * j - 5;
					y = -10;
				}
				else if (i != 0 && j == 0) {
					x = -5;
					y = m_birds[m_map[i][j]]->height * i - 20 * i - 10;
				}
				else if (i == 0 && j == 0) {
					x = -5;
					y = -10;
				}
				else {
					x = m_birds[m_map[i][j]]->width * j - 10 * j - 5;
					y = m_birds[m_map[i][j]]->height * i - 20 * i - 10;
				}
				//cout << x << endl;
				m_points.push_back(CvPoint(x, y));
				compose(CvPoint(x, y), m_birds[m_map[i][j]], back);
			}
		}
	}
	return back;
}

int DiamondGameTetris::find(vector<CvPoint> points, int x, int flag) {
	for (vector<CvPoint>::iterator it = points.begin(); it != points.end(); it++) {
		if (flag == 0) {
			if ((*it).x == x) {
				return (*it).y;
			}
		}
		else if (flag == 1) {
			if ((*it).y == x) {
				return (*it).x;
			}
		}
	}
	return -1;
}

bool DiamondGameTetris::ifMove(vector<CvPoint> points, int x) {
	vector<CvPoint> bird_point;
	if (x == 1) {
		/*for (vector<CvPoint>::iterator it = points.begin(); it != points.end(); it++) {
		int a = find(bird_point, (*it).x, 0);
		if ((*it).x >= 14) {
		return false;
		}

		bird_point.push_back((*it));
		}*/

		for (vector<CvPoint>::iterator it = points.begin(); it != points.end(); it++) {
			if ((*it).x >= 14) {
				return false;
			}
			if (m_map[(*it).x + 1][(*it).y] != -1) {
				return false;
			}
		}
		return true;
	}
	else if (x == 2) {

		for (vector<CvPoint>::iterator it = points.begin(); it != points.end(); it++) {
			if ((*it).y >= 11) {
				return false;
			}
			if (m_map[(*it).x][(*it).y + 1] != -1) {
				return false;
			}
		}
		return true;
	}
	else if (x == 3) {
		/*for (vector<CvPoint>::iterator it = points.begin(); it != points.end(); it++) {
		if ((*it).y <= 0)return false;
		int a = find(bird_point, (*it).y, 1);
		if (a == -1) {
		bird_point.push_back((*it));
		}
		else {
		bird_point.push_back(cvPoint(a, (*it).y));
		}
		}*/
		for (vector<CvPoint>::iterator it = points.begin(); it != points.end(); it++) {
			if ((*it).y <= 0)return false;
			if (m_map[(*it).x][(*it).y - 1] != -1) {
				return false;
			}
		}
		return true;
	}
	return false;
}

void DiamondGameTetris::insert(vector<CvPoint> points) {
	for (vector<CvPoint>::iterator it = points.begin(); it != points.end(); it++) {
		m_map[(*it).x][(*it).y] = m_bird;
	}
	srand(time(0));
	m_nowShape = m_preShape;
	m_bird = m_preBird;
	m_preShape = rand() % 6;
	m_preBird = rand() % m_birds.size();
}

int DiamondGameTetris::getShape() {
	return m_nowShape;
}

int DiamondGameTetris::getBird() {
	return m_bird;
}

bool DiamondGameTetris::ifDie() {
	for (int i = 0; i < 12; i++) {
		if (m_map[0][i] != -1) {

			return true;
		}
	}
	return false;
}

void DiamondGameTetris::eliminate(int x) {
	for (int i = x; i >= 0; i--) {
		for (int j = 0; j < 12; j++) {
			if (i == 0) {
				m_map[i][j] = -1;
			}
			else {
				m_map[i][j] = m_map[i - 1][j];
			}
		}
	}
}

int DiamondGameTetris::ifEliminate() {
	int x = 0;
	for (int i = 14; i >= 0; i--) {
		bool flag = true;
		for (int j = 0; j < 12; j++) {
			if (m_map[i][j] == -1) {
				flag = false;
			}
		}
		if (flag) {
			eliminate(i);
			x++;
			i++;
		}
	}
	return x;
}

bool DiamondGameTetris::ifChange(vector<CvPoint> b_points) {
	for (vector<CvPoint>::iterator it = b_points.begin(); it != b_points.end(); it++) {
		if (m_map[(*it).x][(*it).y] != -1) {
			return false;
		}
	}
	return true;
}