remote-commander
================

Remote Control for multiple devices over IR, RS-232 and network.

Designed to run on the Raspberry Pi and interface with a Samsung TV, Onkyo receiver, and a MythTV box,
but easily extensible to control other devices as well.

So far controlling a Samsung TV via serial, and controlling anything via LIRC / IR works well, using
the command line --command options.

Devices will need to be configured in the config file.

Parsing of macros is not yet working, and control of mythTV is not yet tested. network and LIRC control
of Remote Commander is not yet functional.
