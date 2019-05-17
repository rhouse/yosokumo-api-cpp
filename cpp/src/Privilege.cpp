// Privilege.cpp

#include "Privilege.h"

using namespace Yosokumo;

Privilege::Privilege(int value)
{
    this->value = value;
}


int Privilege::getNumber() const
{
    return value;
}

std::string Privilege::getName() const
{
    switch (value)
    {
    case  1:  return "GET_STUDY"   ;
    case  2:  return "DELETE_STUDY";
    case  3:  return "GET_ROSTER"  ;
    case  4:  return "POST_ROSTER" ;
    case  5:  return "GET_ROLE"    ;
    case  6:  return "PUT_ROLE"    ;
    case  7:  return "DELETE_ROLE" ;
    case  8:  return "GET_PANEL"   ;
    case  9:  return "GET_CONTROL" ;
    case 10:  return "PUT_CONTROL" ;
    case 11:  return "POST_TABLE"  ;
    case 12:  return "GET_MODEL"   ;
    case 13:  return "POST_MODEL"  ;
    default:  return "***** UNDEFINE PRIVILEGE *****";
    }
}

Privilege::Type Privilege::valueOf(int value) 
{
    switch (value)
    {
    case  1:  return GET_STUDY   ;
    case  2:  return DELETE_STUDY;
    case  3:  return GET_ROSTER  ;
    case  4:  return POST_ROSTER ;
    case  5:  return GET_ROLE    ;
    case  6:  return PUT_ROLE    ;
    case  7:  return DELETE_ROLE ;
    case  8:  return GET_PANEL   ;
    case  9:  return GET_CONTROL ;
    case 10:  return PUT_CONTROL ;
    case 11:  return POST_TABLE  ;
    case 12:  return GET_MODEL   ;
    case 13:  return POST_MODEL  ;
    default:  return Type(0)     ;
    }
}

// end Privilege.cpp
