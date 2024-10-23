# goldsrc_src-master
My attempt to reverse engineer goldsrc engine source code 

Naming convention:

o C prefix - class,

o I prefix - interface,

o g_ - prefix for global variables,

Engine architecture:

o Engine is separated to server and client side.

o Almost every class is implementing some interface then expose a global variable for further using.
