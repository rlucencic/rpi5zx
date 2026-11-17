# rpi5zx: the ZX Spectrum 128K, +2, +3 on the Raspberry Pi 5

esp32zx's Spectrum (`../esp32zx/components/zx`, platform independent) on
the rpi5emu runtime (`../rpi5emu`, its CLAUDE.md: the workflow, the Pi,
the lessons), the Z80 and uPD765 esp32emu's. The machine's own behaviour,
lessons and tests are esp32zx's CLAUDE.md; this project is the glue.

## Layout

| Path | What |
|---|---|
| `src/main.c` | The Spectrum as an `emu_machine_t`: esp32zx's `main/main.c` ported (malloc for PSRAM, `EMU_LOGx`, `usleep`, the ROM message, `shutdown()` writes the disks back, `main()`) |
| `src/settings.c` | Section `zx` of the settings file: `model`, `joystick`, `tape_fast` |
| `src/rom_store.c` | `~/rpi5emu/zx/roms/` (`emu_rom_dir()`): 128.rom, plus2.rom, plus3.rom, trdos.rom (any case) |
| `CMakeLists.txt` | esp32zx's core, `CONFIG_Z80_CONTENTION=1`, the cores z80, upd765, diskspace |

Keep `src/main.c` in step with esp32zx's `main/main.c` (the key map, the
drives, the status): a change there is usually wanted here too.

## Build, run, check

```sh
../rpi5emu/tools/pi.sh rpi5zx build
../rpi5emu/tools/pi.sh rpi5zx run          # the setup screen first; -S straight in
../rpi5emu/tools/console.sh i
```

Console: the runtime's (`h`) and esp32zx's: `k <n>` tap key n (half-row *
8 + bit, 48 ENTER, 56 SPACE, 0 CAPS SHIFT), `K <n> 0|1`, `T <text>` (`\n`
ENTER), `j <bits>`, `P` tape play/stop, `W` rewind, `R <model>` restart as
0 128K, 1 +2, 2 +3. The 128's menu: `K 0 1`, `k 36`, `K 0 0` (cursor
down), `k 48` (ENTER) picks 128 BASIC.

Checked on the Pi (2026-11-15, the window forwarded to the PC): the 128 and
+3 menus at 100% (50 frames a second, the emulation thread ~1-2% of a
core); a BASIC program typed and run (PRINT, BEEP); a model change from the
console (`c 0 2`) and from the setup screen (Restart); a blank +3 disk
made, a program saved to it and found in the image after quitting
(`shutdown()`); the settings and the drive remembered across starts; the
web API from the PC (info, status, disk list, upload, download identical,
new blank tape, insert, eject, delete refused while in a drive, reset).
Not yet: the keyboard and mouse in the window by hand, sound heard (the
Pi had no output: PipeWire's null sink), tapes and games, the debugger,
a monitor on the Pi.
