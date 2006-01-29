/// \file 
/// \date 2005.01.28
/// \author Xavier Michelon
///
/// \brief Implementation of utility functions


#include "Utils.h"
#include <ctime>

static const int timeBufferLen = 512;


//************************************************************************************************
/// \brief Return a string containing the time described in the time structure given as a 
/// parameter
//************************************************************************************************
std::string getTimeString(__timeb64 const& time)
{
   char timestr[timeBufferLen];
   char buffer[timeBufferLen];
   std::strftime(timestr, timeBufferLen, "%Y.%m.%d %H:%M:%S", _localtime64(&time.time));
   _snprintf(buffer, timeBufferLen, "%s.%d", timestr, time.millitm);
   return buffer;
}


//************************************************************************************************
/// \brief return a string containing the current time
//************************************************************************************************
std::string getCurrentTimeString()
{
   __timeb64 time;
   _ftime64(&time);
   return getTimeString(time);
}
