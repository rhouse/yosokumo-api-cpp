// TestYosokumo.cpp  --  Run UnitTest++ tests of Yosokumo

#include <UnitTest++.h>
#include "yosokumo.pb.h"

int main()
{
    // Make sure the Google protocol buffer library version agrees with 
    // the version of the header files we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    int retval = UnitTest::RunAllTests();

    // Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return retval;
}

//  end TestYosokumo.cpp
