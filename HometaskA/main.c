#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *Shift(int FirstBase, int SecondBase, char *);

char *GetLine();

char SymbShift(int FirsBase, int SecondBase, char *str);

char *SymbConvert(int FirsBase, int SecondBase, char *str);

char *ShiftTen(int SecondBase, const char *str);

char *ShiftTenInt(int SecondBase, long long Number);

bool zero(char *str);

char Numbers[36] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";


int main() {
    int P; // Input number system
    int Q; // Output number system
    scanf("%d%d", &P, &Q);
    char *Line = NULL;
    Line = GetLine();
    char *str = NULL;
    //str = Shift(P, Q, Line);
    str = SymbConvert(P, Q, Line);
    free(Line);
    int i = 0;
    while (str[i] != '\0')
        i++;
    for (i = i - 1; i >= 0; i--)
        printf("%c", str[i]);
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
    size_t BestInp = 1;
    size_t i = 0, j = 0;
    while (fgets(Buffer, Length, stdin)) {
        while (Buffer[i] != '\0') {
            i++;
            if (i == 30)
                break;
        }
        NumberCharacters = i;
        CurrentInp += NumberCharacters;
        if (Buffer[NumberCharacters] == '\0') {
            FinalInp = malloc(NumberCharacters + 1);
            FinalInp[0] = '\0';
            for (i = 0; FinalInp[i] != '\0'; i++);
            for (j = 0; Buffer[j] != '\0'; j++)
                FinalInp[i + j] = Buffer[j];
            FinalInp[i + j] = '\0';
            break;
        }
        if (CurrentInp >= BestInp) {                 // Reallocating memory if needed
            BestInp += Iter;
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

char *Shift(int FirstBase, int SecondBase, char *str) {
    char *Num = NULL;
    if (FirstBase == 10)
        Num = ShiftTen(SecondBase, str);
    else {
        long long Buffer = 0;
        int NumberCharacters = 0;
        int current = 0;
        int Dec = 0;
        int i = 0, j = 0;
        while (str[i] != '\0')                                      //Количество элементов без Strlen
            i++;
        for (int x = i - 1; x >= 0; x--) {
            Dec = str[x];
            if ((47 < Dec) && (Dec < 58))
                Dec -= 48;
            else if ((96 < Dec) && (Dec < 123))
                Dec -= 87;
            else if ((64 < Dec) && (Dec < 91))
                Dec -= 55;
            else
                Dec = -1;
            if (Dec >= 0) {
                current = Dec;
                j = NumberCharacters;
                while (j > 0) {
                    current *= FirstBase;
                    j--;
                }
                Buffer += current;
                NumberCharacters++;
            }
        }
        if (SecondBase != 10)
            Num = ShiftTenInt(SecondBase, Buffer);
        else {
            size_t it = 0;
            long long numeral = Buffer;
            while (numeral > 0) {
                it++;
                numeral /= 10;
            }
            char Numb[it + 1];
            size_t z = 0;
            while (Buffer > 0) {
                numeral = Buffer % 10;
                Numb[z] = (char) (numeral + 48);
                Buffer /= 10;
                z++;
            }
            Numb[z] = '\0';
            Num = malloc(z + 1);
            Num[0] = '\0';
            int j = 0;
            for (i = 0; Num[i] != '\0'; i++);
            for (j = 0; Numb[j] != '\0'; j++)
                Num[i + j] = Numb[j];
            Num[z] = '\0';
        }
    }
    return Num;
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

char *ShiftTenInt(int SecondBase, long long Number) {
    char *Num = NULL;
    char Buff[32];
    Buff[0] = '\0';
    int NumberCharacters = 0;
    size_t BestInp = 0;
    int i = 0, j = 0;
    long long inp = 0;
    while (Number >= SecondBase) {
        if (NumberCharacters >= BestInp) {
            BestInp += 32;
            Num = realloc(Num, BestInp);
            Num[0] = '\0';
            Buff[i + 1] = '\0';
            for (i = 0; Num[i] != '\0'; i++);
            for (j = 0; Buff[j] != '\0'; j++)
                Num[i + j] = Buff[j];
            Num[i + j] = '\0';
            i = 0;
        }
        inp = Number % SecondBase;
        Buff[i] = Numbers[inp];
        Number /= SecondBase;
        i++;
        NumberCharacters++;
    }
    Buff[i] = Numbers[Number];
    Buff[i + 1] = '\0';
    Num[j] = '\0';
    for (i = 0; Num[i] != '\0'; i++);
    for (j = 0; Buff[j] != '\0'; j++)
        Num[i + j] = Buff[j];
    Num[i + j] = '\0';
    return Num;
}

char SymbShift(int FirstBase, int SecondBase, char *str) {
    int tmp = 0;
    int len = 1;
    char String;
    while (str[len] != '\0')
        len++;
    len--;
    int Dec = 0;
    for (int i = 0; i < len; i++) {
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
        NewStr = realloc(NewStr, i);
        NewStr[i] = SymbShift(FirstBase, SecondBase, str);
        i++;
        size++;
    } while (!zero(str));
    return NewStr;
}

bool zero(char *str) {
    int len = 1;
    while (str[len] != '\0')
        len++;
    len--;
    for (int i = 1; i < len; i++)
        if (str[i] != '0')
            return false;
    return true;
}