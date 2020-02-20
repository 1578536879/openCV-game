#include "stdafx.h"
#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
}

void Game::compose(IplImage *back, IplImage *voice) {
	if (voice && back) {
		CvPoint point = cvPoint(200, 100);
		for (int i = 0; i < voice->height; i++) {
			for (int j = 0; j < voice->width; j++) {
				int r = CV_IMAGE_ELEM(voice, uchar, i, j * 3);
				int g = CV_IMAGE_ELEM(voice, uchar, i, j * 3 + 1);
				int b = CV_IMAGE_ELEM(voice, uchar, i, j * 3 + 2);
				if (!(r >= 249 && r <= 255 && g >= 249 && g <= 255 && b >= 249 && b <= 255)) {
					CV_IMAGE_ELEM(back, uchar, i + point.y, (j + point.x) * 3) = r;
					CV_IMAGE_ELEM(back, uchar, i + point.y, (j + point.x) * 3 + 1) = g;
					CV_IMAGE_ELEM(back, uchar, i + point.y, (j + point.x) * 3 + 2) = b;
				}
			}
		}
	}
}

bool voice = true;
void mouse_callback(int e, int x, int y, int flags, void *ustc) {
	if (e == 1) {

		if (x >= 34 && x <= 125 && y >= 110 && y <= 163) {
			cvDestroyWindow("Fappy Bird");
			FlyBirdGame flybird;
			flybird.init(voice);
		}
		else if (x >= 126 && x <= 226 && y >= 221 && y <= 270) {
			cvDestroyWindow("Fappy Bird");
			DiamondGame diamondGame;
			diamondGame.init(voice);
		}
		if (x >= 204 && x <= 237 && y >= 103 && y <= 132) {
			Game g;
			IplImage *background = cvLoadImage(".//menu.png");
			if (voice) {
				voice = false;
				IplImage *closeVoice = cvLoadImage(".//close.png"); 
				g.compose(background, closeVoice);
			}
			else {
				voice = true;
				IplImage *openVoice = cvLoadImage(".//open.png");
				g.compose(background, openVoice);
			}
			cvShowImage("Fappy Bird", background);
		}
		cout << x << " " << y << endl;
		return;
	}
}

void Game::init() {
	openVoice = cvLoadImage(".//open.png");
	closeVoice = cvLoadImage(".//close.png");
	back = cvLoadImage(".//menu.png");
	voice = true;
	show();
}

void Game::show() {
	IplImage *background = cvCreateImage(cvSize(back->width, back->height), back->depth, back->nChannels);
	while (true) {
		cvCopy(back, background);
		compose(background, openVoice);
		cvNamedWindow("Fappy Bird", 1);
		cvShowImage("Fappy Bird", background);
		cvSetMouseCallback("Fappy Bird", mouse_callback, (void*)background);
		cvWaitKey(0);
	}
}

