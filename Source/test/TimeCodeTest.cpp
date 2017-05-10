//
//  TimeCodeTest.cpp
//  OSCTimecode
//
//  Created by Sander ter Braak on 10/05/2017.
//
//

#include "TimeCodeTest.hpp"


TimeCodeTest::TimeCodeTest():UnitTest("TimeCodeTest") {}

TimeCodeTest::~TimeCodeTest() {}

void TimeCodeTest::initialise() {}

void TimeCodeTest::shutdown() {}

String TimeCodeTest::addLeadingZero(int value, int length)
{
    
    String s(value);
    
    while (s.length() < length) {
        s = "0" + s;
    }
    return s;
}

void TimeCodeTest::testTime(int hours, int minutes, int seconds, int frames, double fps)
{
    String tcString =  addLeadingZero(hours,2)+  ":" + addLeadingZero(minutes,2)+  ":" + addLeadingZero(seconds,2)+  ":" + addLeadingZero(frames,2);
    TimeCode tcResult = TimeCode(tcString, fps);
    String result = tcResult.toString(fps);
    //DBG(tcString + " >> " + result  + " >> " + String(tcResult));
    expect (result == tcString);
}

void TimeCodeTest::runTest()
{
    /// set this to 24, 25, 29.9, 30 or anything you like...
    
    const double fps = 25;
    
    beginTest ("Testing TimeCode String to int to String - all frames at " + String(fps) + "fps");
    for(int i = 0; i < fps; i++)
        testTime(0, 0, 0, i, fps);
    
    
    beginTest ("Testing TimeCode String to int to String - all seconds at " + String(fps) + "fps");
    for(int i = 0; i < 59; i++)
        testTime(0, 0, i, 0, fps);
    
    beginTest ("Testing TimeCode String to int to String - all minutes at " + String(fps) + "fps");
    for(int i = 0; i < 59; i++)
        testTime(0, i, 0, 0, fps);
    
    beginTest ("Testing TimeCode String to int to String - all hours at " + String(fps) + "fps");
    for(int i = 0; i < 30; i++)
        testTime(i, 0, 0, 0, fps);
    
    
    Random r = getRandom();
    
    beginTest ("Testing TimeCode String to int to String - 100 random times at " + String(fps) + "fps");
    for(int i = 0; i < 100; i++)
    {
        const int H = r.nextInt(30);
        const int M = r.nextInt(60);
        const int S = r.nextInt(60);
        const int F = r.nextInt(25);
        
        testTime(H, M, S, F, fps);
    }
}
