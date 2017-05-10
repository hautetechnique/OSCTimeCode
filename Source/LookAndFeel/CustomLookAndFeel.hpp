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

#ifndef CustomLookAndFeel_hpp
#define CustomLookAndFeel_hpp

#include "../JuceLibraryCode/JuceHeader.h"

class CustomLookAndFeel : public LookAndFeel_V3 {
    
public:
    
    
    Colour HAUTE_BLUE = Colour(0xFF169ee4);
    
    CustomLookAndFeel()
    {
        
        setColour(TextEditor::focusedOutlineColourId, Colours::white);
        setColour(TextEditor::ColourIds::highlightColourId, Colours::white);
        setColour(ListBox::ColourIds::backgroundColourId,  Colours::darkgrey);

        setColour(TextButton::ColourIds::buttonColourId, Colour(0xFF606060));
        setColour(TextButton::ColourIds::textColourOffId, Colour(0xffEFEFEF));
        setColour(TextButton::ColourIds::textColourOnId, Colour(0xffEFEFEF));

        setColour(TextEditor::ColourIds::outlineColourId, Colours::grey);
        setColour(TextEditor::ColourIds::focusedOutlineColourId, Colours::grey);
        
        setColour(TextEditor::backgroundColourId, Colours::black);
        setColour(TextEditor::ColourIds::highlightColourId, Colour(0xFF5dcffc));
        setColour(TextEditor::ColourIds::textColourId, Colours::white);
        setColour(CaretComponent::ColourIds::caretColourId, Colour(0xFFFFFFFF));
        
        setColour(Label::textColourId, Colours::white);
    }
    
    void drawButtonText (Graphics& g, TextButton& button, bool isMouseOverButton, bool /*isButtonDown*/)
    {
        Font font = g.getCurrentFont();
        
        g.setFont (font);
        
        Colour c = button.findColour (button.getToggleState() ? TextButton::textColourOnId
                                      : TextButton::textColourOffId)
        .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f);
        
        if(isMouseOverButton) c = Colours::white;
        
        g.setColour (c);
        
        
        g.drawFittedText (button.getButtonText(),
                          0,
                          1,
                          button.getWidth() ,
                          button.getHeight() ,
                          Justification::centred, 2);
    }
    
    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown)
    {
        Colour baseColour (backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
                           .withMultipliedAlpha (button.isEnabled() ? 0.9f : 0.5f));
        
        if (isButtonDown || isMouseOverButton)
            baseColour = HAUTE_BLUE.contrasting (isButtonDown ? 0.4f : 0.2f);
        
        const bool flatOnLeft   = button.isConnectedOnLeft();
        const bool flatOnRight  = button.isConnectedOnRight();
        const bool flatOnTop    = button.isConnectedOnTop();
        const bool flatOnBottom = button.isConnectedOnBottom();
        
        const float width  = button.getWidth();
        const float height = button.getHeight();
        
        if (width > 0 && height > 0)
        {
            const float cornerSize = 5.0f;
            
            Path outline;
            outline.addRoundedRectangle (0, 0, width, height, cornerSize, cornerSize,
                                         ! (flatOnLeft  || flatOnTop),
                                         ! (flatOnRight || flatOnTop),
                                         ! (flatOnLeft  || flatOnBottom),
                                         ! (flatOnRight || flatOnBottom));
            
            
            g.setColour(baseColour);
            g.fillPath(outline);
            
            
            const int bs = 1;
            
            Path fill;
            fill.addRoundedRectangle (bs, bs, width-(bs *2), height - (bs * 2), cornerSize, cornerSize,
                                      ! (flatOnLeft  || flatOnTop),
                                      ! (flatOnRight || flatOnTop),
                                      ! (flatOnLeft  || flatOnBottom),
                                      ! (flatOnRight || flatOnBottom));
            
            if(isButtonDown) g.setColour(HAUTE_BLUE.withBrightness(0.6));
            else if(isMouseOverButton) g.setColour(HAUTE_BLUE.withBrightness(0.3));
            else g.setColour(Colours::black);
            
            g.fillPath(fill);
            
        }
    }
};


#endif /* CustomLookAndFeel_hpp */
