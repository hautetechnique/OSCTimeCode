# Binary

Included is a C++ example that allows you to send and recieve OSCTimecode over ethernet.

# Installation

This example is written in Juce, C++ and tested for Mac and Windows.

**Structure**

OSC messages are structured like so:

|*Type*   	| *String*		| *Format*								   	|
|-----------|---------------|-------------------------------------------|
|*Address*  | /TC1/time/30	| / {TimeCode layer} / time / {Frames per second} 	| 
|*Argument* | 00:00:00:00	| HH:MM:SS:FF								|

The layer can be TC1 or TC2, representing TimeCode 1 or TimeCode 2
 
**Screenshots**

*Sender*

![Sender](/Screenshots/screenshot-sender.png?raw=true "Sender")

*Receiver*

![Receiver](/Screenshots/screenshot-receiver.png?raw=true "Receiver")

# References

- [OSC wiki](https://en.wikipedia.org/wiki/Open_Sound_Control)
- [TimeCode Live software](https://www.blckbook.nl) 
- [Juce](https://www.juce.com)
