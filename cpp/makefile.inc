# makefile.inc for yosokumo C++ api

# The yosokumo C++ library is in ??? FIX THIS COMMENT
#
#       $(YOSOKUMO_DIR)/lib

YOSOKUMO_DIR   = /home/roger/yosokumo/cpp

SRC_DIR  = $(YOSOKUMO_DIR)/src
OBJ_DIR  = $(YOSOKUMO_DIR)/obj
TEST_DIR = $(OBJ_DIR)/test
LIB_DIR  = $(YOSOKUMO_DIR)/lib

###JAR_DIR             = $(YOSOKUMO_DIR)/jar
DOXYGEN_DIR         = $(YOSOKUMO_DIR)/doxygen
###DOXYGEN_PRIVATE_DIR = $(YOSOKUMO_DIR)/javadoc-private

PROTO_SRC_DIR       = $(YOSOKUMO_DIR)/protobuf
###??? Need to install latest Google protocol buffer stuff and fix this:
###PROTO_INC_DIR       = /home/roger/tests/gpb/protobuf-2.3.0/src
PROTO_CPP_DIR       = $(YOSOKUMO_DIR)/protobuf/cpp
PROTO_OBJ_DIR       = $(YOSOKUMO_DIR)/obj/protobuf
###PROTO_SERVICE_DIR   = $(YOSOKUMO_DIR)/com/yosokumo/core/protobuf
###PROTO_CLASS_ONLY    = com/yosokumo/core/protobuf

###GOOGLE_PROTOBUF_JAR = /usr/share/java/protobuf.jar

###HTTP_DIR = /home/roger/OpenSourceCode/HttpClient/httpcomponents-client-4.0.1/lib
###HTTP_PATH := $(HTTP_DIR)/httpcore.jar
###HTTP_PATH := $(HTTP_PATH):$(HTTP_DIR)/httpclient.jar
####HTTP_PATH := $(HTTP_PATH):$(HTTP_DIR)/commons-codec.jar
###HTTP_PATH := $(HTTP_PATH):$(HTTP_DIR)/commons-logging.jar

###JUNIT_JAR = /usr/share/java/junit4.jar

CXX = g++
CXXFLAGS = -std=c++98 -pedantic -Wall -Werror -g
# The -g flag used above produces debug info - this is needed for valgrind

UNITTEST_DIR = /home/roger/OpenSourceCode/unittest++/UnitTest++
UNITTEST_INC = $(UNITTEST_DIR)/src

OPENSSL_DIR = /usr/local/ssl

# end makefile.inc
