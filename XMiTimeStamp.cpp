/// \file 
/// \date 2006.01.29
/// \author Xavier Michelon
/// 
/// \brief Implementation of time class


#include "XMiTimeStamp.h"
#ifdef MACOS
#include <sys/time.h>
#endif // #ifdef MACOS
#ifdef WIN32
#include <sys/timeb.h>
#include <ctime>
#endif


using namespace std;


namespace XMi {


#ifdef MACOS
//************************************************************************************************
/// \brief The platform dependant private implementation of the low level time management 
/// functions
//************************************************************************************************
class TimeStamp::pimpl {
public:
   pimpl() { gettimeofday(&tp_, 00); }
   pimpl(pimpl const& p) : tp_(p.tp_) {}
   pimpl& operator=(pimpl const& p) { tp_ = p.tp_; return *this; }
   ~pimpl() {}
   string getString() 
   { 
      char buffer[200];
      char ms[10];
      struct tm t;
      localtime_r(&tp_.tv_sec, &t);
      strftime(buffer, 200, "%Y.%m.%d %H:%M:%S.", &t);
      sprintf(ms, "%03d", int(tp_.tv_usec / 1000.0f)); 
      return string(buffer) + string(ms); 
   }
private:
   struct timeval tp_;
};
#endif


#ifdef WIN32
//************************************************************************************************
/// \brief The platform dependant private implementation of the low level time management 
/// functions
//************************************************************************************************
class TimeStamp::pimpl {
public:
   pimpl() { _ftime64_s(&time_); }
   pimpl(pimpl const& p) { time_ = p.time_; }
   pimpl& operator=(pimpl const& p) { time_ = p.time_; return *this; }
   ~pimpl() {}
   string getString()
   {
      const int timeBufferLen = 1024;
      char timestr[timeBufferLen];
      char buffer[timeBufferLen];
      struct tm t;
      _localtime64_s(&t, &time_.time);
      std::strftime(timestr, timeBufferLen, "%Y.%m.%d %H:%M:%S", &t);
      _snprintf_s(buffer, timeBufferLen, "%s.%d", timestr, time_.millitm);
      return buffer;
   }
private:
   __timeb64 time_;
};
#endif


//************************************************************************************************
/// \brief Constructor
//************************************************************************************************
TimeStamp::TimeStamp()
   : pimpl_(new pimpl)
{
}


//************************************************************************************************
/// \brief Copy constructor
//************************************************************************************************
TimeStamp::TimeStamp(TimeStamp const& time)
   : pimpl_(new pimpl(*(time.pimpl_)))
{
}


//************************************************************************************************
/// \brief Destructor
//************************************************************************************************
TimeStamp::~TimeStamp()
{
   delete pimpl_;
}


//************************************************************************************************
/// \brief Assignment operator
//************************************************************************************************
TimeStamp& TimeStamp::operator=(TimeStamp const& time)
{
   pimpl_ = time.pimpl_;
   return *this;
}


//************************************************************************************************
/// \brief return a string containing the date/time stored in the instance
//************************************************************************************************
std::string TimeStamp::getString() const
{
   return pimpl_->getString();
}


} // namespace XMi
