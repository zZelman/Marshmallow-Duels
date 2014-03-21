################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/PowerUps/CPowerUp_Container.cpp \
../src/PowerUps/CPowerUp_holder.cpp 

OBJS += \
./src/PowerUps/CPowerUp_Container.o \
./src/PowerUps/CPowerUp_holder.o 

CPP_DEPS += \
./src/PowerUps/CPowerUp_Container.d \
./src/PowerUps/CPowerUp_holder.d 


# Each subdirectory must supply rules for building sources it contributes
src/PowerUps/%.o: ../src/PowerUps/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DDEBUG -I"/home/zZelman/Dropbox/Marshmallow-Duels/SFML-2.1/include" -I"/home/zZelman/Dropbox/Marshmallow-Duels/rapidxml-1.13" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


