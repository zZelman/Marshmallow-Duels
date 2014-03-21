################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/UI/subdir.mk
-include src/Tiles/subdir.mk
-include src/PowerUps/subdir.mk
-include src/Players/subdir.mk
-include src/Physics/subdir.mk
-include src/Interfaces/subdir.mk
-include src/Graphics/subdir.mk
-include src/Abstracts/subdir.mk
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
all: Marshmallow-Duels

# Tool invocations
Marshmallow-Duels: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -L"/home/zZelman/Dropbox/Marshmallow-Duels/SFML-2.1/lib" -Xlinker -rpath "/home/zZelman/Dropbox/Marshmallow-Duels/SFML-2.1/lib" -o "Marshmallow-Duels" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) Marshmallow-Duels
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
