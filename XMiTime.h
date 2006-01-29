/// \file 
/// \date 2006.01.29
/// \author Xavier Michelon
/// 
/// \brief Implementation of time class


#pragma once
#ifndef XMI_TIME_H
#define XMI_TIME_H


#include <string>


//************************************************************************************************
/// \brief a class for holding a time/date 
//************************************************************************************************
class XMiTime
{
public:
   XMiTime();
   XMiTime(XMiTime const& time);
   XMiTime& operator=(XMiTime const& time);
   ~XMiTime();
   std::string getString() const;
private:
   class pimpl;
   pimpl *pimpl_;
};


#endif // #ifndef XMI_TIME_H
