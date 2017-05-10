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

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "TimeLabel.hpp"
#include "TimeCode.hpp"
#include "LookAndFeel/CustomLookAndFeel.hpp"
#include "TimeCodeTest.hpp"


class MainContentComponent   :  public Component,
                                public Button::Listener,
                                public Timer,
                                public OSCReceiver::Listener<OSCReceiver::MessageLoopCallback>
{
public:
    
    MainContentComponent();
    ~MainContentComponent();
    
    
    static TimeCodeTest test;

    void 	paint (Graphics&) override;
    void 	resized() override;
    
    double 	framesPerSecond;
    
    int64   currentTimeMillis;
    
    int64   lastUpdateMillis;
    
    String  ip;
    
    int     port;
    
    bool    sender;
    
    bool 	active;
    
    ScopedPointer<OSCSender>    oscSender;
    
    ScopedPointer<OSCReceiver>  oscReceiver;
    
    
    
    ScopedPointer<TextButton>   activeButton;
    
    ScopedPointer<TextButton>   senderButton;
    
    ScopedPointer<TimeLabel>    timeLabel;
    
    ScopedPointer<TextEditor> 	ipEditor;
    
    ScopedPointer<TextEditor> 	portEditor;
    
    ScopedPointer<TextEditor> 	fpsEditor;
    
    ScopedPointer<TextEditor>   offsetEditor;
    
    ScopedPointer<Label>        modeLabel;
    
    ScopedPointer<CustomLookAndFeel> lookAndFeel;
    
private:
    
    void validateFields();
    
    void buttonClicked(Button *button) override;
    
    void timerCallback() override;
    
    void oscMessageReceived (const OSCMessage& message) override;
    
    void start();
    
    void stop();
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
    
};


#endif  // MAINCOMPONENT_H_INCLUDED
