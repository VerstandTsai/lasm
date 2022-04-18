#include <stdio.h>
#include <string.h>

void assemble(char filename[]) {
    char *inst_set[] = {
        "lda",
        "sta",
        "ldb",
        "stb",
        "jmp",
        "jc",
        "out",
        "hlt",
        "and",
        "or",
        "xor",
        "not",
        "shl",
        "shr",
        "add",
        "sub"
    };

    char outname[32];
    strcpy(outname, filename);
    char *outext = strrchr(outname, '.');
    *outext = '\0';

    int binary[16];
    for (int i=0; i<16; i++) { binary[i] = 0; }
    FILE *code = fopen(filename, "r");
    char operator[8];
    int operand0;
    int operand1;
    int bin_index = 0;
    while (fscanf(code, "%s %d %d", operator, &operand0, &operand1) != EOF) {
        if (!strcmp(operator, "dat")) {
            binary[operand0] = operand1;
            continue;
        }
        for (int i=0; i<16; i++) {
            if (!strcmp(operator, inst_set[i])) {
                binary[bin_index] = 16*i;
                binary[bin_index] += operand0;
                break;
            }
        }
        bin_index++;
    }
    fclose(code);

    FILE *binfile = fopen(outname, "w");
    fprintf(binfile, "v3.0 hex words plain\n");
    for (int i=0; i<16; i++) {
        fprintf(binfile, "%x", binary[i]);
        if (i != 15) { fprintf(binfile, " "); }
    }
    fclose(binfile);
}

int main(int argc, char *argv[]) {
    assemble(argv[1]);
    return 0;
}
