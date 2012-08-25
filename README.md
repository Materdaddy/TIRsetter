TIR DMX Address Setter
======================
This is a sketch I threw together for Arduino folks to set the DMX addresses on their TIR Systems Destiny CG Lights recently obtained by rfallatt and sold to the members of DIYC.

I take no credit for the work here.  This is due to the work of the following (in alphabetical order):
- airsouth
- chelmuth
- jklingert
- lightman
- mschell
- RavingLunatic
- rfallatt

I simply took what they found and wrote a simple DMX sender for arduino.

This is untested at this point.

The DMX code I based this off of came from here:
http://arduino.cc/playground/Learning/DMXSerial

The thread with all the information on this special DMX data is here:
http://doityourselfchristmas.com/forums/showthread.php?21586-Initializer-Program-for-TIR-Systems-Destiny-CG-Lights-Commercial-LED-Spots&p=220032#post220032

Usage
=====
Edit the ".ino" file in the arduino IDE and upload.  The values you'll need to chagne are on lines 6 and 7.

Change the value on line 6 to your serial number (without the dash)
Change the value on line 7 to the red channel DMX value you wish to be your starting address

PM Materdaddy on DIYC or post in this thread if you test this and it works, or if there's a problem:
http://doityourselfchristmas.com/forums/showthread.php?21586-Initializer-Program-for-TIR-Systems-Destiny-CG-Lights-Commercial-LED-Spots
