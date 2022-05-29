
CC=arm-none-eabi-gcc

CC_FLAGS = -mcpu=cortex-m4		\
	 	   -mthumb        		\
		   -specs=nano.specs	\
		   -specs=nosys.specs	\
		   -mfpu=fpv4-sp-d16 	\
		   -mfloat-abi=hard		\
		   -fmessage-length=0	\
		   -ffunction-sections	\
		   -c					\

CC_LINKER_FLAGS =-mcpu=cortex-m4		\
				-mthumb				\
				-specs=nano.specs	\
				-specs=nosys.specs	\
				-mfpu=fpv4-sp-d16	\
				-mfloat-abi=hard	\
				-Wl,--gc-sections	\
				-T"linker.ld"		\
				-Wl,-Map=memmap.map	\


all: executavel
executavel: demo_01.o startup.o
	$(CC) $(CC_LINKER_FLAGS) demo_01.o startup.o -o demo_01.elf


startup.o:
	$(CC) $(CC_FLAGS) startup.S -o startup.o

demo_01.o:
	$(CC) $(CC_FLAGS) demo_01.c -o demo_01.o