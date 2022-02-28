/* 
 * Daniel Viksporre 2022-02-28 - (28 feb 2022)
 * ***************************************************************
 * A Linux demo example of a ALSA RawMIDI out in C code.
 * The purpose is to get you started programming RawMIDI out code.
 * ***************************************************************
 * Licence type: MIT No Attribution
 *
 * dependencies for compilation (please report missing dependencies to list):
 *	sudo apt-get install libasound2-dev
 * 
 * compile with: 
 *	gcc -o rawmidi_out rawmidi_out.c -lasound
 *
 * start program in a terminal with a virtual rawmidi port: 
 * (no hardware neaded use a command like aconnectgui to connect to a virtual synth like for example qsynth)
 *	./rawmidi_out
 *
 * start program with connection to a real rawmidi port. Exchange hw:4,2 with uniqe port (run amidi -l if you don't know) 
 *	./rawmidi_out hw:4,2
 *
 * How to find the correct name of your RawMIDI out port:
 *	run the following terminal command to find ports to connect to
 *	amidi -l
 *	
 * how to use program:
 * 	Start program in terminal it will give a virtual RawMIDI out unit.
 *	To connect to a read hardware out port specify the name of the port
 *	with a command line option of the hardware port name directly after
 * 	the program name.
 *	When ready press return for the first note.
 *	Press return again for sending note off message.
 *	Press return again to close the program.
 *
 * help wanted:
 * 	* corrections and improvements of code comments, that improves understanding.
 *	* more complete listing of dependencies	
 */

#include <alsa/asoundlib.h>     /* Interface to the ALSA system */

// wait function for pressing ENTER on computer keyboard
void wait_for_return_key(void){ // Function has nothing to do with ALSA
		fflush(stdin);
		getchar(); // wait for pressing ENTER on computer keyboard
}

int main(int argc, char *argv[]) {
	snd_rawmidi_t *out_handle = 0;
	unsigned char ch; // temporary variable for more readable code
	int err; // for error handling

	const char* portname = "virtual"; // to create a virtual port if no one is specified in the terminal as an command option.
	if ((argc > 1) && (strncmp("hw:", argv[1], 3) == 0)) {
	      portname = argv[1]; // replace the string "virtual" to the one written in the terminal as a command option.
	}
	
	// Create a virtual ALSA RawMIDI out
        err = snd_rawmidi_open(NULL,&out_handle,portname,SND_RAWMIDI_SYNC);
        if(err) fprintf(stderr,"snd_rawmidi_open %s failed: %d\n",portname,err); // error handling

	// Wait for a incomming computer keyboard event. Then send MIDI message after that.
	printf("Press [Enter] key to play note\n"); wait_for_return_key();

	// send Note-on		
	ch=0x90; snd_rawmidi_write(out_handle,&ch,1); // Note-on
	ch=60;   snd_rawmidi_write(out_handle,&ch,1); // note
	ch=100;  snd_rawmidi_write(out_handle,&ch,1); // velocity
	snd_rawmidi_drain(out_handle);

	// Wait for a incomming computer keyboard event. Then send MIDI message after that.
	printf("Press [Enter] key to end note\n"); wait_for_return_key();
	
	// send note-off
	ch=0x80; snd_rawmidi_write(out_handle,&ch,1); // Note-off
	ch=60;   snd_rawmidi_write(out_handle,&ch,1); // Note
	ch=0;    snd_rawmidi_write(out_handle,&ch,1); // Velocity
	snd_rawmidi_drain(out_handle); 

	// Wait for a incomming computer keyboard event. Then end program after that.
	printf("Press [Enter] key to exit\n"); wait_for_return_key();
	
	// Close down and make a clean exit
	snd_rawmidi_drain(out_handle); // Waits until all MIDI bytes in the rawmidi I/O ring buffer are drained (sent) to the hardware device.
	snd_rawmidi_close(out_handle); // Closes the specified RawMidi handle and frees all associated resources. 
	
}

/*
MIT No Attribution
Copyright <2022> <Daniel Viksporre>
Permission is hereby granted, free of charge, to any person obtaining a copy of this
software and associated documentation files (the "Software"), to deal in the Software
without restriction, including without limitation the rights to use, copy, modify,
merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

