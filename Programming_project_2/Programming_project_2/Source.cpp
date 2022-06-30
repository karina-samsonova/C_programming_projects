#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#pragma warning(disable: 6031)

#define size 200
#define SIZE 30
#define MAX 2147483647
#define st_point 3

void Csin(char str[]) {
	double a = 0;
	double b = 0;
	sscanf(str, "%lf %lf j", &a, &b);
	double ares = sin(a) * cosh(b);
	double bres = cos(a) * sinh(b);
	str[0] = '\0';
	sprintf(str, "%lf %lf j", ares, bres);
}
void Ccos(char str[]) {
	double a = 0;
	double b = 0;
	sscanf(str, "%lf %lf j", &a, &b);
	double ares = cos(a) * cosh(b);
	double bres = 0 - sin(a) * sinh(b);
	str[0] = '\0';
	sprintf(str, "%lf %lf j", ares, bres);
}
void Ctan(char str[]) {
	double a = 0;
	double b = 0;
	sscanf(str, "%lf %lf j", &a, &b);
	double ares = sin(2 * a) / (cos(2 * a) + cosh(2 * b));
	double bres = sinh(2 * b) / (cos(2 * a) + cosh(2 * b));
	str[0] = '\0';
	sprintf(str, "%lf %lf j", ares, bres);
}
double Cabs(char str[]) {
	double a = 0;
	double b = 0;
	sscanf(str, "%lf %lf j", &a, &b);
	return sqrt(pow(a, 2) + pow(b, 2));
}
void Csqrt(char str[]) {
	double a = 0;
	double b = 0;
	sscanf(str, "%lf %lf j", &a, &b);
	double r = Cabs(str);
	double fi;
	if (a == 0)
		fi = 89.3634;
	else
		fi = atan(b / a);
	double ares = sqrt(r) * cos(fi / 2);
	double bres = sqrt(r) * sin(fi / 2);
	str[0] = '\0';
	sprintf(str, "%lf %lf j", ares, bres);
}
void Cexp(char str[]) {
	double a = 0;
	double b = 0;
	sscanf(str, "%lf %lf j", &a, &b);
	/*double ares = pow(0.540302306, b) * exp(a);
	double bres = pow(0.841470985, b) * exp(a);*/
	double ares = cos(b) * exp(a);
	double bres = sin(b) * exp(a);
	str[0] = '\0';
	sprintf(str, "%lf %lf j", ares, bres);
}
void Cln(char str[]) {
	double a = 0;
	double b = 0;
	sscanf(str, "%lf %lf j", &a, &b);
	double r = Cabs(str);
	double fi;
	if (a == 0)
		fi = 89.3634;
	else
		fi = atan(b / a);
	a = log(r);
	str[0] = '\0';
	sprintf(str, "%lf %lf j", a, fi);
}
void Clog(char str[]) {
	double a = 0;
	double b = 0;
	sscanf(str, "%lf %lf j", &a, &b);
	double r = Cabs(str);
	double fi = atan(b / a)/log(10);
	a = log(r)/log(10);
	str[0] = '\0';
	sprintf(str, "%lf %lf j", a, fi);
}
int FindInd(char names[][SIZE], char name[], int k) {
	for (int i = 0; i < k; ++i) {
		if (strcmp(names[i], name) == 0)
			return i;
	}
	return -1;
}
int IsComplex(char str[]) { //0 - yes, 1 - no
	if (str[strlen(str) - 1] == 'j' && str[strlen(str) - 2] == ' ' && str[strlen(str) - 3] >= 48 && str[strlen(str) - 3] <= 57) 
		return 0;
	return 1;
}
void Solving(char str[], int index, char names[][SIZE], int k, char expressions[][size], int* err) {
	int priorities[130] = { 0 };
	priorities[43] = 1;
	priorities[45] = 1;
	priorities[42] = 2;
	priorities[47] = 2;
	priorities[94] = 3;
	priorities[40] = 0;
	priorities[126] = 5;
	for (int p = 97; p <= 122; ++p)
		priorities[p] = 4;
	char temp[SIZE] = { 0 };
	char operations[SIZE][SIZE] = { 0 };
	int iop = 0;
	char res[SIZE][SIZE] = { 0 };
	int ires = 0;
	char* p = strchr(str, str[0]);
	while (strlen(p) > 0) {
		sscanf(p, "%s", temp);
		p = strstr(p, temp) + strlen(temp);
		if (strcmp(temp, "cos") == 0 || strcmp(temp, "sin") == 0 || strcmp(temp, "tg") == 0 || strcmp(temp, "log") == 0 || strcmp(temp, "ln") == 0 || 
			strcmp(temp, "sqrt") == 0 || strcmp(temp, "exp") == 0 || strcmp(temp, "real") == 0 || strcmp(temp, "imag") == 0 || strcmp(temp, "mag") == 0 || 
			strcmp(temp, "phase") == 0 || strcmp(temp, "-") == 0 || strcmp(temp, "(") == 0 || strcmp(temp, ")") == 0 || strcmp(temp, "*") == 0 || 
			strcmp(temp, "+") == 0 || strcmp(temp, "/") == 0 || strcmp(temp, "^") == 0 || strcmp(temp, "abs") == 0 || strcmp(temp, "~") == 0) {
			if (strcmp(temp, "(") == 0) {
				strcpy(operations[iop], temp);
				iop++;
			}
			else if (strcmp(temp, ")") == 0) {
				while (strcmp(operations[iop - 1], "(") != 0) {
					strcpy(res[ires], operations[iop - 1]);
					ires++;
					iop--;
				}
				iop--;
			}
			else if (iop == 0 || (iop != 0 && priorities[(int)temp[0]] > priorities[(int)operations[iop - 1][0]])) {
				strcpy(operations[iop], temp);
				iop++;
			}
			else {
				while (priorities[(int)temp[0]] <= priorities[(int)operations[iop - 1][0]] && iop > 0) {
					strcpy(res[ires], operations[iop - 1]);
					ires++;
					iop--;
				}
				iop++;
				strcpy(operations[iop - 1], temp);
			}
		}
		else {
			int ind = FindInd(names, temp, k);
			if (ind == -1)
				strcpy(res[ires], temp);
			else
				strcpy(res[ires], expressions[ind]);
			ires++;
		}
	}
	while (iop > 0) {
		strcpy(res[ires], operations[iop - 1]);
		ires++;
		iop--;
	}

	int icur = 0;
	while (ires > 1) {
		icur = 0;
		while (!(strcmp(res[icur], "cos") == 0 || strcmp(res[icur], "sin") == 0 || strcmp(res[icur], "tg") == 0 || strcmp(res[icur], "log") == 0 || strcmp(res[icur], "ln") == 0 ||
			strcmp(res[icur], "sqrt") == 0 || strcmp(res[icur], "exp") == 0 || strcmp(res[icur], "real") == 0 || strcmp(res[icur], "imag") == 0 || strcmp(res[icur], "mag") == 0 ||
			strcmp(res[icur], "phase") == 0 || strcmp(res[icur], "-") == 0 || strcmp(res[icur], "(") == 0 || strcmp(res[icur], ")") == 0 || strcmp(res[icur], "*") == 0 ||
			strcmp(res[icur], "+") == 0 || strcmp(res[icur], "/") == 0 || strcmp(res[icur], "^") == 0 || strcmp(res[icur], "abs") == 0 || strcmp(res[icur], "~") == 0)) {
			icur++;
		}

		if (strcmp(res[icur], "~") == 0) {
			if (IsComplex(res[icur - 1]) == 0) {
				double a = 0;
				double b = 0;
				sscanf(res[icur - 1], "%lf %lf j", &a, &b);
				a *= -1;
				b *= -1;
				res[icur - 1][0] = '\0';
				sprintf(res[icur - 1], "%lf %lf j", a, b);
			}
			else {
				double a = 0;
				sscanf(res[icur - 1], "%lf", &a);
				a *= -1;
				res[icur - 1][0] = '\0';
				sprintf(res[icur - 1], "%lf", a);
			}
			for (int t = icur; t < ires; ++t) {
				strcpy(res[t], res[t + 1]);
			}
			ires--;
		}

		else if (strcmp(res[icur], "sin") == 0) {
			if (IsComplex(res[icur - 1]) == 0) {
				Csin(res[icur - 1]);
			}
			else {
				double x = 0;
				sscanf(res[icur - 1], "%lf", &x);
				res[icur - 1][0] = '\0';
				sprintf(res[icur - 1], "%lf", sin(x));
			}
			for (int t = icur; t < ires; ++t) {
				strcpy(res[t], res[t + 1]);
			}
			ires--;
		}

		else if (strcmp(res[icur], "cos") == 0) {
			if (IsComplex(res[icur - 1]) == 0) {
				Ccos(res[icur - 1]);
			}
			else {
				double x = 0;
				sscanf(res[icur - 1], "%lf", &x);
				res[icur - 1][0] = '\0';
				sprintf(res[icur - 1], "%lf", cos(x));
			}
			for (int t = icur; t < ires; ++t) {
				strcpy(res[t], res[t + 1]);
			}
			ires--;
		}

		else if (strcmp(res[icur], "tg") == 0) {
			if (IsComplex(res[icur - 1]) == 0) {
				Ctan(res[icur - 1]);
			}
			else {
				double x = 0;
				sscanf(res[icur - 1], "%lf", &x);
				res[icur - 1][0] = '\0';
				sprintf(res[icur - 1], "%lf", tan(x));
			}
			for (int t = icur; t < ires; ++t) {
				strcpy(res[t], res[t + 1]);
			}
			ires--;
		}

		else if (strcmp(res[icur], "abs") == 0) {
			double x = 0;
			sscanf(res[icur - 1], "%lf", &x);
			res[icur - 1][0] = '\0';
			sprintf(res[icur - 1], "%lf", fabs(x));
			for (int t = icur; t < ires; ++t) {
				strcpy(res[t], res[t + 1]);
			}
			ires--;
		}

		else if (strcmp(res[icur], "sqrt") == 0) {
			if (IsComplex(res[icur - 1]) == 0) {
				Csqrt(res[icur - 1]);
			}
			else {
				double x = 0;
				sscanf(res[icur - 1], "%lf", &x);
				res[icur - 1][0] = '\0';
				sprintf(res[icur - 1], "%lf", sqrt(x));
			}
			for (int t = icur; t < ires; ++t) {
				strcpy(res[t], res[t + 1]);
			}
			ires--;
		}

		else if (strcmp(res[icur], "mag") == 0) {
			double r = Cabs(res[icur - 1]);
			res[icur - 1][0] = '\0';
			sprintf(res[icur - 1], "%lf", r);
			for (int t = icur; t < ires; ++t) {
				strcpy(res[t], res[t + 1]);
			}
			ires--;
		}

		else if (strcmp(res[icur], "phase") == 0) {
			double a = 0;
			double b = 0;
			sscanf(res[icur - 1], "%lf %lf j", &a, &b);
			double fi;
			if (a == 0)
				fi = 89.3634;
			else
				fi = atan(b / a);
			res[icur - 1][0] = '\0';
			sprintf(res[icur - 1], "%lf", fi);
			for (int t = icur; t < ires; ++t) {
				strcpy(res[t], res[t + 1]);
			}
			ires--;
		}

		else if (strcmp(res[icur], "real") == 0) {
		double a = 0;
		sscanf(res[icur - 1], "%lf", &a);
		res[icur - 1][0] = '\0';
		sprintf(res[icur - 1], "%lf", a);
		for (int t = icur; t < ires; ++t) {
			strcpy(res[t], res[t + 1]);
		}
		ires--;
		}

		else if (strcmp(res[icur], "imag") == 0) {
		double a = 0;
		double b = 0;
		sscanf(res[icur - 1], "%lf %lf j", &a, &b);
		res[icur - 1][0] = '\0';
		sprintf(res[icur - 1], "%lf", b);
		res[icur - 1][strlen(res[icur - 1])] = '\0';
		for (int t = icur; t < ires; ++t) {
			strcpy(res[t], res[t + 1]);
		}
		ires--;
		}

		else if (strcmp(res[icur], "*") == 0) {
		if (IsComplex(res[icur - 2]) == 0 && IsComplex(res[icur - 1]) == 0) {
			double a = 0;
			double b = 0;
			sscanf(res[icur - 2], "%lf %lf j", &a, &b);
			double c = 0;
			double d = 0;
			sscanf(res[icur - 1], "%lf %lf j", &c, &d);
			double ares = a * c - b * d;
			double bres = a * d + b * c;
			res[icur - 2][0] = '\0';
			sprintf(res[icur - 2], "%lf %lf j", ares, bres);
		}
		else if (IsComplex(res[icur - 2]) == 1 && IsComplex(res[icur - 1]) == 0) {
			double c = 0;
			sscanf(res[icur - 2], "%lf", &c);
			double a = 0;
			double b = 0;
			sscanf(res[icur - 1], "%lf %lf j", &a, &b);
			double ares = a * c;
			double bres = b * c;
			res[icur - 2][0] = '\0';
			sprintf(res[icur - 2], "%lf %lf j", ares, bres);
		}
		else if (IsComplex(res[icur - 2]) == 0 && IsComplex(res[icur - 1]) == 1) {
			double c = 0;
			sscanf(res[icur - 1], "%lf", &c);
			double a = 0;
			double b = 0;
			sscanf(res[icur - 2], "%lf %lf j", &a, &b);
			double ares = a * c;
			double bres = b * c;
			res[icur - 2][0] = '\0';
			sprintf(res[icur - 2], "%lf %lf j", ares, bres);
		}
		else {
			double a = 0;
			double b = 0;
			sscanf(res[icur - 2], "%lf", &a);
			sscanf(res[icur - 1], "%lf", &b);
			res[icur - 2][0] = '\0';
			sprintf(res[icur - 2], "%lf", a * b);
		}
		for (int t = icur - 1; t < ires; ++t) {
			strcpy(res[t], res[t + 2]);
		}
		ires = ires - 2;
		}

		else if (strcmp(res[icur], "+") == 0) {
		if (IsComplex(res[icur - 2]) == 0 && IsComplex(res[icur - 1]) == 0) {
			double a = 0;
			double b = 0;
			sscanf(res[icur - 2], "%lf %lf j", &a, &b);
			double c = 0;
			double d = 0;
			sscanf(res[icur - 1], "%lf %lf j", &c, &d);
			double ares = a + c;
			double bres = b + d;
			res[icur - 2][0] = '\0';
			sprintf(res[icur - 2], "%lf %lf j", ares, bres);
		}
		else if (IsComplex(res[icur - 2]) == 1 && IsComplex(res[icur - 1]) == 0) {
			double c = 0;
			sscanf(res[icur - 2], "%lf", &c);
			double a = 0;
			double b = 0;
			sscanf(res[icur - 1], "%lf %lf j", &a, &b);
			a += c;
			res[icur - 2][0] = '\0';
			sprintf(res[icur - 2], "%lf %lf j", a, b);
		}
		else if (IsComplex(res[icur - 2]) == 0 && IsComplex(res[icur - 1]) == 1) {
			double c = 0;
			sscanf(res[icur - 1], "%lf", &c);
			double a = 0;
			double b = 0;
			sscanf(res[icur - 2], "%lf %lf j", &a, &b);
			a += c;
			res[icur - 2][0] = '\0';
			sprintf(res[icur - 2], "%lf %lf j", a, b);
		}
		else {
			double a = 0;
			double b = 0;
			sscanf(res[icur - 2], "%lf", &a);
			sscanf(res[icur - 1], "%lf", &b);
			res[icur - 2][0] = '\0';
			sprintf(res[icur - 2], "%lf", a + b);
		}
		for (int t = icur - 1; t < ires; ++t) {
			strcpy(res[t], res[t + 2]);
		}
		ires = ires - 2;
		}

		else if (strcmp(res[icur], "-") == 0) {
		if (IsComplex(res[icur - 2]) == 0 && IsComplex(res[icur - 1]) == 0) {
			double a = 0;
			double b = 0;
			sscanf(res[icur - 2], "%lf %lf j", &a, &b);
			double c = 0;
			double d = 0;
			sscanf(res[icur - 1], "%lf %lf j", &c, &d);
			double ares = a - c;
			double bres = b - d;
			res[icur - 2][0] = '\0';
			sprintf(res[icur - 2], "%lf %lf j", ares, bres);
		}
		else if (IsComplex(res[icur - 2]) == 1 && IsComplex(res[icur - 1]) == 0) {
			double c = 0;
			sscanf(res[icur - 2], "%lf", &c);
			double a = 0;
			double b = 0;
			sscanf(res[icur - 1], "%lf %lf j", &a, &b);
			double ares = c - a;
			double bres = 0 - b;
			res[icur - 2][0] = '\0';
			sprintf(res[icur - 2], "%lf %lf j", ares, bres);
		}
		else if (IsComplex(res[icur - 2]) == 0 && IsComplex(res[icur - 1]) == 1) {
			double c = 0;
			sscanf(res[icur - 1], "%lf", &c);
			double a = 0;
			double b = 0;
			sscanf(res[icur - 2], "%lf %lf j", &a, &b);
			a -= c;
			res[icur - 2][0] = '\0';
			sprintf(res[icur - 2], "%lf %lf j", a, b);
		}
		else {
			double a = 0;
			double b = 0;
			sscanf(res[icur - 2], "%lf", &a);
			sscanf(res[icur - 1], "%lf", &b);
			res[icur - 2][0] = '\0';
			sprintf(res[icur - 2], "%lf", a - b);
		}
		for (int t = icur - 1; t < ires; ++t) {
			strcpy(res[t], res[t + 2]);
		}
		ires = ires - 2;
		}

		else if (strcmp(res[icur], "/") == 0) {
		if (IsComplex(res[icur - 2]) == 0 && IsComplex(res[icur - 1]) == 0) {
			double a = 0;
			double b = 0;
			sscanf(res[icur - 2], "%lf %lf j", &a, &b);
			double c = 0;
			double d = 0;
			sscanf(res[icur - 1], "%lf %lf j", &c, &d);
			double ares = (a * c + b * d) / (c * c + d * d);
			double bres = (b * c - a * d) / (c * c + d * d);
			res[icur - 2][0] = '\0';
			sprintf(res[icur - 2], "%lf %lf j", ares, bres);
		}
		else if (IsComplex(res[icur - 2]) == 1 && IsComplex(res[icur - 1]) == 0) {
			double c = 0;
			sscanf(res[icur - 2], "%lf", &c);
			double a = 0;
			double b = 0;
			sscanf(res[icur - 1], "%lf %lf j", &a, &b);
			double ares = (a * c) / (a * a + b * b);
			double bres = 0 - (b * c) / (a * a + b * b);
			res[icur - 2][0] = '\0';
			sprintf(res[icur - 2], "%lf %lf j", ares, bres);
		}
		else if (IsComplex(res[icur - 2]) == 0 && IsComplex(res[icur - 1]) == 1) {
			double c = 0;
			sscanf(res[icur - 1], "%lf", &c);
			if (c == 0) {
				printf("Division by 0 is not allowed\n\n\n\n");
				*err += 1;
				return;
			}
			double a = 0;
			double b = 0;
			sscanf(res[icur - 2], "%lf %lf j", &a, &b);
			a /= c;
			b /= c;
			res[icur - 2][0] = '\0';
			sprintf(res[icur - 2], "%lf %lf j", a, b);
		}
		else {
			double a = 0;
			double b = 0;
			sscanf(res[icur - 2], "%lf", &a);
			sscanf(res[icur - 1], "%lf", &b);
			if (b == 0) {
				printf("Division by 0 is not allowed\n\n\n\n");
				*err += 1;
				return;
			}
			res[icur - 2][0] = '\0';
			sprintf(res[icur - 2], "%lf", a / b);
		}
		for (int t = icur - 1; t < ires; ++t) {
			strcpy(res[t], res[t + 2]);
		}
		ires = ires - 2;
		}
		else if (strcmp(res[icur], "exp") == 0) {
		if (IsComplex(res[icur - 1]) == 0) {
			Cexp(res[icur - 1]);
		}
		else {
			double x = 0;
			sscanf(res[icur - 1], "%lf", &x);
			res[icur - 1][0] = '\0';
			sprintf(res[icur - 1], "%lf", exp(x));
		}
		for (int t = icur; t < ires; ++t) {
			strcpy(res[t], res[t + 1]);
		}
		ires--;
		}

		else if (strcmp(res[icur], "^") == 0) {
		if (IsComplex(res[icur - 2]) == 0 && IsComplex(res[icur - 1]) == 0) {
			double a = 0;
			double b = 0;
			sscanf(res[icur - 2], "%lf %lf j", &a, &b);
			Clog(res[icur - 2]);
			sscanf(res[icur - 2], "%lf %lf j", &a, &b);
			double c = 0;
			double d = 0;
			sscanf(res[icur - 1], "%lf %lf j", &c, &d);
			double x = a * c - b * d;
			double y = a * d + b * c;
			double ares = cos(y) * exp(x);
			double bres = sin(y) * exp(x);
			res[icur - 2][0] = '\0';
			sprintf(res[icur - 2], "%lf %lf j", ares, bres);
		}
		else if (IsComplex(res[icur - 2]) == 1 && IsComplex(res[icur - 1]) == 0) {
			double c = 0;
			sscanf(res[icur - 2], "%lf", &c);
			c = log(c);
			double a = 0;
			double b = 0;
			sscanf(res[icur - 1], "%lf %lf j", &a, &b);
			double ares = a * c;
			double bres = b * c;
			res[icur - 2][0] = '\0';
			sprintf(res[icur - 2], "%lf %lf j", ares, bres);
			Cexp(res[icur - 2]);
		}
		else if (IsComplex(res[icur - 2]) == 0 && IsComplex(res[icur - 1]) == 1) {
			double c = 0;
			sscanf(res[icur - 1], "%lf", &c);
			double a = 0;
			double b = 0;
			sscanf(res[icur - 2], "%lf %lf j", &a, &b);
			double fi;
			if (a == 0)
				fi = 89.3634;
			else
				fi = atan(b / a);
			double r = Cabs(res[icur - 2]);
			a = cos(c * fi) * pow(r, c);
			b = sin(c * fi) * pow(r, c);
			res[icur - 2][0] = '\0';
			sprintf(res[icur - 2], "%lf %lf j", a, b);
		}
		else {
			double a = 0;
			double b = 0;
			sscanf(res[icur - 2], "%lf", &a);
			sscanf(res[icur - 1], "%lf", &b);
			res[icur - 2][0] = '\0';
			sprintf(res[icur - 2], "%lf", pow(a, b));
		}
		for (int t = icur - 1; t < ires; ++t) {
			strcpy(res[t], res[t + 2]);
		}
		ires = ires - 2;
		}

		else if (strcmp(res[icur], "ln") == 0) {
		if (IsComplex(res[icur - 1]) == 0) {
			Cln(res[icur - 1]);
		}
		else {
			double x = 0;
			sscanf(res[icur - 1], "%lf", &x);
			res[icur - 1][0] = '\0';
			sprintf(res[icur - 1], "%lf", log(x));
		}
		for (int t = icur; t < ires; ++t) {
			strcpy(res[t], res[t + 1]);
		}
		ires--;
		}

		else if (strcmp(res[icur], "log") == 0) {
		if (IsComplex(res[icur - 1]) == 0) {
			Clog(res[icur - 1]);
		}
		else {
			double x = 0;
			sscanf(res[icur - 1], "%lf", &x);
			res[icur - 1][0] = '\0';
			sprintf(res[icur - 1], "%lf", log10(x));
		}
		for (int t = icur; t < ires; ++t) {
			strcpy(res[t], res[t + 1]);
		}
		ires--;
		}

	}
	strcpy(expressions[index], res[0]);
}
int main() { //****************************************************************************************************************************************
	char str[size] = { 0 };
	char names[SIZE][SIZE] = { 0 };
	char expressions[SIZE][size] = { 0 };
	double values[SIZE] = { 0 };
	int status[SIZE] = { 0 };
	strcpy(names[0], "PI");
	strcpy(expressions[0], "3.14159");
	strcpy(names[1], "j");
	strcpy(expressions[1], "0.0 1.0 j");
	strcpy(names[2], "e");
	strcpy(expressions[2], "2.718281");

	int count = 0;
	int itemp = st_point;
	char word[SIZE] = { 0 };

	FILE* in = fopen("input.txt", "rt");

	while (!feof(in)) {
		fgets(str, size, in);
		if (count == 0) {
			if (str[strlen(str) - 1] == '\n')
				str[strlen(str) - 1] = '\0';
			strcpy(expressions[itemp], str);
			if (IsComplex(str) == 0) {
				for (int t = 0; t < strlen(str); ++t) {
					if (expressions[itemp][t] == '+') {
						expressions[itemp][t] = ' ';
					}
					if (t > 0 && expressions[itemp][t - 1] == '-') {
						expressions[itemp][t - 1] = ' ';
						expressions[itemp][t] = '-';
						t++;
					}
					
				}
			}
			itemp++;
			count++;
		}
		else {
			if (str[strlen(str) - 1] == '\n')
				str[strlen(str) - 1] = '\0';
			sscanf(str, "%s", names[itemp]);
			char* p = strchr(str, '=') + 2;
			if (IsComplex(p) == 0) {
				strcpy(expressions[itemp], p);
				for (int t = 0; t < strlen(p); ++t) {
					if (expressions[itemp][t] == '+') {
						expressions[itemp][t] = ' ';
					}
					if (t > 0 && expressions[itemp][t - 1] == '-') {
						expressions[itemp][t - 1] = ' ';
						expressions[itemp][t] = '-';
						t++;
					}
				}
			}
			else
				strcpy(expressions[itemp], p);
			itemp++;
		}
	}
	fclose(in);

	int err = 0;
	for (int i = itemp - 1; i >= st_point; i--) { //**************************************************************************************************
		if (strchr(expressions[i], ' ') != NULL && IsComplex(expressions[i]) == 1) {
			Solving(expressions[i], i, names, itemp, expressions, &err);
		}
	}
	if (err != 0)
		return 0;
	printf("The answer is\t"); //*********************************************************************************************************************
	if (IsComplex(expressions[st_point]) == 0) {
		double a = 0;
		double b = 0;
		sscanf(expressions[st_point], "%lf %lf j", &a, &b);
		if (fabs(b) == 0) {
			if (fabs(a) == 0)
				printf("0 ");
			else if (a < 0) {
				a *= -1;
				if (floor(a) - a == 0)
					printf("- %.0lf ", a);
				else
					printf("- %.6lf ", a);
			}
			else {
				if (floor(a) - a == 0)
					printf("%.0lf ", a);
				else
					printf("%.6lf ", a);
			}
		}
		else {
			if (a < 0 && fabs(a) != 0) {
				a *= -1;
				if (floor(a) - a == 0)
					printf("- %.0lf ", a);
				else
					printf("- %.6lf ", a);
			}
			else if (fabs(a) != 0) {
				if (floor(a) - a == 0)
					printf("%.0lf ", a);
				else
					printf("%.6lf ", a);
			}
			if (b < 0) {
				b *= -1;
				if (floor(b) - b == 0)
					printf("- %.0lfj", b);
				else
					printf("- %.6lfj", b);
			}
			else if (fabs(a) == 0) {
				if (floor(b) - b == 0)
					printf("%.0lfj", b);
				else
					printf("%.6lfj", b);
			}
			else {
				if (floor(b) - b == 0)
					printf("+ %.0lfj", b);
				else
					printf("+ %.6lfj", b);
			}
		}
		
	}
	else {
		double a = 0;
		sscanf(expressions[st_point], "%lf", &a);
		if (fabs(a) == 0)
			printf("0");
		else if (floor(a) - a == 0)
			printf("%.0lf", a);
		else
			printf("%.6lf", a);
	}
	printf("\n\n\n\n");

	//fclose(in);
	return 0;
}
