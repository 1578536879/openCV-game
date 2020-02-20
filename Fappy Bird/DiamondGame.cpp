#include "stdafx.h"
#include "DiamondGame.h"


DiamondGame::DiamondGame()
{
}


DiamondGame::~DiamondGame()
{
	cvDestroyWindow("Bird Word");
	cvReleaseImage(&m_back);
}

/*void DiamondGame::show() {
	Game::show();
}*/

void DiamondGame::init(bool flag) {

	m_back = cvLoadImage(".//img//background.jpg");
	ifstream file("squareHightestScore.txt");
	char buf[100];
	if (file.is_open()) {
		file.getline(buf, 100);
		file.close();
	}
	m_highestScore = atoi(buf);
	if (flag) {
		mciSendString(TEXT("open music1.wma alias mysong"), NULL, 0, NULL);
		mciSendString(TEXT("play mysong repeat"), NULL, 0, NULL);
	}
	run(0);
}

void DiamondGame::run(int x) {
	if (x == 0) {
		m_tetris.init();
		m_player.init(m_tetris.getShape(), m_tetris.getBird());
	}
	IplImage *background = cvCreateImage(cvSize(m_back->width, m_back->height), m_back->depth, m_back->nChannels);
	cvCopy(m_back, background);
	
	
	if (background) {
		int i = 0;
		IplImage *b;
		while (true) {
			//m_tetris.show();
			cvNamedWindow("DiamondGame", 1);
			b = m_tetris.show(background);
			write(background);
			b = m_player.showPalyer(b);
			cvShowImage("DiamondGame", b);
			b_points = m_player.getPosition();
			int key = addEventListener();
			bool flag = false;
			if (key == 1 || key == 2 || key == 3) {
				flag = m_tetris.ifMove(b_points, key);
				if (flag) m_player.move(key);
			}
			else if (key == 4) {
				vector<CvPoint> points = m_player.getChangePoints();
				if (points.size() != 0) {
					bool ifchange = m_tetris.ifChange(points);
					if (ifchange) m_player.changeShape();
				}
			}
			else if (key == 5) {
				stop(b);
			}
			if (key != 1 && key != 2 && key != 3) {
				flag = m_tetris.ifMove(b_points, 1);
				if (flag) m_player.move(1);
				else {
					m_tetris.insert(b_points);
					int x = m_tetris.ifEliminate();
					if (x != 0) {
						m_socre += x;
					}
					bool ifdie = m_tetris.ifDie();
					if (ifdie) {
						break;
					}
					m_player.init(m_tetris.getShape(), m_tetris.getBird());
				}
			}
			cvCopy(m_back, background);
			
		}
		die(b);

	}
}

int DiamondGame::addEventListener() {
	int s = 1000;
	if (m_socre > 15) {
		s = 1000 - m_socre;
	}
	int key = cvWaitKey(s);
	if (key == 50 || key == 115) {
		key = 1;
	}
	else if (key == 54 || key == 100) {
		key = 2;
	}
	else if (key == 52 || key == 97) {
		key = 3;
	}
	else if (key == 56 || key == 119) { /*  ±ä»»ÐÎ×´  */
		key = 4;
	}
	else if (key == 32) {				/*  ÔÝÍ£  */
		key = 5;
	}
	return key;
}

void DiamondGame::write(IplImage *back) {
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_TRIPLEX, 1.0, 2.0, 10);
	cvPutText(back, "Score:", cvPoint(455, 50), &font, cvScalar(255, 228, 181));
	char str[100];
	_itoa_s(m_socre, str, 10);
	cvInitFont(&font, CV_FONT_HERSHEY_SCRIPT_COMPLEX, 1.5, 2.0, 10);
	cvPutText(back, str, cvPoint(600, 100), &font, cvScalar(255, 165, 0));

	cvInitFont(&font, CV_FONT_HERSHEY_TRIPLEX, 0.6, 0.6, 10);
	cvPutText(back, "Next:", cvPoint(480, 130), &font, cvScalar(95, 158, 160));

	cvInitFont(&font, CV_FONT_HERSHEY_TRIPLEX, 0.5, 0.5, 10);
	int y = 300;
	int add = 20;
	cvPutText(back, "Rules", cvPoint(480, y), &font, cvScalar(95, 158, 160));
	cvPutText(back, "Down: 2/s", cvPoint(480, y + add), &font, cvScalar(240, 248, 255));
	cvPutText(back, "Left: 4/a", cvPoint(480, y + add * 2), &font, cvScalar(240, 248, 255));
	cvPutText(back, "Right: 6/d", cvPoint(480, y + add * 3), &font, cvScalar(240, 248, 255));
	cvPutText(back, "Change: 8/w", cvPoint(480, y + add * 4), &font, cvScalar(240, 248, 255));
	cvPutText(back, "Stop: blankSpace", cvPoint(480, y + add * 5), &font, cvScalar(240, 248, 255));
}

void DiamondGame::stop(IplImage *b) {
	while (true) {
		cvNamedWindow("DiamondGame", 1);
		cvShowImage("DiamondGame", b);
		int key = cvWaitKey(10);
		if (key == 13) {
			run(1);
		}
	}
	return;
}

void my_mouse_callback(int e, int x, int y, int flags, void *ustc) {
	if (e != 0) {
		if (x >= 257 && x <= 330 && y >= 280 && y <= 299) {
			cvDestroyWindow("DiamondGame");
			Game d;
			d.init();
		}
	}
	return;
}

void DiamondGame::die(IplImage *back) {
	mciSendString(TEXT("close mysong"), NULL, 0, NULL);
	ofstream inFile;
	inFile.open("squareHightestScore.txt");
	bool flag = false;

	if (m_socre > m_highestScore) {
		flag = true;
		inFile << m_socre;
		inFile.close();
	}

	IplImage *gameOver = cvLoadImage(".//img//game_over.png");
	if (back) {
		CvPoint point = cvPoint(200, 100);
		if (back != NULL) {
			for (int i = 0; i < gameOver->height; i++) {
				for (int j = 0; j < gameOver->width; j++) {
					int r = CV_IMAGE_ELEM(gameOver, uchar, i, j * 3);
					int g = CV_IMAGE_ELEM(gameOver, uchar, i, j * 3 + 1);
					int b = CV_IMAGE_ELEM(gameOver, uchar, i, j * 3 + 2);
					if (!(r == 0 && g == 0 && b == 0)) {
						CV_IMAGE_ELEM(back, uchar, i + point.y, (j + point.x) * 3) = r;
						CV_IMAGE_ELEM(back, uchar, i + point.y, (j + point.x) * 3 + 1) = g;
						CV_IMAGE_ELEM(back, uchar, i + point.y, (j + point.x) * 3 + 2) = b;
					}
				}
			}
		}
		CvFont font;
		if (flag) {
			cvInitFont(&font, CV_FONT_HERSHEY_TRIPLEX, 0.5, 0.5, 10);
			cvPutText(back, "Congratulations!", cvPoint(220, 180), &font, cvScalar(255, 255, 0));
			cvInitFont(&font, CV_FONT_HERSHEY_TRIPLEX, 0.4, 0.4, 10);
			cvPutText(back, "Break the record", cvPoint(240, 200), &font, cvScalar(255, 255, 0));

		}
		cvInitFont(&font, CV_FONT_HERSHEY_TRIPLEX, 0.5, 0.5, 10);
		cvPutText(back, "Sorce:", cvPoint(220, 250), &font, cvScalar(245, 222, 179));
		char str[100];
		_itoa_s(m_socre, str, 10);
		cvInitFont(&font, CV_FONT_HERSHEY_SCRIPT_COMPLEX, 1.5, 2.0, 10);
		cvPutText(back, str, cvPoint(280, 250), &font, cvScalar(255, 228, 181));
		cvInitFont(&font, CV_FONT_HERSHEY_TRIPLEX, 1.0, 1.0, 10);
		cvPutText(back, "Back", cvPoint(250, 300), &font, cvScalar(255, 222, 173));
		while (true) {
			cvNamedWindow("DiamondGame", 1);
			cvShowImage("DiamondGame", back);
			Game g;
			cvSetMouseCallback("DiamondGame", my_mouse_callback, (void*)back);
			cvWaitKey();
		}
	}
}