# alsa-rawmidi-out-example
Simple Linux example code in C for ALSA RawMIDI out. To connect to MIDI hardware, or software if the default to create a virtual RawMIDI port is used.

### dependencies for compilation (please report missing dependencies to list):
	sudo apt-get install libasound2-dev
 
### compile with: 
	gcc -o rawmidi_out rawmidi_out.c -lasound

### start program in a terminal with a virtual rawmidi port: 
(no hardware neaded use a command like aconnectgui to connect to a virtual synth like for example qsynth)
	./rawmidi_out

### start program with connection to a real rawmidi port. Exchange hw:4,2 with uniqe port (run amidi -l if you don't know) 
	./rawmidi_out hw:4,2

## How to find the correct name of your RawMIDI out port:
	run the following terminal command to find ports to connect to
	amidi -l
	
## how to use program:
 	Start program in terminal it will give a virtual RawMIDI out unit.
	To connect to a read hardware out port specify the name of the port
	with a command line option of the hardware port name directly after
 	the program name.
	When ready press return for the first note.
	Press return again for sending note off message.
	Press return again to close the program.

### help wanted:
 	* corrections and improvements of code comments, that improves understanding.
	* more complete listing of dependencies	



