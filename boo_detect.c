// boo_detect.c
// Compile: gcc boo_detect.c -o moo_detect
// Usage: ./boo_detect file_to_check quarantine_folder

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define BOO_PADDER 4
#define BOO_KEY    0xFF
#define SAMPLE_BYTES 16

int looks_like_boo_encrypted(unsigned char *buffer, size_t size) {
    for (size_t i = 0; i < size; i++) {
        unsigned char dec = (buffer[i] ^ BOO_KEY) - BOO_PADDER;
        if (dec < 0x20 || dec > 0x7E) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: %s <file_to_check> <quarantine_folder>\n", argv[0]);
        return 1;
    }

    const char *file_path = argv[1];
    const char *quarantine_folder = argv[2];

    FILE *f = fopen(file_path, "rb");
    if (!f) {
        perror("Cannot open file");
        return 1;
    }

    unsigned char sample[SAMPLE_BYTES];
    size_t read = fread(sample, 1, SAMPLE_BYTES, f);
    fclose(f);

    if (read == 0) {
        printf("File empty or cannot read sample.\n");
        return 1;
    }

    if (looks_like_moo_encrypted(sample, read)) {
        printf("Warning: File appears to be encrypted by MOO! -> %s\n", file_path);
        char newpath[1024];
        snprintf(newpath, sizeof(newpath), "%s/%s", quarantine_folder, strrchr(file_path, '/') ? strrchr(file_path, '/')+1 : file_path);
        if (rename(file_path, newpath) == 0) {
            printf("File moved to quarantine: %s\n", newpath);
        } else {
            perror("Failed to move file to quarantine");
            return 1;
        }
    } else {
        printf("File looks normal (not moo-encrypted).\n");
    }

    return 0;
}
