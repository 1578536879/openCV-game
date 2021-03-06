// Fappy Bird.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"DiamondGame.h"
#include"Game.h"
#include<opencv2\opencv.hpp>
using namespace std;
/*void compose(IplImage *back, IplImage *voice) {
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

void mouse_callback(int e, int x, int y, int flags, void *ustc) {
	if (e == 1) {
		
		if (x >= 34 && x <= 125 && y >= 110 && y <= 163) {
			fly = true;
		}
		else if (x >= 126 && x <= 226 && y >= 221 && y <= 270) {
			diamond = true;
			cvDestroyWindow("Fappy Bird");
			DiamondGame diamondGame;
			diamondGame.init(flag);
		}
		if (x >= 204 && x <= 237 && y >= 103 && y <= 132) {
			IplImage *background = cvLoadImage(".//menu.png");
			if (flag) {
				flag = false;
				IplImage *closeVoice = cvLoadImage(".//close.png");
				compose(background, closeVoice);
			}
			else {
				flag = true;
				IplImage *openVoice = cvLoadImage(".//open.png");
				compose(background, openVoice);
			}
			cvShowImage("Fappy Bird", background);
		}
		cout << x << " " << y << endl;
		return;
	}
}



void voiceShow() {
	IplImage *openVoice = cvLoadImage(".//open.png");
	IplImage *closeVoice = cvLoadImage(".//close.png"); 
	IplImage *back = cvLoadImage(".//menu.png");
	IplImage *voice;
	IplImage *background = cvCreateImage(cvSize(back->width, back->height), back->depth, back->nChannels);
	while (true) {
		/*cvCopy(back, background);
		if (flag) {
			voice = cvCreateImage(cvSize(openVoice->width, openVoice->height), openVoice->depth, openVoice->nChannels);
			cvCopy(openVoice, voice);
		}
		else {
			voice = cvCreateImage(cvSize(openVoice->width, openVoice->height), openVoice->depth, openVoice->nChannels);
			cvCopy(closeVoice, voice);
		}
		cout << 1 << endl;*/
		/*compose(back, openVoice);
		cvNamedWindow("Fappy Bird", 1);
		cvShowImage("Fappy Bird", back);
		cvSetMouseCallback("Fappy Bird", mouse_callback, (void*)background);
		cvWaitKey(0);
	}
	
}*/

int main()
{
	
	Game game;
	game.init();
	 
	

    return 0;
}

