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

#ifndef TImeCode_hpp
#define TImeCode_hpp

#include "../JuceLibraryCode/JuceHeader.h"

class TimeCode
{

public:
	
    
    TimeCode();
    
    TimeCode(const TimeCode& other);
    
    TimeCode(const int64& other);
    
    TimeCode(const String& string, const double fps);
    
    operator int64() const noexcept;
    
    
    
    TimeCode& operator= (const String& other);
    
    TimeCode& operator= (const int64& other);
    
    TimeCode& operator= (const TimeCode& other);
    
    bool operator== (const TimeCode& other) const;
    
    bool operator== (const int64& other) const;
    
    bool operator!= (const TimeCode& other) const;
    
    bool operator<  (const TimeCode& other) const;
    
    bool operator>  (const TimeCode& other) const;
    
    bool operator<= (const TimeCode& other) const;
    
    bool operator>= (const TimeCode& other) const;
    
    void       setFromString(const String &string,const  double fps);
    
    String     toString(const double fps) const;
    
    int64      timeMillis {0};
    
};

#endif /* TImeCode_hpp */
