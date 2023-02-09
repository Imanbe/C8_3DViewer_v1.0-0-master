#include "parser.h"

int Parsing(char* filename, data_t *obj) {
    FILE* fpen = fopen(filename, "r");
    int result = 0;

    int index_faces_cords = 0, index_vertex_cords = 0;
    char line[255] = {};


    if (fpen != NULL) {

        ParseVertFacCount(fpen, obj);
        
        if ((*obj).vertex_count > 0 && (*obj).faces_count > 0) {
            (*obj).vertex_cords = malloc((*obj).vertex_count * 3 * sizeof(double) + 1);
            (*obj).faces_cords = malloc((*obj).faces_count * 2 * sizeof(int) + 1);
        }

        
        // Добавляем всё в массив
        fpen = fopen(filename, "r");
        while (fgets(line, 255, fpen) != NULL) {
            if (line[0] == 'v' && line[1] == ' ') {
                ParseVertex(line, obj, &index_vertex_cords);
            } else if (line[0] == 'f' && line[1] == ' ') {
                index_faces_cords = ParseFaces(line, obj, index_faces_cords);
            }
        }

        PrintCords(obj);
        printf("\n\n\n");
        PrintCords2(obj);
        // PrintCords2(obj);

    } else {
        perror("fopen() ");
        result = 1;
        printf("%s name of file\n", filename);
    }

    return result;
    free(obj->faces_cords);
    free(obj->vertex_cords);
    obj->faces_cords = NULL;
    obj->vertex_cords = NULL;
}


void ParseVertex(char *line, data_t *obj, int *index_of_cords) {
    double digital;
    for (size_t i = 0; i < strlen(line); i++) {
        if (line[i] == ' ') {
            i += 1;
            const char *dig_start = &line[i];
            while (strchr(line, ' ') == NULL) {
                i += 1;
            }
            char *dig_end = &line[i];
            digital = strtod(dig_start, &dig_end);
            (*obj).vertex_cords[*index_of_cords] = digital;
            *index_of_cords += 1;
        }
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
            // int i_str = i;
            while (s21_digit_supp(line[i])) {
                str[j] = line[i];
                i++;
                j++;
            }
            char *dig_end;
            digital = strtol(str, &dig_end, 10);
            (*obj).faces_cords[index_of_cords] = digital;

            if (i_flag == 1) {
                closure_dig = digital;
                ++index_of_cords;
            }
            if (i_flag != 1) {
                (*obj).faces_cords[++index_of_cords] = digital;
                ++index_of_cords;
            }
        }
    }
    (*obj).faces_cords[index_of_cords++] = closure_dig;
    return (index_of_cords);
}

void ParseVertFacCount(FILE *fpen, data_t *obj) {
    char c;
    char bel_c;

    c = fgetc(fpen);
    bel_c = fgetc(fpen);

    while ((bel_c != EOF)) {
        if (c == 'v' && bel_c == ' ') {
            (*obj).vertex_count += 1;
        } else if (c == 'f') {
            while (bel_c != '\n' && bel_c != EOF) {
                if (bel_c == ' ') {
                    (*obj).faces_count += 1;
                }
                bel_c = fgetc(fpen);
            }
        }
        c = bel_c;
        bel_c = fgetc(fpen);
    }        
}

void PrintCords(data_t *obj) {
    printf("---%lf---\n", (*obj).vertex_count);
    int j = 1;
    for (int i = 0; i < (*obj).vertex_count * 3; i++) {
        printf("%lf ", (*obj).vertex_cords[i]);
        if (j % 3 == 0) {
            printf("\n");
        }
        j++;
    }
}

void PrintCords2(data_t *obj) {
    printf("---%d---\n", (*obj).faces_count);
    int j = 1;
    for (int i = 0; i < (*obj).faces_count * 2; i++) {
        printf("%d ", (*obj).faces_cords[i]);
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
