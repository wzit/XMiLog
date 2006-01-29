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


const char *XMiLogEntry::EntryTypeString[3] = { "Echo", "Warn", "Fatal"};


//************************************************************************************************
/// \brief Constructor
//************************************************************************************************
XMiLogEntry::XMiLogEntry(EntryType type, string const& message)
   : type_(type)
   , message_(message)
   , time_()
{
#if  defined(WIN32) && defined(_DEBUG)
   OutputDebugString((getText() + "\n").c_str());
#endif
}


//************************************************************************************************
/// \brief Copy constructor
//************************************************************************************************
XMiLogEntry::XMiLogEntry(XMiLogEntry const& entry)
   : type_(entry.type_)
   , message_(entry.message_)
   , time_(entry.time_)
{
}


//************************************************************************************************
/// \brief Destructor
//************************************************************************************************
XMiLogEntry::~XMiLogEntry()
{
}


//************************************************************************************************
/// \brief 
//************************************************************************************************
XMiLogEntry& XMiLogEntry::operator=(XMiLogEntry const& entry)
{
   type_ = entry.type_;
   message_ = entry.message_;
   time_ = entry.time_;
   return *this;
}


//************************************************************************************************
/// \brief Return the text for the log entry
//************************************************************************************************
string XMiLogEntry::getText(bool showType, bool showTime) const
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
string XMiLogEntry::getHTML(bool showType, bool showTime) const
{
   string s = "      <tr>";
   if (showType)
      s += "<td class=\"" + string(EntryTypeString[type_]) + "\">" + EntryTypeString[type_] + "</td>";
   if (showTime)
      s += "<td class=\"Time\">" + time_.getString() + "</td>";
   return s + "<td class=\"Text\">" + message_ + "</td></tr>";
}


