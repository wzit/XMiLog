/// \file 
/// \date 2006.01.29
/// \author Xavier Michelon
/// 
/// \brief Implementation of time class


#include "XMiTime.h"
#ifdef MACOS
#include <sys/time.h>
#endif // #ifdef MACOS


using namespace std;


#ifdef MACOS
class XMiTime::pimpl {
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


//************************************************************************************************
/// \brief Constructor
//************************************************************************************************
XMiTime::XMiTime()
   : pimpl_(new pimpl)
{
}


//************************************************************************************************
/// \brief Copy constructor
//************************************************************************************************
XMiTime::XMiTime(XMiTime const& time)
   : pimpl_(new pimpl(*(time.pimpl_)))
{
}


//************************************************************************************************
/// \brief Destructor
//************************************************************************************************
XMiTime::~XMiTime()
{
   delete pimpl_;
}


//************************************************************************************************
/// \brief Assignment operator
//************************************************************************************************
XMiTime& XMiTime::operator=(XMiTime const& time)
{
   pimpl_ = time.pimpl_;
   return *this;
}


//************************************************************************************************
/// \brief return a string containing the date/time stored in the instance
//************************************************************************************************
std::string XMiTime::getString() const
{
   return pimpl_->getString();
}
