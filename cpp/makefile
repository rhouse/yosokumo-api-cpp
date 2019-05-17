# top-level makefile for building C++ version of yosokumo

include makefile.inc

OBJ_FILES = $(OBJ_DIR)/Base64.o           \
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
            $(OBJ_DIR)/Roster.o            \
            $(OBJ_DIR)/ServiceException.o \
            $(OBJ_DIR)/SpecialValue.o     \
            $(OBJ_DIR)/Specimen.o         \
            $(OBJ_DIR)/SpecimenBlock.o    \
            $(OBJ_DIR)/Study.o            \
            $(OBJ_DIR)/Value.o            \
            $(OBJ_DIR)/YosokumoDIF.o      \
            $(OBJ_DIR)/YosokumoProtobuf.o \
            $(OBJ_DIR)/YosokumoRequest.o  \
            $(PROTO_OBJ_DIR)/yosokumo.pb.o


# Create C++ code, compile C++ code, and make a library for yosokumo

.PHONY: all
all :
	@rm -f $(LIB_DIR)/yosokumo.a
	@cd src; $(MAKE) $(MAKEFLAGS)

#Create a library for yosokumo (includes object files from generated C++)

	@ar rvs $(LIB_DIR)/libyosokumo.a $(OBJ_FILES)

# Create C++ source files from a Google Protocol Buffer description, and 
# compile the created files
.PHONY: protobuf
protobuf :
	@cd protobuf; $(MAKE) $(MAKEFLAGS)

# Compile all the UnitTest test classes for yosokumo as well as other tests
.PHONY: tests
tests :
	@cd test-files; $(MAKE) $(MAKEFLAGS)

#Create public and private doxygen for yosokumo
.PHONY: doxygen
doxygen:
	@doxygen doxyfile.cfg >doxygen.log 2>&1
	@if grep -i warn doxygen.log; then :; fi # make complains if
	@if grep -i err doxygen.log;  then :; fi #   grep returns 1

###	@doxygen -classpath .:$(GOOGLE_PROTOBUF_JAR):$(HTTP_PATH) \
###             -private -d $(DOXYGEN_PRIVATE_DIR) src/*.java

# Get rid of all object files in OBJ_DIR
.PHONY: clean
clean :
	@rm -f $(OBJ_DIR)/*.o

# Get rid of all class files and other files
.PHONY: real-clean
real-clean :
	@rm -f $(OBJ_DIR)/*.o
	@rm -f $(LIB_DIR)/yosokumo.a
	@rm -rf $(DOXYGEN_DIR)
	@mkdir $(DOXYGEN_DIR)
###	@rm -rf $(DOXYGEN_PRIVATE_DIR)
###	@mkdir $(DOXYGEN_PRIVATE_DIR)
	@cd test-files;  $(MAKE) clean
	@cd protobuf;    $(MAKE) clean

# end makefile
