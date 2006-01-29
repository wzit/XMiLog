/// \file 
/// \date 2005.01.27
/// \author Xavier Michelon
///
/// \brief Implementation of XMiLog class


#include "XMiLog.h"
#include "Utils.h"
#include <cstdio>

using namespace std;


const string htmlHeader1(
"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n"
"<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
"  <head>\n");

const string htmlHeader2(
   "    <meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\" />\n"
   "    <style type=\"text/css\">\n"
);

const string defaultStyleSheet(
   "      body {font-family: \"Trebuchet MS\",\"Arial\",\"Verdana\",\"Helvetica\", sans-serif; font-size: 75%;}\n"
   "      table.log {width: 100%;border: solid 1px #999999;}\n"
   "      table.log td { padding-left: 5px; padding-right: 5px;}\n"
   "      .title  {color: black;text-align: center;font-size: 200%;font-weight:bold;margin-bottom: 15px;}\n"
   "      td.Echo {color: white;background-color: #73C840;white-space: nowrap;}\n"
   "      td.Warn {color: white;background-color: #FF9600;white-space: nowrap;}\n"
   "      td.Fatal{color: white;background-color: #FF1800;white-space: nowrap;}\n"
   "      td.Time {color: black;background-color: #dddddd;white-space: nowrap;}\n"
   "      td.Text {color: black;background-color: #eeeeee;width: 100%;}\n"
   "      .footer {width: 100%;font-size: 90%; text-align: right; font-style: italic;}\n"
);

const string htmlHeader3(
   "    </style>\n"
   "  </head>\n"
   "  <body>\n"
);

const string htmlFooter(
   "  </body>\n"
   "</html>\n"
);


//************************************************************************************************
/// \brief Constructor. 
/// 
/// If writeImmediately is set to true (default), log is written to logfile as soon as entry are 
/// created. This will ensure the log is not lost if the application crash, but due to file I/O 
/// routines, turning this feature on can have a significant cost. If the immediate log file 
/// can't be created, the user will not be warned, but the standard loggin feature will continue
/// normally.
//************************************************************************************************
XMiLog::XMiLog(bool writeImmediately, const char *logfile)
   : writeImmediately_(writeImmediately)
   , fp_(00)
{

   if (writeImmediately_)
      if (!(fp_ = fopen(logfile, "w")))
         writeImmediately_ = false;
}


//************************************************************************************************
/// \brief Destructor
//************************************************************************************************
XMiLog::~XMiLog()
{
   if (writeImmediately_ && (!!fp_))
      fclose(fp_);
}

//************************************************************************************************
/// \brief Add an 'echo' message to the log
//************************************************************************************************
void XMiLog::echo( string const& text)
{
   XMiLogEntry entry(XMiLogEntry::etEcho, text);
   entries_.push_back(entry);
   if (writeImmediately_ && (!!fp_))
   {
      fputs((entry.getText() + "\n").c_str(), fp_);
      // force log to be written to file to ensure maximum number of items are written if app crashes
      fflush(fp_); 
   }
}


//************************************************************************************************
/// \brief Add a warning message to the log
//************************************************************************************************
void XMiLog::warn( string const& text)
{
   XMiLogEntry entry(XMiLogEntry::etWarn, text);
   entries_.push_back(entry);
   if (writeImmediately_ && (!!fp_))
   {
      fputs((entry.getText() + "\n").c_str(), fp_);
      fflush(fp_);
   }
}


//************************************************************************************************
/// \brief add a fatal message to the log
//************************************************************************************************
void XMiLog::fatal(string const& text)
{
   XMiLogEntry entry(XMiLogEntry::etFatal, text);
   entries_.push_back(entry);
   if (writeImmediately_ && (!!fp_))
   {
      fputs((entry.getText() + "\n").c_str(), fp_);
      fflush(fp_);
   }
}


//************************************************************************************************
/// \brief return a string containing the full log in text format
//************************************************************************************************
string XMiLog::getTextLog(bool showType, bool showTime, const char *title) const
{
   string s;
   if (title)
   s += string(title) +"\n";
   for (vector<XMiLogEntry const>::const_iterator iter = entries_.begin();iter < entries_.end(); 
        iter++)
      s += (*iter).getText(showType, showTime) + "\n";
   return s;
}


//************************************************************************************************
/// \brief Return a string containing the log in html format
//************************************************************************************************
string XMiLog::getHTMLLog(bool showType, bool showTime, const char *title) const
{
   return _getHTMLLog(defaultStyleSheet, showType, showTime, title);
}


//************************************************************************************************
/// \brief Return a string containing the log in html format with a specified stylesheet
//************************************************************************************************
string XMiLog::getHTMLLog(string const& styleSheet, bool showType, bool showTime, 
                          const char *title) const
{
   return _getHTMLLog(styleSheet, showType, showTime, title);
}

//************************************************************************************************
/// \brief return the html log. Internal function to avoid code replication.
//************************************************************************************************
string XMiLog::_getHTMLLog(string const& styleSheet,bool showType, bool showTime, 
                           const char *title) const
{
   string s = htmlHeader1;
   if (title)
      s += string("<title>") + title + "</title>\n";
   s += htmlHeader2 + styleSheet + htmlHeader3;
   if (title)
      s += string("<div class=\"title\">") + title + "</div>\n";
   s += "    <table class=\"log\">\n";
   for (vector<XMiLogEntry const>::const_iterator iter = entries_.begin(); iter < entries_.end(); iter++)
      s += (*iter).getHTML(showType, showTime) + "\n";
   return  s + "    </table>"
             + "<div class=\"footer\">Generated on " + getCurrentTimeString() + "</div>\n" 
             + htmlFooter;
}


//************************************************************************************************
/// \brief reset the log (remove all entries)
//************************************************************************************************
void XMiLog::reset()
{
   entries_.clear();
}


//************************************************************************************************
/// \brief Write an entry to the immediate log
//************************************************************************************************
void XMiLog::writeEntryImmediately(XMiLogEntry const& entry) const
{
   if (writeImmediately_ && (!!fp_))
   {
      fputs((entry.getText() + "\n").c_str(), fp_);
      fflush(fp_);
   }
}