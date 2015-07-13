#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::makePCBtransparent()
{
    pcb.setImageType(OF_IMAGE_COLOR_ALPHA);

    unsigned char * pix_dst = pcb.getPixelsRef().getPixels();
    int channel_dst  = pcb.getPixelsRef().getBytesPerPixel();
    int imgWidth =  pcb.getWidth(); //webcam->getWidth();
    int imgHeight = pcb.getHeight();// webcam->getHeight();


    for (int x = 0 ; x < imgWidth; x++)
    {
        for (int y = 0 ; y < imgHeight; y++)
        {
            int arrpos_dst = (y*channel_dst*imgWidth) + x*channel_dst;
            if (pix_dst[arrpos_dst] < 10 && pix_dst[arrpos_dst+1] < 10 && pix_dst[arrpos_dst+2] < 10 )
            {
                pix_dst[arrpos_dst+3] = 0;
            }

            if (pix_dst[arrpos_dst] > 200 && pix_dst[arrpos_dst+1] > 200 && pix_dst[arrpos_dst+2] > 200 )
            {
                pix_dst[arrpos_dst]     = 80;
                pix_dst[arrpos_dst+1]   = 80;
                pix_dst[arrpos_dst+2]   = 80;
            }

        }
    }

    pcb.update();
    pcb.saveImage("pcb_trans.png");
}

void ofApp::processPCB(string fileName)
{
    pcb.loadImage(fileName);


//    exit();
//    pcb.loadImage(fileName);


    pcb_cv.setFromPixels(pcb.getPixelsRef());
//    //pcb_cv_gray.setFromPixels(pcb_cv.getPixels(), pcb_cv.width, pcb_cv.height);
    pcb_cv_gray = pcb_cv;


    cv::Mat pcb_can = pcb_cv_gray.getCvImage();
    cv::HoughLinesP(pcb_can, lines, 1, CV_PI/180, 100, 100,0.1);
}

void ofApp::extractCorner()
{
    for (int lid = 1; lid < lines.size(); lid++)
        {

        cv::Point2f  l1;
        cv::Point2f  l2;

        l1 = cv::Point2f( lines.at(lid)[0], lines.at(lid)[1] );
        l2 = cv::Point2f( lines.at(lid)[2], lines.at(lid)[3] );


        corners.push_back(l1);
        corners.push_back(l2);


        }

    topleftcorner = corners.at(0);
    bottomrightcorner = corners.at(0);

    for (int cid = 1; cid < lines.size(); cid++)
    {
        if (topleftcorner.x > corners.at(cid).x) topleftcorner.x = corners.at(cid).x;
        if (topleftcorner.y > corners.at(cid).y) topleftcorner.y = corners.at(cid).y;

        if (bottomrightcorner.x < corners.at(cid).x) bottomrightcorner.x = corners.at(cid).x;
        if (bottomrightcorner.y < corners.at(cid).y) bottomrightcorner.y = corners.at(cid).y;
    }


    pcb_rect.set(topleftcorner.x, topleftcorner.y, bottomrightcorner.x - topleftcorner.x, bottomrightcorner.y - topleftcorner.y );
}

void ofApp::makePCBRender()
{
    cairo.setupMemoryOnly(ofCairoRenderer::IMAGE,true,false, ofRectangle(0,0, 630, 630));


    int w = 21;
    int h = 21;
//    cairo.background(0,0,0,255);
    cairo.background(227, 240, 250, 255);
  //cairo.clear(100);
//cairo.setFillMode(OF_OUTLINE);
    cairo.setColor(165,205,237, 120); //nasty bug cairo colorspace is b g r
///    cairo.setBackgroundAuto(true);
    int padding = 30;

    string idx = "ABCDEFGHIJKLMNOPQRTUVWXY";



    for (int i =0 ; i < w ; i++)
    {
        cairo.setColor(0,0,0, 100);

        cairo.drawString(   ofToString(idx.at(i)),  i*padding, 21*padding,0, OF_BITMAPMODE_SIMPLE);


        for (int j =0 ; j < h ; j++)
        {

            cairo.setColor(0,0,0, 10);

            cairo.drawString(  ofToString(j),  0*padding, j*padding,0, OF_BITMAPMODE_SIMPLE);





            cairo.setColor(165,205,237, 120);

            cairo.drawCircle(i*padding, j*padding, 0, 8);

            cairo.setColor(250, 250, 250, 255);

            cairo.drawCircle(i*padding, j*padding, 0, 2);
        }

//        cairo.setColor(199, 224, 244, 255);

//        for (int j =0 ; j < h ; j++)
//        {
//            cairo.drawCircle(i*padding, j*padding, 0, 3);
//        }


//        if ((pcb_rect.getTopLeft().x + i*padding) < pcb_rect.getTopRight().x)
//            cairo.drawLine(i*padding, 0, 0, i*padding , pcb_rect.height, 0);
//        cairo.drawLine(i*padding, 0, 0, i*padding , 630, 0);

//        if( (pcb_rect.getTopLeft().y + i*padding) < pcb_rect.getBottomRight().y)
//            cairo.drawLine(0, i*padding, 0, pcb_rect.width, i*padding, 0);
//        cairo.drawLine(0, i*padding, 0, 630, i*padding, 0);

    }



   // cairo.drawCircle(11,11,0,10);

    cairo.update();
    cairoimg.setFromPixels(cairo.getImageSurfacePixels());
    cairoimg.saveImage("cairo.png");
}

void ofApp::setup()
{
    ofSetFrameRate(30);

    center.x = 0;
    center.y = 0;
    cairoimg.setImageType(OF_IMAGE_COLOR_ALPHA);

    processPCB("/Users/xcorex/pcb2.png");
    extractCorner();
    makePCBtransparent();

    makePCBRender();



//     Get mass center
//        for (int j = 0; j < corners.size(); j++)
//            center += corners[j];
//        center *= (1. / corners.size());
//   sortCorners(corners, center);

    pcbBgColor.set(244,224,199);
    pcbPadColor.set(223, 149, 114);
    pcbBoardColor.set(241,217,187, 255);
    pcbGridColor.set(237, 205, 165,255);

}
//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::generatePerfBoard(int width, int height)
{
//    cairo.drawCircle(10,10,10);
}

void ofApp::drawPerfGrid()
{
    int padding = 30;
    ofPushStyle();
    ofSetColor(pcbGridColor);

    for (int i =0 ; i < 40 ; i++)
    {
        if ((pcb_rect.getTopLeft().x + i*padding) < pcb_rect.getTopRight().x)
        {
            ofLine(pcb_rect.getTopLeft() + ofPoint(i*padding, 0), pcb_rect.getBottomLeft() + ofPoint(i*padding, 0));
        }
        if( (pcb_rect.getTopLeft().y + i*padding) < pcb_rect.getBottomRight().y)
        {
            //ofCircle(pcb_rect.getTopLeft() + ofPoint(0, i*padding), 5);
            ofLine(pcb_rect.getTopLeft() + ofPoint(0, i*padding), pcb_rect.getTopRight() + ofPoint(0, i*padding));
        }
    }
    ofPopStyle();
}

void ofApp::draw()
{
    ofBackground(pcbBgColor);



    ofPushMatrix();
//    ofTranslate( (ofGetWidth()/2 )- cairo , ( ofGetHeight()/2 ) - 800);

    ofPushStyle();
    ofSetColor(pcbBoardColor);
    ofRect(pcb_rect);



    ofEnableAlphaBlending();
    cairoimg.draw(pcb_rect.x, pcb_rect.y);
    ofDisableAlphaBlending();

    ofEnableAlphaBlending();
    ofPushStyle();
        ofSetColor(255,255,255,80);
    pcb.draw(0,0);
    ofPopStyle();
    ofDisableAlphaBlending();



    ofPopMatrix();


    ofPushStyle();
    ofSetColor(255,0,0);
    ofLine(mouseX,mouseY - 50, mouseX, mouseY + 50);
    ofLine(mouseX - 50, mouseY, mouseX + 50, mouseY);
    ofPopStyle();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}
