/*
    OSCTimecode - Juce OSC Timecode example application
 
    Copyright (C) 2017 Haute Technique - Sander ter Braak and Jan de Boer <info@hautetechnique.com>
 
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.
 
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.
 
    You should have received a copy of the GNU Lesser General Public
    License along with this library.
 
    If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TimeLabel_hpp
#define TimeLabel_hpp

#include "../JuceLibraryCode/JuceHeader.h"

#include "TimeCode.hpp"

class TimeLabel : public Component
{

public:
	
	TimeLabel();
	
    void setTimeCode(const String& timeString);

    void setText(const String &text);
    
private:
	
    void resized() override ;
	
    ScopedPointer<Label> label;
    
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimeLabel)

};

#endif /* TimeLabel_hpp */
