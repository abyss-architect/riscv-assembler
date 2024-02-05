cc := gcc
FLAGS :=
EXE := riscv_asm
.PHONY : clean cleanall compile_trace_1

$(EXE) : main.o parser.o instruction.o register.o
	$(cc) $(FLAGS) $^ -o $@

main.o : main.c parser.h
	$(cc) $(FLAGS) -c $<

parser.o : parser.c parser.h instruction_memory.h register.h
	$(cc) $(FLAGS) -c $<
	
instruction.o : instruction.c instruction.h
	$(cc) $(FLAGS) -c $<

register.o : register.c register.h
	$(cc) $(FLAGS) -c $<

clean :
	-\rm *.o

cleanall :
	-\rm $(EXE)
	-\rm *.o

compile_trace_1 :
	-./$(EXE) < ./cpu_traces/trace_1