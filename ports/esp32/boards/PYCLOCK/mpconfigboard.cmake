set(IDF_TARGET esp32c3)
set(MICROPY_PORT_PICLIB y) #

set(SDKCONFIG_DEFAULTS
	boards/sdkconfig.base
	boards/sdkconfig.ble
	boards/PYCLOCK/sdkconfig.board
)

if(NOT MICROPY_FROZEN_MANIFEST)
    set(MICROPY_FROZEN_MANIFEST ${MICROPY_PORT_DIR}/boards/manifest.py)
endif()
