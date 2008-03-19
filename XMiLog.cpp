/// \file 
/// \date 2005.01.27
/// \author Xavier Michelon
///
/// \brief Implementation of Log class


#include "XMiLog.h"
#include <cstdio>

using namespace std;


namespace {
   const string htmlHeader1(
   "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n"
   "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
   "  <head>\n");

   const string htmlHeader2(
      "    <meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\" />\n"
      "    <style type=\"text/css\">\n"
   );

   const string defaultStyleSheet(
      "      body {font-family: \"Verdana\",\"Helvetica\", sans-serif; font-size: 70%%;}\n"
      "      table.log {width: 100%%;border: solid 1px #999999;}\n"
      "      table.log td { padding-left: 5px; padding-right: 5px;}\n"
      "      .title  {color: black;text-align: center;font-size: 100%%;font-weight:bold;margin-bottom: 15px;}\n"
      "      td.Echo {color: white;background-color: #73C840;white-space: nowrap;}\n"
      "      td.Warn {color: white;background-color: #FF9600;white-space: nowrap;}\n"
      "      td.Fatal{color: white;background-color: #FF1800;white-space: nowrap;}\n"
      "      td.Time {color: black;background-color: #dddddd;white-space: nowrap;}\n"
      "      td.Text {color: black;background-color: #eeeeee;width: 80%%;}\n"
      "      .footer {width: 100%%;font-size: 90%%; text-align: right; font-style: italic;}\n"
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
}


namespace XMi {


//************************************************************************************************
/// \brief Constructor. 
/// 
/// If writeImmediately is set to true (default), log is written to logfile as soon as entry are 
/// created. This will ensure the log is not lost if the application crash, but due to file I/O 
/// routines, turning this feature on can have a significant cost. If the immediate log file 
/// can't be created, the user will not be warned, but the standard loggin feature will continue
/// normally.
//************************************************************************************************
Log::Log(bool writeImmediately, const char *logfile)
   : writeImmediately_(writeImmediately)
   , fp_(00)
{

   if (writeImmediately_)
#ifdef MACOS
      if (!(fp_ = fopen(logfile, "w")))
#endif
#ifdef WIN32
      if (fopen_s(&fp_, logfile, "w"))
#endif
         writeImmediately_ = false;
}


//************************************************************************************************
/// \brief Destructor
//************************************************************************************************
Log::~Log()
{
   if (writeImmediately_ && (!!fp_))
      fclose(fp_);
}

//************************************************************************************************
/// \brief Add an 'echo' message to the log
//************************************************************************************************
void Log::echo( string const& text)
{
   LogEntry entry(LogEntry::etEcho, text);
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
void Log::warn( string const& text)
{
   LogEntry entry(LogEntry::etWarn, text);
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
void Log::fatal(string const& text)
{
   LogEntry entry(LogEntry::etFatal, text);
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
string Log::getTextLog(bool showType, bool showTime, const char *title) const
{
   string s;
   if (title)
   s += string(title) +"\n";
   for (vector<LogEntry>::const_iterator iter = entries_.begin();iter != entries_.end(); iter++)
      s += (*iter).getText(showType, showTime) + "\n";
   return s;
}


//************************************************************************************************
/// \brief Return a string containing the log in html format
//************************************************************************************************
string Log::getHTMLLog(bool showType, bool showTime, const char *title) const
{
   return _getHTMLLog(defaultStyleSheet, showType, showTime, title);
}


//************************************************************************************************
/// \brief Return a string containing the log in html format with a specified stylesheet
//************************************************************************************************
string Log::getHTMLLog(string const& styleSheet, bool showType, bool showTime, 
                          const char *title) const
{
   return _getHTMLLog(styleSheet, showType, showTime, title);
}

//************************************************************************************************
/// \brief return the html log. Internal function to avoid code replication.
//************************************************************************************************
string Log::_getHTMLLog(string const& styleSheet,bool showType, bool showTime, 
                           const char *title) const
{
   TimeStamp now;
   string s = htmlHeader1;
   if (title)
      s += string("<title>") + title + "</title>\n";
   s += htmlHeader2 + styleSheet + htmlHeader3;
   if (title)
      s += string("<div class=\"title\">") + title + "</div>\n";
   s += "    <table class=\"log\">\n";
   for (vector<LogEntry>::const_iterator iter = entries_.begin(); iter != entries_.end(); iter++)
      s += (*iter).getHTML(showType, showTime) + "\n";
   return  s + "    </table>"
             + "<div class=\"footer\">Generated on " + now.getString() + "</div>\n"
             + htmlFooter;
}


//************************************************************************************************
/// \brief reset the log (remove all entries)
//************************************************************************************************
void Log::reset()
{
   entries_.clear();
}


//************************************************************************************************
/// \brief Write an entry to the immediate log
//************************************************************************************************
void Log::writeEntryImmediately(LogEntry const& entry) const
{
   if (writeImmediately_ && (!!fp_))
   {
      fputs((entry.getText() + "\n").c_str(), fp_);
      fflush(fp_);
   }
}


} // namespace XMi
