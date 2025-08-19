// boo_decrypt.c
// Compile: gcc boo_decrypt.c -o boo_decrypt
// Usage: ./boo_decrypt encrypted_file output_file

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define BOO_PADDER 4
#define BOO_KEY    0xFF

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: %s <encrypted_file> <output_file>\n", argv[0]);
        return 1;
    }

    const char *enc_path = argv[1];
    const char *out_path = argv[2];

    FILE *f_in = fopen(enc_path, "rb");
    if (!f_in) {
        perror("Unable to open encrypted file");
        return 1;
    }

    fseek(f_in, 0, SEEK_END);
    long file_size = ftell(f_in);
    rewind(f_in);

    unsigned char *buffer = malloc(file_size);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(f_in);
        return 1;
    }

    fread(buffer, 1, file_size, f_in);
    fclose(f_in);

    for (long i = 0; i < file_size; i++) {
        buffer[i] = (buffer[i] ^ BOO_KEY) - BOO_PADDER;
       
    }

    FILE *f_out = fopen(out_path, "wb");
    if (!f_out) {
        perror("Unable to create output file");
        free(buffer);
        return 1;
    }

    fwrite(buffer, 1, file_size, f_out);
    fclose(f_out);
    free(buffer);
    printf("Decryption complete! Output saved to %s\n", out_path);

    return 0;
}
