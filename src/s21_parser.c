#include "s21_parser.h"

/**********************************************************************/
/*                                                                    */
/*                      Parser of .obj files                          */
/*                                                                    */
/**********************************************************************/


int Parsing(char* filename, data_t *obj) {
    if (obj->meta_inf.memory_check != MEMORY_NULL) {
        free(obj->vertex_cords);
        free(obj->faces_cords);
    }
    initModel(obj);
    int result = 0;

    int index_faces_cords = 0, index_vertex_cords = 0;
    char line[512] = {};

    // количество vertex и face
    ParseVertFacCount(filename, obj);

    FILE* fpen = fopen(filename, "r");
    if (fpen != NULL) {
        
        // выделяем память для массивов
        if (obj->meta_inf.vertex_count > 0 && obj->meta_inf.faces_count > 0) {
            obj->vertex_cords = malloc(obj->meta_inf.vertex_count * sizeof(double));
            obj->faces_cords = malloc(obj->meta_inf.faces_count * sizeof(unsigned));
        }

        if (obj->vertex_cords != NULL && obj->faces_cords != NULL) {
            // Добавляем всё в массив
            while (fgets(line, 512, fpen) != NULL) {
                if (line[0] == 'v' && line[1] == ' ') {
                    ParseVertex(line, obj, &index_vertex_cords);
                } else if (line[0] == 'f' && line[1] == ' ') {
                    index_faces_cords = ParseFaces(line, obj, index_faces_cords);
                }
            }
            obj->meta_inf.memory_check = MEMORY_OK;
        } else {
            obj->meta_inf.memory_check = MEMORY_NULL;
        }

    } else {
        perror("fopen() ");
        obj->meta_inf.memory_check = MEMORY_NULL;
    }

    return result;
}

//
// Функция для добавления координат вершин в массив из плавающих точек
// index_of_cords - индекс координат вершин
//

void ParseVertex(char *line, data_t *obj, int *index_of_cords) {
    if (line[0] == 'v' && line[1] == ' ')  {
        sscanf(line, "v %lf %lf %lf",
        &obj->vertex_cords[*index_of_cords],
        &obj->vertex_cords[*index_of_cords+1],
        &obj->vertex_cords[*index_of_cords+2]);
        *index_of_cords += 3;
    }
}

//
// Функция для добавления индексов вершин в массив
// index_of_cords - индекс координат индексов
// closure_dig = первый индекс внутри f строчки в .obj файле, которым в конце нужно закрыть полигон
// (1) - индекс вершин в .obj файле начинается с 1, поэтому из каждого индекса отнимает 1
//

int ParseFaces(char *line, data_t *obj, int index_of_cords) {
    int closure_dig = '\0';
    int i_flag = 0;
    for (size_t i = 0; i < strlen(line); i++) {
        long int digital = 0;
        if (line[i] == ' ' && s21_digit_supp(line[++i])) {
            ++i_flag;
            char str[10] = {'\0'};
            int j = 0;
            while (s21_digit_supp(line[i])) {
                str[j] = line[i];
                i++;
                j++;
            }
            char *dig_end;
            digital = strtol(str, &dig_end, 10) - 1;  // (1)
            obj->faces_cords[index_of_cords] = digital;

            if (i_flag == 1) {
                closure_dig = digital;
                ++index_of_cords;
            }
            if (i_flag != 1) {
                obj->faces_cords[++index_of_cords] = digital;
                ++index_of_cords;
            }
        }
    }
    obj->faces_cords[index_of_cords++] = closure_dig;
    return (index_of_cords);
}

//
// Функция для считывания количества вершин и полигонов в .obj файле
// poligons - количество f строчек
// vertexes - количество v строчек
// faces_count - количество индексов внутри полигонов
//

void ParseVertFacCount(char *filename, data_t *obj) {
    FILE *fpen = fopen(filename, "r");

    int vertexes = 0,poligons = 0;

    if (fpen != NULL) {
        char line[512] = {};
        while (fgets(line, 512, fpen) != NULL) {
            if (line[0] == 'v' && line[1] == ' ') {
                vertexes += 1;
            } else if (line[0] == 'f' && line[1] == ' ') {
                for (int i = 0; i < (int)strlen(line); i++) {
                    if (line[i] == ' ' && s21_digit_supp(line[i+1])) {
                        poligons += 1;
                    }
                }
            }
        }
        obj->meta_inf.poligons_count = poligons;
        obj->meta_inf.faces_count = poligons * 2;
        obj->meta_inf.vertex_count = vertexes * 3;
        fclose(fpen);
    }
}

//
// Функция для проверки символа на принадлежность числа
//


int s21_digit_supp(char token) {
  int result = 0;
  if (token >= '0' && token <= '9') {
    result = 1;
  }
  return result;
}

// Инициализация модели

void initModel(data_t *obj) {
    obj->meta_inf.faces_count = 0;
    obj->meta_inf.vertex_count= 0;
    obj->meta_inf.memory_check= MEMORY_NULL;
}

