#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxtiming.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        //pcb theme color
        ofColor pcbPadColor;
        ofColor pcbBoardColor;
        ofColor pcbBgColor;
        ofColor pcbGridColor;

        //pcb source file
        string fileName;

        //auto refresh pcb
        ofxTiming timerCheckTimestamp;
        Poco::Timestamp lastPCBTimestamp;

        ofCairoRenderer cairo;
        ofImage pcb;
        ofImage cairoimg;

        ofxCvColorImage pcb_cv;
        ofxCvGrayscaleImage pcb_cv_gray;
        ofxCvContourFinder pcb_contour;

        cv::Point2f center;
        cv::Point2f topleftcorner;
        cv::Point2f bottomrightcorner;
        std::vector<cv::Point2f> corners;
        std::vector<cv::Vec4i> lines;
        ofRectangle pcb_rect;

        int margin_test;


        int sch_x;
        int sch_y;


        void processPCB(string fileName);
        void extractCorner();
        void generatePerfBoard(int width, int height);
        void makePCBtransparent();
        void makePCBRender();
        void drawPerfGrid();
        void loadAndProcessPCB();
};
