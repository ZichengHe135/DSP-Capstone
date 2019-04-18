################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
ISRs.obj: ../ISRs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.16/bin/cl6x" -mv6740 --abi=coffabi -g --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.16/include" --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="ISRs.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

LCDK_Support_DSP.obj: ../LCDK_Support_DSP.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.16/bin/cl6x" -mv6740 --abi=coffabi -g --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.16/include" --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="LCDK_Support_DSP.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

StartUp.obj: ../StartUp.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.16/bin/cl6x" -mv6740 --abi=coffabi -g --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.16/include" --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="StartUp.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

function.obj: ../function.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.16/bin/cl6x" -mv6740 --abi=coffabi -g --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.16/include" --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="function.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.16/bin/cl6x" -mv6740 --abi=coffabi -g --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.16/include" --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="main.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

vectors.obj: ../vectors.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.16/bin/cl6x" -mv6740 --abi=coffabi -g --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.16/include" --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="vectors.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


