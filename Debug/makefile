################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/Teaching/subdir.mk
-include src/NeuronFactory/subdir.mk
-include src/Neuron/subdir.mk
-include src/NeuralNetwork/subdir.mk
-include src/NetworkTopology/subdir.mk
-include src/Learning/Evolution/Resilient/subdir.mk
-include src/Learning/Evolution/EvolutionStrategy/subdir.mk
-include src/Learning/Evolution/subdir.mk
-include src/Learning/subdir.mk
-include src/Graphics/subdir.mk
-include src/Function/subdir.mk
-include src/Examples/subdir.mk
-include src/Diagnostic/subdir.mk
-include src/ClusterAnalysis/subdir.mk
-include src/ActivationOrder/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: LightBulb

# Tool invocations
LightBulb: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	g++ -pg -o "LightBulb" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) LightBulb
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
