################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
stuff/%.obj: ../stuff/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"/home/taylor/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.3/bin/cl6x" -mv6740 --abi=eabi -Ooff --opt_for_speed=0 -ms0 --include_path="/home/taylor/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.3/include" -g --relaxed_ansi --gcc --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="stuff/$(basename $(<F)).d_raw" --obj_directory="stuff" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

stuff/%.obj: ../stuff/%.cpp $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"/home/taylor/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.3/bin/cl6x" -mv6740 --abi=eabi -Ooff --opt_for_speed=0 -ms0 --include_path="/home/taylor/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.3/include" -g --relaxed_ansi --gcc --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="stuff/$(basename $(<F)).d_raw" --obj_directory="stuff" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


