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

    map<string,string> mapElementLibrary;
    map<string,EaglePackage> mapLibraryPackage;


    void addXmlChildWireToBoard(float scale, int layer)
    {

        if (xmlEagleBoard.getName() == "wire" && xmlEagleBoard.getAttribute("layer") == ofToString(layer))
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

                EagleWire * wire = new EagleWire();
                wire->set(x1,y1,x2,y2,width);

                board.add(wire);
            }

    }


    void addXmlChildWireToPackage(int j, float scale, EaglePackage * pkg)
    {
        xmlEagleBoard.setToChild(j);

        if (xmlEagleBoard.getName() == "wire")
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

                EagleWire * wire = new EagleWire();
                wire->set(x1,y1,x2,y2,width);
                pkg->add(wire);
            }

        xmlEagleBoard.setToParent();

    }

    void parse()
    {
        xmlEagleBoard.load("/Users/xcorex/Documents/Projects/EagleCad/projects/lifepatch/peakdetector/peakdetect_arduino/Untitled.brd");

        xmlEagleBoard.setTo("eagle");
        xmlEagleBoard.setTo("drawing");
        xmlEagleBoard.setTo("board"); //parent


        //--------------

        xmlEagleBoard.setTo("plain"); //set to plain
        //parse board dimension
        int numChild = xmlEagleBoard.getNumChildren();
        float scale = 10;

        for (int childIdx = 0; childIdx < numChild; childIdx++)
            {
                xmlEagleBoard.setToChild(childIdx);
                addXmlChildWireToBoard(scale, 20);
                xmlEagleBoard.setToParent();
            }
        xmlEagleBoard.setToParent(); //back to board


        //--------------


        //--------------


        xmlEagleBoard.setTo("libraries"); //set to libraries
        xmlEagleBoard.setTo("library[0]"); //set to packages

        do
            {
                string library_name = xmlEagleBoard.getAttribute("name");

                xmlEagleBoard.setTo("packages"); //set to packages
                xmlEagleBoard.setTo("package[0]"); //set to package

                do
                    {
                        string package_name = xmlEagleBoard.getAttribute("name");
                        EaglePackage * eaglePkg = new EaglePackage();

                        int childnum = xmlEagleBoard.getNumChildren();
                        for (int childIdx = 0; childIdx < childnum; childIdx++)
                            {

                                addXmlChildWireToPackage(childIdx, scale, eaglePkg);
                            }

                        mapLibraryPackage[library_name + package_name] = *eaglePkg;

                    }
                while(xmlEagleBoard.setToSibling());  // go the next package[]


                xmlEagleBoard.setToParent(); //back to packages
                xmlEagleBoard.setToParent(); //back to library[]

            }
        while(xmlEagleBoard.setToSibling()); // go the next library[]



        xmlEagleBoard.setToParent(); //back to libraries
        xmlEagleBoard.setToParent(); //back to board




        //--------------


        xmlEagleBoard.setTo("elements"); //set to elements
        xmlEagleBoard.setTo("element[0]"); //set to element[0]

        do
            {
                mapElementLibrary[xmlEagleBoard.getAttribute("name")] = xmlEagleBoard.getAttribute("library") + xmlEagleBoard.getAttribute("package");
            }
        while(xmlEagleBoard.setToSibling()); // go the next PT

        xmlEagleBoard.setToParent(); //back to elements
        xmlEagleBoard.setToParent(); //back to board


        for(map<string,string>::iterator it = mapElementLibrary.begin(); it != mapElementLibrary.end(); it++)
            {
                ofLog() << it->second;
            }

        //--------------

        //parse all signals
        xmlEagleBoard.setTo("signals");
        xmlEagleBoard.setTo("signal[0]");
        // get each individual x,y for each point
        // iterate signal 0 ... end
        // signals
        //  |______signal[0] / GND
        //                |_________ wire
        //                |_________ contact ref
        //                |_________ via
        //  |______signal[1] / VCC..
        //                |_________ contact ref
        //                |_________ via
        do
            {
                int childnum = xmlEagleBoard.getNumChildren();
                for (int childIdx = 0; childIdx < childnum; childIdx++)
                    {
                        xmlEagleBoard.setToChild(childIdx); //enter child

                        if (xmlEagleBoard.getName() == "wire")
                            {

                                addXmlChildWireToBoard(scale, 16);
                            }
                        else if (xmlEagleBoard.getName() == "contactref")
                            {
                                string element_name = xmlEagleBoard.getAttribute("element");



                            }
                        else if  (xmlEagleBoard.getName() == "via")
                            {

                            }
                        xmlEagleBoard.setToParent(); //exit child
                    }
            }
        while(xmlEagleBoard.setToSibling()); // go the next PT

        xmlEagleBoard.setToParent(); //back to signals
        xmlEagleBoard.setToParent(); //back to board


        //--------------

    }

    void draw()
    {
        mapLibraryPackage["linearDIL08"].draw();
        board.draw();
    }
};

#endif // OFXEAGLEBOARD

