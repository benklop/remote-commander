remote-commander
================

Remote Control for multiple devices over IR, RS-232 and network.

Designed to run on the Raspberry Pi and interface with a Samsung TV, Onkyo receiver, and a MythTV box,
but easily extensible to control other devices as well.

So far controlling a Samsung TV via serial, and controlling anything via LIRC / IR works well, using
the command line --command options.

Devices will need to be configured in the config file.

Macros work, and allow you to have a command from any device run multiple commands in sequence or in parallel. 
it is possible to have commands toggle through lists of commands, either to devices or other macros.

Network socket communication is possible as well, currently tested with netcat, but will eventually be used by outside clients as well.
