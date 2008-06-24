/// \file 
/// \date 2005.01.28
/// \author Xavier Michelon
///
/// \brief Declaration of log entry class


#ifdef WIN32
#include <windows.h>
#endif
#include "XMiLogEntry.h"


using namespace std;


namespace XMi {


const char *LogEntry::EntryTypeString[3] = { "Echo", "Warn", "Fatal"};


//************************************************************************************************
/// \brief Constructor
//************************************************************************************************
LogEntry::LogEntry(EntryType type, string const& message)
   : type_(type)
   , message_(message)
   , time_()
{
#if defined(WIN32) && defined(_DEBUG)
   OutputDebugStringA((getText() + "\n").c_str());
#endif
#if defined(MACOS) && defined(_DEBUG)
   printf((getText() + string("\n")).c_str());
#endif
}


//************************************************************************************************
/// \brief Copy constructor
//************************************************************************************************
LogEntry::LogEntry(LogEntry const& entry)
   : type_(entry.type_)
   , message_(entry.message_)
   , time_(entry.time_)
{
}


//************************************************************************************************
/// \brief Destructor
//************************************************************************************************
LogEntry::~LogEntry()
{
}


//************************************************************************************************
/// \brief 
//************************************************************************************************
LogEntry& LogEntry::operator=(LogEntry const& entry)
{
   type_ = entry.type_;
   message_ = entry.message_;
   time_ = entry.time_;
   return *this;
}


//************************************************************************************************
/// \brief Return the text for the log entry
//************************************************************************************************
string LogEntry::getText(bool showType, bool showTime) const
{
   string s = message_;
   if (showTime)
      s = time_.getString() + ": " + s;
   if (showType)
      s = string(EntryTypeString[type_]) + ": " + s;
   return  s;
}


//************************************************************************************************
/// \brief Return a string containing the log entry in HTML format
//************************************************************************************************
string LogEntry::getHTML(bool showType, bool showTime) const
{
   string s = "      <tr>";
   if (showType)
      s += "<td class=\"" + string(EntryTypeString[type_]) + "\">" + EntryTypeString[type_] + "</td>";
   if (showTime)
      s += "<td class=\"Time\">" + time_.getString() + "</td>";
   return s + "<td class=\"Text\">" + message_ + "</td></tr>";
}


} // namespace XMi
