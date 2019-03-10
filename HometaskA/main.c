#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *Shift(int FirstBase, int SecondBase, char *);

char *GetLine();

char *ShiftTen(int SecondBase, char *str);

char *ShiftTenInt(int SecondBase, int Number);

char Numbers[36] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main() {
    int P; // Input number system
    int Q; // Output number system
    scanf("%d%d", &P, &Q);
    char *str = Shift(P, Q, GetLine());
    int i = 0;
    while (str[i] != '\0')
        i++;
    for (i = i - 1; i >= 0; i--)
        printf("%c", str[i]);
    return 0;
}

char *GetLine() {
    const size_t Length = 32;
    const size_t Incr = 32;
    char Buffer[Length];
    char *FinalInp = NULL;
    int NumberCharacters = 0;
    size_t CurrentInp = 0;
    size_t BestInp = 0;
    int i = 0;
    while (fgets(Buffer, Length, stdin)) {
        while (Buffer[i] != '\0')
            i++;
        NumberCharacters = i;
        CurrentInp += NumberCharacters;
        if (Buffer[NumberCharacters - 1] == '\n') {
            Buffer[NumberCharacters - 1] = '\0';
            FinalInp = realloc(FinalInp, BestInp);
            strcat(FinalInp, Buffer);
            break;
        }
        if (CurrentInp >= BestInp) {                 // Reallocating memory if needed
            BestInp += Incr;
            FinalInp = realloc(FinalInp, BestInp);
            strcat(FinalInp, Buffer);
        }
        if (ferror(stdin)) {
            if (FinalInp)
                free(FinalInp);
            printf("[error]\n");
            exit(0);                                // In case there is Input Error, we stop program with exit + std::Error
        }

    }

    return FinalInp;
}

char *Shift(int FirstBase, int SecondBase, char *str) {
    char *Num = NULL;
    if (FirstBase == 10)
        Num = ShiftTen(SecondBase, str);
    else {
        int Buffer = 0;
        int NumberCharacters = 0;
        int current = 0;
        int Dec = 0;
        int i = 0;                                      //Количество элементов без strlen
        while (str[i] != '\0')
            i++;
        for (int x = i - 1; x >= 0; x--) {
            Dec = str[x];
            if ((47 < Dec) && (Dec < 58))
                Dec -= 48;
            else
                Dec -= 60;
            if (Dec >= 0) {
                current = Dec;
                while (NumberCharacters > 0) {
                    current *= FirstBase;
                    NumberCharacters--;
                }
                Buffer += current;
                NumberCharacters++;
            }
        }
        if (SecondBase != 10)
            Num = ShiftTenInt(SecondBase, Buffer);
        else {
            i = 0;
            int numeral = Buffer;
            while (numeral > 0) {
                i++;
                numeral /= 10;
            }
            char Numb[i + 1];
            int z = 0;
            while (Buffer > 0) {
                numeral = Buffer % 10;
                Numb[z] = (char) (numeral + 48);
                Buffer /= 10;
                z++;
            }
            Numb[i] = '\0';
            Num = realloc(Num, (i + 1));
            Num = Numb;
        }
    }
    return Num;
}

char *ShiftTen(int SecondBase, char *str) {
    char Buff[32];
    Buff[0] = '\0';
    char *Num = NULL;
    size_t NumberCharacters = 0;
    int NewNum = atoi(str);
    int i = 0;
    size_t BestInp = 0;
    while (NewNum >= SecondBase) {
        if (NumberCharacters >= BestInp) {
            BestInp += 32;
            Num = realloc(Num, BestInp);
            strcat(Num, Buff);
            i = 0;
        }
        Buff[i] = Numbers[NewNum % SecondBase];
        NewNum /= SecondBase;
        NumberCharacters++;
        i++;
    }
    Buff[i] = Numbers[NewNum];
    strcat(Num, Buff);
    return Num;
}

char *ShiftTenInt(int SecondBase, int Number) {
    char *Num = NULL;
    char Buff[32];
    Buff[0] = '\0';
    int NumberCharacters = 0;
    size_t BestInp = 0;
    int i = 0;
    int inp = 0;
    while (Number >= SecondBase) {
        if (NumberCharacters >= BestInp) {
            BestInp += 32;
            Num = realloc(Num, BestInp);
            strcat(Num, Buff);
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
    strcat(Num, Buff);
    return Num;
}