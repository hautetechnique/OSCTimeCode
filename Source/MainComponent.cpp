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

#include "MainComponent.h"

TimeCodeTest MainContentComponent::test;

MainContentComponent::MainContentComponent()
{
    lookAndFeel = new CustomLookAndFeel();
    LookAndFeel::setDefaultLookAndFeel(lookAndFeel);
    
    UnitTestRunner ur;
    ur.runAllTests();
    
    active = false;
    sender = true;
    
    activeButton = new TextButton("Start");
    activeButton->addListener(this);
    addAndMakeVisible(activeButton);
    
    
    modeLabel = new Label();
    addAndMakeVisible(modeLabel);
    modeLabel->setJustificationType(Justification::centred);
    modeLabel->setText("Sender", dontSendNotification);
    
    
    senderButton = new TextButton("Sender");
    senderButton->addListener(this);
    addAndMakeVisible(senderButton);
    
    
    ipEditor = new TextEditor();
    ipEditor->setText("127.0.0.1");
    addAndMakeVisible(ipEditor);
    
    portEditor = new TextEditor();
    portEditor->setText("1337");
    addAndMakeVisible(portEditor);
   
    fpsEditor = new TextEditor();
    fpsEditor->setText("30");
    addAndMakeVisible(fpsEditor);
    
    offsetEditor = new TextEditor();
    offsetEditor->setText("00:00:00:00");
    addAndMakeVisible(offsetEditor);
    
    timeLabel = new TimeLabel();
    timeLabel->setText("--:--:--:--");
    
    addAndMakeVisible(timeLabel);
    
    setSize (320, 300);
}

MainContentComponent::~MainContentComponent()
{
    if(active)
        stop();
}

void MainContentComponent::paint (Graphics& g)
{
    const int spacing = 30;
    
    g.setColour(Colours::white);
    g.drawText("IP:", 15, 24, 80, 30, Justification::topRight);
    g.drawText("PORT:", 15, 24 + spacing, 80, 30, Justification::topRight);
    g.drawText("FPS:", 15, 24 + spacing * 2, 80, 30, Justification::topRight);
    g.drawText("OFFSET:", 15, 24 + spacing * 3, 80, 30, Justification::topRight);
    g.drawText("MODE:", 15, 24 + spacing * 4, 80, 30, Justification::topRight);
}

void MainContentComponent::resized()
{
    Rectangle<int> area = getLocalBounds();
    Rectangle<int> top = area.removeFromTop(area.getHeight()).reduced(15, 15);
    Rectangle<int> topLeft = top.removeFromLeft(top.getWidth()).removeFromRight(210);
    
    ipEditor->setBounds(topLeft.removeFromTop(30).reduced(5, 5));
    portEditor->setBounds(topLeft.removeFromTop(30).reduced(5, 5));
    fpsEditor->setBounds(topLeft.removeFromTop(30).reduced(5, 5));
    offsetEditor->setBounds(topLeft.removeFromTop(30).reduced(5, 5));
    senderButton->setBounds(topLeft.removeFromTop(30).reduced(5, 5));
    modeLabel->setBounds(senderButton->getBounds().reduced(5, 5));
    activeButton->setBounds(topLeft.withRight(200).removeFromTop(30).reduced(5, 5));
    timeLabel->setBounds(getLocalBounds().withTop(210).withHeight(60));
}

void MainContentComponent::start()
{
    
    validateFields();
    
    framesPerSecond = fpsEditor->getText().getIntValue();
    ip = ipEditor->getText();
    port = portEditor->getText().getIntValue();
    
    if(sender)
    {
        oscSender = new OSCSender();
        if(!oscSender->connect(ip, port))
            DBG("Unable to connect to " + ip  + ":" + String(port));
        
        currentTimeMillis = TimeCode(offsetEditor->getText(), framesPerSecond);

        startTimer(1000 / 60);
    
        lastUpdateMillis = Time::currentTimeMillis();
        
        DBG("Sending");
    }
    else
    {
        oscReceiver = new OSCReceiver();
        oscReceiver->addListener(this);
        oscReceiver->connect(port);
        
        timeLabel->setText("--:--:--:--");
        
        DBG("Listening on port: " + String(port));
    }
    
}

void MainContentComponent::validateFields()
{
    // IP
    const IPAddress ip(ipEditor->getText());
    ipEditor->setText(ip.toString());
    
    
    // port
    int port = portEditor->getText().getIntValue();
    port = jmax(jmin(port, 65535), 1024);
    portEditor->setText(String(port));
    
    // FPS
    int fps = fpsEditor->getText().getIntValue();
    fps = jmax(jmin(fps, 1000), 1);
    fpsEditor->setText(String(fps));
    
    // OFFSET
    const TimeCode currentOffset(offsetEditor->getText(), fps);
    
    offsetEditor->setText(currentOffset.toString(fps));
}

void MainContentComponent::stop()
{
    if(sender)
    {
        oscSender->disconnect();
        stopTimer();
        
        DBG("Stopped sending");
    }
    else
    {
        oscReceiver->disconnect();
        
        DBG("Stopped receiving");
    }
    
    timeLabel->setText("--:--:--:--");
}

void MainContentComponent::buttonClicked(Button *button)
{
    if(button == activeButton)
    {
        if(active)
            stop();
        else
            start();
        
        active = !active;
        
        String buttonText = active ? "Stop" : "Start";
        activeButton->setButtonText(buttonText);
        senderButton->setVisible(!active);
    }
    else if(button == senderButton)
    {
        if(!active)
        {
            sender = !sender;
            
            String buttonText = sender ? "Sender" : "Receiver";
            senderButton->setButtonText(buttonText);
            modeLabel->setText(buttonText, dontSendNotification);
        }
    }
    
    const bool enabled = !active && sender;
    
    ipEditor->setEnabled(enabled);
    portEditor->setEnabled(!active);
    fpsEditor->setEnabled(enabled);
    offsetEditor->setEnabled(enabled);
}

void MainContentComponent::timerCallback()
{
    const int64 diffInMillis = (Time::currentTimeMillis() - lastUpdateMillis);
    currentTimeMillis += diffInMillis;
    lastUpdateMillis = Time::currentTimeMillis();

    const TimeCode currentTime(currentTimeMillis);
    
    String timeString = currentTime.toString(framesPerSecond);
    
    OSCMessage message("/TC1/time/" + String(framesPerSecond));
    message.addString(timeString);
    
    if(!oscSender->send(message))
        DBG("Unable to send");
    
    timeLabel->setTimeCode(timeString);
}

void MainContentComponent::oscMessageReceived (const OSCMessage& message)
{
    const OSCAddressPattern pattern("/TC*/time/*");
    
    OSCAddressPattern messagePattern = message.getAddressPattern();
    
    // Did we recieve an timecode message
    if(pattern.matches(messagePattern.toString()))
    {
        if(message.size() == 1)
        {
            const String timeString = message[0].getString();
            timeLabel->setText(timeString);
        }
        else
        {
            DBG("Received invalid timecode message");
        }
    }
}





