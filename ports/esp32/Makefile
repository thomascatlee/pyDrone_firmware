# Makefile for MicroPython on ESP32.
#
# This is a simple, convenience wrapper around idf.py (which uses cmake).

# BOARD ?= PYWIFI_C3
# BOARD ?= PYWIFI
# BOARD ?= PYWIFI_P
# BOARD ?= PYWIFI_S2P
# BOARD ?= PYWIFI_S3P
# BOARD ?= PYWIFI_S3PR8
# BOARD ?= PYWIFI_S3P_AI
# BOARD ?= PYCONTROLLER
# BOARD ?= PYCLOCK
BOARD ?= PYDRONE

BUILD ?= build-$(BOARD)
ifeq ($(BOARD),PYWIFI_C3)
MAKEIMG = makeimg_c3.py
else
MAKEIMG = makeimg.py
endif

# Device serial settings.
PORT ?= /dev/ttyUSB0
BAUD ?= 460800

PYTHON ?= python3

GIT_SUBMODULES = lib/berkeley-db-1.xx

.PHONY: all clean deploy erase submodules FORCE

CMAKE_ARGS =

ifdef USER_C_MODULES
	CMAKE_ARGS += -DUSER_C_MODULES=${USER_C_MODULES}
endif

IDFPY_FLAGS += -D MICROPY_BOARD=$(BOARD) -B $(BUILD) $(CMAKE_ARGS)

ifdef FROZEN_MANIFEST
       IDFPY_FLAGS += -D MICROPY_FROZEN_MANIFEST=$(FROZEN_MANIFEST)
endif

all:
	idf.py $(IDFPY_FLAGS) build
	@$(PYTHON) makeimg.py \
		$(BUILD)/sdkconfig \
		$(BUILD)/bootloader/bootloader.bin \
		$(BUILD)/partition_table/partition-table.bin \
    		$(BUILD)/micropython.bin \
    		$(BUILD)/firmware.bin

$(BUILD)/bootloader/bootloader.bin $(BUILD)/partition_table/partition-table.bin $(BUILD)/micropython.bin: FORCE

clean:
	idf.py $(IDFPY_FLAGS) fullclean

deploy:
	idf.py $(IDFPY_FLAGS) -p $(PORT) -b $(BAUD) flash

erase:
	idf.py $(IDFPY_FLAGS) -p $(PORT) -b $(BAUD) erase_flash

submodules:
	git submodule update --init $(addprefix ../../,$(GIT_SUBMODULES))

idf-usb-patch:
	cp -r $(IDF_PATH)/components/usb/CMakeLists.txt $(IDF_PATH)/components/usb/CMakeLists.txt.bak
	cp -r esp32-camera/CMakeLists.txt $(IDF_PATH)/components/usb/CMakeLists.txt
	cat $(IDF_PATH)/components/usb/CMakeLists.txt
