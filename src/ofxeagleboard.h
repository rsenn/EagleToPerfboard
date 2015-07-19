#ifndef OFXEAGLEBOARD
#define OFXEAGLEBOARD

#include "ofMain.h"
#include "eagleelement.h"

class ofxEagleBoard
{
public:
    //read xml
    ofXml xmlEagleBoard;
    vector<EagleWire> wires;
    EagleBoard board;

    void parse()
    {
        xmlEagleBoard.load("/Users/xcorex/Documents/Projects/EagleCad/projects/lifepatch/peakdetector/peakdetect_arduino/Untitled.brd");

        xmlEagleBoard.setTo("eagle");
        xmlEagleBoard.setTo("drawing");
        xmlEagleBoard.setTo("board");
        xmlEagleBoard.setTo("plain");

        //parse board dimension

        int numChild = xmlEagleBoard.getNumChildren();
        float scale = 10;

        for (int i = 0; i < numChild; i++)
            {
                xmlEagleBoard.setToChild(i);

                float x1 = std::atof(xmlEagleBoard.getAttribute("x1").c_str());
                float y1 = std::atof(xmlEagleBoard.getAttribute("y1").c_str());
                float x2 = std::atof(xmlEagleBoard.getAttribute("x2").c_str());
                float y2 = std::atof(xmlEagleBoard.getAttribute("y2").c_str());
                float width = std::atof(xmlEagleBoard.getAttribute("width").c_str());

                xmlEagleBoard.setToParent();

                x1 = x1 * scale;
                y1 = y1 * scale;
                x2 = x2 * scale;
                y2 = y2 * scale;

                //ofLog() << xmlEagleBoard.getName() << "start: " << x1 << "," << y1 << " stop: " << x2 << "," << y2;

//                wire line;
//                line.start.set(x1,y1);
//                line.stop.set(x2,y2);
//                line.width = width;
//                wires.push_back(line);
                  EagleWire * wire = new EagleWire();
                  wire->set(x1,y1,x2,y2,width);
                  //wires.push_back(wire);
                  board.add(wire);

            }
        xmlEagleBoard.setToParent();


        //parse all signals

        xmlEagleBoard.setTo("signals[0]");
        xmlEagleBoard.setTo("signal[0]");

        // get each individual x,y for each point
        do
            {
                ofLog() << xmlEagleBoard.getAttribute("name");
                int childnum = xmlEagleBoard.getNumChildren();

                for (int j = 0; j < childnum; j++)
                    {

                        xmlEagleBoard.setToChild(j);

                        if (xmlEagleBoard.getName() == "wire" && xmlEagleBoard.getAttribute("layer") == "16")
                            {
                                float x1 = std::atof(xmlEagleBoard.getAttribute("x1").c_str());
                                float y1 = std::atof(xmlEagleBoard.getAttribute("y1").c_str());
                                float x2 = std::atof(xmlEagleBoard.getAttribute("x2").c_str());
                                float y2 = std::atof(xmlEagleBoard.getAttribute("y2").c_str());
                                float width = std::atof(xmlEagleBoard.getAttribute("width").c_str());

                                x1 = x1 * scale;
                                y1 = y1 * scale;
                                x2 = x2 * scale;
                                y2 = y2 * scale;

                                //ofLog() << xmlEagleBoard.getName() << "start: " << x1 << "," << y1 << " stop: " << x2 << "," << y2;

//                                wire line;
//                                line.start.set(x1,y1);
//                                line.stop.set(x2,y2);
//                                line.width = width;
//                                wires.push_back(line);

                                EagleWire * wire = new EagleWire();
                                wire->set(x1,y1,x2,y2,width);
//                                wires.push_back(wire);
                                board.add(wire);
                            }

                        xmlEagleBoard.setToParent();
                    }

            }
        while(xmlEagleBoard.setToSibling()); // go the next PT



//        vector<EagleWire>::iterator it = wires.begin();
//        for(; it != wires.end(); ++it)
//            {
//                EagleWire  *w = &(*it);
//                ofLog() << xmlEagleBoard.getName() << "start: " << w->start << " stop: " <<  w->stop;
//            }


        //    do
        //        {
        //            if (xmlEagleBoard.getAttribute("layer") == "20")
        //            {
        //                string x1 = xmlEagleBoard.getAttribute("x1");
        //                string y1 = xmlEagleBoard.getAttribute("y1");

        //                string x2 = xmlEagleBoard.getAttribute("x2");
        //                string y2 = xmlEagleBoard.getAttribute("y2");


        //                float x1f = atof(x1.c_str());

        //                ofLog() << xmlEagleBoard.getName();

        //    //            printf("%s found\n", x1.c_str());
        //               // printf("%f found\n", x1f);
        //            }


        //        }

        //    xmlEagleBoard.
        //    while(xmlEagleBoard.setToSibling());

        //std::exit();


    }

    void draw()
    {

        board.draw();

//        vector<EagleWire>::iterator it = wires.begin();



//        // loop through, increasing to next element until the end is reached
//        for(; it != wires.end(); ++it)
//            {
//                EagleWire  *w = &(*it);
//                w->draw();
////                ofPushStyle();
////                ofSetLineWidth(w->width*10);

////                ofLine(w->start, w->stop);
////                ofPopStyle();
////                ofCircle(w->start, w->width*5);
////                ofCircle(w->stop,  w->width*5);

//            }

    }
};

#endif // OFXEAGLEBOARD

