#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ARRAYTEXT_H
#define ARRAYTEXT_H

void arrtext(const char *filename, int **data, int rows, int cols);
void textarr(const char *filename, int ***data, int *rows, int *cols); // Sütun sayısını otomatik belirleyecek

#endif // ARRAYTEXT_H
