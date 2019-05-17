# begin makefile to compile yosokumo C++ code

include ../makefile.inc

.PHONY: all
all : create-cpp-files compile

.PHONY: create-cpp-files
create-cpp-files : 
	@cd ws-cpp; $(MAKE) $(MFLAGS)

.PHONY: compile
compile :                         \
    $(OBJ_DIR)/Base64.o           \
    $(OBJ_DIR)/Block.o            \
    $(OBJ_DIR)/Catalog.o          \
    $(OBJ_DIR)/Cell.o             \
    $(OBJ_DIR)/CellBlock.o        \
    $(OBJ_DIR)/Credentials.o      \
    $(OBJ_DIR)/DigestRequest.o    \
    $(OBJ_DIR)/EmptyBlock.o       \
    $(OBJ_DIR)/EmptyValue.o       \
    $(OBJ_DIR)/IntegerValue.o     \
    $(OBJ_DIR)/Message.o          \
    $(OBJ_DIR)/NaturalValue.o     \
    $(OBJ_DIR)/Panel.o            \
    $(OBJ_DIR)/Predictor.o        \
    $(OBJ_DIR)/PredictorBlock.o   \
    $(OBJ_DIR)/Privilege.o        \
    $(OBJ_DIR)/RealValue.o        \
    $(OBJ_DIR)/Role.o             \
    $(OBJ_DIR)/Roster.o           \
    $(OBJ_DIR)/ServiceException.o \
    $(OBJ_DIR)/SpecialValue.o     \
    $(OBJ_DIR)/Specimen.o         \
    $(OBJ_DIR)/SpecimenBlock.o    \
    $(OBJ_DIR)/Study.o            \
    $(OBJ_DIR)/Value.o            \
    $(OBJ_DIR)/YosokumoDIF.o      \
    $(OBJ_DIR)/YosokumoProtobuf.o \
    $(OBJ_DIR)/YosokumoRequest.o

#### Save this stuff
###.PHONY: compile
###compile :                         \
###    $(OBJ_DIR)/Service.o          \
###    $(OBJ_DIR)/YosokumoRequest.o

$(OBJ_DIR)/Block.o : Block.cpp Block.h
	@rm -f $(OBJ_DIR)/Block.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/Block.o -c Block.cpp 

$(OBJ_DIR)/Base64.o : Base64.cpp Base64.h
	@rm -f $(OBJ_DIR)/Base64.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/Base64.o -c Base64.cpp 

$(OBJ_DIR)/Catalog.o : Catalog.cpp Catalog.h
	@rm -f $(OBJ_DIR)/Catalog.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/Catalog.o -c Catalog.cpp 

$(OBJ_DIR)/Cell.o : Cell.cpp Cell.h
	@rm -f $(OBJ_DIR)/Cell.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/Cell.o -c Cell.cpp 

$(OBJ_DIR)/CellBlock.o : CellBlock.cpp CellBlock.h
	@rm -f $(OBJ_DIR)/CellBlock.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/CellBlock.o -c CellBlock.cpp 

$(OBJ_DIR)/Credentials.o : Credentials.cpp Credentials.h
	@rm -f $(OBJ_DIR)/Credentials.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/Credentials.o -c Credentials.cpp 

$(OBJ_DIR)/DigestRequest.o : DigestRequest.cpp DigestRequest.h \
                                                    Credentials.h Base64.h
	@rm -f $(OBJ_DIR)/DigestRequest.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/DigestRequest.o \
                            -I$(OPENSSL_DIR)/include -c DigestRequest.cpp 

$(OBJ_DIR)/EmptyBlock.o : EmptyBlock.cpp EmptyBlock.h
	@rm -f $(OBJ_DIR)/EmptyBlock.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/EmptyBlock.o -c EmptyBlock.cpp 

$(OBJ_DIR)/EmptyValue.o : EmptyValue.cpp EmptyValue.h
	@rm -f $(OBJ_DIR)/EmptyValue.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/EmptyValue.o -c EmptyValue.cpp 

$(OBJ_DIR)/IntegerValue.o : IntegerValue.cpp IntegerValue.h
	@rm -f $(OBJ_DIR)/IntegerValue.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/IntegerValue.o -c IntegerValue.cpp 

$(OBJ_DIR)/Message.o : Message.cpp Message.h
	@rm -f $(OBJ_DIR)/Message.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/Message.o -c Message.cpp 

$(OBJ_DIR)/NaturalValue.o : NaturalValue.cpp NaturalValue.h
	@rm -f $(OBJ_DIR)/NaturalValue.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/NaturalValue.o -c NaturalValue.cpp 

$(OBJ_DIR)/Panel.o : Panel.cpp Panel.h
	@rm -f $(OBJ_DIR)/Panel.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/Panel.o -c Panel.cpp 

$(OBJ_DIR)/Predictor.o : Predictor.cpp Predictor.h
	@rm -f $(OBJ_DIR)/Predictor.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/Predictor.o -c Predictor.cpp 

$(OBJ_DIR)/PredictorBlock.o : PredictorBlock.cpp PredictorBlock.h
	@rm -f $(OBJ_DIR)/PredictorBlock.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/PredictorBlock.o -c PredictorBlock.cpp 

$(OBJ_DIR)/Privilege.o : Privilege.cpp Privilege.h
	@rm -f $(OBJ_DIR)/Privilege.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/Privilege.o -c Privilege.cpp 

$(OBJ_DIR)/RealValue.o : RealValue.cpp RealValue.h
	@rm -f $(OBJ_DIR)/RealValue.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/RealValue.o -c RealValue.cpp 

$(OBJ_DIR)/Role.o : Role.cpp Role.h
	@rm -f $(OBJ_DIR)/Role.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/Role.o -c Role.cpp 

$(OBJ_DIR)/Roster.o : Roster.cpp Roster.h
	@rm -f $(OBJ_DIR)/Roster.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/Roster.o -c Roster.cpp 

$(OBJ_DIR)/ServiceException.o : ServiceException.cpp ServiceException.h
	@rm -f $(OBJ_DIR)/ServiceException.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/ServiceException.o -c ServiceException.cpp 

$(OBJ_DIR)/SpecialValue.o : SpecialValue.cpp SpecialValue.h
	@rm -f $(OBJ_DIR)/SpecialValue.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/SpecialValue.o -c SpecialValue.cpp 

$(OBJ_DIR)/Specimen.o : Specimen.cpp Specimen.h EmptyValue.h
	@rm -f $(OBJ_DIR)/Specimen.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/Specimen.o -c Specimen.cpp 

$(OBJ_DIR)/SpecimenBlock.o : SpecimenBlock.cpp SpecimenBlock.h
	@rm -f $(OBJ_DIR)/SpecimenBlock.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/SpecimenBlock.o -c SpecimenBlock.cpp 

$(OBJ_DIR)/Study.o : Study.cpp Study.h
	@rm -f $(OBJ_DIR)/Study.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/Study.o -c Study.cpp 

$(OBJ_DIR)/Value.o : Value.cpp Value.h
	@rm -f $(OBJ_DIR)/Value.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/Value.o -c Value.cpp 

$(OBJ_DIR)/YosokumoDIF.o : YosokumoDIF.cpp YosokumoDIF.h
	@rm -f $(OBJ_DIR)/YosokumoDIF.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/YosokumoDIF.o -c YosokumoDIF.cpp 

$(OBJ_DIR)/YosokumoProtobuf.o : YosokumoProtobuf.cpp YosokumoProtobuf.h \
                                                            StringUtil.h
	@rm -f $(OBJ_DIR)/YosokumoProtobuf.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/YosokumoProtobuf.o \
                -I$(PROTO_CPP_DIR) -Wno-long-long -c YosokumoProtobuf.cpp

$(OBJ_DIR)/YosokumoRequest.o : YosokumoRequest.cpp YosokumoRequest.h
	@rm -f $(OBJ_DIR)/YosokumoRequest.o
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/YosokumoRequest.o \
                -I$(PROTO_CPP_DIR) -Wno-long-long -c YosokumoRequest.cpp


# h file dependencies

Block.h            : Predictor.h Specimen.h 
Catalog.h          : Study.h
Cell.h             : Value.h
CellBlock.h        : Block.h Cell.h
Credentials.h      : ServiceException.h
DigestRequest.h    : ServiceException.h
EmptyBlock.h       : Block.h
EmptyValue.h       : Value.h
IntegerValue.h     : Value.h
NaturalValue.h     : Value.h
PredictorBlock.h   : Block.h Predictor.h
RealValue.h        : Value.h
Role.h             : Privilege.h
Roster.h           : Role.h
SpecialValue.h     : Value.h
Specimen.h         : Cell.h
SpecimenBlock.h    : Block.h Specimen.h
YosokumoDIF.h      : Block.h Catalog.h Cell.h Message.h Panel.h Predictor.h \
                        Role.h Roster.h ServiceException.h Specimen.h Study.h
YosokumoProtobuf.h : YosokumoDIF.h $(PROTO_CPP_DIR)/yosokumo.pb.h
YosokumoRequest.h  : YosokumoDIF.h

# clean gets rid of all object files in OBJ_DIR

.PHONY: clean
clean :
	@rm -f $(OBJ_DIR)/*.o

#### end makefile to compile yosokumo C++ code
