// MessageTest.cpp  -  Test the Message class

#include "UnitTest++.h"

#include "Message.h"

#include <iostream>

using namespace Yosokumo;



TEST(allMethodsForMessage)
{
    std::cout << "Message allMethodsForMessage" << '\n';

    // Default ctor

    Message mess0;
    
    CHECK_EQUAL(mess0.getText(), "");
    CHECK_EQUAL(mess0.getType(), Message::INFORMATION);

    // Information message

    std::string text1   = "This is an information message";
    Message::Type type1 = Message::INFORMATION;
    Message mess1(type1, text1);
    
    CHECK_EQUAL(mess1.getText(), text1);
    CHECK_EQUAL(mess1.getType(), type1);

    std::string expectedToString1 = 
        "Message:\n"
        "  type = 0\n"
        "  text = This is an information message\n";
    CHECK_EQUAL(mess1.toString(), expectedToString1);

    // Error message

    std::string text2   = "This is an error message";
    Message::Type type2 = Message::ERROR;
    Message mess2(type2, text2);
    
    CHECK_EQUAL(mess2.getText(), text2);
    CHECK_EQUAL(mess2.getType(), type2);

    std::string expectedToString2 = 
        "Message:\n"
        "  type = 1\n"
        "  text = This is an error message\n";
    CHECK_EQUAL(mess2.toString(), expectedToString2);

    // Setters

    Message mess3;

    std::string text3   = "This is another information message";
    Message::Type type3 = Message::INFORMATION;
    
    mess3.setText(text3);
    mess3.setType(type3);
    
    CHECK_EQUAL(mess3.getText(), text3);
    CHECK_EQUAL(mess3.getType(), type3);

    Message mess4;

    std::string text4   = "This is another error message";
    Message::Type type4 = Message::ERROR;
    
    mess4.setText(text4);
    mess4.setType(type4);
    
    CHECK_EQUAL(mess4.getText(), text4);
    CHECK_EQUAL(mess4.getType(), type4);

}

// end MessageTest.cpp
