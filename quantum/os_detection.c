/* Copyright 2022 Ruslan Sayfutdinov (@KapJI)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "os_detection.h"

#include <string.h>

#ifdef OS_DETECTION_DEBUG_ENABLE
#    include "eeconfig.h"
#    include "eeprom.h"
#    include "print.h"
#include <quantum/logging/debug.h>

#    define STORED_USB_SETUPS 50
#    define EEPROM_USER_OFFSET (uint8_t*)EECONFIG_SIZE

#define MAX_USB_SETUPINFO 100

struct usb_setupinfo {
    uint8_t descriptorIndex;
    uint16_t wIndex;
    uint16_t wLength;
};

struct usb_setupinfo setupdump[MAX_USB_SETUPINFO] = {0};

unsigned int setup_data_count = 0;

uint16_t usb_setups[STORED_USB_SETUPS];
#endif

#ifdef OS_DETECTION_ENABLE
struct setups_data_t {
    uint8_t      count;
    uint8_t      cnt_02;
    uint8_t      cnt_04;
    uint8_t      cnt_ff;
    uint16_t     last_wlength;
    os_variant_t detected_os;
};

struct setups_data_t setups_data = {
    .count       = 0,
    .cnt_02      = 0,
    .cnt_04      = 0,
    .cnt_ff      = 0,
    .detected_os = OS_UNSURE,
};

// Some collected sequences of wLength can be found in tests.
void make_guess(void) {
    if (setups_data.count < 3) {
        return;
    }
    if (setups_data.cnt_ff >= 2 && setups_data.cnt_04 >= 1) {
        setups_data.detected_os = OS_WINDOWS;
        return;
    }
    if (setups_data.count == setups_data.cnt_ff) {
        // Linux has 3 packets with 0xFF.
        setups_data.detected_os = OS_LINUX;
        return;
    }
    if (setups_data.count == 5 && setups_data.last_wlength == 0xFF && setups_data.cnt_ff == 1 && setups_data.cnt_02 == 2) {
        setups_data.detected_os = OS_MACOS;
        return;
    }
    if (setups_data.count == 4 && setups_data.cnt_ff == 0 && setups_data.cnt_02 == 2) {
        // iOS and iPadOS don't have the last 0xFF packet.
        setups_data.detected_os = OS_IOS;
        return;
    }
    if (setups_data.cnt_ff == 0 && setups_data.cnt_02 == 3 && setups_data.cnt_04 == 1) {
        // This is actually PS5.
        setups_data.detected_os = OS_LINUX;
        return;
    }
    if (setups_data.cnt_ff >= 1 && setups_data.cnt_02 == 0 && setups_data.cnt_04 == 0) {
        // This is actually Quest 2 or Nintendo Switch.
        setups_data.detected_os = OS_LINUX;
        return;
    }
}



void process_wlength(const uint8_t descriptorIndex, const uint16_t wIndex, const uint16_t w_length) {
#    ifdef OS_DETECTION_DEBUG_ENABLE
    usb_setups[setups_data.count] = w_length;
#    endif
    setups_data.count++;
    setups_data.last_wlength = w_length;
    if (w_length == 0x2) {
        setups_data.cnt_02++;
    } else if (w_length == 0x4) {
        setups_data.cnt_04++;
    } else if (w_length == 0xFF) {
        setups_data.cnt_ff++;
    }

#ifdef OS_DETECTION_DEBUG_ENABLE
    if (setup_data_count < MAX_USB_SETUPINFO) {
        setupdump[setup_data_count].descriptorIndex = descriptorIndex;
        setupdump[setup_data_count].wIndex = wIndex;
        setupdump[setup_data_count].wLength = w_length;
        setup_data_count++;
    }
#endif
    make_guess();
}

#ifdef OS_DETECTION_DEBUG_ENABLE
void clear_setupdump() {
    setup_data_count = 0;
}

void print_setupdump() {
    dprintf("begin print_setupdump()\n");
    for (int i = 0; i < setup_data_count; i++) {
        dprintf("idx: %u descriptorIndex %X wIndex %u wLength %X\n",
            i, 
            setupdump[i].descriptorIndex,
            setupdump[i].wIndex,
            setupdump[i].wLength);
    }
    dprintf("end print_setupdump()\n");
}
#else
void clear_setupdump(void) {}
void print_setupdump(void) {}
#endif

os_variant_t detected_host_os(void) {
    return setups_data.detected_os;
}

void erase_wlength_data(void) {
    memset(&setups_data, 0, sizeof(setups_data));
}
#endif // OS_DETECTION_ENABLE

#ifdef OS_DETECTION_DEBUG_ENABLE
void print_stored_setups(void) {
#    ifdef CONSOLE_ENABLE
    uint8_t cnt = eeprom_read_byte(EEPROM_USER_OFFSET);
    for (uint16_t i = 0; i < cnt; ++i) {
        uint16_t* addr = (uint16_t*)EEPROM_USER_OFFSET + i * sizeof(uint16_t) + sizeof(uint8_t);
        xprintf("i: %d, wLength: 0x%02X\n", i, eeprom_read_word(addr));
    }
#    endif
}

void store_setups_in_eeprom(void) {
    eeprom_update_byte(EEPROM_USER_OFFSET, setups_data.count);
    for (uint16_t i = 0; i < setups_data.count; ++i) {
        uint16_t* addr = (uint16_t*)EEPROM_USER_OFFSET + i * sizeof(uint16_t) + sizeof(uint8_t);
        eeprom_update_word(addr, usb_setups[i]);
    }
}

#endif // OS_DETECTION_DEBUG_ENABLE
