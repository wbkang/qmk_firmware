## Woongbin's Changes

### Layers

FN key switches to Fn layer. If on MacOS layer, it also turns on the MacOS Fn layer.

1. Windows Layer (white)
    1. `Caps Lock` is `Ctrl`
2. MacOS Layer (red)
    1. Swap LALT/LGUI
    2. Bind RALT to switch language (alt-space) like in Windows.
3. Fn Layer (green)
    1. `0` - mute speakers
    2. `-` - volume down
    3. `=` - volume up
    1. `F10` - prev song
    2. `F11` - pause/play
    3. `F12` - next song
    4. `PrintScrn` - toggle debug log
    5. `Pause` - bootloader
    6. `INS` - print number of keystrokes.
    7. `M` - manual layer toggle for the Mac layer.
    8. `Caps Lock` is `Caps Lock`
4. Mac Fn Layer (orange)
    1. `.` - `Ctrl+Gui+Space` (Emoji picker) - this is way too complicated compared to Windows so I changed it.
    
Layers
1. Windows Layer
2. Mac Layer
3. Media Layer

## OS Detection

I merged the os detection code from [KapJI/qmk_firmware/tree/guess-os](https://github.com/KapJI/qmk_firmware/tree/guess-os). 

There is a hook into `notify_usb_device_state_change_user` to detect USB device switching/reset and schedule a job in a second to carry out the layout switch based on the OS.