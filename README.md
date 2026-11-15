# rpi5zx

A ZX Spectrum 128K, +2 and +3 for the Raspberry Pi 5, in a window of its
own: [esp32zx](https://github.com/rlucencic/esp32zx)'s Spectrum on the
[rpi5emu](https://github.com/rlucencic/rpi5emu) runtime.

- The Z80 with the ULA's memory contention, the ULA, the AY, 128K and +3
  paging; the +3's floppy controller (DSK), a Beta 128 with TR-DOS (TRD,
  SCL) on the 128K and +2.
- Tapes (TAP, TZX) in real time, standard blocks loaded at once; snapshots
  (SNA, Z80).
- The setup screen (model, tape speed, sound, the drives), the web page for
  the disk images, the console, as the rest of the family.

## Building

See [rpi5emu](https://github.com/rlucencic/rpi5emu#building): esp32emu,
rpi5emu, esp32zx and rpi5zx cloned side by side, then

```sh
cd rpi5zx && cmake -S . -B build -G Ninja && cmake --build build
```

## ROMs

`128.rom` (32 KB), `plus2.rom` (32 KB), `plus3.rom` (64 KB) and, for the
Beta 128's disks, `trdos.rom` (16 KB) in the data folder's `roms/`
(`~/rpi5emu/roms`). Not part of this repository.

## Running

```sh
build/rpi5zx                        # the setup screen first
build/rpi5zx -S --choice Model=+3   # straight into a +3
build/rpi5zx game.tzx               # with a tape in
```

Disks, tapes and snapshots live in `~/rpi5emu/zx/` (or come from the
command line, the window or the web page). The keyboard: letters and digits
as on the Spectrum; Shift is CAPS SHIFT, Ctrl and Alt SYMBOL SHIFT;
Backspace DELETE, Esc BREAK, the cursor keys, Tab EXTEND MODE, punctuation
as its character. The numeric keypad is the joystick (8 4 6 2, 0 or 5
fire); F12 makes the cursor keys the joystick too (Alt fire), F11 switches
Kempston, Sinclair and cursor; F9 starts or stops the tape, F10 rewinds it.

## Licence

MIT.
