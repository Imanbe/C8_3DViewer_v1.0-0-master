#include "parser.h"

int Parsing(char* filename, data_t *obj) {
    int result = 0;

    int index_faces_cords = 0, index_vertex_cords = 0;
    char line[255] = {};

    // количество vertex и face
    ParseVertFacCount(filename, obj);

    FILE* fpen = fopen(filename, "r");
    if (fpen != NULL) {
        
        // выделяем память для массивов
        if (obj->meta_inf.vertex_count > 0 && obj->meta_inf.faces_count > 0) {
            obj->vertex_cords = malloc(obj->meta_inf.vertex_count * 3 * sizeof(double) + 1);
            obj->faces_cords = malloc(obj->meta_inf.faces_count * 2 * sizeof(int) + 1);
        }
        
        // Добавляем всё в массив
        while (fgets(line, 255, fpen) != NULL) {
            if (line[0] == 'v' && line[1] == ' ') {
                ParseVertex(line, obj, &index_vertex_cords);
            } else if (line[0] == 'f' && line[1] == ' ') {
                index_faces_cords = ParseFaces(line, obj, index_faces_cords);
            }
        }

    } else {
        perror("fopen() ");
        obj->meta_inf.memory_check = MEMORY_ERROR;
    }

    return result;
}


void ParseVertex(char *line, data_t *obj, int *index_of_cords) {
    if (line[0] == 'v' && line[1] == ' ')  {
        sscanf(line, "v %lf %lf %lf",
        &obj->vertex_cords[*index_of_cords],
        &obj->vertex_cords[*index_of_cords+1],
        &obj->vertex_cords[*index_of_cords+2]);
        *index_of_cords += 3;
    }
}

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
            digital = strtol(str, &dig_end, 10);
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

void ParseVertFacCount(char *filename, data_t *obj) {
    FILE *fpen = fopen(filename, "r");
    int i = 0;

    if (fpen != NULL) {
        char line[255] = {};
        while (fgets(line, 255, fpen) != NULL) {
            if (line[0] == 'v' && line[1] == ' ') {
                obj->meta_inf.vertex_count += 1;
            } else if (line[0] == 'f' && line[1] == ' ') {
                i = 0;
                while (line[i] != '\n' && line[i] != '\0') {
                    if (line[i] == ' ') {
                        obj->meta_inf.faces_count += 1;
                    }
                    i++;
                }
            }
        }
        fclose(fpen);
    }
}

void PrintCords(data_t *obj) {
    printf("---%d---\n", obj->meta_inf.vertex_count);
    int j = 1;
    for (int i = 0; i < obj->meta_inf.vertex_count * 3; i++) {
        printf("%lf ", obj->vertex_cords[i]);
        if (j % 3 == 0) {
            printf("\n");
        }
        j++;
    }
}

void PrintCords2(data_t *obj) {
    printf("---%d---\n", obj->meta_inf.faces_count);
    int j = 1;
    for (int i = 0; i < obj->meta_inf.faces_count * 2; i++) {
        printf("%d ", obj->faces_cords[i]);
        if (j % 3 == 0) {
            printf("\n");
        }
        j++;
    }
}

int s21_digit_supp(char ind) {
  int result = 0;
  if (ind >= '0' && ind <= '9') {
    result = 1;
  }
  return result;
}
