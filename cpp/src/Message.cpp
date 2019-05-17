// Message.cpp

#include <sstream>

#include "Message.h"

using namespace Yosokumo;

// Constructors

Message::Message() :
    type(Message::INFORMATION),
    text("")
{}

Message::Message(Type type, const std::string &text) :
    type(type),
    text(text)
{}

// Getters (there are no setters)

std::string Message::getText() const
{
    return text;
}

Message::Type Message::getType() const
{
    return type;
}

void Message::setText(const std::string &text)
{
    this->text = text;
}

void Message::setType(Type type)
{
    this->type = type;
}

// Utility

std::string Message::toString() const
{
    std::stringstream s;

    s <<
        "Message:"               << "\n" <<
        "  type = " << getType() << "\n" <<
        "  text = " << getText() << "\n"
    ;

    return s.str();
}

// end Message.cpp
