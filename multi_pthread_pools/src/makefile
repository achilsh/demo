DIR_SUB := concurrency test 
.PHONY : mks
mks: 
	@for sub_dir in $(DIR_SUB); do echo "go $$sub_dir and make";  make clean  -C $$sub_dir clean ; make -C $$sub_dir; done
clean:  
	@for sub_dir in $(DIR_SUB); do echo "go $$sub_dir and make clean";  make clean  -C $$sub_dir clean ; done
