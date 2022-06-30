#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define size 200
#define SIZE 100
#define Size 50

typedef struct Out {
	//int ins[SIZE];
	//int ins_count;
	int out;
	int nesting;
}OUT;
typedef struct Func {
	char name[Size];
	int rets_names_count;
	int rets_count;
	int rets[Size];
	char rets_names[Size][Size];
}FUNC;
typedef struct Args {
	char args_names[Size][Size];
	int args_count;
	int args_status;
	int args_num;
	char args_str[SIZE];
}ARGS;
int recursion(FUNC funcs[], int target, int cur, int* rec) {
	for (int f = 0; f < funcs[cur].rets_count; ++f) {
		if (funcs[cur].rets[f] == target) {
			//функция ... рекурсивна
			*rec += 1;
			return 1;
		}
	}
	for (int f = 0; f < funcs[cur].rets_count; ++f) {
		if (recursion(funcs, target, funcs[cur].rets[f], &*rec) == 1)
			break;
	}
	return 0;
}
int isArg(char str[]) {			//1 - yes , 0 - no
	int i = 0;
	for (; i < strlen(str); ++i) {
		if (str[strlen(str)] == ')')
			str[strlen(str)] = '\0';
		if (str[0] == '(') {
			for (int j = 0; j < strlen(str); ++j)
				str[j] = str[j + 1];
		}
		if (str[i] >= 65 && str[i] <= 90 || str[i] >= 97 && str[i] <= 122 || str[i] == 95)
			break;
	}
	if (i < strlen(str))
		return 1;
	return 0;
}
void argsSearch(char str[], char args[][Size], int* args_count) {
	char req[SIZE] = { 0 };
	char* p = strchr(str, '(');
	strcpy(req, p);
	p = strrchr(req, ')');
	int ind = p - req;
	req[ind] = '\0';
	while (strlen(req) > 0) {
		sscanf(req, "%s", args[*args_count]);
		for (int j = 0; j < strlen(req); ++j)
			req[j] = req[j + strlen(args[*args_count]) + 1];
		*args_count += 1;
	}
	for (int a = 0; a < *args_count; ++a) {
		if (isArg(args[a]) == 0) {
			for (int i = a; i < *args_count; ++i) 
				strcpy(args[i], args[i + 1]);
			a--;
			*args_count -= 1;
		}
	}
}
int main() {
	char* locale;
	locale = setlocale(LC_ALL, "RUS");
	FILE* in = fopen("input.txt", "rt");
	FILE* out = fopen("output.txt", "wt");
	FILE* draft = fopen("draft.txt", "w+t");
	FILE* draft2 = fopen("draft2.txt", "w+t");
	OUT outs[Size];
	int outs_count = 1;
	int outs_cur = 0;
	outs[0].out = -1;
	outs[0].nesting = 0;
	//outs[0].ins_count = 0;
	FUNC funcs[Size];
	int funcs_count = 0;
	char str[size] = { 0 };
	char file[size][size] = { 0 };
	int len = 0;
	int tab = 0;
	int com = 0;
	char comment[size] = { 0 };
	int com_end = 0;
	int del_end = 0;
	int tabtemp = 0;
	int oper_status[Size] = { 0 };		//0 - if, 1 - while, 2 - for
	int oper_count = 0;
	ARGS args[Size];
	int args_cur = 0;
	int limit[Size] = { 0 };
	int shift[Size] = { 0 };
	char for_args[Size][Size] = { 0 };
	int for_count = 0;
	char for_str[Size][SIZE] = { 0 };
	int for_num[Size] = { 0 };

	while (!feof(in)) {
		fgets(file[len], size, in);
		len++;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for (int l = 0; l < len; ++l) {
		int ind = 0;
		int icom = -1;
		for (; ind < strlen(file[l]); ++ind) {
			if (file[l][ind] != ' ' && file[l][ind] != '\t' && file[l][ind] != '\n')
				break;
		}
		if (ind == strlen(file[l])) {	//удаляем пустую строку
			for (int i = l; i < len; ++i) {
				strcpy(file[i], file[i + 1]);
			}
			len--;
			l--;
			continue;
		}
		if (file[l][ind] == '/' && file[l][ind + 1] == '/')
			continue;
		if (file[l][ind] == '/' && file[l][ind + 1] == '*') {
			char* p = strstr(file[l], "*/");
			if (p == NULL) {
				com++;
				continue;
			}
		}
		char* p = strstr(file[l], "//");
		if (p != NULL)
			icom = p - file[l];
		else {
			p = strstr(file[l], "/*");
			if (p != NULL) {
				icom = p - file[l];
				com++;
			}
				
		}
		p = strchr(file[l], ';');
		if (p != NULL && com == 0) {
			p = strstr(file[l], "for");
			if (p == NULL) {
				p = strchr(file[l], ';');
				p += 1;
				int itemp = p - file[l];
				if (!(icom != -1 && icom < itemp)) {
					if (icom != -1) {
						while (file[l][itemp] == ' ' || file[l][itemp] == '\t') {
							itemp++;
						}
						if (icom != itemp) {
							for (int i = len; i > l; i--) {
								strcpy(file[i], file[i - 1]);
							}
							strcpy(file[l + 1], p);
							len++;
							file[l][itemp] = '\n';
							file[l][itemp + 1] = '\0';
						}
					}
					else {
						for (int i = len; i > l; i--) {
							strcpy(file[i], file[i - 1]);
						}
						strcpy(file[l + 1], p);
						len++;
						file[l][itemp] = '\n';
						file[l][itemp + 1] = '\0';
					}
				}
			}
		}
		p = strchr(file[l], '{');
		if (p != NULL && com == 0) {
			p += 1;
			int itemp = p - file[l];
			if (!(icom != -1 && icom < itemp)) {
				if (icom != -1) {
					while (file[l][itemp] == ' ' || file[l][itemp] == '\t') {
						itemp++;
					}
					if (icom != itemp) {
						for (int i = len; i > l; i--) {
							strcpy(file[i], file[i - 1]);
						}
						strcpy(file[l + 1], p);
						len++;
						file[l][itemp] = '\n';
						file[l][itemp + 1] = '\0';
					}
				}
				else {
					for (int i = len; i > l; i--) {
						strcpy(file[i], file[i - 1]);
					}
					strcpy(file[l + 1], p);
					len++;
					file[l][itemp] = '\n';
					file[l][itemp + 1] = '\0';
				}
			}
		}
		p = strchr(file[l], '}');
		if (p != NULL && com == 0) {
			p += 1;
			int itemp = p - file[l];
			if (!(icom != -1 && icom < itemp)) {
				if (icom != -1) {
					while (file[l][itemp] == ' ' || file[l][itemp] == '\t') {
						itemp++;
					}
					if (icom != itemp) {
						for (int i = len; i > l; i--) {
							strcpy(file[i], file[i - 1]);
						}
						strcpy(file[l + 1], p);
						len++;
						file[l][itemp] = '\n';
						file[l][itemp + 1] = '\0';
					}
				}
				else {
					for (int i = len; i > l; i--) {
						strcpy(file[i], file[i - 1]);
					}
					strcpy(file[l + 1], p);
					len++;
					file[l][itemp] = '\n';
					file[l][itemp + 1] = '\0';
				}
			}
		}
		p = strstr(file[l], "*/");
		if (p != NULL) {
			com = 0;
			p += 2;
			int itemp = p - file[l];
			for (int i = len; i > l; i--) {
				strcpy(file[i], file[i - 1]);
			}
			strcpy(file[l + 1], p);
			len++;
			file[l][itemp] = '\n';
			file[l][itemp + 1] = '\0';
		}

	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for (int l = 0; l < len; ++l) {
		char temp[size] = { 0 };
		char* p = strstr(file[l], "/*");			//комментирование
		if (p == NULL) {
			p = strstr(file[l], "//");
			if (p != NULL) {
				int count = 0;
				int i = p - file[l];
				for (int itemp = 0; itemp < i; ++itemp) {
					if (file[l][itemp] != ' ' || file[l][itemp] != '\t')
						count++;
				}
				if (count > 0) {
					strcpy(comment, p);
					com_end++;
					del_end++;
					file[l][i] = '\0';
				}
			}
		}
		else {
			int count = 0;
			int i = p - file[l];
			file[l][i + 1] = '/';
			for (int itemp = 0; itemp < i; ++itemp) {
				if (file[l][itemp] != ' ' || file[l][itemp] != '\t')
					count++;
			}
			p = strstr(file[l], "*/");
			if (p == NULL) {
				p = strstr(file[l], "//");
				if (count > 0) {
					strcpy(comment, p);
					com_end++;
					file[l][i] = '\0';
				}
				else {
					p = strstr(file[l], "//");
					int itemp = p - file[l];
					for (; itemp < strlen(file[l]); ++itemp)
						file[l][itemp] = file[l][itemp + 2];
					com++;
				}
			}
			else {
				i = p - file[l];
				file[l][i] = '\n';
				file[l][i + 1] = '\0';
				p = strstr(file[l], "//");
				strcpy(comment, p);
				com_end++;
				del_end++;
				i = p - file[l];
				file[l][i] = '\0';
			}
			
		}
		for (int i = 0; i < strlen(file[l]); ++i) {		//tab => space
			if (file[l][i] == '\t' && com == 0)
				file[l][i] = ' ';
		}
		int ind = 0;
		for (; ind < strlen(file[l]); ++ind) {
			if (file[l][ind] != ' ' && file[l][ind] != '\t' && file[l][ind] != '\n')
				break;
		}
		int t = 0;					//табуляция
		for (; t < tab; ++t)
			temp[t] = '\t';
		if (com == 1) {
			temp[t] = '/';
			t++;
			temp[t] = '/';
			t++;
		}
		else {
			p = strstr(file[l], "  ");
			while (p != NULL) {				//пробелы
				int i = p - file[l];
				for (; i < strlen(file[l]); ++i)
					file[l][i] = file[l][i + 1];
				file[l][i] = '\0';
				p = strstr(file[l], "  ");
			}
			ind = 0;
			for (; ind < strlen(file[l]); ++ind) {
				if (file[l][ind] != ' ' && file[l][ind] != '\t' && file[l][ind] != '\n')
					break;
			}
			char signs[10] = {'=', '-', '+', '<', '>', '*', '/', '!'};
			for (int s = 0; s < 8; ++s) {
				p = strchr(file[l], signs[s]);
				while (p != NULL) {
					int i = p - file[l];
					if (file[l][i] == '/' && file[l][i + 1] == '*' || file[l][i] == '*' && file[l][i - 1] == '/' ||
						file[l][i] == '*' && file[l][i + 1] == '/' || file[l][i] == '/' && file[l][i - 1] == '*' ||
						file[l][i] == '/' && file[l][i + 1] == '/' || file[l][i] == '/' && file[l][i - 1] == '/')
						break;
					else if (file[l][i] == '+' && file[l][i + 1] == '+' || file[l][i] == '-' && file[l][i + 1] == '-') {
						if (file[l][i - 1] == ' ') {
							for (int itemp = i - 1; itemp < strlen(file[l]); ++itemp)
								file[l][itemp] = file[l][itemp + 1];
						}
						if (file[l][i + 2] == ' ') {
							for (int itemp = i + 2; itemp < strlen(file[l]); ++itemp)
								file[l][itemp] = file[l][itemp + 1];
						}
						break;
					}
					else if (file[l][i] == '+' && file[l][i - 1] == '+' || file[l][i] == '-' && file[l][i - 1] == '-') {
						if (file[l][i + 1] == ' ') {
							for (int itemp = i + 1; itemp < strlen(file[l]); ++itemp)
								file[l][itemp] = file[l][itemp + 1];
						}
						if (file[l][i - 2] == ' ') {
							for (int itemp = i - 2; itemp < strlen(file[l]); ++itemp)
								file[l][itemp] = file[l][itemp + 1];
						}
						break;
					}
					if (file[l][i - 1] != ' ' && file[l][i - 1] != '=' && file[l][i - 1] != '-' && file[l][i - 1] != '+' && file[l][i - 1] != '<' &&
						file[l][i - 1] != '>' && file[l][i - 1] != '*' && file[l][i - 1] != '/' && file[l][i - 1] != '!') {
						int itemp = strlen(file[l]);
						for (; itemp >= i; itemp--)
							file[l][itemp + 1] = file[l][itemp];
						file[l][i] = ' ';
						p += 1;
						i++;
					}
					if (file[l][i + 1] != ' ' && file[l][i + 1] != '=') {
						int itemp = strlen(file[l]);
						for (; itemp > i; itemp--)
							file[l][itemp + 1] = file[l][itemp];
						file[l][i + 1] = ' ';
						p += 1;
					}
					else if (file[l][i + 1] == ' ' && file[l][i + 2] == '='){
						for (; i < strlen(file[l]); ++i)
							file[l][i + 1] = file[l][i + 2];
					}
					p += 1;
					p = strchr(p, signs[s]);
				}
			}
			p = strchr(file[l], ';');
			while (p != NULL) {
				int i = p - file[l];
				if (file[l][i - 1] == ' ') {
					int itemp = i;
					for (; i <= strlen(file[l]); ++i)
						file[l][i - 1] = file[l][i];
					i = itemp - 1;
				}
				if (file[l][i + 1] != ' ') {
					int itemp = strlen(file[l]);
					for (; itemp >= i + 1; itemp--)
						file[l][itemp + 1] = file[l][itemp];
					file[l][i + 1] = ' ';
				}
				p += 1;
				p = strchr(p, ';');
			}
			char brackets[4] = {'(', '{', ')', '}'};
			for (int b = 0; b < 2; ++b) {
				p = strchr(file[l], brackets[b]);
				if (p != NULL) {
					int i = p - file[l];
					if (file[l][i - 1] != ' ') {
						int itemp = strlen(file[l]);
						for (; itemp >= i; itemp--)
							file[l][itemp + 1] = file[l][itemp];
						file[l][i] = ' ';
						p += 1;
						i++;
					}
					if (file[l][i + 1] == ' ') {
						for (; i <= strlen(file[l]) - 2; ++i)
							file[l][i + 1] = file[l][i + 2];
					}
				}
			}
			for (int b = 2; b < 4; ++b) {
				p = strchr(file[l], brackets[b]);
				if (p != NULL) {
					int i = p - file[l];
					if (file[l][i + 1] != ' ') {
						int itemp = strlen(file[l]);
						for (; itemp >= i + 1; itemp--)
							file[l][itemp + 1] = file[l][itemp];
						file[l][i + 1] = ' ';
					}
					if (file[l][i - 1] == ' ') {
						for (; i <= strlen(file[l]); ++i)
							file[l][i - 1] = file[l][i];
					}
					p = strchr(file[l], brackets[b]);
					i = p - file[l];
					if (b == 3) {						//************}************
						tab--;
						if (oper_count > 0) {
							if (oper_status[oper_count - 1] > 0)
								outs_cur = outs[outs_cur].out;
							oper_count--;
							if (oper_status[oper_count] == 1) {
								if (args[args_cur - 1].args_status > 0 && args[args_cur - 1].args_count > 0) {
									//сообщение о зацикливании
									fprintf(draft2, "%d строка> Оператор '%s' может стать причиной зацикливания.\n", args[args_cur - 1].args_num, args[args_cur - 1].args_str);
								}
								args_cur--;
							}
							else if (oper_status[oper_count] == 2) {
								if (limit[for_count - 1] == 1 || shift[for_count - 1] == 1) {
									fprintf(draft2, "%d строка> Оператор '%s' может стать причиной зацикливания.\n", for_num[for_count - 1], for_str[for_count - 1]);
								}
								for_count--;
							}
						}
					}
				}
			}
			p = strchr(file[l], ';');
			while (p != NULL) {
				int i = p - file[l];
				if (file[l][i - 1] == ' ') {
					int itemp = i;
					for (; i <= strlen(file[l]); ++i)
						file[l][i - 1] = file[l][i];
					i = itemp - 1;
				}
				p += 1;
				p = strchr(p, ';');
			}
		}
		//while looping
		if (com == 0 && args_cur >= 0) {
			p = strstr(file[l], "break;");
			if (p != NULL && oper_status[oper_count] == 1)
				args_cur--;
			for (int a = 0; a < args[args_cur - 1].args_count; ++a) {
				p = strstr(file[l], args[args_cur - 1].args_names[a]);
				if (p != NULL) {
					int istart = p - file[l];
					int iend = istart + strlen(args[args_cur - 1].args_names[a]);
					int ind = 0;
					for (; ind < strlen(file[l]); ++ind) {
						if (file[l][ind] != ' ' && file[l][ind] != '\t')
							break;
					}
					if (istart == ind && ((file[l][iend] == ' ' && (file[l][iend + 1] == '+' || 
						file[l][iend + 1] == '-' || file[l][iend + 1] == '*' || file[l][iend + 1] == '/' || file[l][iend + 1] == '=')) ||
						file[l][iend] == '+' || file[l][iend] == '-')) {
						for (int j = a; j < args[args_cur - 1].args_count; ++j)
							strcpy(args[args_cur - 1].args_names[j], args[args_cur - 1].args_names[j + 1]);
						args[args_cur - 1].args_count--;
						a--;
					}
					else if (istart == ind + 2 && (file[l][ind] == '-' && file[l][ind + 1] == '-' || 
						file[l][ind] == '+' && file[l][ind + 1] == '+')) {
						for (int j = a; j < args[args_cur - 1].args_count; ++j)
							strcpy(args[args_cur - 1].args_names[j], args[args_cur - 1].args_names[j + 1]);
						args[args_cur - 1].args_count--;
						a--;
					}
					
				}
			}
		}	
		//for looping
		if (for_count > 0 && com == 0) {
			if (limit[for_count - 1] > 0) {
				p = strstr(file[l], "break;");
				if (p != NULL)
					limit[for_count - 1] = 0;
			}
			if (shift[for_count - 1] > 0) {
				p = strstr(file[l], for_args[for_count - 1]);
				if (p != NULL) {
					int istart = p - file[l];
					int iend = istart + strlen(for_args[for_count - 1]);
					int ind = 0;
					for (; ind < strlen(file[l]); ++ind) {
						if (file[l][ind] != ' ' && file[l][ind] != '\t')
							break;
					}
					if (istart == ind && ((file[l][iend] == ' ' && (file[l][iend + 1] == '+' ||
						file[l][iend + 1] == '-' || file[l][iend + 1] == '*' || file[l][iend + 1] == '/' || file[l][iend + 1] == '=')) ||
						file[l][iend] == '+' || file[l][iend] == '-')) {
						shift[for_count - 1] = 0;
					}
					else if (istart == ind + 2 && (file[l][ind] == '-' && file[l][ind + 1] == '-' ||
						file[l][ind] == '+' && file[l][ind + 1] == '+')) {
						shift[for_count - 1] = 0;
					}

				}
			}
		}

		p = strstr(file[l], "*/");
		int k = 0;
		if (p != NULL) {
			int i = p - file[l];
			file[l][i++] = '\n';
			file[l][i] = '\0';
			k++;
		}
		ind = 0;
		for (; ind < strlen(file[l]); ++ind) {
			if (file[l][ind] != ' ' && file[l][ind] != '\t' && file[l][ind] != '\n')
				break;
		}
		if (file[l][ind] == '}')
			t--;
		while (ind != strlen(file[l]))
			temp[t++] = file[l][ind++];
		if (tabtemp > 0) {							//однострочный цикл
			tab--;
			tabtemp = 0;
		}
		//функции
		char types[10][20] = { "int", "char", "float", "double", "short", "long", "signed", "unsigned" };
		for (int t = 0; t < 8; ++t) {
			p = strstr(temp, types[t]);
			if (p != NULL) {
				if (tab == 0) {
					p = strchr(temp, '{');
					if (p == NULL) {
						p = strchr(file[l + 1], '{');
						if (p != NULL) {
							p = strstr(temp, types[t]) + strlen(types[t]) + 1;
							sscanf(p, "%s", funcs[funcs_count].name);
							funcs[funcs_count].rets_names_count = 0;
							funcs[funcs_count].rets_count = 0;
							funcs_count++;
						}
					}
					else {
						p = strstr(temp, types[t]) + strlen(types[t]) + 1;
						sscanf(p, "%s", funcs[funcs_count].name);
						funcs[funcs_count].rets_names_count = 0;
						funcs[funcs_count].rets_count = 0;
						funcs_count++;
					}	
				}
				else {
					p = strchr(temp, '=');
					if (p == NULL) {
						char arg[SIZE] = { 0 };
						p = strstr(temp, types[t]) + strlen(types[t]) + 1;
						sscanf(p, "%s", arg);
						int itemp = 0;
						for (; itemp < strlen(arg); ++itemp) {
							if (arg[itemp] == ';')
								break;
						}
						if (itemp < strlen(arg))
							arg[itemp] = '\0';
						fprintf(draft, "%d строка> Переменная '%s' не получила начального значения.\n", l + 1, arg);
						//ПЕРЕМЕННАЯ НЕ ИНИЦИАЛИЗИРОВАНА
						break;
					}
				}
			}
		}
		p = strstr(temp, "return");
		if (p != NULL) {
			p += 7;
			sscanf(p, "%s", funcs[funcs_count - 1].rets_names[funcs[funcs_count - 1].rets_names_count]);
			int itemp = 0;
			for (; itemp < strlen(funcs[funcs_count - 1].rets_names[funcs[funcs_count - 1].rets_names_count]); ++itemp) {
				if (funcs[funcs_count - 1].rets_names[funcs[funcs_count - 1].rets_names_count][itemp] == ';')
					break;
			}
			if (itemp < strlen(funcs[funcs_count - 1].rets_names[funcs[funcs_count - 1].rets_names_count]))
				funcs[funcs_count - 1].rets_names[funcs[funcs_count - 1].rets_names_count][itemp] = '\0';
			funcs[funcs_count - 1].rets_names_count++;
		}
		p = strchr(temp, '{');
		if (p != NULL && com == 0) {
			tab++;
		}
		else {
			p = strstr(temp, "while");
			if (p != NULL && com == 0) {
				p = strchr(file[l + 1], '{');
				if (p == NULL) {
					tab++;
					tabtemp++;
				}
			}
			else {
				p = strstr(temp, "for");
				if (p != NULL && com == 0) {
					p = strchr(file[l + 1], '{');
					if (p == NULL) {
						tab++;
						tabtemp++;
					}
				}
				else {
					p = strstr(temp, "if");
					if (p != NULL && com == 0) {
						p = strchr(file[l + 1], '{');
						if (p == NULL) {
							tab++;
							tabtemp++;
						}
					}
				}
			}
		}
		if (k > 0) {
			com = 0;
			k = 0;
		}
		//вложенные циклы и зацикливание
		p = strstr(temp, "while");
		if (p != NULL) {
			args[args_cur].args_count = 0;
			args[args_cur].args_status = 0;
			args[args_cur].args_num = l + 1;
			strcpy(args[args_cur].args_str, p);
			p = strrchr(args[args_cur].args_str, ')');
			int itemp = p - args[args_cur].args_str;
			args[args_cur].args_str[itemp + 1] = '\0';
			argsSearch(temp, args[args_cur].args_names, &args[args_cur].args_count);
			p = strchr(temp, '{');
			if (p != NULL) {
				/*outs[outs_cur].ins[outs[outs_cur].ins_count] = outs_count;
				outs[outs_cur].ins_count++;
				outs[outs_count].ins_count = 0;*/
				outs[outs_count].out = outs_cur;
				outs[outs_count].nesting = outs[outs_cur].nesting + 1;
				outs_cur = outs_count;
				outs_count++;
				oper_status[oper_count++] = 1;

				if (args[args_cur].args_count > 0)
					args[args_cur].args_status++;
			}
			else {
				p = strchr(file[l + 1], '{');
				if (p != NULL) {
					/*outs[outs_cur].ins[outs[outs_cur].ins_count] = outs_count;
					outs[outs_cur].ins_count++;
					outs[outs_count].ins_count = 0; */
					outs[outs_count].out = outs_cur;
					outs[outs_count].nesting = outs[outs_cur].nesting + 1;
					outs_cur = outs_count;
					outs_count++;
					oper_status[oper_count++] = 1;

					if (args[args_cur].args_count > 0)
						args[args_cur].args_status++;
				}
				else {
					/*outs[outs_cur].ins[outs[outs_cur].ins_count] = outs_count;
					outs[outs_cur].ins_count++;
					outs[outs_count].ins_count = 0;*/
					outs[outs_count].out = outs_cur;
					outs[outs_count].nesting = outs[outs_cur].nesting + 1;
					outs_count++;

					int a = 0;
					for (; a < args[args_cur].args_count; ++a) {
						p = strstr(file[l + 1], args[args_cur].args_names[a]);
						if (p == NULL)
							break;
					}
					if (a < args[args_cur].args_count) {
						//сообщение
						fprintf(draft2, "%d строка> Оператор '%s' может стать причиной зацикливания.\n", args[args_cur].args_num, args[args_cur].args_str);
					}
				}
			}
			args_cur++;
		}
		else {
			p = strstr(temp, "for");
			if (p != NULL) {
				strcpy(for_str[for_count], p);
				p = strrchr(for_str[for_count], ')');
				int itemp = p - for_str[for_count];
				for_str[for_count][itemp + 1] = '\0';
				for_num[for_count] = l;
				p = strstr(temp, ";;");
				if (p != NULL) {
					limit[for_count]++;
				}
				p = strstr(temp, ";)");
				if (p != NULL) {
					shift[for_count]++;
				}
				if (limit[for_count] > 0 || shift[for_count] > 0) {
					p = strstr(temp, "(;");
					if (p == NULL) {
						p = strchr(temp, '(');
						p = strchr(p, ' ');
						sscanf(p, "%s", for_args[for_count]);
					}
					else {
						if (limit[for_count] == 0) {
							p = strchr(temp, ';');
							p += 1;
							sscanf(p, "%s", for_args[for_count]);
						}
						else {
							if (shift[for_count] == 0) {
								p = strchr(temp, ';');
								p += 1;
								p = strchr(p, ';');
								p += 1;
								sscanf(p, "%s", for_args[for_count]);
								if (for_args[for_count][strlen(for_args[for_count]) - 1] == ')')
									for_args[for_count][strlen(for_args[for_count]) - 1] = '\0';
								if (for_args[for_count][0] == '-' && for_args[for_count][1] == '-'
									|| for_args[for_count][0] == '+' && for_args[for_count][1] == '+') {
									for (int j = 0; j < strlen(for_args[for_count]); ++j) {
										for_args[for_count][j] = for_args[for_count][j + 2];
									}
								}
								if (for_args[for_count][strlen(for_args[for_count]) - 1] == '-' && for_args[for_count][strlen(for_args[for_count]) - 2] == '-'
									|| for_args[for_count][strlen(for_args[for_count]) - 1] == '+' && for_args[for_count][strlen(for_args[for_count]) - 2] == '+') {
									for_args[for_count][strlen(for_args[for_count]) - 2] = '\0';
								}
							}
							else {
								fprintf(draft2, "%d строка> Оператор '%s' может стать причиной зацикливания.\n", for_num[for_count], for_str[for_count]);
								for_count--;
							}
						}
					}
					for_count++;
				}
				p = strchr(temp, '{');
				if (p != NULL) {
					/*outs[outs_cur].ins[outs[outs_cur].ins_count] = outs_count;
					outs[outs_cur].ins_count++;
					outs[outs_count].ins_count = 0;*/
					outs[outs_count].out = outs_cur;
					outs[outs_count].nesting = outs[outs_cur].nesting + 1;
					outs_cur = outs_count;
					outs_count++;
					oper_status[oper_count++] = 2;
					
				}
				else {
					p = strchr(file[l + 1], '{');
					if (p != NULL) {
						/*outs[outs_cur].ins[outs[outs_cur].ins_count] = outs_count;
						outs[outs_cur].ins_count++;
						outs[outs_count].ins_count = 0;*/
						outs[outs_count].out = outs_cur;
						outs[outs_count].nesting = outs[outs_cur].nesting + 1;
						outs_cur = outs_count;
						outs_count++;
						oper_status[oper_count++] = 2;
					}
					else {
						/*outs[outs_cur].ins[outs[outs_cur].ins_count] = outs_count;
						outs[outs_cur].ins_count++;
						outs[outs_count].ins_count = 0;*/
						outs[outs_count].out = outs_cur;
						outs[outs_count].nesting = outs[outs_cur].nesting + 1;
						outs_count++;
					}
				}
			}
		}
		if (com_end != 0) {
			strcat(temp, comment);
			com_end = 0;
			if (del_end == 0)
				com++;
		}
		fputs(temp, out);
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	fprintf(out, "\n\n\n");
	fseek(draft, 0, SEEK_END);
	long pos = ftell(draft);
	if (pos == 0) {
		fprintf(out, "Все переменные получили начальные значения.\n");
	}
	else {
		fseek(draft, 0, SEEK_SET);
		fgets(str, size, draft);
		while (!feof(draft)) {
			fputs(str, out);
			fgets(str, size, draft);
		}
	}
	int max_nest = 1;
	for (int c = 0; c < outs_count; ++c) {
		if (outs[c].nesting > max_nest)
			max_nest = outs[c].nesting;
	}
	if (max_nest == 1) {
		//в программе нет вложенных циклов
		fprintf(out, "В программе нет вложенных циклов.\n");
	}
	else {
		//маскимальная вложенность циклов равна ...
		fprintf(out, "Максимальная вложенность циклов равна %d.\n", max_nest);
	}
	for (int f = 0; f < funcs_count; ++f) {
		for (int n = 0; n < funcs[f].rets_names_count; ++n) {
			for (int s = 0; s < funcs_count; ++s) {
				if (strcmp(funcs[f].rets_names[n], funcs[s].name) == 0)
					funcs[f].rets[funcs[f].rets_count++] = s;
			}
		}
	}
	int count = 0;
	for (int f = 0; f < funcs_count; ++f) {
		int rec = 0;
		recursion(funcs, f, f, &rec);
		if (rec > 0) {
			//сообщение
			count++;
			fprintf(out, "Функция %s рекурсивна.\n", funcs[f].name);
		}
	}
	if (count == 0)
		fprintf(out, "В программе нет рекурсивных функций.\n");

	fseek(draft, 0, SEEK_END);
	pos = ftell(draft2);
	if (pos == 0) {
		fprintf(out, "Зацикливаний в программе не обнаружено.\n");
	}
	else {
		fseek(draft2, 0, SEEK_SET);
		fgets(str, size, draft2);
		while (!feof(draft2)) {
			fputs(str, out);
			fgets(str, size, draft2);
		}
	}

    fclose(in);
    fclose(out);
	fclose(draft);
	fclose(draft2);
    return 0;
}