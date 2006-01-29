/// \file 
/// \date 2005.01.28
/// \author Xavier Michelon
///
/// \brief Implementation of log entry class


#pragma once
#ifndef XMI_LOG_ENTRY_H
#define XMI_LOG_ENTRY_H


#include "XMiTime.h"
#include <string>



//************************************************************************************************
/// \brief XMiLog entry class to store log entry data
//************************************************************************************************
class XMiLogEntry {
public:
   enum EntryType { etEcho = 0, etWarn , etFatal };
   static const char *EntryTypeString[3];
   XMiLogEntry(EntryType type, std::string const& message);
   XMiLogEntry(XMiLogEntry const&);
   ~XMiLogEntry();
   XMiLogEntry& operator=(XMiLogEntry const& entry);
   std::string getText(bool showType = true, bool showTime = true) const;
   std::string getHTML(bool showType = true, bool showTime = true) const;
private:
   EntryType type_;                 
   std::string message_;
   XMiTime time_;
};


#endif //#ifndef XMI_LOG_ENTRY_H