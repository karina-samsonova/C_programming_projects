#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define size 200

typedef struct Racers{
    int number;
    char sign[5];
    char name[6][20];
    char surname[6][20];
    char car[20];
    char country[6][20];
    int score;
}RACERS;
void Declensions(int racers_count, RACERS racers[]) {        //склонение имен участников гонок
    for (int i = 0; i < racers_count; ++i) {
        for (int j = 1; j < 6; ++j) {
            strcpy(racers[i].name[j], racers[i].name[0]);
            strcpy(racers[i].surname[j], racers[i].surname[0]);
            strcpy(racers[i].country[j], racers[i].country[0]);
        }
        int end = strlen(racers[i].name[0]) - 1;
        if (!(racers[i].name[0][end] == 'а' || racers[i].name[0][end] == 'о' ||
            racers[i].name[0][end] == 'е' || racers[i].name[0][end] == 'и' ||
            racers[i].name[0][end] == 'у' || racers[i].name[0][end] == 'э' ||
            racers[i].name[0][end] == 'ю' || racers[i].name[0][end] == 'я')) {
            if (racers[i].name[0][end] == 'ь')
                end--;
            end++;
            racers[i].name[1][end] = 'а';
            racers[i].name[2][end] = 'у';
            racers[i].name[3][end] = 'а';
            racers[i].name[4][end] = 'о';
            racers[i].name[4][end + 1] = 'м';
            racers[i].name[5][end] = 'е';
            end++;
            racers[i].name[1][end] = '\0';
            racers[i].name[2][end] = '\0';
            racers[i].name[3][end] = '\0';
            racers[i].name[4][end + 1] = '\0';
            racers[i].name[5][end] = '\0';
        }

        end = strlen(racers[i].surname[0]) - 1;
        if (!(racers[i].surname[0][end] == 'а' || racers[i].surname[0][end] == 'о' ||
            racers[i].surname[0][end] == 'е' || racers[i].surname[0][end] == 'и' ||
            racers[i].surname[0][end] == 'у' || racers[i].surname[0][end] == 'э' ||
            racers[i].surname[0][end] == 'ю' || racers[i].surname[0][end] == 'я')) {
            if (racers[i].surname[0][end] == 'ь')
                end--;
            end++;
            racers[i].surname[1][end] = 'а';
            racers[i].surname[2][end] = 'у';
            racers[i].surname[3][end] = 'а';
            racers[i].surname[4][end] = 'о';
            racers[i].surname[4][end + 1] = 'м';
            racers[i].surname[5][end] = 'е';
            end++;
            racers[i].surname[1][end] = '\0';
            racers[i].surname[2][end] = '\0';
            racers[i].surname[3][end] = '\0';
            racers[i].surname[4][end + 1] = '\0';
            racers[i].surname[5][end] = '\0';
        }

        end = strlen(racers[i].country[0]) - 1;
        if (racers[i].country[0][end] == 'я') {
            racers[i].country[1][end] = 'и';
            racers[i].country[2][end] = 'и';
            racers[i].country[3][end] = 'ю';
            racers[i].country[4][end] = 'е';
            racers[i].country[4][end + 1] = 'й';
            racers[i].country[5][end] = 'и';
            end++;
            racers[i].country[1][end] = '\0';
            racers[i].country[2][end] = '\0';
            racers[i].country[3][end] = '\0';
            racers[i].country[4][end + 1] = '\0';
            racers[i].country[5][end] = '\0';
        }
        else if (racers[i].country[0][end] == 'ы') {
            racers[i].country[1][end] = '\0';
            racers[i].country[2][end] = 'а';
            racers[i].country[2][end + 1] = 'м';
            racers[i].country[4][end] = 'а';
            racers[i].country[4][end + 1] = 'м';
            racers[i].country[4][end + 2] = 'и';
            racers[i].country[5][end] = 'а';
            racers[i].country[5][end + 1] = 'х';
            end++;
            racers[i].country[2][end + 1] = '\0';
            racers[i].country[3][end] = '\0';
            racers[i].country[4][end + 2] = '\0';
            racers[i].country[5][end + 1] = '\0';
        }
        else {
            end++;
            racers[i].country[1][end] = '\0';
            racers[i].country[2][end] = '\0';
            racers[i].country[3][end] = '\0';
            racers[i].country[4][end] = '\0';
            racers[i].country[5][end] = '\0';
        }
    }
}
int RacerSearch(char sign[], int racers_count, RACERS racers[]) {
    for (int i = 0; i < racers_count; ++i) {
        if (strcmp(racers[i].sign, sign) == 0)
            return i;
    }
    return -1;
}
int main() {
    char* locale;
    locale = setlocale(LC_ALL, "RUS");
    FILE* in = fopen("input.txt", "rt");
    RACERS racers[50];
    int racers_count = 0;
    char str[size] = { 0 };

    FILE* fracers = fopen("racers.txt", "rt");
    while (!feof(fracers)) {        //считываем файл с участниками гонок
        fgets(str, size, fracers);
        sscanf(str, "%d %s %s %s", &racers[racers_count].number, racers[racers_count].sign, racers[racers_count].name[0], 
            racers[racers_count].surname[0]);
        int ind = strlen(racers[racers_count].sign) + strlen(racers[racers_count].name[0]) + strlen(racers[racers_count].surname[0]) + 2;
        while (str[ind] < 'A' || str[ind] > 'z')
            ++ind;
        int temp = ind;
        while ((str[ind] >= 'A' && str[ind] <= 'z') || str[ind] == ' ') {
            racers[racers_count].car[ind - temp] = str[ind];
            ++ind;
        }
        racers[racers_count].car[ind - temp] = '\0';
        char* p = strstr(str, racers[racers_count].car) + strlen(racers[racers_count].car);
        sscanf(p, "%s %d", racers[racers_count].country, &racers[racers_count].score);
        /*char* p = strstr(str, racers[racers_count].surname[0]) + strlen(racers[racers_count].surname[0]);
        char str1[size] = { 0 };
        char str2[size] = { 0 };
        sscanf(p, "%s %s", str1, str2);
        if (str2[0] >= 'A' && str2[0] <= 'z') {
            strcpy(racers[racers_count].car, str1);
            int len = strlen(racers[racers_count].car);
            racers[racers_count].car[len] = ' ';
            int j = len + 1;
            for (; j < len + strlen(str2) + 1; ++j)
                racers[racers_count].car[j] = str2[j - len - 1];
            racers[racers_count].car[j] = '\0';
            p = strstr(str, str2) + strlen(str2);
            sscanf(p, "%s %d", racers[racers_count].country[0], &racers[racers_count].score);
        }
        else {
            strcpy(racers[racers_count].car, str1);
            strcpy(racers[racers_count].country[0], str2);
            p = strstr(str, str2) + strlen(str2);
            sscanf(p, "%d", &racers[racers_count].score);
        }*/
        racers_count++;
    }
    fclose(fracers);
    Declensions(racers_count, racers);
    
    srand(time(NULL));
    int temp_circle = 0;
    int r_circle = -1;
    int r_start = -1;
    int r_deroad = -1;
    int r_mistake = -1;
    int r_stop = -1;
    int r_best = -1;
    int r_leader = -1;
    int r_finish = -1;
    int r_overtake = -1;
    int r_moving = -1;
    int r_pace = -1;
    int r_fight = -1;
    int r_collision = -1;
    int r_score = -1;
    int r_final_score = -1;
    int final_score[10] = { 10, 8, 6, 5, 4, 3, 2, 1 };
    while (!feof(in)) {
        fgets(str, size, in);
        int circle = 0;
        char sign[20] = { 0 };
        char act[20] = { 0 };
        sscanf(str, "%d %s %s", &circle, sign, act);
        if (circle != temp_circle) {
            if (circle > 1)
                printf("\n");
            int r = rand() % 4;
            if (r == r_circle)
                r = (r + 1) % 4;
            r_circle = r;
            if (r == 0)
                printf("События %d-го круга:\n", circle);
            else if (r == 1)
                printf("Начинаем следить за %d-м кругом:\n", circle);
            else if (r == 2)
                printf("Пошел %d-й круг:\n", circle);
            else if (r == 3)
                printf("Наблюдаем за событиями %d-го круга:\n", circle);
            temp_circle = circle;
        }
        char* p = strstr(str, act) + strlen(act);

        if (strcmp(act, "старт") == 0) {
            int position = 0;
            char str1[size] = { 0 };
            sscanf(p, "%s", str1);
            sscanf(str1, "%d", &position);
            p = strstr(p, str1) + strlen(str1);
            int r = rand() % 7;
            if (r == r_start)
                r = (r + 1) % 7;
            r_start = r;
            int i = RacerSearch(sign, racers_count, racers);
            if (position == 2) {
                if (r == 0) {
                    printf("Участник команды %s %s %s из %s стартовал со %d-й позиции", racers[i].car, racers[i].name[0], racers[i].surname[0], racers[i].country[5], position);
                }
                else if (r == 1) {
                    printf("Со %d-й позиции стартовал представитель команды %s %s %s из %s", position, racers[i].car, racers[i].name[0], racers[i].surname[0], racers[i].country[5]);
                }
                else if (r == 2) {
                    if (position == 3)
                        printf("%d-я позиция на стартовой решетке у %s %s из %s, представляющего %s", position, racers[i].name[1], racers[i].surname[1], racers[i].country[5], racers[i].car);
                    else
                        printf("%d-ая позиция на стартовой решетке у %s %s из %s, представляющего %s", position, racers[i].name[1], racers[i].surname[1], racers[i].country[5], racers[i].car);
                }
                else if (r == 3) {
                    printf("Член команды %s %s %s из %s начал гонку со %d-го места", racers[i].car, racers[i].name[0], racers[i].surname[0], racers[i].country[5], position);
                }
                else if (r == 4) {
                    printf("Со %d-го места начал заезд %s %s из %s, представляющий команду %s", position, racers[i].name[0], racers[i].surname[0], racers[i].country[5], racers[i].car);
                }
                else if (r == 5) {
                    printf("Со %d-й позиции начал гонку %s %s из %s, участвующий от команды %s", position, racers[i].name[0], racers[i].surname[0], racers[i].country[5], racers[i].car);
                }
                else if (r == 6) {
                    printf("%s %s из %s, представляющий команду %s, начал соревнование со %d-й позиции", racers[i].name[0], racers[i].surname[0], racers[i].country[5], racers[i].car, position);
                }
            }
            else {
                if (r == 0) {
                    printf("Участник команды %s %s %s из %s стартовал с %d-й позиции", racers[i].car, racers[i].name[0], racers[i].surname[0], racers[i].country[5], position);
                }
                else if (r == 1) {
                    printf("С %d-й позиции стартовал представитель команды %s %s %s из %s", position, racers[i].car, racers[i].name[0], racers[i].surname[0], racers[i].country[5]);
                }
                else if (r == 2) {
                    if (position == 3)
                        printf("%d-я позиция на стартовой решетке у %s %s из %s, представляющего %s", position, racers[i].name[1], racers[i].surname[1], racers[i].country[5], racers[i].car);
                    else
                        printf("%d-ая позиция на стартовой решетке у %s %s из %s, представляющего %s", position, racers[i].name[1], racers[i].surname[1], racers[i].country[5], racers[i].car);
                }
                else if (r == 3) {
                    printf("Член команды %s %s %s из %s начал гонку с %d-го места", racers[i].car, racers[i].name[0], racers[i].surname[0], racers[i].country[5], position);
                }
                else if (r == 4) {
                    printf("С %d-го места начал заезд %s %s из %s, представляющий команду %s", position, racers[i].name[0], racers[i].surname[0], racers[i].country[5], racers[i].car);
                }
                else if (r == 5) {
                    printf("С %d-й позиции начал гонку %s %s из %s, участвующий от команды %s", position, racers[i].name[0], racers[i].surname[0], racers[i].country[5], racers[i].car);
                }
                else if (r == 6) {
                    printf("%s %s из %s, представляющий команду %s, начал соревнование с %d-й позиции", racers[i].name[0], racers[i].surname[0], racers[i].country[5], racers[i].car, position);
                }
            }
            strcpy(str1, p);
            while (str1[p - str1] == '\t') {
                p = strchr(str1, '\t') + 1;
                strcpy(str1, p);
            }
            if (strlen(p) > 1) {
                p[strlen(p) - 1] = '\0';
                if (p[0] != ':' && p[0] != ',')
                    printf(" ");
                printf("%s", p);
            }
            printf(". \n");
        }

        else if (strcmp(act, "сход") == 0) {
            int r = rand() % 7;
            if (r == r_deroad)
                r = (r + 1) % 7;
            r_deroad = r;
            int i = RacerSearch(sign, racers_count, racers);
            if (r == 0) {
                printf("%s %s вынужден закончить гонку", racers[i].name[0], racers[i].surname[0]);
            }
            else if (r == 1) {
                printf("%s %s сошел с дистанции", racers[i].name[0], racers[i].surname[0]);
            }
            else if (r == 2) {
                printf("%s %s вынужден закончить заезд", racers[i].name[0], racers[i].surname[0]);
            }
            else if (r == 3) {
                printf("%s %s вынужден закончить соревнование", racers[i].name[0], racers[i].surname[0]);
            }
            else if (r == 4) {
                printf("%s %s вынужден завершить гонку", racers[i].name[0], racers[i].surname[0]);
            }
            else if (r == 5) {
                printf("%s %s вынужден завершить заезд", racers[i].name[0], racers[i].surname[0]);
            }
            else if (r == 6) {
                printf("%s %s вынужден завершить соревнование", racers[i].name[0], racers[i].surname[0]);
            }
            char str1[size] = { 0 };
            strcpy(str1, p);
            while (str1[p - str1] == '\t') {
                p = strchr(str1, '\t') + 1;
                strcpy(str1, p);
            }
            if (strlen(p) > 1) {
                p[strlen(p) - 1] = '\0';
                if (p[0] != ':' && p[0] != ',')
                    printf(" ");
                printf("%s", p);
            }
            printf(". \n");
        }

        else if (strcmp(act, "ошибка") == 0) {
            char str1[size] = { 0 };
            strcpy(str1, p);
            while (str1[p - str1] == '\t') {
                p = strchr(str1, '\t') + 1;
                strcpy(str1, p);
            }
            if (strlen(p) > 1)
                p[strlen(p) - 1] = '\0';
            int r = rand() % 3;
            if (r == r_mistake)
                r = (r + 1) % 3;
            r_mistake = r;
            int i = RacerSearch(sign, racers_count, racers);
            if (r == 0) {
                printf("%s %s ошибся - %s", racers[i].name[0], racers[i].surname[0], p);
            }
            else if (r == 1) {
                printf("Из-за ошибки (%s) %s потерял свою позицию", p, racers[i].surname[0]);
            }
            else if (r == 2) {
                printf("%s %s совершил ошибку - %s", racers[i].name[0], racers[i].surname[0], p);
            }
            printf(". \n");
        }

        else if (strcmp(act, "питстоп") == 0) {
            int r = rand() % 6;
            if (r == r_stop)
                r = (r + 1) % 6;
            r_stop = r;
            int i = RacerSearch(sign, racers_count, racers);
            if (r == 0) {
                printf("%s %s заехал в боксы", racers[i].name[0], racers[i].surname[0]);
            }
            else if (r == 1) {
                printf("%s обслужил свой болид %s", racers[i].surname[0], racers[i].car);
            }
            else if (r == 2) {
                printf("%s %s сделал питстоп", racers[i].name[0], racers[i].surname[0]);
            }
            else if (r == 3) {
                printf("Свой питстоп сделал %s %s", racers[i].name[0], racers[i].surname[0]);
            }
            else if (r == 4) {
                printf("В боксах отметился %s", racers[i].surname[0]);
            }
            else if (r == 5) {
                printf("%s обслужил свой автомобиль %s", racers[i].surname[0], racers[i].car);
            }
            char str1[size] = { 0 };
            strcpy(str1, p);
            while (str1[p - str1] == '\t') {
                p = strchr(str1, '\t') + 1;
                strcpy(str1, p);
            }
            if (strlen(p) > 1) {
                p[strlen(p) - 1] = '\0';
                if (p[0] != ':' && p[0] != ',')
                    printf(" ");
                printf("%s", p);
            }
            printf(". \n");

        }

        else if (strcmp(act, "лучшкруг") == 0) {
            char sec[50] = { 0 };
            sscanf(p, "%s", sec);
            int r = rand() % 5;
            if (r == r_best)
                r = (r + 1) % 5;
            r_best = r;
            int i = RacerSearch(sign, racers_count, racers);
            if (r == 0) {
                printf("Лучший круг у %s %s: %s.\n", racers[i].name[1], racers[i].surname[1], sec);
            }
            else if (r == 1) {
                printf("Лучший круг у %s %s - %s.\n", racers[i].name[1], racers[i].surname[1], sec);
            }
            else if (r == 2) {
                printf("%s %s прошел круг за %s.\n", racers[i].name[0], racers[i].surname[0], sec);
            }
            else if (r == 3) {
                printf("Самый быстрый круг у %s %s: %s.\n", racers[i].name[1], racers[i].surname[1], sec);
            }
            else if (r == 4) {
                printf("Самый быстрый круг у %s %s - %s.\n", racers[i].name[1], racers[i].surname[1], sec);
            }
        }
        else if (strcmp(act, "лидер") == 0) {
            float sec = 0;
            int bef = 0;
            int aft = 0;
            sscanf(p, "%d.%d", &bef, &aft);
            sec = sec + bef + (float)(aft * 0.1);
            int r = rand() % 2;
            if (r == r_leader)
                r = (r + 1) % 2;
            r_leader = r;
            int i = RacerSearch(sign, racers_count, racers);
            if (aft == 0) {
                if (r == 0) {
                    printf("%s лидирует в гонке с отрывом в %d секунд", racers[i].surname[0], (int)sec);
                    if (sec == 1.0)
                        printf("у.\n");
                    else if (sec - 5.0 > 0.0 && aft == 0.0)
                        printf(". \n");
                    else
                        printf("ы.\n");
                }
                else if (r == 1) {
                    printf("Первым идет %s, опережая ближайшего преследователя на %d секунд", racers[i].surname[0], (int)sec);
                    if (sec == 1.0)
                        printf("у.\n");
                    else if (sec - 5.0 > 0.0 && aft == 0.0)
                        printf(". \n");
                    else
                        printf("ы.\n");
                }
            }
            else {
                if (r == 0) {
                    printf("%s лидирует в гонке с отрывом в %.1f секунд", racers[i].surname[0], sec);
                    if (sec == 1.0)
                        printf("у.\n");
                    else if (sec - 5.0 > 0.0 && aft == 0.0)
                        printf(". \n");
                    else
                        printf("ы.\n");
                }
                else if (r == 1) {
                    printf("Первым идет %s, опережая ближайшего преследователя на %.1f секунд", racers[i].surname[0], sec);
                    if (sec == 1.0)
                        printf("у.\n");
                    else if (sec - 5.0 > 0.0 && aft == 0.0)
                        printf(". \n");
                    else
                        printf("ы.\n");
                }
            }
        }

        else if (strcmp(act, "обгон") == 0) {
            char pilot[20] = { 0 };
            sscanf(p, "%s", pilot);
            p = strstr(p, pilot) + strlen(pilot);
            int r = rand() % 7;
            if (r == r_overtake)
                r = (r + 1) % 7;
            r_overtake = r;
            int i = RacerSearch(sign, racers_count, racers);
            int j = RacerSearch(pilot, racers_count, racers);
            if (r == 0) {
                printf("%s %s обогнал %s %s", racers[i].name[0], racers[i].surname[0], racers[j].name[3], racers[j].surname[3]);
            }
            else if (r == 1) {
                printf("%s обогнал %s", racers[i].surname[0], racers[j].surname[3]);
            }
            else if (r == 2) {
                printf("%s %s выиграл борьбу у %s %s", racers[i].name[0], racers[i].surname[0], racers[j].name[1], racers[j].surname[1]);
            }
            else if (r == 3) {
                printf("%s %s опередил %s %s", racers[i].name[0], racers[i].surname[0], racers[j].name[3], racers[j].surname[3]);
            }
            else if (r == 4) {
                printf("%s опередил %s", racers[i].surname[0], racers[j].surname[3]);
            }
            else if (r == 5) {
                printf("%s %s обошел %s %s", racers[i].name[0], racers[i].surname[0], racers[j].name[3], racers[j].surname[3]);
            }
            else if (r == 6) {
                printf("%s обошел %s", racers[i].surname[0], racers[j].surname[3]);
            }
            char str1[size] = { 0 };
            strcpy(str1, p);
            while (str1[p - str1] == '\t') {
                p = strchr(str1, '\t') + 1;
                strcpy(str1, p);
            }
            if (strlen(p) > 1) {
                p[strlen(p) - 1] = '\0';
                if (p[0] != ':' && p[0] != ',')
                    printf(" ");
                printf("%s", p);
            }
            printf(". \n");

        }

        else if (strcmp(act, "перемещ") == 0) {
            int position = 0;
            char str1[size] = { 0 };
            sscanf(p, "%s", str1);
            p = strstr(p, str1) + strlen(str1);
            sscanf(str1, "%d", &position);
            strcpy(str1, p);
            while (str1[p - str1] == '\t') {
                p = strchr(str1, '\t') + 1;
                strcpy(str1, p);
            }
            int r = rand() % 5;
            if (r == r_moving)
                r = (r + 1) % 5;
            r_moving = r;
            int i = RacerSearch(sign, racers_count, racers);
            if (r == 0) {
                if (position == 3)
                    printf("%s переместился на %d-ю позицию", racers[i].surname[0], position);
                else
                    printf("%s переместился на %d-ую позицию", racers[i].surname[0], position);
            }
            else if (r == 1) {
                printf("%s стал %d-м", racers[i].surname[0], position);
            }
            else if (r == 2) {
                if (position == 3)
                    printf("%s вышел на %d-ю позицию", racers[i].surname[0], position);
                else
                    printf("%s вышел на %d-ую позицию", racers[i].surname[0], position);
            }
            else if (r == 3) {
                printf("%s переместился на %d-е место", racers[i].surname[0], position);
            }
            else if (r == 4) {
                printf("%s вышел на %d-е место", racers[i].surname[0], position);
            }
            if (strlen(p) > 1) {
                p[strlen(p) - 1] = '\0';
                if (p[0] != ':' && p[0] != ',')
                    printf(" ");
                printf("%s", p);
            }
            printf(". \n");
        }

        else if (strcmp(act, "пейскар") == 0) {
            char reason[size] = { 0 };
            char str1[size] = { 0 };
            while (p[0] == '\t')
                p++;
            int temp = 0;
            while (p[0] != '\t') {
                reason[temp] = p[0];
                temp++;
                p++;
            }
            while (p[0] == '\t')
                p++;
            temp = 0;
            while (p[0] != '\n' && p[0] != '\0') {
                str1[temp] = p[0];
                temp++;
                p++;
            }
            int r = rand() % 8;
            if (r == r_pace)
                r = (r + 1) % 8;
            r_pace = r;
            int i = RacerSearch(sign, racers_count, racers);
            if (r == 0) {
                printf("%s на трассе появился пейс-кар", reason);
            }
            else if (r == 1) {
                printf("%s на трассу выпустили пейс-кар", reason);
            }
            else if (r == 2) {
                printf("%s на треке появился пейс-кар", reason);
            }
            else if (r == 3) {
                printf("%s на трек выпустили пейс-кар", reason);
            }
            else if (r == 4) {
                printf("%s на трассе появился сейфти-кар", reason);
            }
            else if (r == 5) {
                printf("%s на трассу выпустили сейфти-кар", reason);
            }
            else if (r == 6) {
                printf("%s на треке появился сейфти-кар", reason);
            }
            else if (r == 7) {
                printf("%s на трек выпустили сейфти-кар", reason);
            }
            if (strlen(p) > 1) {
                p[strlen(p) - 1] = '\0';
                if (p[0] != ':' && p[0] != ',')
                    printf(" ");
                printf("%s", p);
            }
            printf(". \n");

        }

        else if (strcmp(act, "борьба") == 0) {
            char pilot[20] = { 0 };
            int bef = 0;
            int aft = 0;
            sscanf(p, "%s %s %s", pilot, &bef, &aft);
            p += strlen(pilot);
            while (p[0] == '\t' || (p[0] >= 48 && p[0] <= 57))
                p++;
            int r = rand() % 8;
            if (r == r_fight)
                r = (r + 1) % 8;
            r_fight = r;
            int i = RacerSearch(sign, racers_count, racers);
            int j = RacerSearch(pilot, racers_count, racers);
            if (bef == 2) {
                if (r == 0) {
                    if (aft == 3)
                        printf("%s в результате борьбы с %s выходит на %d-ю позицию", racers[i].surname[0], racers[j].surname[4], aft);
                    else
                        printf("%s в результате борьбы с %s выходит на %d-ую позицию", racers[i].surname[0], racers[j].surname[4], aft);
                }
                else if (r == 1) {
                    if (aft == 3)
                        printf("Из-за борьбы с %s %s перемещается со %d-й на %d-ю позицию", racers[j].surname[4], racers[i].surname[0], bef, aft);
                    else
                        printf("Из-за борьбы с %s %s перемещается со %d-й на %d-ую позицию", racers[j].surname[4], racers[i].surname[0], bef, aft);
                }
                else if (r == 2) {
                    if (aft == 3)
                        printf("%s вследствие противостояния с %s выходит на %d-ю позицию", racers[i].surname[0], racers[j].surname[4], aft);
                    else
                        printf("%s вследствие противостояния с %s выходит на %d-ую позицию", racers[i].surname[0], racers[j].surname[4], aft);
                }
                else if (r == 3) {
                    if (aft == 3)
                        printf("В результате противостояния с %s %s перемещается со %d-й на %d-ю позицию", racers[j].surname[4], racers[i].surname[0], bef, aft);
                    else
                        printf("В результате противостояния с %s %s перемещается со %d-й на %d-ую позицию", racers[j].surname[4], racers[i].surname[0], bef, aft);
                }
                else if (r == 4) {
                    printf("%s из-за борьбы с %s выходит на %d-е место", racers[i].surname[0], racers[j].surname[4], aft);
                }
                else if (r == 5) {
                    printf("Вследствие борьбы с %s %s перемещается со %d-го на %d-е место", racers[j].surname[4], racers[i].surname[0], bef, aft);
                }
                else if (r == 6) {
                    printf("%s в результате противостояния с %s выходит на %d-е место", racers[i].surname[0], racers[j].surname[4], aft);
                }
                else if (r == 7) {
                    printf("Вследствие противостояния с %s %s перемещается со %d-го на %d-е место", racers[j].surname[4], racers[i].surname[0], bef, aft);
                }
            }
            else {
                if (r == 0) {
                    if (aft == 3)
                        printf("%s в результате борьбы с %s выходит на %d-ю позицию", racers[i].surname[0], racers[j].surname[4], aft);
                    else
                        printf("%s в результате борьбы с %s выходит на %d-ую позицию", racers[i].surname[0], racers[j].surname[4], aft);
                }
                else if (r == 1) {
                    if (aft == 3)
                        printf("Из-за борьбы с %s %s перемещается с %d-й на %d-ю позицию", racers[j].surname[4], racers[i].surname[0], bef, aft);
                    else
                        printf("Из-за борьбы с %s %s перемещается с %d-й на %d-ую позицию", racers[j].surname[4], racers[i].surname[0], bef, aft);
                }
                else if (r == 2) {
                    if (aft == 3)
                        printf("%s вследствие противостояния с %s выходит на %d-ю позицию", racers[i].surname[0], racers[j].surname[4], aft);
                    else
                        printf("%s вследствие противостояния с %s выходит на %d-ую позицию", racers[i].surname[0], racers[j].surname[4], aft);
                }
                else if (r == 3) {
                    if (aft == 3)
                        printf("В результате противостояния с %s %s перемещается с %d-й на %d-ю позицию", racers[j].surname[4], racers[i].surname[0], bef, aft);
                    else
                        printf("В результате противостояния с %s %s перемещается с %d-й на %d-ую позицию", racers[j].surname[4], racers[i].surname[0], bef, aft);
                }
                else if (r == 4) {
                    printf("%s из-за борьбы с %s выходит на %d-е место", racers[i].surname[0], racers[j].surname[4], aft);
                }
                else if (r == 5) {
                    printf("Вследствие борьбы с %s %s перемещается с %d-го на %d-е место", racers[j].surname[4], racers[i].surname[0], bef, aft);
                }
                else if (r == 6) {
                    printf("%s в результате противостояния с %s выходит на %d-е место", racers[i].surname[0], racers[j].surname[4], aft);
                }
                else if (r == 7) {
                    printf("Вследствие противостояния с %s %s перемещается с %d-го на %d-е место", racers[j].surname[4], racers[i].surname[0], bef, aft);
                }
            }
            if (strlen(p) > 1) {
                p[strlen(p) - 1] = '\0';
                if (p[0] != ':' && p[0] != ',')
                    printf(" ");
                printf("%s", p);
            }
            printf(". \n");
        }

        else if (strcmp(act, "столкнов") == 0) {
        char pilot[20] = { 0 };
        sscanf(p, "%s", pilot);
        p = strstr(p, pilot) + strlen(pilot);
        int r = rand() % 6;
        if (r == r_collision)
            r = (r + 1) % 6;
        r_collision = r;
        int i = RacerSearch(sign, racers_count, racers);
        int j = RacerSearch(pilot, racers_count, racers);
        if (r == 0) {
            printf("Произошло столкновение между %s и %s", racers[i].surname[4], racers[j].surname[4]);
        }
        else if (r == 1) {
            printf("%s и %s столкнулись", racers[i].surname[0], racers[j].surname[0]);
        }
        else if (r == 2) {
            printf("%s %s столкнулся с %s %s", racers[i].name[0], racers[i].surname[0], racers[j].name[4], racers[j].surname[4]);
        }
        else if (r == 3) {
            printf("Произошла коллизия между %s и %s", racers[i].surname[4], racers[j].surname[4]);
        }
        else if (r == 4) {
            printf("Произошла коллизия между двумя пилотами: %s %s и %s %s", racers[i].name[4], racers[i].surname[4], racers[j].name[4], racers[j].surname[4]);
        }
        else if (r == 5) {
            printf("Произошло столкновение между двумы гонщиками: %s %s и %s %s", racers[i].name[4], racers[i].surname[4], racers[j].name[4], racers[j].surname[4]);
        }
        char str1[size] = { 0 };
        strcpy(str1, p);
        while (str1[p - str1] == '\t') {
            p = strchr(str1, '\t') + 1;
            strcpy(str1, p);
        }
        if (strlen(p) > 1) {
            p[strlen(p) - 1] = '\0';
            if (p[0] != ':' && p[0] != ',')
                printf(" ");
            printf("%s", p);
        }
        printf(". \n");
        }

        else if (strcmp(act, "финиш") == 0) {
        int position = 0;
        sscanf(p, "%d", &position);
        int i = RacerSearch(sign, racers_count, racers);
        if (position == 1) {
            printf("Участник команды %s %s %s из %s финишировал 1-м, став победителем сегодняшней гонки! ", racers[i].car, racers[i].name[0], racers[i].surname[0], racers[i].country[5]);
        }
        else {
            int r = rand() % 4;
            if (r == r_finish)
                r = (r + 1) % 4;
            r_finish = r;
            if (r == 0) {
                printf("%d-м финишировал %s %s из %s, представляющий команду %s. ", position, racers[i].name[0], racers[i].surname[0], racers[i].country[5], racers[i].car);
            }
            else if (r == 1) {
                printf("%d-м закончил гонку представитель команды %s %s %s из %s. ", position, racers[i].car, racers[i].name[0], racers[i].surname[0], racers[i].country[5]);
            }
            else if (r == 2) {
                printf("Член команды %s %s %s из %s закончил гонку, заняв %d-е место. ", racers[i].car, racers[i].name[0], racers[i].surname[0], racers[i].country[5], position);
            }
            else if (r == 3) {
                printf("%s %s из %s, участвующий от команды %s, финишировал, заняв %d-е место. ", racers[i].name[0], racers[i].surname[0], racers[i].country[5], racers[i].car, position);
            }
        }
        int r = rand() % 5;
        if (r == r_final_score)
            r = (r + 1) % 5;
        r_final_score = r;
        if (r == 0) {
            printf("Количество очков участника - %d", racers[i].score + final_score[position - 1]);
        }
        else if (r == 1) {
            printf("У гонщика на данный момент %d баллов", racers[i].score + final_score[position - 1]);
        }
        else if (r == 2) {
            printf("Сейчас у спортсмена %d баллов", racers[i].score + final_score[position - 1]);
        }
        else if (r == 3) {
            printf("Количество баллов %s - %d", racers[i].surname[1], racers[i].score + final_score[position - 1]);
        }
        else if (r == 4) {
            printf("Количество баллов %s %s составляет %d", racers[i].name[1], racers[i].surname[1], racers[i].score + final_score[position - 1]);
        }
        printf(".\n");
        }
    }
    printf("\n\n");
    fclose(in);

    return 0;
}