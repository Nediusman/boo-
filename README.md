bOO Tools - Detection and Decryption
====================================

This zip archive contains two C programs:

1. moo_decrypt.c
----------------
- Decrypts a file that was encrypted using the MOO XOR encryption scheme.
- Compile: gcc boo_decrypt.c -o moo_decrypt
- Usage: ./boo_decrypt encrypted_file output_file

2. boo_detect.c
---------------
- Detects files likely encrypted by the MOO algorithm and moves them to a quarantine folder.
- Compile: gcc boo_detect.c -o boo_detect
- Usage: ./boo_detect file_to_check quarantine_folder

Instructions:
-------------
1. Compile the programs using gcc as shown above.
2. Use `boo_detect` to find and isolate suspicious files.
3. Use `boo_decrypt` to recover original contents from encrypted files.
