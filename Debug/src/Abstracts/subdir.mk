################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Abstracts/ARenderable.cpp \
../src/Abstracts/AUpdate.cpp \
../src/Abstracts/AUserInput.cpp 

OBJS += \
./src/Abstracts/ARenderable.o \
./src/Abstracts/AUpdate.o \
./src/Abstracts/AUserInput.o 

CPP_DEPS += \
./src/Abstracts/ARenderable.d \
./src/Abstracts/AUpdate.d \
./src/Abstracts/AUserInput.d 


# Each subdirectory must supply rules for building sources it contributes
src/Abstracts/%.o: ../src/Abstracts/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DDEBUG -I"/home/zZelman/Dropbox/Covert-Collisions Host dir/Covert-Collisions/SFML-2.1/include" -I"/home/zZelman/Dropbox/Covert-Collisions Host dir/Covert-Collisions/rapidxml-1.13" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


