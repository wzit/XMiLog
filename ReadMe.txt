XMiLog v0.9
==========

Xavier Michelon, 2005/02/07

What is XMiLog ?
===============
XMiLog is a C++ library made of a single class that implement an application
log mechanism. Oriented toward simplicity and efficiency, the class offers to
opportunity to log the three types of events generally found in a log: simple
echos, warning and fatal errors.

The class offer the opportunity get a text or an XHTML 1.0 version of the log.
The HTML version can also be formatted using a user provided stylesheet.

Finally, the class offers a 'immediate write' mode, where the log event are 
written in a text file as soon as they are added, so that the log is not lost
if the application crashes.

Usage
=====
This library is made for use by software developers. This software has been
developed under the Microsoft Visual C++ .NET 2003 environment. A complete
solution for this environment is provided, including projects settings
for building the library and a test program. 
The library can be easily ported to other platforms. Only a few non-ANSI time
management routines need to be modified. However, no such port has yet been 
done and no makefile is provided.

Documentation
=============
No manual is provided with this software, but the source code is highly 
commented and an automatic documentation can be generated using
doxygen (http://www.stack.nl/~dimitri/doxygen/). This documentation
is avaiable online from the author's webpage (http://xmilog.x-mi.com).
A test program for the library is also provided with this distribution.

Copyright
=========
This software is placed under the terms of the GNU Library General Public
License version 2.1. A copy of this license is provided in the file LGPL.txt
that is included in this distribution.

Acknowledgements
================
Many thanks goes to Ivan Vecerina for the code reviews and advice he provided 
during the development of this software.
