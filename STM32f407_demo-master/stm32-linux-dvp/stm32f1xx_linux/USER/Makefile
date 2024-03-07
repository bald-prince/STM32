PRO_NAME = env_item
OBJ = startup_stm32f103x6.o main.o led.o seg.o time.o uart.o#Start.o  main.o led.o 

#CC  = arm-linux-gnueabihf-gcc
#LD  = arm-linux-gnueabihf-ld
#CP  = arm-linux-gnueabihf-objcopy
#DM  = arm-linux-gnueabihf-objdump 

CC  = arm-none-eabi-gcc
LD  = arm-none-eabi-ld
CP  = arm-none-eabi-objcopy
DM  = arm-none-eabi-objdump 


FLAG = -g -W -Wall -std=c99 \
-lm -lc -mcpu=cortex-m4 -mthumb \
-DSTM32F10X_LD -DHSE_VALUE=8000000

LD_FLAG = -lc -lm -mcpu=cortex-m3 -mthumb -Wl,--gc-sections -specs=nano.specs -specs=nosys.specs#-Wl,-u,Reset_Handler 

VPATH = ./     :\
		../INCLUDE :\
		../INCLUDE/LED :\
		../INCLUDE/UART :\
		../INCLUDE/TIM :\
		../INCLUDE/SEG :\
		./CORE :\



$(PRO_NAME).bin : $(OBJ)
	$(CC) -T STM32F103X6_FLASH.ld -o $(PRO_NAME).elf $^ $(LD_FLAG) 
	$(CP) -O binary -S $(PRO_NAME).elf $@
	$(CP) $(PRO_NAME).elf $(PRO_NAME).hex -Oihex
	$(DM) -D -m arm $(PRO_NAME).elf > $(PRO_NAME).dls

%.o : %.c
	$(CC) $(FLAG) -o $@ -c $<

%.o : %.s
	$(CC) $(FLAG) -o $@ -c $<

clean:
	rm ./*.o ./$(PRO_NAME)* -rf

