/// \file 
/// \date 2005.01.28
/// \author Xavier Michelon
///
/// \brief Declaration of utility functions


#pragma once
#ifndef UTILS_H
#define UTILS_H


#include <string>
#include <sys/timeb.h>


std::string getTimeString(__timeb64 const& time);
std::string getCurrentTimeString();


#endif //#ifndef UTILS_H
