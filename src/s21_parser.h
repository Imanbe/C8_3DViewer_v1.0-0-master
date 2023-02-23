#ifndef SRC_PARSER_H

#define SRC_PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define MEMORY_OK 1
#define MEMORY_ERROR -1
#define MEMORY_NULL 0

//
// Структура для хранения данных .obj файла
//
// meta_t:
// 1. vertex_count - количество вершин
// 2. faces_count - количество индексов
// 3. poligons_count - количество полигонов
// 4. memory_check - проверка на корректность загрузки модели
//
// data_t:
// 1. vertex_cords - массив вершин
// 2. faces_cords - массив индексов
// 3. meta_t


typedef struct METADATA {
    unsigned vertex_count;
    unsigned faces_count;
    unsigned poligons_count;
    unsigned memory_check;
} meta_t;

typedef struct DATA {
    double *vertex_cords;
    unsigned *faces_cords;
    meta_t meta_inf;
} data_t;

int Parsing(char* filename, data_t *obj);
void ParseVertFacCount(char *filename, data_t *obj);
void ParseVertex(char *line, data_t *obj, int *index_of_cords);
int ParseFaces(char *line, data_t *obj, int index_of_cords);
int s21_digit_supp(char token);

void initModel(data_t *obj);

#endif  // SRC_PARSER_H
