/// \file 
/// \date 2005.01.27
/// \author Xavier Michelon
///
/// \brief Declaration of Log class


#pragma once
#ifndef XMI_LOG_H
#define XMI_LOG_H


#include "XMiLogEntry.h"
#include <vector>
#include <string>


namespace XMi {


//************************************************************************************************
/// \brief Log class
//************************************************************************************************
class Log {
public:
   Log(bool writeImmediately = true, const char *logfile = "log.txt");
   ~Log();
   void echo( std::string const& text);
   void warn( std::string const& text);
   void fatal(std::string const& text);
   std::string getTextLog(bool showType = true, bool showTime = true, const char *title = 00) const;
   std::string getHTMLLog(bool showType = true, bool showTime = true, const char *title = 00) const;
   std::string getHTMLLog(std::string const& styleSheet, bool showType = true, 
                          bool showTime = true, const char *title = 00) const;
   void reset();
   std::vector<LogEntry> entries_;
private:
   void writeEntryImmediately(LogEntry const& entry) const;
   std::string _getHTMLLog(std::string const& styleSheet, bool showType, bool showTime,
                           const char *title) const;
   bool writeImmediately_;
   FILE *fp_;
};


} // namespace XMi


#endif //#ifndef XMI_LOG_H
