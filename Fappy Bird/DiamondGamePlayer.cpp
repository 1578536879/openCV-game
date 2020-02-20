#include "stdafx.h"
#include "DiamondGamePlayer.h"


DiamondGamePlayer::DiamondGamePlayer()
{
	char file[] = ".//img//bird0_0.png";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			sprintf_s(file, ".//img//bird%d_%d.png", i, j);
			m_birds.push_back(cvLoadImage(file, 1));
		}
	}
}


DiamondGamePlayer::~DiamondGamePlayer()
{
}

void DiamondGamePlayer::init(int x, int y) {
	m_shape = x;
	m_bird = y;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			m_player[i][j] = -1;
			m_playerX[i][j] = -1;
			m_playerY[i][j] = -1;
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			judge[i][j] = -1;
		}
	}
	newShape();
}

void DiamondGamePlayer::newShape() {
	srand(time(0));
	int pos = rand() % 10;
	if (m_shape == 0) {
		/*形状： xx
		xx
		*/
		m_player[0][x] = m_shape;
		m_player[0][x + 1] = m_shape;
		m_player[1][x] = m_shape;
		m_player[1][x + 1] = m_shape;
		m_playerX[0][x] = 0;
		m_playerX[0][x + 1] = 0;
		m_playerX[1][x] = 1;
		m_playerX[1][x + 1] = 1;
		m_playerY[0][x] = pos;
		m_playerY[0][x + 1] = pos + 1;
		m_playerY[1][x] = pos;
		m_playerY[1][x + 1] = pos + 1;

	}
	else if (m_shape == 1) {
		/*形状： xx
		xx
		*/
		if (pos + 2 > 12) newShape();
		for (int i = 0; i < 2; i++) {
			m_player[0][x + i] = m_shape;
			m_playerX[0][x + i] = 0;
			m_playerY[0][x + i] = pos + i;
		}
		for (int i = 0; i < 2; i++) {
			m_player[1][x + i + 1] = m_shape;
			m_playerX[1][x + i + 1] = 1;
			m_playerY[1][x + i + 1] = pos + i + 1;
		}
	}
	else if (m_shape == 2) {
		/*形状： x
		xxx
		*/
		if (pos + 2 > 12) newShape();
		else {
			m_player[0][x + 2] = m_shape;
			m_playerX[0][x + 2] = 0;
			m_playerY[0][x + 2] = pos + 2;
			for (int i = 0; i < 3; i++) {
				m_player[1][x + i] = m_shape;
				m_playerX[1][x + i] = 1;
				m_playerY[1][x + i] = pos + i;
			}
		}
	}
	else if (m_shape == 3) {
		/*形状：x
		x
		x
		*/
		for (int i = 0; i < 3; i++) {
			m_player[i][1] = m_shape;
			m_playerX[i][1] = i;
			m_playerY[i][1] = pos;
		}
	}
	else if (m_shape == 4) {
		/*形状：x
		xxx
		*/
		if (pos + 2 > 12) newShape();
		for (int i = 0; i < 3; i++) {
			m_player[1][x + i] = m_shape;
			m_playerX[1][x + i] = 1;
			m_playerY[1][x + i] = pos + i;
		}
		m_player[0][x + 1] = m_shape;
		m_playerX[0][x + 1] = 0;
		m_playerY[0][x + 1] = pos + 1;
	}
	else {
		/* 形状：x
		*/
		m_player[0][x] = m_shape;
		m_playerX[0][x] = 0;
		m_playerY[0][x] = pos;
	}
}

vector<CvPoint> DiamondGamePlayer::getPosition() {
	vector<CvPoint> points;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (m_playerX[i][j] != -1 && m_playerY[i][j] != -1) {
				points.push_back(cvPoint(m_playerX[i][j], m_playerY[i][j]));
			}
		}
	}
	return points;
}

void DiamondGamePlayer::swap(int &a, int &b) {
	int t = a;
	a = b;
	b = t;
}

void DiamondGamePlayer::changeShape() {
	if (m_shape == 0 || m_shape == 5) {
		return;
	}
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3 - i; ++j) {
			swap(m_player[i][j], m_player[2 - j][2 - i]);
			if (m_playerX[i][j] != -1 && m_playerY[i][j] != -1) {
				if (i < 2 - j) {
					m_playerX[i][j] += 2 - j - i;
				}
				else if (i > 2 - j) {
					m_playerX[i][j] -= i - 2 + j;
				}
				if (j > 2 - i) {
					m_playerY[i][j] -= j - 2 + i;
				}
				else if (j < 2 - i) {
					m_playerY[i][j] += 2 - i - j;
				}
			}
			if (m_playerX[2 - j][2 - i] != -1 && m_playerY[2 - j][2 - i] != -1) {
				if (i < 2 - j) {
					m_playerX[2 - j][2 - i] -= 2 - j - i;
				}
				else if (i > 2 - j) {
					m_playerX[2 - j][2 - i] += i - 2 + j;
				}
				if (j > 2 - i) {
					m_playerY[2 - j][2 - i] += j - 2 + i;
				}
				else if (j < 2 - i) {
					m_playerY[2 - j][2 - i] -= 2 - i - j;
				}
			}

			swap(m_playerX[i][j], m_playerX[2 - j][2 - i]);
			swap(m_playerY[i][j], m_playerY[2 - j][2 - i]);
		}
	}
	for (int i = 0; i < 3 / 2; ++i) {
		for (int j = 0; j < 3; ++j) {
			swap(m_player[i][j], m_player[2 - i][j]);
			if (m_playerX[i][j] != -1 && m_playerY[i][j] != -1) {
				if (i < 2 - i) {
					m_playerX[i][j] += 2 - i - i;
				}
				else if (i > 2 - i) {
					m_playerX[i][j] -= i - 2 + i;
				}
			}
			if (m_playerX[2 - i][j] != -1 && m_playerY[2 - i][j] != -1) {
				if (i < 2 - i) {
					m_playerX[2 - i][j] -= 2 - i - i;
				}
				else if (i > 2 - i) {
					m_playerX[2 - i][j] += i - 2 + i;
				}
			}
			swap(m_playerX[i][j], m_playerX[2 - i][j]);
			swap(m_playerY[i][j], m_playerY[2 - i][j]);
		}
	}
}

void DiamondGamePlayer::move(int x) {
	if (x == 1) {
		/*
		向下移
		*/
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (m_player[i][j] != -1) {
					m_playerX[i][j]++;
				}
			}
		}
	}
	else if (x == 2) {
		/*
		向右移
		*/
		for (int i = 0; i<3; i++) {
			for (int j = 0; j < 3; j++) {
				if (m_playerY[i][j] != -1) {
					m_playerY[i][j]++;
				}
			}
		}
	}
	else if (x == 3) {
		/*
		向左移
		*/
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (m_playerY[i][j] != -1) {
					m_playerY[i][j]--;
				}
			}
		}
	}
}

void DiamondGamePlayer::compose(CvPoint point, IplImage *bird, IplImage *back) {
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

IplImage *DiamondGamePlayer::showPalyer(IplImage *back) {
//vector<CvPoint> points;
for (int i = 0; i < 3; i++) {
	for (int j = 0; j < 3; j++) {
		if (m_player[i][j] != -1) {
			int x, y;
			if (m_playerX[i][j] == 0 && m_playerY[i][j] != 0) {
				x = m_birds[m_bird]->width * m_playerY[i][j] - 10 * m_playerY[i][j] - 5;
				y = -10;
			}
			else if (m_playerX[i][j] != 0 && m_playerY[i][j] == 0) {
				x = -5;
				y = m_birds[m_bird]->height * m_playerX[i][j] - 20 * m_playerX[i][j] - 10;
			}
			else if (m_playerX[i][j] == 0 && m_playerY[i][j] == 0) {
				x = -5;
				y = -10;
			}
			else {
				x = m_birds[m_bird]->width * m_playerY[i][j] - 10 * m_playerY[i][j] - 5;
				y = m_birds[m_bird]->height * m_playerX[i][j] - 20 * m_playerX[i][j] - 10;
			}
			//cout << x << endl;
			//points.push_back(CvPoint(x, y));
			compose(CvPoint(x, y), m_birds[m_bird], back);
		}
	}
}
return back;
}

vector<CvPoint> DiamondGamePlayer::getChangePoints() {
	int changeX[3][3], changeY[3][3];
	vector<CvPoint> changePoints;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			changeX[i][j] = m_playerX[i][j];
			changeY[i][j] = m_playerY[i][j];
		}
	}
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3 - i; ++j) {
			if (changeX[i][j] != -1 && changeY[i][j] != -1) {
				if (i < 2 - j) {
					changeX[i][j] += 2 - j - i;
					if (changeX[i][j] > 11)return changePoints;
				}
				else if (i > 2 - j) {
					changeX[i][j] -= i - 2 + j;
					if (changeX[i][j] < 0)return changePoints;
				}
				if (j > 2 - i) {
					changeY[i][j] -= j - 2 + i;
					if (changeY[i][j] < 0)return changePoints;
				}
				else if (j < 2 - i) {
					changeY[i][j] += 2 - i - j;
					if (changeY[i][j] > 11)return changePoints;
				}
			}
			if (changeX[2 - j][2 - i] != -1 && changeY[2 - j][2 - i] != -1) {
				if (i < 2 - j) {
					changeX[2 - j][2 - i] -= 2 - j - i;
					if (changeX[2 - j][2 - i] < 0)return changePoints;
				}
				else if (i > 2 - j) {
					changeX[2 - j][2 - i] += i - 2 + j;
					if (changeX[2 - j][2 - i] > 11)return changePoints;
				}
				if (j > 2 - i) {
					changeY[2 - j][2 - i] += j - 2 + i;
					if (changeX[i][j] > 11)return changePoints;
				}
				else if (j < 2 - i) {
					changeY[2 - j][2 - i] -= 2 - i - j;
					if (changeY[2 - j][2 - i] < 0)return changePoints;
				}
			}
			swap(changeX[i][j], changeX[2 - j][2 - i]);
			swap(changeY[i][j], changeY[2 - j][2 - i]);
		}
	}
	for (int i = 0; i < 3 / 2; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (changeX[i][j] != -1 && changeY[i][j] != -1) {
				if (i < 2 - i) {
					changeX[i][j] += 2 - i - i;
				}
				else if (i > 2 - i) {
					changeX[i][j] -= i - 2 + i;
				}
			}
			if (changeX[2 - i][j] != -1 && changeY[2 - i][j] != -1) {
				if (i < 2 - i) {
					changeX[2 - i][j] -= 2 - i - i;
				}
				else if (i > 2 - i) {
					changeX[2 - i][j] += i - 2 + i;
				}
			}
			swap(changeX[i][j], changeX[2 - i][j]);
			swap(changeY[i][j], changeY[2 - i][j]);
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (changeX[i][j] != -1 && changeY[i][j] != -1) {
				changePoints.push_back(cvPoint(changeX[i][j], changeY[i][j]));
			}
		}
	}
	return changePoints;
}