/* Пученков Дмитрий
 * АПО13
 * Составить программу для перевода чисел из системы счисления по основанию P в систему счисления по основанию Q, где 2 меньше или равно Q меньше P меньше или равно 36.
Значения P, Q и строковое представление S числа в исходной системе счисления вводятся с клавиатуры в следующем порядке:
P Q S

S не выходит за границы size_t.

Процедура перевода не может использовать соответствующей функции системной библиотеки и должна быть оформлена в виде отдельной функции, на вход которой подаются значения P, Q и S, размещенные в динамической памяти.
На выход функция должна возвращать строковое представление S1 числа в целевой системе счисления.

Программа должна уметь обрабатывать ошибки во входных данных.
В случае возникновения ошибки нужно вывести в поток стандартного вывода сообщение "[error]" (без кавычек) и завершить выполнение программы.

ВАЖНО! Программа в любом случае должна возвращать 0. Не пишите return -1, exit(1) и т.п. Даже если обнаружилась какая-то ошибка, все равно необходимо вернуть 0! (и напечатать [error] в stdout). */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


char *GetLine();

char SymbShift(int FirstBase, int SecondBase, char *str);

char *SymbConvert(int FirstBase, int SecondBase, char *str);

bool zero(const char *str);

bool InputCheck(char *str, int FirstBase, int SecondBase);

char Numbers[36] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main() {
    int P; // Input number system
    int Q; // Output number system
    scanf("%d%d", &P, &Q);
    char *Line = NULL;
    Line = GetLine();
    char *str = NULL;
    if (InputCheck(Line, P, Q)) {
        str = SymbConvert(P, Q, Line);
        free(Line);
        int i = 0;
        while (str[i] != '\0')
            i++;
        for (i = i - 1; i >= 0; i--)
            printf("%c", str[i]);
    }
    free(str);
    return 0;
}

char *GetLine() {
    const size_t Iter = 32;
    const size_t Length = 32;
    char Buffer[Length];
    Buffer[0] = '\0';
    char *FinalInp = NULL;
    size_t NumberCharacters = 0;
    size_t CurrentInp = 0;
    size_t BestInp = 31;
    size_t i = 0, j = 0;
    while (fgets(Buffer, Length, stdin)) {
        while (Buffer[i] != '\0' && Buffer[i] != '\n') {
            if ((Buffer[i] < '0' || (Buffer[i] > '9' && Buffer[i] < 'A') || (Buffer[i] > 'Z' && Buffer[i] < 'a') ||
                 Buffer[i] > 'z') && Buffer[i] != ' ') {
                printf("[error]");
                exit(0);
            }
            i++;
            if (i == 30)
                break;
        }
        NumberCharacters = i;
        CurrentInp += NumberCharacters;
        if (Buffer[NumberCharacters] == '\0' || Buffer[NumberCharacters] == '\n') {
            FinalInp = malloc(NumberCharacters + 2);
            FinalInp[0] = '\0';
            for (i = 0; FinalInp[i] != '\0'; i++);
            for (j = 0; Buffer[j] != '\0'; j++)
                FinalInp[i + j] = Buffer[j];
            FinalInp[i + j] = '\0';
            break;
        }
        if (CurrentInp >= BestInp) {                 // Reallocating memory if needed
            BestInp ++;
            FinalInp = realloc(FinalInp, BestInp);
            Buffer[i] = '\0';
            FinalInp[0] = '\0';
            for (i = 0; FinalInp[i] != '\0'; i++);
            for (j = 0; Buffer[j] != '\0'; j++)
                FinalInp[i + j] = Buffer[j];
            FinalInp[i + j] = '\0';
            i = 0;
        }

        if (ferror(stdin)) {
            if (FinalInp)
                free(FinalInp);
            printf("[error]\n");
            exit(0);                                // In case there is Input Error, we stop program with exit + std::Error
        }
    }
    if (FinalInp == NULL) {
        FinalInp = malloc(sizeof(size_t));
        FinalInp[0] = '\0';
    }
    return FinalInp;
}

char *ShiftTen(int SecondBase, const char *str) {
    char Buff[32];
    Buff[0] = '\0';
    int NewNum = 0;
    int i = 0, j = 0;
    size_t len = 1;
    while (str[len] != '\0')
        len++;
    len--;
    for (i = 1; (i != len + 1) && str[i] >= '0' && str[i] <= '9'; i++) {
        NewNum = (NewNum * 10) + (str[i] - '0');
    }
    i = 0;
    char *Num;
    Num = malloc(sizeof(len));
    Num[0] = '\0';
    while (NewNum >= SecondBase) {
        Buff[i] = Numbers[NewNum % SecondBase];
        NewNum /= SecondBase;
        i++;
    }
    Buff[i] = Numbers[NewNum];
    Buff[i + 1] = '\0';
    Num[0] = '\0';
    for (i = 0; Num[i] != '\0'; i++);
    for (j = 0; Buff[j] != '\0'; j++)
        Num[i + j] = Buff[j];
    Num[i + j] = '\0';
    return Num;
}

char SymbShift(int FirstBase, int SecondBase, char *str) {
    int tmp = 0;
    int len = 0;
    char String;
    while (str[len] != '\0' && str[len] != '\n')
        len++;
    len--;
    int Dec = 0;
    for (int i = 1; i <= len; i++) {
        Dec = str[i];
        if ((47 < Dec) && (Dec < 58))
            Dec -= 48;
        else if ((96 < Dec) && (Dec < 123))
            Dec -= 87;
        else if ((64 < Dec) && (Dec < 91))
            Dec -= 55;
        else
            Dec = -1;
        if (Dec >= 0) {
            tmp = tmp * FirstBase + Dec;
            Dec = tmp / SecondBase;
            tmp = tmp % SecondBase;
            if (-1 < Dec && Dec < 10)
                str[i] = (char) (Dec + 48);
            if (9 < Dec && Dec < 37)
                str[i] = (char) (Dec + 87);
        }
    }
    String = Numbers[tmp];
    return String;
}

char *SymbConvert(int FirstBase, int SecondBase, char *str) {
    char *NewStr = NULL;
    size_t size = 1;
    int i = 0;
    do {
        NewStr = realloc(NewStr, size + 1);
        NewStr[i] = SymbShift(FirstBase, SecondBase, str);
        i++;
        size++;
    } while (!zero(str));
    NewStr[size - 1] = '\0';
    return NewStr;
}

bool zero(const char *str) {
    int len = 0;
    while (str[len] != '\0' && str[len] != '\n')
        len++;
    len--;
    for (int i = 1; i <= len; i++)
        if (str[i] != '0')
            return false;
    return true;
}

bool InputCheck(char *str, int FirstBase, int SecondBase) {
    int i = 0;
    if (FirstBase < SecondBase) {
        printf("[error]");
        exit(0);
    }
    if (SecondBase < 2 || FirstBase > 36){
        printf("[error]");
        exit(0);
    }
    size_t len = 0;
    while (str[len] != '\0' && str[len] != '\n')
        len++;
    len--;
    char tmp[len];
    while (str[i] != '\0' && str[i] != '\n') {
        if (str[i] > 'a' && str[i] < 123) {
            tmp[i] = str[i] - 32;
            if (tmp[i] > Numbers[FirstBase - 1]) {
                printf("[error]");
                exit(0);
            }
        } else if ((str[i] > 64) && (str[i] < 91))
            if (str[i] > Numbers[FirstBase - 1]) {
                printf("[error]");
                exit(0);
            }
        i++;
    }
    return true;
}