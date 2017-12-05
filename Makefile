all: folder alice bob

GCC = gcc
BIN = bin
OBJ = obj
INC = -Iinc/ -w

bob: folder cripto
	+@echo "Compile: $@"
	@$(GCC) src/$@.c $(INC) -c -o $(OBJ)/$@.o -lm

	@echo "Linking..."
	+@$(GCC) -o $(BIN)/appBob $(OBJ)/bob.o $(OBJ)/cripto.o -lm
	@echo "Binary are ready in $(BIN)/appBob"

alice: folder cripto
	+@echo "Compile: $@"
	@$(GCC) src/$@.c $(INC) -c -o $(OBJ)/$@.o -lm

	@echo "Linking..."
	+@$(GCC) -o $(BIN)/appAlice $(OBJ)/alice.o $(OBJ)/cripto.o -lm
	@echo "Binary are ready in $(BIN)/appAlice"

cripto:
	+@echo "Compile: $@"
	@$(GCC) src/$@.c $(INC) -c -o $(OBJ)/$@.o -lm

folder:
	@mkdir -p $(OBJ) $(BIN)

clean:
	@rm -rf $(OBJ)/* $(BIN)/* $(OBJ) $(BIN)

###############################################################################
