AHRS_ROOT = sensors
include $(AHRS_ROOT)/ahrs.mk

PROJECT_CSRC 	= main.c ch_hw.c usbcfg.c $(AHRS_CSRS)
PROJECT_CPPSRC 	= 

PROJECT_INCDIR	= $(AHRS_INC)

PROJECT_LIBS	= -lm

