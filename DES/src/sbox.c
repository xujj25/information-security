#include <stdio.h>

int main(int argc, char const *argv[])
{
    int s_box[8][4][16];
    int i, j, k;
    for (i = 0; i < 8; i++)
        for (j = 0; j < 4; j++)
            for (k = 0; k < 16; k++)
                scanf("%d", &s_box[i][j][k]);

    printf("{\n");
    for (i = 0; i < 8; i++) {
        printf("\t{\n");
        for (j = 0; j < 4; j++) {
            printf("\t\t{ ");
            for (k = 0; k < 15; k++)
                printf("%d, ", s_box[i][j][k]);
            printf("%d", s_box[i][j][15]);
            printf(" },\n");
        }
        printf("\t},\n");
    }
    printf("};\n");

    return 0;
}