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

#include "TimeCode.hpp"

#include <regex>
#include <sstream>
#include <iomanip>

TimeCode::TimeCode()
{
}

TimeCode::TimeCode(const TimeCode& other)
{
    this->timeMillis = other.timeMillis;
}

TimeCode::TimeCode(const int64& other)
{
    this->timeMillis = other;
}

TimeCode::TimeCode(const String& string, const double fps)
{
    setFromString(string, fps);
}

TimeCode::operator int64() const noexcept
{
    return timeMillis;
}

TimeCode& TimeCode::operator= (const String& other)
{
    setFromString(other, 25);
    return *this;
}

TimeCode& TimeCode::operator= (const int64& other)
{
    this->timeMillis = other;
    return *this;
}

TimeCode& TimeCode::operator= (const TimeCode& other)
{
    this->timeMillis = other.timeMillis;
    return *this;
}

bool TimeCode::operator== (const TimeCode& other) const
{
    return this->timeMillis == other.timeMillis;
}

bool TimeCode::operator== (const int64& other) const
{
    return this->timeMillis == other;
}

bool TimeCode::operator!= (const TimeCode& other) const
{
    return ! operator==(other);
}

bool TimeCode::operator< (const TimeCode& other) const
{
    return this->timeMillis < other.timeMillis;
}

bool TimeCode::operator> (const TimeCode& other) const
{
    return this->timeMillis > other.timeMillis;
}

bool TimeCode::operator<= (const TimeCode& other) const
{
    return this->timeMillis <= other.timeMillis;
}

bool TimeCode::operator>= (const TimeCode& other) const
{
    return this->timeMillis >= other.timeMillis;
}


void TimeCode::setFromString(const String &string, const double fps)
{
    using namespace std;
    
    regex r("([0-9]+):([0-9]+):([0-9]+):([0-9]+)");
    smatch matches;
    
    if(regex_search(string.toStdString(), matches, r) && matches.size() == 5)
    {
        int hours = stoi(matches[1]);
        int minutes = stoi(matches[2]);
        int seconds = stoi(matches[3]);
        int frame = stoi(matches[4]);
        
        timeMillis = (hours * 60 * 60 * 1000) + (minutes * 60 * 1000) + (seconds * 1000) + ceil(frame * (1000.0 / fps));
    }
}

String TimeCode::toString(const double fps) const
{
    int hours = floor(timeMillis / (1000 * 60 * 60));
    int minutes = (int)floor(timeMillis / (1000 * 60))  % 60;
    int seconds = (int)floor(timeMillis / 1000) % 60;
    int frame = double(timeMillis % 1000) / (1000.0 / fps);
    
    using namespace std;
    
    stringstream stream;
    stream <<
        setfill('0') << setw(2) << hours << ":" <<
        setfill('0') << setw(2) << minutes << ":" <<
        setfill('0') << setw(2) << seconds << ":" <<
        setfill('0') << setw(2) << frame;
    
    return String(stream.str());
}


