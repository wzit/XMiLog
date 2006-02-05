/// \file 
/// \date 2005.01.28
/// \author Xavier Michelon
///
/// \brief Implementation of log entry class


#pragma once
#ifndef XMI_LOG_ENTRY_H
#define XMI_LOG_ENTRY_H


#include "XMiTimeStamp.h"
#include <string>


namespace XMi {


//************************************************************************************************
/// \brief Log entry class to store log entry data
//************************************************************************************************
class LogEntry {
public:
   enum EntryType { etEcho = 0, etWarn , etFatal };
   static const char *EntryTypeString[3];
   LogEntry(EntryType type, std::string const& message);
   LogEntry(LogEntry const&);
   ~LogEntry();
   LogEntry& operator=(LogEntry const& entry);
   std::string getText(bool showType = true, bool showTime = true) const;
   std::string getHTML(bool showType = true, bool showTime = true) const;
private:
   EntryType type_;        ///< Log entry type
   std::string message_;   ///< Message held by the entry
   TimeStamp time_;        ///< Time stamp for the entry
};


} // namespace XMi


#endif //#ifndef XMI_LOG_ENTRY_H