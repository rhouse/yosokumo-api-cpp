# begin makefile to compile yosokumo C++ code for unit tests and other tests

include ../makefile.inc

INC = -I$(UNITTEST_INC) -I$(SRC_DIR)

OBJ_TEST_FILES =                             \
         $(TEST_DIR)/Base64Test.o            \
         $(TEST_DIR)/BlockTest.o             \
         $(TEST_DIR)/CatalogTest.o           \
         $(TEST_DIR)/CredentialsTest.o       \
         $(TEST_DIR)/DigestRequestTest.o     \
         $(TEST_DIR)/MessageTest.o           \
         $(TEST_DIR)/PanelTest.o             \
         $(TEST_DIR)/PredictorTest.o         \
         $(TEST_DIR)/PrivilegeTest.o         \
         $(TEST_DIR)/RoleTest.o              \
         $(TEST_DIR)/RosterTest.o            \
         $(TEST_DIR)/ServiceExceptionTest.o  \
         $(TEST_DIR)/SpecimenTest.o          \
         $(TEST_DIR)/StudyTest.o             \
         $(TEST_DIR)/TestYosokumo.o          \
         $(TEST_DIR)/ValueTest.o             \
         $(TEST_DIR)/YosokumoProtobufTest.o  \
         $(TEST_DIR)/YosokumoRequestTest.o


.PHONY: all
all : create-cpp-files compile link

.PHONY: create-cpp-files
create-cpp-files:
	@cd ws-cpp; $(MAKE) $(MFLAGS)   # make all the test source files

.PHONY: compile
compile: $(OBJ_TEST_FILES)

$(TEST_DIR)/Base64Test.o : Base64Test.cpp $(SRC_DIR)/Base64.h
	$(CXX) $(CXXFLAGS) $(INC) -o $(TEST_DIR)/Base64Test.o \
        -DBUFFERSIZE=1024 \
        -I/home/roger/OpenSourceCode/base64/libb64-1.2/include/b64 \
        -c Base64Test.cpp
# Note that the -D, -I, and -L options above are needed so we can use some
# open source code implementing libb64 so we can compare our base64 encoding
# and decoding with an independent source.  (Moved -L to link step above.)

$(TEST_DIR)/BlockTest.o : BlockTest.cpp $(SRC_DIR)/Block.h                    \
    $(SRC_DIR)/Cell.h  $(SRC_DIR)/CellBlock.h  $(SRC_DIR)/EmptyBlock.h        \
    $(SRC_DIR)/Predictor.h $(SRC_DIR)/PredictorBlock.h  $(SRC_DIR)/RealValue.h\
    $(SRC_DIR)/Specimen.h $(SRC_DIR)/SpecimenBlock.h  $(SRC_DIR)/Value.h 
	$(CXX) $(CXXFLAGS) $(INC) -o $(TEST_DIR)/BlockTest.o -c BlockTest.cpp 

$(TEST_DIR)/CatalogTest.o : CatalogTest.cpp $(SRC_DIR)/Catalog.h \
                                                        $(SRC_DIR)/Study.h
	$(CXX) $(CXXFLAGS) $(INC) -o $(TEST_DIR)/CatalogTest.o -c \
                                                        CatalogTest.cpp 

$(TEST_DIR)/CredentialsTest.o : CredentialsTest.cpp $(SRC_DIR)/Credentials.h \
                                            $(SRC_DIR)/ServiceException.h
	$(CXX) $(CXXFLAGS) $(INC) -o $(TEST_DIR)/CredentialsTest.o -c \
                                            CredentialsTest.cpp 

$(TEST_DIR)/DigestRequestTest.o : DigestRequestTest.cpp                 \
                    $(SRC_DIR)/DigestRequest.h $(SRC_DIR)/Credentials.h \
                    $(SRC_DIR)/ServiceException.h
	$(CXX) $(CXXFLAGS) $(INC) -o $(TEST_DIR)/DigestRequestTest.o -c \
                    DigestRequestTest.cpp 

$(TEST_DIR)/MessageTest.o : MessageTest.cpp $(SRC_DIR)/Message.h 
	$(CXX) $(CXXFLAGS) $(INC) -o $(TEST_DIR)/MessageTest.o -c \
                    MessageTest.cpp 

$(TEST_DIR)/PanelTest.o : PanelTest.cpp $(SRC_DIR)/Panel.h
	$(CXX) $(CXXFLAGS) $(INC) -o $(TEST_DIR)/PanelTest.o -c PanelTest.cpp 

$(TEST_DIR)/PredictorTest.o : PredictorTest.cpp $(SRC_DIR)/Predictor.h
	$(CXX) $(CXXFLAGS) $(INC) -o $(TEST_DIR)/PredictorTest.o -c \
                    PredictorTest.cpp 

$(TEST_DIR)/PrivilegeTest.o : PrivilegeTest.cpp $(SRC_DIR)/Privilege.h
	$(CXX) $(CXXFLAGS) $(INC) -o $(TEST_DIR)/PrivilegeTest.o -c \
                    PrivilegeTest.cpp 

$(TEST_DIR)/RoleTest.o : RoleTest.cpp $(SRC_DIR)/Role.h $(SRC_DIR)/Privilege.h
	$(CXX) $(CXXFLAGS) $(INC) -o $(TEST_DIR)/RoleTest.o -c RoleTest.cpp 

$(TEST_DIR)/RosterTest.o : RosterTest.cpp $(SRC_DIR)/Roster.h \
                                $(SRC_DIR)/Role.h $(SRC_DIR)/Privilege.h
	$(CXX) $(CXXFLAGS) $(INC) -o $(TEST_DIR)/RosterTest.o -c \
                                RosterTest.cpp 

$(TEST_DIR)/ServiceExceptionTest.o : ServiceExceptionTest.cpp \
                                            $(SRC_DIR)/ServiceException.h
	$(CXX) $(CXXFLAGS) $(INC) -o $(TEST_DIR)/ServiceExceptionTest.o -c \
                                            ServiceExceptionTest.cpp 

$(TEST_DIR)/SpecimenTest.o : SpecimenTest.cpp $(SRC_DIR)/Specimen.h \
            $(SRC_DIR)/Cell.h $(SRC_DIR)/IntegerValue.h             \
            $(SRC_DIR)/NaturalValue.h $(SRC_DIR)/RealValue.h        \
            $(SRC_DIR)/Value.h
	$(CXX) $(CXXFLAGS) $(INC) -o $(TEST_DIR)/SpecimenTest.o -c \
                                SpecimenTest.cpp 

$(TEST_DIR)/StudyTest.o : StudyTest.cpp $(SRC_DIR)/Study.h
	$(CXX) $(CXXFLAGS) $(INC) -o $(TEST_DIR)/StudyTest.o -c StudyTest.cpp 

$(TEST_DIR)/TestYosokumo.o : TestYosokumo.cpp $(PROTO_CPP_DIR)/yosokumo.pb.h
	$(CXX) $(CXXFLAGS) -I$(UNITTEST_INC) -o $(TEST_DIR)/TestYosokumo.o \
            -I$(PROTO_CPP_DIR) -Wno-long-long -c TestYosokumo.cpp 

$(TEST_DIR)/ValueTest.o : ValueTest.cpp $(SRC_DIR)/Value.h      \
            $(SRC_DIR)/EmptyValue.h   $(SRC_DIR)/IntegerValue.h \
            $(SRC_DIR)/NaturalValue.h $(SRC_DIR)/RealValue.h    \
            $(SRC_DIR)/SpecialValue.h $(SRC_DIR)/Value.h
	$(CXX) $(CXXFLAGS) $(INC) -o $(TEST_DIR)/ValueTest.o -c ValueTest.cpp 

$(TEST_DIR)/YosokumoProtobufTest.o : YosokumoProtobufTest.cpp           \
            $(SRC_DIR)/YosokumoProtobuf.h $(SRC_DIR)/Block.h            \
            $(SRC_DIR)/Catalog.h $(SRC_DIR)/Cell.h $(SRC_DIR)/Message.h \
            $(SRC_DIR)/Panel.h $(SRC_DIR)/Predictor.h $(SRC_DIR)/Role.h \
            $(SRC_DIR)/Roster.h $(SRC_DIR)/ServiceException.h           \
            $(SRC_DIR)/Specimen.h $(SRC_DIR)/Study.h                    \
            $(SRC_DIR)/YosokumoDIF.h $(PROTO_CPP_DIR)/yosokumo.pb.h
	$(CXX) $(CXXFLAGS) $(INC) -o $(TEST_DIR)/YosokumoProtobufTest.o \
            -I$(PROTO_CPP_DIR) -Wno-long-long -c YosokumoProtobufTest.cpp 

$(TEST_DIR)/YosokumoRequestTest.o : YosokumoRequestTest.cpp           \
            $(SRC_DIR)/YosokumoRequest.h 
	$(CXX) $(CXXFLAGS) $(INC) -o $(TEST_DIR)/YosokumoRequestTest.o \
            -I$(PROTO_CPP_DIR) -Wno-long-long -c YosokumoRequestTest.cpp 

# Link all the stuff compiled above into the executable TestYosokumo

.PHONY: link
link: $(TEST_DIR)/TestYosokumo

$(TEST_DIR)/TestYosokumo : $(OBJ_TEST_FILES) $(LIB_DIR)/libyosokumo.a
	g++ -o $(TEST_DIR)/TestYosokumo $(OBJ_TEST_FILES) -L$(UNITTEST_DIR) \
        -L$(LIB_DIR) -L$(OPENSSL_DIR)/lib \
        -L/home/roger/OpenSourceCode/base64/libb64-1.2/src \
        -lUnitTest++ -lyosokumo -lb64 -lcrypto -ldl -lprotobuf


# clean gets rid of all test class files in TEST_DIR

.PHONY: clean
clean :
	@rm -f $(TEST_DIR)/*.o

# end makefile to compile yosokumo C++ code for unit tests and other tests
