#include "ofApp.h"


void ofApp::setup()
{
    ofSetFrameRate(30);

    sch_x = 0;
    sch_y = 0;

    center.x = 0;
    center.y = 0;

    fileName = "/Users/xcorex/pcb2.png";

    loadAndProcessPCB();


    pcbBgColor.set(244,224,199);
    pcbPadColor.set(223, 149, 114);
    pcbBoardColor.set(241,217,187, 255);
    pcbGridColor.set(237, 205, 165,255);

    //every half sec check file timestamp
    timerCheckTimestamp.setInterval(0.5);


    // xmlEagleBoard.setTo("wire[0]");

    // ofLog() << xmlEagleBoard.getNumChildren();

    eagle.parse();
}
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
    pcb_cv.setFromPixels(pcb.getPixelsRef());
    pcb_cv_gray = pcb_cv;
    cv::Mat pcb_can = pcb_cv_gray.getCvImage();
    lines.clear();
    cv::HoughLinesP(pcb_can, lines, 1, CV_PI/180, 100, 100,0.1);
}

void ofApp::extractCorner()
{
    corners.clear();

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

    int margin = 60;
    int padding = 60;

    int pcb_hole_h = 12;
    int pcb_hole_v = 12;

    int pcb_hole_diameter_outer = 16;
    int pcb_hole_diameter_inner = 4;

//    margin = margin + pcb_hole_diameter_outer;

    int canvas_w = margin*2 + ((pcb_hole_h-1) * padding);
    int canvas_h = margin*2 + ((pcb_hole_v-1) * padding);



    cairo.setupMemoryOnly(ofCairoRenderer::IMAGE,true,false, ofRectangle(0,0, canvas_w, canvas_h));
    cairo.background(141, 175, 213, 255);
    cairo.setColor(165,205,237, 120); //nasty bug cairo colorspace is b g r


    string idx = "ABCDEFGHIJKLMNOPQRTUVWXY";

    for (int i =0 ; i < pcb_hole_h ; i++)
        {


            cairo.pushMatrix();
            cairo.translate(margin, margin);

            cairo.setColor(0,0,0, 100);
            cairo.drawString(   ofToString(idx.at(i)),  i*padding, pcb_hole_v*padding - (margin/2),0, OF_BITMAPMODE_SIMPLE);

            for (int k =0 ; k < pcb_hole_v ; k++)
                {
                    cairo.setColor(0,0,0, 10);
                    cairo.drawString(  ofToString(k),  -(margin/2), k*padding,0, OF_BITMAPMODE_SIMPLE);

                }

            for (int j =0 ; j < pcb_hole_v ; j++)
                {
                    cairo.setColor(121,160,205, 120);
                    cairo.drawCircle(i*padding, j*padding, 0, pcb_hole_diameter_outer);
                    cairo.setColor(154, 184, 219, 255);
                    cairo.drawCircle(i*padding, j*padding, 0, pcb_hole_diameter_inner);
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
            cairo.popMatrix();
        }

    // cairo.drawCircle(11,11,0,10);
    cairo.update();
    cairoimg.setFromPixels(cairo.getImageSurfacePixels());
    cairoimg.saveImage("cairo.png");
}

void ofApp::loadAndProcessPCB()
{
    processPCB(fileName);
    extractCorner();
    makePCBtransparent();
    makePCBRender();
}


//--------------------------------------------------------------
void ofApp::update()
{
    if(timerCheckTimestamp.tick())
        {
            ofFile fragFile(fileName);
            Poco::Timestamp PCBTimestamp = fragFile.getPocoFile().getLastModified();
            if(PCBTimestamp != lastPCBTimestamp)
                {
                    loadAndProcessPCB();
                    lastPCBTimestamp = PCBTimestamp;
                }
        }
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
    ofBackground(0,0,0);
//    ofBackground(222,189,160);

    ofPushMatrix();
    ofTranslate(10*sch_x, 10*sch_y);
//    ofScale(0.75,0.75);

//    ofPushMatrix();
//    ofTranslate( (ofGetWidth()/2 )- cairoimg.width - 10, ( ofGetHeight()/2 ) - cairoimg.height/2);
//    ofPushStyle();
//    cairoimg.draw(0,0);
//    ofEnableAlphaBlending();
//    ofPushStyle();
//    ofSetColor(255,255,255,80);
//    ofRotateZ(90);
//    pcb.draw(60*sch_x-pcb_rect.x,60*sch_y-pcb_rect.y);
//    ofPopStyle();
//    ofDisableAlphaBlending();
//    ofPopMatrix();


//    ofPushMatrix();
//    ofTranslate( (ofGetWidth()/2 ) + 10 , ( ofGetHeight()/2 ) - cairoimg.height/2);
//    ofPushStyle();
//    cairoimg.draw(0,0);
//    ofEnableAlphaBlending();
//    ofPushStyle();
//    ofSetColor(255,255,255,80);
//    pcb.draw(60*(-sch_x+1)+pcb_rect.x +8 + pcb.width,60*sch_y-pcb_rect.y, -pcb.width, pcb.height);
//    ofPopStyle();
//    ofDisableAlphaBlending();
//    ofPopMatrix();


    eagle.draw();

    ofPopMatrix();

//    //crosshair
//    ofPushStyle();
//    ofSetColor(255,0,0);
//    ofLine(mouseX,mouseY - 50, mouseX, mouseY + 50);
//    ofLine(mouseX - 50, mouseY, mouseX + 50, mouseY);
//    ofPopStyle();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)

{
    if (key == 'w')
        {
            sch_y--;
        }
    else if ( key == 's')
        {
            sch_y++;
        }
    else if ( key == 'a')
        {
            sch_x--;
        }
    else if ( key == 'd')
        {
            sch_x++;
        }
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
