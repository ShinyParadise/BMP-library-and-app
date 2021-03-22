#define _CRT_SECURE_NO_WARNINGS
#define strMAX 21
#define fileMAX 100


#include "fileHandling.h"
#include "rotate.h"
#include "flip.h"
#include "upscale.h"
#include "downscale.h"
#include "bright.h"
#include "crop.h"
#include <iostream>
#include <cstring>

int main() {
    FILE* comms = fopen("command.txt", "rt");
    short C, N;
    (void)fscanf(comms, "%hi\n%hi\n", &C, &N);

    auto inputs = new bmpFile[C];

    for (int i = 0; i < C; i++)
        inputs[i] = readBMP(i+1);

    for (int i = 0; i < N; i++) {
        auto fileList = new short[fileMAX]();
        char func[strMAX] = { 0 };
        char strFiles[300] = { 0 };
        short V = 1, H = 1, angle = 0, f = 0, delta = 0;
        char args = 0;

        (void)fscanf(comms, "%s : %s : ", strFiles, func);

        if (!strcmp(func, "upscale") || !strcmp(func, "downscale"))
            (void)fscanf(comms, "%hi %hi\n", &V, &H);
        else if (!strcmp(func, "flip"))
            (void)fscanf(comms, "%c\n", &args);
        else if (!strcmp(func, "rotate"))
            (void)fscanf(comms, "%hi\n", &angle);
        else if (!strcmp(func, "bright"))
            (void)fscanf(comms, "%hi\n", &f);
        else if (!strcmp(func, "crop"))
            (void)fscanf(comms, "%hi\n", &delta);

        // парсинг номеров нужных файлов для обработки
        int listSize = 0;
        for (int j = 0; strFiles[j] != '\0'; j+=3) {
            char buf[2] = { 0 };
            buf[0] = strFiles[j];
            buf[1] = strFiles[j+1];
            fileList[listSize] = (short)atoi(buf);
            listSize++;
        }


        if (fileList[0] != 0) {
            for (int k = 0; k < listSize; k++) {
                if (!strcmp(func, "flip"))
                    flip(&inputs[fileList[k]-1], args);
                else if (!strcmp(func, "rotate"))
                    rotate(&inputs[fileList[k]-1], angle);
                else if (!strcmp(func, "upscale"))
                    upscale(&inputs[fileList[k]-1], V, H);
                else if (!strcmp(func, "downscale"))
                    downscale(&inputs[fileList[k]-1], V, H);
                else if (!strcmp(func, "bright"))
                    bright(&inputs[fileList[k]-1], f);
                else if (!strcmp(func, "crop"))
                    crop(delta, &inputs[fileList[k]-1]);
            }
        }
        else {
            for (int k = 0; k < C; k++) {
                if (!strcmp(func, "flip"))
                    flip(&inputs[k], args);
                else if (!strcmp(func, "rotate"))
                    rotate(&inputs[k], angle);
                else if (!strcmp(func, "upscale"))
                    upscale(&inputs[k], V, H);
                else if (!strcmp(func, "downscale"))
                    downscale(&inputs[k], V, H);
                else if (!strcmp(func, "bright"))
                    bright(&inputs[k], f);
                else if (!strcmp(func, "crop"))
                    crop(delta, &inputs[k]);
            }
        }
        delete[] fileList;
    }
    
    for (int i = 0; i < C; i++)
        writeBMP(i+1, &inputs[i]);

    delete[] inputs;
    fclose(comms);
    return 0;
}
