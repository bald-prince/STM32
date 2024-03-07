PRO_NAME = led
OBJ =  system_stm32f4xx.o startup_stm32f40_41xxx.o main.o led.o sys.o delay.o uart.o#Start.o  main.o led.o 

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
-DSTM32F407xx -DHSE_VALUE=8000000 -D__CC_ARM 

LD_FLAG = -lc -lm -mcpu=cortex-m4 -mthumb -Wl,--gc-sections #-Wl,-u,Reset_Handler 

VPATH = ./     :\
		./User :\
		./Include :\
		./Hardware :\
		./Src :\



$(PRO_NAME).bin : $(OBJ)
	$(CC) -T stm32f4xx_flash_extsram.ld -o $(PRO_NAME).elf $^ $(LD_FLAG) 
	$(CP) -O binary -S $(PRO_NAME).elf $@
	$(CP) $(PRO_NAME).elf $(PRO_NAME).hex -Oihex
	$(DM) -D -m arm $(PRO_NAME).elf > $(PRO_NAME).dls

%.o : %.c
	$(CC) $(FLAG) -o $@ -c $<

%.o : %.s
	$(CC) $(FLAG) -o $@ -c $<

clean:
	rm ./*.o ./$(PRO_NAME)* -rf

Download-Dir = $(shell pwd)/$(PRO_NAME).bin

dw:
	openocd -f /usr/share/openocd/scripts/board/stm32f4discovery.cfg


