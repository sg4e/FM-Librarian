/*
 * MIT License
 *
 * Copyright (c) 2021 sg4e
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>

#define LIBRARY_BYTE_SIZE 91
#define MEMCARD_BLOCK_SIZE 0x2000
#define FRAME_OFFSET 0xCBC
#define OFFSET MEMCARD_BLOCK_SIZE + FRAME_OFFSET
#define MIN_MEMCARD_SIZE 128 * 1024

void print_help();

int main (int argc, char **argv) {
    FILE *fp;
    FILE *fout;
    unsigned char *buf;
    unsigned int card;
    unsigned int total;
    unsigned int offset;
    char *memcard_path;
    char *textfile_path;

    offset = OFFSET;
    if(argc >= 2 && (strcmp(argv[1], "--help") == 0)) {
        print_help(argv[0]);
        return 0;
    }
    else if(argc == 5 && strcmp(argv[1], "--block") == 0) {
        int block = atoi(argv[2]);
        if(block < 1 || block > 15) {
            printf("Invalid block number. Exiting...");
            return 0;
        }
        printf("Using block %d\n", block);
        offset = (MEMCARD_BLOCK_SIZE * block) + FRAME_OFFSET;
        memcard_path = argv[3];
        textfile_path = argv[4];
    }
    else if(argc == 3) {
      memcard_path = argv[1];
      textfile_path = argv[2];
    }
    else {
        print_help(argv[0]);
        return 0;
    }

    fp = fopen(memcard_path,"rb");
    buf = (unsigned char *)malloc(LIBRARY_BYTE_SIZE);

    fseek(fp, 0L, SEEK_END);
    int size = ftell(fp);
    if(size < MIN_MEMCARD_SIZE) {
        printf("Memory card image is too small. Memory cards must be 128kb.");
        fclose(fp);
        return 0;
    }
    if(size > MIN_MEMCARD_SIZE) {
        printf("Memory card image is larger than expected. Memory cards should be 128kb. "
        "Results may be inaccurate.");
    }
    rewind(fp);
    fseek(fp, offset, SEEK_SET);
    fread(buf, LIBRARY_BYTE_SIZE, 1, fp);
    fclose(fp);

    fout = fopen(textfile_path,"w");

    card = 1;
    total = 0;
    for(unsigned int index = 0; index < LIBRARY_BYTE_SIZE; index++) {
        unsigned char bitfield = buf[index];
        for(unsigned int bit = 1; bit <= 8; bit++) {
            if(card == 1) { // the top bits of the 1st library byte are ignored
                bit++;
            }
            if((bitfield >> (8 - bit)) & 0x01) {
                fprintf(fout, "%d\n", card);
                total++;
            }
            card++;
        }
    }
    printf("Total cards: %d\n", total);
    fclose(fout);
    return(0);
}

void print_help(char *executable_name) {
    printf("Usage: %s (options) [memory card image] [output file]\n", executable_name);
    printf("\nOptions:\n--help\t\tPrints this help text\n");
    printf("--block [n]\tRead the nth block on the memory card. "
    "Default: 1. Values other than 1 are untested\n");
}
