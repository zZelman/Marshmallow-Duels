################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Tiles/CTile.cpp \
../src/Tiles/CTile_Container.cpp 

OBJS += \
./src/Tiles/CTile.o \
./src/Tiles/CTile_Container.o 

CPP_DEPS += \
./src/Tiles/CTile.d \
./src/Tiles/CTile_Container.d 


# Each subdirectory must supply rules for building sources it contributes
src/Tiles/%.o: ../src/Tiles/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DDEBUG -I"/home/zZelman/Dropbox/Marshmallow-Duels/SFML-2.1/include" -I"/home/zZelman/Dropbox/Marshmallow-Duels/rapidxml-1.13" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


