# goldsrc_src-master
My attempt to reverse engineer goldsrc engine source code 

Naming convention:
C prefix - class,
I prefix - interface,
g_ - prefix for global variables,

Engine architecture:
Engine is separated to server and client side.
Almost every class is implementing some interface then expose a global variable for further using.
