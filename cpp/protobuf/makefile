# begin makefile to create C++ source code from a Google Protocol Buffer 
# description and compile the C++ 

include ../makefile.inc

.PHONY: all
all : compile

.PHONY: compile
compile : $(PROTO_OBJ_DIR)/yosokumo.pb.o 

$(PROTO_OBJ_DIR)/yosokumo.pb.o : $(PROTO_CPP_DIR)/yosokumo.pb.cc
	@rm -f $(PROTO_OBJ_DIR)/*.o
	@$(CXX) $(CXXFLAGS) -Wno-long-long -o $(PROTO_OBJ_DIR)/yosokumo.pb.o \
            -c $(PROTO_CPP_DIR)/yosokumo.pb.cc 
# Note the -Wno-long-long to suppress warnings about the C99 long long 
# values appearing in yosokumo.pb.cc.  We're using -std=c++98 and C99 
# long longs are not allowed in that standard.

$(PROTO_CPP_DIR)/yosokumo.pb.cc : $(PROTO_SRC_DIR)/yosokumo.proto
	@protoc -I=$(PROTO_SRC_DIR)       \
           --cpp_out=$(PROTO_CPP_DIR)  \
           $(PROTO_SRC_DIR)/yosokumo.proto

# clean gets rid of generated C++ files and object file

.PHONY: clean
clean :
	@rm -f $(PROTO_OBJ_DIR)/*.o
	@rm -f $(PROTO_CPP_DIR)/yosokumo.pb.*

# end makefile to create and compile yosokumo C++ code from GPB
