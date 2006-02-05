/// \file 
/// \date 2006.01.29
/// \author Xavier Michelon
/// 
/// \brief Implementation of time class


#pragma once
#ifndef XMI_TIME_STAMP_H
#define XMI_TIME_STAMP_H


#include <string>


namespace XMi {


//************************************************************************************************
/// \brief a class for holding a time/date 
//************************************************************************************************
class TimeStamp
{
public:
   TimeStamp();
   TimeStamp(TimeStamp const& time);
   TimeStamp& operator=(TimeStamp const& time);
   ~TimeStamp();
   std::string getString() const;
private:
   class pimpl;
   pimpl *pimpl_;
};


} // namespace XMi


#endif // #ifndef XMI_TIME_STAMP_H
