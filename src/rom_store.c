#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emu/emu.h"
#include "emu/log.h"
#include "rom_store.h"

#define SLOT        16384

static const char *TAG = "rom";

static const struct {
    const char *name;
    uint8_t slots;
} roms[ROM_COUNT] = {
    { "128.rom", 2 }, { "plus2.rom", 2 }, { "plus3.rom", 4 }, { "trdos.rom", 1 },
};

const char *rom_store_name(rom_id_t id)
{
    return id < ROM_COUNT ? roms[id].name : "";
}

uint32_t rom_store_size(rom_id_t id)
{
    return id < ROM_COUNT ? roms[id].slots * SLOT : 0;
}

/* Something in every 16 KB: not erased, not zeros */
static bool plausible(const uint8_t *p, uint32_t size)
{
    for (uint32_t off = 0; off < size; off += SLOT) {
        bool ff = true, zero = true;
        for (int i = 0; i < 64; i++) {
            ff &= p[off + i] == 0xFF;
            zero &= p[off + i] == 0x00;
        }
        if (ff || zero) {
            return false;
        }
    }
    return true;
}

bool rom_store_load(rom_id_t id, uint8_t *buf)
{
    if (id >= ROM_COUNT) {
        return false;
    }
    uint32_t size = rom_store_size(id);
    char path[1200];
    snprintf(path, sizeof(path), "%s/roms/%s", emu_data_dir(), roms[id].name);
    FILE *f = fopen(path, "rb");
    if (f == NULL) {
        /* as copied from a FAT card: upper case */
        char *name = path + strlen(path) - strlen(roms[id].name);
        for (char *p = name; *p; p++) {
            *p = (*p >= 'a' && *p <= 'z') ? *p - 32 : *p;
        }
        f = fopen(path, "rb");
    }
    if (f == NULL) {
        return false;
    }
    long n = fread(buf, 1, size, f);
    fclose(f);
    if (n != (long)size || !plausible(buf, size)) {
        EMU_LOGW(TAG, "%s isn't a %lu KB ROM", path, (unsigned long)size / 1024);
        return false;
    }
    EMU_LOGI(TAG, "%s", path);
    return true;
}
