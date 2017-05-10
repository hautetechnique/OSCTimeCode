//
//  TimeCodeTest.hpp
//  OSCTimecode
//
//  Created by Sander ter Braak on 10/05/2017.
//
//

#ifndef TimeCodeTest_hpp
#define TimeCodeTest_hpp

#include "../JuceLibraryCode/JuceHeader.h"
#include "TimeCode.hpp"

class TimeCodeTest : public UnitTest
{

public:
	
	TimeCodeTest();
	
	~TimeCodeTest();
    
    void initialise();
    
    void testTime(int hours, int minutes, int seconds, int frames, double fps);
    
    String addLeadingZero(int value, int length);
    
    void shutdown();
    
    void runTest();
	
private:
	
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimeCodeTest)

};

#endif /* TimeCodeTest_hpp */
