BOOTMAGIC_ENABLE           = no  # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE            = no  # Mouse keys(+4700)
EXTRAKEY_ENABLE            = yes # Audio control and System control(+450)
CONSOLE_ENABLE             = no  # Console for debug(+400)
COMMAND_ENABLE             = no  # Commands for debug and configuration
NKRO_ENABLE                = yes # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE           = no  # Enable keyboard backlight functionality
MIDI_ENABLE                = no  # MIDI controls
AUDIO_ENABLE               = no  # Audio output on port C6
UNICODE_ENABLE             = no  # Unicode
BLUETOOTH_ENABLE           = no  # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE            = no  # Enable WS2812 RGB underlight.
SWAP_HANDS_ENABLE          = no  # Enable one-hand typing
RGB_MATRIX_ENABLE = WS2812

OLED_DRIVER_ENABLE = yes

SLEEP_LED_ENABLE = no
#TAP_DANCE_ENABLE = yes

# If you want to change the display of OLED, you need to change here
SRC +=  ./glcdfont.c
