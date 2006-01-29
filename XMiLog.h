/// \file 
/// \date 2005.01.27
/// \author Xavier Michelon
///
/// \brief Implementation of XMiLog class


#pragma once
#ifndef XMI_LOG_H
#define XMI_LOG_H


#include "XMiLogEntry.h"
#include <vector>
#include <string>


//************************************************************************************************
/// \brief XMiLog class
//************************************************************************************************
class XMiLog {
public:
   XMiLog(bool writeImmediately = true, const char *logfile = "log.txt");
   ~XMiLog();
   void echo( std::string const& text);
   void warn( std::string const& text);
   void fatal(std::string const& text);
   std::string getTextLog(bool showType = true, bool showTime = true, const char *title = 00) const;
   std::string getHTMLLog(bool showType = true, bool showTime = true, const char *title = 00) const;
   std::string getHTMLLog(std::string const& styleSheet, bool showType = true, 
                          bool showTime = true, const char *title = 00) const;
   void reset();
   std::vector<XMiLogEntry> entries_;
private:
   void writeEntryImmediately(XMiLogEntry const& entry) const;
   std::string _getHTMLLog(std::string const& styleSheet, bool showType, bool showTime,
                           const char *title) const;
   bool writeImmediately_;
   FILE *fp_;
};


#endif //#ifndef XMI_LOG_H
