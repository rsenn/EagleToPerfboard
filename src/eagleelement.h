#ifndef EAGLEELEMENT
#define EAGLEELEMENT


#include "ofMain.h"


struct wire
{
    ofPoint start;
    ofPoint stop;
    float width;
};


class EagleElement
{
public:
    virtual void draw()
    {

    }
};

class EaglePad : public EagleElement
{

};

class EagleWire : public EagleElement
{
public:
    EagleWire()
    {

    }

    void set(float x1, float y1, float x2, float y2, float _width)
    {
        start.set(x1,y1);
        stop.set(x2,y2);
        width = 5;
    }

    void set(ofPoint _start, ofPoint _stop, float _width)
    {
        start = _start;
        stop  = _stop;
        width = _width;
    }

    EagleWire(ofPoint _start, ofPoint _stop, float _width)
    {
        set(_start, _stop, _width);
    }

    void draw()
    {
        ofPushStyle();
        ofSetLineWidth(width);
        ofLine(start,stop);
        ofPopStyle();

        ofCircle(start, width*0.5);
        ofCircle(stop,  width*0.5);
    }

private:
    ofPoint start;
    ofPoint stop;
    float width;
};


class EagleCircle : public EagleElement
{
public:
    EagleCircle()
    {

    }

    EagleCircle(float _x, float _y, float _radius)
    {
       set( _x,  _y,  _radius);
    }

    void set(float _x, float _y, float _radius)
    {
        pos.set(_x, _y);
        radius = _radius;
    }

    void draw()
    {
        ofCircle(pos, radius);
    }

private:
    ofPoint pos;
    float radius;
};


class EagleRect : public EagleElement
{
public:
    EagleRect()
    {

    }

    EagleRect(float _x1, float _y1, float _x2, float _y2)
    {
//       set( _x,  _y,  _radius);
    }

    void set(float _x1, float _y1, float _x2, float _y2)
    {
//        rect.set()
//        pos.set(_x, _y);
//        radius = _radius;
    }

    void draw()
    {
        //ofRect()
    }

private:
    ofRectangle rect;
};

class EaglePackage : public EagleElement
{
public:

private:

};


class EagleBoard : public EagleElement
{
public:
    void draw()
    {
        for(vector<EagleElement *>::iterator it = elements.begin(); it != elements.end(); it++){
            (*it)->draw();
        }
    }

    void add (EagleElement * _element)
    {
        elements.push_back(_element);
    }

    ~EagleBoard()
    {
        for(vector<EagleElement *>::iterator it = elements.begin(); it != elements.end(); it++){
            delete (*it);
        }
    }

private:
    vector <EagleElement *> elements;
};
#endif // EAGLEELEMENT

