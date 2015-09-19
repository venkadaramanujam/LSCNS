OBJ_FILES := $(addprefix ./bin/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS := 

myproj: $(OBJ_FILES)
	make -C folder1
	make 
	make -C ../folder2
	make
	make -C ../
	g++ $(LD_FLAGS) -o $@ $^
