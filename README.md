# XMiLog v0.9.1


**Xavier Michelon, 2008/06/24**

[https://github.com/xmichelo/XMiLog](https://github.com/xmichelo/XMiLog)

##What is XMiLog ?

XMiLog is a C++ library made of a single class that implement an application
log mechanism. Oriented toward simplicity and efficiency, the class offers to
opportunity to log the three types of events generally found in a log: simple
echos, warning and fatal errors.

The class offer the opportunity get a text or an XHTML 1.0 version of the log.
The HTML version can also be formatted using a user provided stylesheet.

Finally, the class offers a 'immediate write' mode, where the log event are 
written in a text file as soon as they are added, so that the log is not lost
if the application crashes.

##Usage

This library is made for use by software developers. This software has been
developed under :
* Microsoft Visual Studio 2008 for the Windows version (developed and tested
under Windows XP)
* Xcode 3.1 for the Mac OS X version (developed and tested under Mac OS X 
10.5, a.k.a Leopard)
Project files for those two development environments are provided. No Linux
port is available so far. Porting would be easy, only the time management
routine are platform-dependent. The platform-dependent code has been
isolated in a private implementation (pimpl) for the time management class
XMiTime.

##Documentation

No manual is provided with this software, but the source code is highly 
commented and an automatic documentation can be generated using [doxygen](http://www.stack.nl/~dimitri/doxygen/).
A test program for the library is also provided with this distribution.

## Copyright

This software is placed under the terms of the [GNU Library General Public
License version 2.1](http://www.gnu.org/licenses/old-licenses/lgpl-2.1.en.html). 
A copy of this license is provided in the file LGPL.txt
that is included in this distribution.

## Acknowledgements

Many thanks goes to [Ivan Vecerina](http://vecerina.com) for the code reviews and advice he provided 
during the development of this software.