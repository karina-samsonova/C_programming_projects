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
void Declensions(int racers_count, RACERS racers[]) {        //��������� ���� ���������� �����
    for (int i = 0; i < racers_count; ++i) {
        for (int j = 1; j < 6; ++j) {
            strcpy(racers[i].name[j], racers[i].name[0]);
            strcpy(racers[i].surname[j], racers[i].surname[0]);
            strcpy(racers[i].country[j], racers[i].country[0]);
        }
        int end = strlen(racers[i].name[0]) - 1;
        if (!(racers[i].name[0][end] == '�' || racers[i].name[0][end] == '�' ||
            racers[i].name[0][end] == '�' || racers[i].name[0][end] == '�' ||
            racers[i].name[0][end] == '�' || racers[i].name[0][end] == '�' ||
            racers[i].name[0][end] == '�' || racers[i].name[0][end] == '�')) {
            if (racers[i].name[0][end] == '�')
                end--;
            end++;
            racers[i].name[1][end] = '�';
            racers[i].name[2][end] = '�';
            racers[i].name[3][end] = '�';
            racers[i].name[4][end] = '�';
            racers[i].name[4][end + 1] = '�';
            racers[i].name[5][end] = '�';
            end++;
            racers[i].name[1][end] = '\0';
            racers[i].name[2][end] = '\0';
            racers[i].name[3][end] = '\0';
            racers[i].name[4][end + 1] = '\0';
            racers[i].name[5][end] = '\0';
        }

        end = strlen(racers[i].surname[0]) - 1;
        if (!(racers[i].surname[0][end] == '�' || racers[i].surname[0][end] == '�' ||
            racers[i].surname[0][end] == '�' || racers[i].surname[0][end] == '�' ||
            racers[i].surname[0][end] == '�' || racers[i].surname[0][end] == '�' ||
            racers[i].surname[0][end] == '�' || racers[i].surname[0][end] == '�')) {
            if (racers[i].surname[0][end] == '�')
                end--;
            end++;
            racers[i].surname[1][end] = '�';
            racers[i].surname[2][end] = '�';
            racers[i].surname[3][end] = '�';
            racers[i].surname[4][end] = '�';
            racers[i].surname[4][end + 1] = '�';
            racers[i].surname[5][end] = '�';
            end++;
            racers[i].surname[1][end] = '\0';
            racers[i].surname[2][end] = '\0';
            racers[i].surname[3][end] = '\0';
            racers[i].surname[4][end + 1] = '\0';
            racers[i].surname[5][end] = '\0';
        }

        end = strlen(racers[i].country[0]) - 1;
        if (racers[i].country[0][end] == '�') {
            racers[i].country[1][end] = '�';
            racers[i].country[2][end] = '�';
            racers[i].country[3][end] = '�';
            racers[i].country[4][end] = '�';
            racers[i].country[4][end + 1] = '�';
            racers[i].country[5][end] = '�';
            end++;
            racers[i].country[1][end] = '\0';
            racers[i].country[2][end] = '\0';
            racers[i].country[3][end] = '\0';
            racers[i].country[4][end + 1] = '\0';
            racers[i].country[5][end] = '\0';
        }
        else if (racers[i].country[0][end] == '�') {
            racers[i].country[1][end] = '\0';
            racers[i].country[2][end] = '�';
            racers[i].country[2][end + 1] = '�';
            racers[i].country[4][end] = '�';
            racers[i].country[4][end + 1] = '�';
            racers[i].country[4][end + 2] = '�';
            racers[i].country[5][end] = '�';
            racers[i].country[5][end + 1] = '�';
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
    while (!feof(fracers)) {        //��������� ���� � ����������� �����
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
                printf("������� %d-�� �����:\n", circle);
            else if (r == 1)
                printf("�������� ������� �� %d-� ������:\n", circle);
            else if (r == 2)
                printf("����� %d-� ����:\n", circle);
            else if (r == 3)
                printf("��������� �� ��������� %d-�� �����:\n", circle);
            temp_circle = circle;
        }
        char* p = strstr(str, act) + strlen(act);

        if (strcmp(act, "�����") == 0) {
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
                    printf("�������� ������� %s %s %s �� %s ��������� �� %d-� �������", racers[i].car, racers[i].name[0], racers[i].surname[0], racers[i].country[5], position);
                }
                else if (r == 1) {
                    printf("�� %d-� ������� ��������� ������������� ������� %s %s %s �� %s", position, racers[i].car, racers[i].name[0], racers[i].surname[0], racers[i].country[5]);
                }
                else if (r == 2) {
                    if (position == 3)
                        printf("%d-� ������� �� ��������� ������� � %s %s �� %s, ��������������� %s", position, racers[i].name[1], racers[i].surname[1], racers[i].country[5], racers[i].car);
                    else
                        printf("%d-�� ������� �� ��������� ������� � %s %s �� %s, ��������������� %s", position, racers[i].name[1], racers[i].surname[1], racers[i].country[5], racers[i].car);
                }
                else if (r == 3) {
                    printf("���� ������� %s %s %s �� %s ����� ����� �� %d-�� �����", racers[i].car, racers[i].name[0], racers[i].surname[0], racers[i].country[5], position);
                }
                else if (r == 4) {
                    printf("�� %d-�� ����� ����� ����� %s %s �� %s, �������������� ������� %s", position, racers[i].name[0], racers[i].surname[0], racers[i].country[5], racers[i].car);
                }
                else if (r == 5) {
                    printf("�� %d-� ������� ����� ����� %s %s �� %s, ����������� �� ������� %s", position, racers[i].name[0], racers[i].surname[0], racers[i].country[5], racers[i].car);
                }
                else if (r == 6) {
                    printf("%s %s �� %s, �������������� ������� %s, ����� ������������ �� %d-� �������", racers[i].name[0], racers[i].surname[0], racers[i].country[5], racers[i].car, position);
                }
            }
            else {
                if (r == 0) {
                    printf("�������� ������� %s %s %s �� %s ��������� � %d-� �������", racers[i].car, racers[i].name[0], racers[i].surname[0], racers[i].country[5], position);
                }
                else if (r == 1) {
                    printf("� %d-� ������� ��������� ������������� ������� %s %s %s �� %s", position, racers[i].car, racers[i].name[0], racers[i].surname[0], racers[i].country[5]);
                }
                else if (r == 2) {
                    if (position == 3)
                        printf("%d-� ������� �� ��������� ������� � %s %s �� %s, ��������������� %s", position, racers[i].name[1], racers[i].surname[1], racers[i].country[5], racers[i].car);
                    else
                        printf("%d-�� ������� �� ��������� ������� � %s %s �� %s, ��������������� %s", position, racers[i].name[1], racers[i].surname[1], racers[i].country[5], racers[i].car);
                }
                else if (r == 3) {
                    printf("���� ������� %s %s %s �� %s ����� ����� � %d-�� �����", racers[i].car, racers[i].name[0], racers[i].surname[0], racers[i].country[5], position);
                }
                else if (r == 4) {
                    printf("� %d-�� ����� ����� ����� %s %s �� %s, �������������� ������� %s", position, racers[i].name[0], racers[i].surname[0], racers[i].country[5], racers[i].car);
                }
                else if (r == 5) {
                    printf("� %d-� ������� ����� ����� %s %s �� %s, ����������� �� ������� %s", position, racers[i].name[0], racers[i].surname[0], racers[i].country[5], racers[i].car);
                }
                else if (r == 6) {
                    printf("%s %s �� %s, �������������� ������� %s, ����� ������������ � %d-� �������", racers[i].name[0], racers[i].surname[0], racers[i].country[5], racers[i].car, position);
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

        else if (strcmp(act, "����") == 0) {
            int r = rand() % 7;
            if (r == r_deroad)
                r = (r + 1) % 7;
            r_deroad = r;
            int i = RacerSearch(sign, racers_count, racers);
            if (r == 0) {
                printf("%s %s �������� ��������� �����", racers[i].name[0], racers[i].surname[0]);
            }
            else if (r == 1) {
                printf("%s %s ����� � ���������", racers[i].name[0], racers[i].surname[0]);
            }
            else if (r == 2) {
                printf("%s %s �������� ��������� �����", racers[i].name[0], racers[i].surname[0]);
            }
            else if (r == 3) {
                printf("%s %s �������� ��������� ������������", racers[i].name[0], racers[i].surname[0]);
            }
            else if (r == 4) {
                printf("%s %s �������� ��������� �����", racers[i].name[0], racers[i].surname[0]);
            }
            else if (r == 5) {
                printf("%s %s �������� ��������� �����", racers[i].name[0], racers[i].surname[0]);
            }
            else if (r == 6) {
                printf("%s %s �������� ��������� ������������", racers[i].name[0], racers[i].surname[0]);
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

        else if (strcmp(act, "������") == 0) {
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
                printf("%s %s ������ - %s", racers[i].name[0], racers[i].surname[0], p);
            }
            else if (r == 1) {
                printf("��-�� ������ (%s) %s ������� ���� �������", p, racers[i].surname[0]);
            }
            else if (r == 2) {
                printf("%s %s �������� ������ - %s", racers[i].name[0], racers[i].surname[0], p);
            }
            printf(". \n");
        }

        else if (strcmp(act, "�������") == 0) {
            int r = rand() % 6;
            if (r == r_stop)
                r = (r + 1) % 6;
            r_stop = r;
            int i = RacerSearch(sign, racers_count, racers);
            if (r == 0) {
                printf("%s %s ������ � �����", racers[i].name[0], racers[i].surname[0]);
            }
            else if (r == 1) {
                printf("%s �������� ���� ����� %s", racers[i].surname[0], racers[i].car);
            }
            else if (r == 2) {
                printf("%s %s ������ �������", racers[i].name[0], racers[i].surname[0]);
            }
            else if (r == 3) {
                printf("���� ������� ������ %s %s", racers[i].name[0], racers[i].surname[0]);
            }
            else if (r == 4) {
                printf("� ������ ��������� %s", racers[i].surname[0]);
            }
            else if (r == 5) {
                printf("%s �������� ���� ���������� %s", racers[i].surname[0], racers[i].car);
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

        else if (strcmp(act, "��������") == 0) {
            char sec[50] = { 0 };
            sscanf(p, "%s", sec);
            int r = rand() % 5;
            if (r == r_best)
                r = (r + 1) % 5;
            r_best = r;
            int i = RacerSearch(sign, racers_count, racers);
            if (r == 0) {
                printf("������ ���� � %s %s: %s.\n", racers[i].name[1], racers[i].surname[1], sec);
            }
            else if (r == 1) {
                printf("������ ���� � %s %s - %s.\n", racers[i].name[1], racers[i].surname[1], sec);
            }
            else if (r == 2) {
                printf("%s %s ������ ���� �� %s.\n", racers[i].name[0], racers[i].surname[0], sec);
            }
            else if (r == 3) {
                printf("����� ������� ���� � %s %s: %s.\n", racers[i].name[1], racers[i].surname[1], sec);
            }
            else if (r == 4) {
                printf("����� ������� ���� � %s %s - %s.\n", racers[i].name[1], racers[i].surname[1], sec);
            }
        }
        else if (strcmp(act, "�����") == 0) {
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
                    printf("%s �������� � ����� � ������� � %d ������", racers[i].surname[0], (int)sec);
                    if (sec == 1.0)
                        printf("�.\n");
                    else if (sec - 5.0 > 0.0 && aft == 0.0)
                        printf(". \n");
                    else
                        printf("�.\n");
                }
                else if (r == 1) {
                    printf("������ ���� %s, �������� ���������� �������������� �� %d ������", racers[i].surname[0], (int)sec);
                    if (sec == 1.0)
                        printf("�.\n");
                    else if (sec - 5.0 > 0.0 && aft == 0.0)
                        printf(". \n");
                    else
                        printf("�.\n");
                }
            }
            else {
                if (r == 0) {
                    printf("%s �������� � ����� � ������� � %.1f ������", racers[i].surname[0], sec);
                    if (sec == 1.0)
                        printf("�.\n");
                    else if (sec - 5.0 > 0.0 && aft == 0.0)
                        printf(". \n");
                    else
                        printf("�.\n");
                }
                else if (r == 1) {
                    printf("������ ���� %s, �������� ���������� �������������� �� %.1f ������", racers[i].surname[0], sec);
                    if (sec == 1.0)
                        printf("�.\n");
                    else if (sec - 5.0 > 0.0 && aft == 0.0)
                        printf(". \n");
                    else
                        printf("�.\n");
                }
            }
        }

        else if (strcmp(act, "�����") == 0) {
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
                printf("%s %s ������� %s %s", racers[i].name[0], racers[i].surname[0], racers[j].name[3], racers[j].surname[3]);
            }
            else if (r == 1) {
                printf("%s ������� %s", racers[i].surname[0], racers[j].surname[3]);
            }
            else if (r == 2) {
                printf("%s %s ������� ������ � %s %s", racers[i].name[0], racers[i].surname[0], racers[j].name[1], racers[j].surname[1]);
            }
            else if (r == 3) {
                printf("%s %s �������� %s %s", racers[i].name[0], racers[i].surname[0], racers[j].name[3], racers[j].surname[3]);
            }
            else if (r == 4) {
                printf("%s �������� %s", racers[i].surname[0], racers[j].surname[3]);
            }
            else if (r == 5) {
                printf("%s %s ������ %s %s", racers[i].name[0], racers[i].surname[0], racers[j].name[3], racers[j].surname[3]);
            }
            else if (r == 6) {
                printf("%s ������ %s", racers[i].surname[0], racers[j].surname[3]);
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

        else if (strcmp(act, "�������") == 0) {
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
                    printf("%s ������������ �� %d-� �������", racers[i].surname[0], position);
                else
                    printf("%s ������������ �� %d-�� �������", racers[i].surname[0], position);
            }
            else if (r == 1) {
                printf("%s ���� %d-�", racers[i].surname[0], position);
            }
            else if (r == 2) {
                if (position == 3)
                    printf("%s ����� �� %d-� �������", racers[i].surname[0], position);
                else
                    printf("%s ����� �� %d-�� �������", racers[i].surname[0], position);
            }
            else if (r == 3) {
                printf("%s ������������ �� %d-� �����", racers[i].surname[0], position);
            }
            else if (r == 4) {
                printf("%s ����� �� %d-� �����", racers[i].surname[0], position);
            }
            if (strlen(p) > 1) {
                p[strlen(p) - 1] = '\0';
                if (p[0] != ':' && p[0] != ',')
                    printf(" ");
                printf("%s", p);
            }
            printf(". \n");
        }

        else if (strcmp(act, "�������") == 0) {
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
                printf("%s �� ������ �������� ����-���", reason);
            }
            else if (r == 1) {
                printf("%s �� ������ ��������� ����-���", reason);
            }
            else if (r == 2) {
                printf("%s �� ����� �������� ����-���", reason);
            }
            else if (r == 3) {
                printf("%s �� ���� ��������� ����-���", reason);
            }
            else if (r == 4) {
                printf("%s �� ������ �������� ������-���", reason);
            }
            else if (r == 5) {
                printf("%s �� ������ ��������� ������-���", reason);
            }
            else if (r == 6) {
                printf("%s �� ����� �������� ������-���", reason);
            }
            else if (r == 7) {
                printf("%s �� ���� ��������� ������-���", reason);
            }
            if (strlen(p) > 1) {
                p[strlen(p) - 1] = '\0';
                if (p[0] != ':' && p[0] != ',')
                    printf(" ");
                printf("%s", p);
            }
            printf(". \n");

        }

        else if (strcmp(act, "������") == 0) {
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
                        printf("%s � ���������� ������ � %s ������� �� %d-� �������", racers[i].surname[0], racers[j].surname[4], aft);
                    else
                        printf("%s � ���������� ������ � %s ������� �� %d-�� �������", racers[i].surname[0], racers[j].surname[4], aft);
                }
                else if (r == 1) {
                    if (aft == 3)
                        printf("��-�� ������ � %s %s ������������ �� %d-� �� %d-� �������", racers[j].surname[4], racers[i].surname[0], bef, aft);
                    else
                        printf("��-�� ������ � %s %s ������������ �� %d-� �� %d-�� �������", racers[j].surname[4], racers[i].surname[0], bef, aft);
                }
                else if (r == 2) {
                    if (aft == 3)
                        printf("%s ���������� �������������� � %s ������� �� %d-� �������", racers[i].surname[0], racers[j].surname[4], aft);
                    else
                        printf("%s ���������� �������������� � %s ������� �� %d-�� �������", racers[i].surname[0], racers[j].surname[4], aft);
                }
                else if (r == 3) {
                    if (aft == 3)
                        printf("� ���������� �������������� � %s %s ������������ �� %d-� �� %d-� �������", racers[j].surname[4], racers[i].surname[0], bef, aft);
                    else
                        printf("� ���������� �������������� � %s %s ������������ �� %d-� �� %d-�� �������", racers[j].surname[4], racers[i].surname[0], bef, aft);
                }
                else if (r == 4) {
                    printf("%s ��-�� ������ � %s ������� �� %d-� �����", racers[i].surname[0], racers[j].surname[4], aft);
                }
                else if (r == 5) {
                    printf("���������� ������ � %s %s ������������ �� %d-�� �� %d-� �����", racers[j].surname[4], racers[i].surname[0], bef, aft);
                }
                else if (r == 6) {
                    printf("%s � ���������� �������������� � %s ������� �� %d-� �����", racers[i].surname[0], racers[j].surname[4], aft);
                }
                else if (r == 7) {
                    printf("���������� �������������� � %s %s ������������ �� %d-�� �� %d-� �����", racers[j].surname[4], racers[i].surname[0], bef, aft);
                }
            }
            else {
                if (r == 0) {
                    if (aft == 3)
                        printf("%s � ���������� ������ � %s ������� �� %d-� �������", racers[i].surname[0], racers[j].surname[4], aft);
                    else
                        printf("%s � ���������� ������ � %s ������� �� %d-�� �������", racers[i].surname[0], racers[j].surname[4], aft);
                }
                else if (r == 1) {
                    if (aft == 3)
                        printf("��-�� ������ � %s %s ������������ � %d-� �� %d-� �������", racers[j].surname[4], racers[i].surname[0], bef, aft);
                    else
                        printf("��-�� ������ � %s %s ������������ � %d-� �� %d-�� �������", racers[j].surname[4], racers[i].surname[0], bef, aft);
                }
                else if (r == 2) {
                    if (aft == 3)
                        printf("%s ���������� �������������� � %s ������� �� %d-� �������", racers[i].surname[0], racers[j].surname[4], aft);
                    else
                        printf("%s ���������� �������������� � %s ������� �� %d-�� �������", racers[i].surname[0], racers[j].surname[4], aft);
                }
                else if (r == 3) {
                    if (aft == 3)
                        printf("� ���������� �������������� � %s %s ������������ � %d-� �� %d-� �������", racers[j].surname[4], racers[i].surname[0], bef, aft);
                    else
                        printf("� ���������� �������������� � %s %s ������������ � %d-� �� %d-�� �������", racers[j].surname[4], racers[i].surname[0], bef, aft);
                }
                else if (r == 4) {
                    printf("%s ��-�� ������ � %s ������� �� %d-� �����", racers[i].surname[0], racers[j].surname[4], aft);
                }
                else if (r == 5) {
                    printf("���������� ������ � %s %s ������������ � %d-�� �� %d-� �����", racers[j].surname[4], racers[i].surname[0], bef, aft);
                }
                else if (r == 6) {
                    printf("%s � ���������� �������������� � %s ������� �� %d-� �����", racers[i].surname[0], racers[j].surname[4], aft);
                }
                else if (r == 7) {
                    printf("���������� �������������� � %s %s ������������ � %d-�� �� %d-� �����", racers[j].surname[4], racers[i].surname[0], bef, aft);
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

        else if (strcmp(act, "��������") == 0) {
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
            printf("��������� ������������ ����� %s � %s", racers[i].surname[4], racers[j].surname[4]);
        }
        else if (r == 1) {
            printf("%s � %s �����������", racers[i].surname[0], racers[j].surname[0]);
        }
        else if (r == 2) {
            printf("%s %s ���������� � %s %s", racers[i].name[0], racers[i].surname[0], racers[j].name[4], racers[j].surname[4]);
        }
        else if (r == 3) {
            printf("��������� �������� ����� %s � %s", racers[i].surname[4], racers[j].surname[4]);
        }
        else if (r == 4) {
            printf("��������� �������� ����� ����� ��������: %s %s � %s %s", racers[i].name[4], racers[i].surname[4], racers[j].name[4], racers[j].surname[4]);
        }
        else if (r == 5) {
            printf("��������� ������������ ����� ����� ���������: %s %s � %s %s", racers[i].name[4], racers[i].surname[4], racers[j].name[4], racers[j].surname[4]);
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

        else if (strcmp(act, "�����") == 0) {
        int position = 0;
        sscanf(p, "%d", &position);
        int i = RacerSearch(sign, racers_count, racers);
        if (position == 1) {
            printf("�������� ������� %s %s %s �� %s ����������� 1-�, ���� ����������� ����������� �����! ", racers[i].car, racers[i].name[0], racers[i].surname[0], racers[i].country[5]);
        }
        else {
            int r = rand() % 4;
            if (r == r_finish)
                r = (r + 1) % 4;
            r_finish = r;
            if (r == 0) {
                printf("%d-� ����������� %s %s �� %s, �������������� ������� %s. ", position, racers[i].name[0], racers[i].surname[0], racers[i].country[5], racers[i].car);
            }
            else if (r == 1) {
                printf("%d-� �������� ����� ������������� ������� %s %s %s �� %s. ", position, racers[i].car, racers[i].name[0], racers[i].surname[0], racers[i].country[5]);
            }
            else if (r == 2) {
                printf("���� ������� %s %s %s �� %s �������� �����, ����� %d-� �����. ", racers[i].car, racers[i].name[0], racers[i].surname[0], racers[i].country[5], position);
            }
            else if (r == 3) {
                printf("%s %s �� %s, ����������� �� ������� %s, �����������, ����� %d-� �����. ", racers[i].name[0], racers[i].surname[0], racers[i].country[5], racers[i].car, position);
            }
        }
        int r = rand() % 5;
        if (r == r_final_score)
            r = (r + 1) % 5;
        r_final_score = r;
        if (r == 0) {
            printf("���������� ����� ��������� - %d", racers[i].score + final_score[position - 1]);
        }
        else if (r == 1) {
            printf("� ������� �� ������ ������ %d ������", racers[i].score + final_score[position - 1]);
        }
        else if (r == 2) {
            printf("������ � ���������� %d ������", racers[i].score + final_score[position - 1]);
        }
        else if (r == 3) {
            printf("���������� ������ %s - %d", racers[i].surname[1], racers[i].score + final_score[position - 1]);
        }
        else if (r == 4) {
            printf("���������� ������ %s %s ���������� %d", racers[i].name[1], racers[i].surname[1], racers[i].score + final_score[position - 1]);
        }
        printf(".\n");
        }
    }
    printf("\n\n");
    fclose(in);

    return 0;
}