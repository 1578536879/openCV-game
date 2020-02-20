#include "stdafx.h"
#include "FlyBirdGame.h"


FlyBirdGame::FlyBirdGame()
{
}


FlyBirdGame::~FlyBirdGame()
{
	cvDestroyWindow("Fly Bird");
}

void _mouse_callback(int e, int x, int y, int flags, void *ustc) {
	if (e != 0) {
		cout << x << " " << y << endl;
		if (x >= 0 && y <= 30 && y >= 0 && y <= 30) {
			cvDestroyWindow("Fly Bird");
			Game game;
			game.init();
		}
	}
}

void FlyBirdGame::init(bool voice) {
	struct tm t;   //tm结构指针
	time_t now;  //声明time_t类型变量
	time(&now);      //获取系统日期和时间
	localtime_s(&t, &now);   //获取当地日期和时间
	cout << t.tm_hour << endl;
	if (t.tm_hour >= 6 && t.tm_hour <= 18) {
		m_back = cvLoadImage(".//images//bg_night.png");
	}
	else m_back = cvLoadImage(".//images//bg_day.png");
	ifstream file("flyBirdHightestScore.txt");
	char buf[100];
	if (file.is_open()) {
		file.getline(buf, 100);
		file.close();
	}
	m_highestSocre = atoi(buf);

	if (voice) {
		mciSendString(TEXT("open music.wma alias mysong"), NULL, 0, NULL);
		mciSendString(TEXT("play mysong repeat"), NULL, 0, NULL);
	}
	run();

}

void FlyBirdGame::run() {
	IplImage *back = cvCreateImage(cvGetSize(m_back), m_back->depth, m_back->nChannels);
	cvCopy(m_back, back);
	m_player.init(back);
	m_obs.init(back);

	cvNamedWindow("Fly Bird", 1);
	while (true) {


		if (back) {
			IplImage *buf = m_obs.show(back);
			m_player.fly(0, true);
			buf = m_player.show(buf);
			CvFont font;
			cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX, 1.0f, 1.5f, 0, 2, 18);
			cvPutText(buf, "<", cvPoint(0, 25), &font, CV_RGB(240, 255, 255));
			cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX, 0.2f, 0.5f, 0, 0, 8);
			cvPutText(buf, "Distance:", cvPoint(buf->width - 90, 10), &font, CV_RGB(255, 240, 245));
			char dis[100];
			_itoa_s(m_dis, dis, 10);
			cvPutText(buf, dis, cvPoint(buf->width - 30, 10), &font, CV_RGB(255, 240, 245));
			cvShowImage("Fly Bird", buf);
			cvSetMouseCallback("Fly Bird", _mouse_callback, (void*)back);
			int key = cvWaitKey(50);
			if (key == 56 || key == 119) {
				key = 1;
			}
			else if (key == 50 || key == 115) {
				key = 0;
			}
			else if (key == 52 || key == 97) {
				key = 2;
			}
			else if (key == 54 || key == 100) {
				key = 3;
			}
			if (key != -1) {
				m_player.fly(key, false);
			}
			bool flag = m_player.ifDie(m_obs.getPoints(), m_obs.getObs());
			if (!flag) {
				die(buf);
				//cout << "die" << endl;
			}
			m_obs.move();
			m_dis += 0.01;
			cvCopy(m_back, back);
		}

	}
}

void FlyBirdGame::die(IplImage *back) {
	mciSendString(TEXT("close mysong"), NULL, 0, NULL);
	ofstream inFile;
	inFile.open("squareHightestScore.txt");
	bool flag = false;

	if (m_dis > m_highestSocre) {
		flag = true;
		inFile << m_dis;
		inFile.close();
	}

	IplImage *gameover = cvLoadImage(".//images//text_game_over.png");
	CvPoint point = cvPoint(50, 100);
	if (back != 0 && gameover != 0) {
		for (int i = 0; i < gameover->height; i++) {
			for (int j = 0; j < gameover->width; j++) {
				int r = CV_IMAGE_ELEM(gameover, uchar, i, j * 3);
				int g = CV_IMAGE_ELEM(gameover, uchar, i, j * 3 + 1);
				int b = CV_IMAGE_ELEM(gameover, uchar, i, j * 3 + 2);
				if (!(r == 0 && g == 0 && b == 0)) {
					CV_IMAGE_ELEM(back, uchar, i + point.y, (j + point.x) * 3) = CV_IMAGE_ELEM(gameover, uchar, i, j * 3);
					CV_IMAGE_ELEM(back, uchar, i + point.y, (j + point.x) * 3 + 1) = CV_IMAGE_ELEM(gameover, uchar, i, j * 3 + 1);
					CV_IMAGE_ELEM(back, uchar, i + point.y, (j + point.x) * 3 + 2) = CV_IMAGE_ELEM(gameover, uchar, i, j * 3 + 2);

				}
			}
		}
	}
	CvFont font;
	if (flag) {
		cvInitFont(&font, CV_FONT_HERSHEY_TRIPLEX, 0.5, 0.5, 10);
		cvPutText(back, "Congratulations!", cvPoint(80, 170), &font, cvScalar(250, 128, 114));
		cvInitFont(&font, CV_FONT_HERSHEY_TRIPLEX, 0.4, 0.4, 10);
		cvPutText(back, "Break the record", cvPoint(90, 190), &font, cvScalar(188, 143, 143));
	}
	cvInitFont(&font, CV_FONT_HERSHEY_TRIPLEX, 0.5, 0.5, 10);
	cvPutText(back, "distance:", cvPoint(90, 250), &font, cvScalar(205, 92, 92));
	char str[100];
	_itoa_s(m_dis, str, 10);
	cvInitFont(&font, CV_FONT_HERSHEY_SCRIPT_COMPLEX, 1.5, 2.0, 10);
	cvPutText(back, str, cvPoint(180, 250), &font, cvScalar(255, 228, 225));
	/*cvInitFont(&font, CV_FONT_HERSHEY_TRIPLEX, 1.0, 1.0, 10);
	cvPutText(back, "Back", cvPoint(100, 300), &font, cvScalar(255, 255, 0));*/
	while (true) {
		cvNamedWindow("Fly Bird", 1);
		cvShowImage("Fly Bird", back);
		cvSetMouseCallback("Fly Bird", _mouse_callback, (void*)back);
		cvWaitKey();
	}
}