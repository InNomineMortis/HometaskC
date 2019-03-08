#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *Shift(int FirstBase, int SecondBase, char *);

char *GetLine();

char *ShiftTen(int SecondBase, char *str);

char Numbers[36] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main() {
    int P; // Input number system
    int Q; // Output number system
    scanf("%d%d", &P, &Q);
    char *str = Shift(P, Q, GetLine());
    for (int i = (int) (strlen(str) - 1); i >= 0; i--)
        printf("%c", str[i]);
    return 0;
}

char *GetLine() {
    const size_t Length = 32;
    const size_t Incr = 32;
    char Buffer[Length];
    char *FinalInp = NULL;
    size_t NumberCharacters = 0;
    size_t CurrentInp = 0;
    size_t BestInp = 0;

    while (fgets(Buffer, Length, stdin)) {
        NumberCharacters = strlen(Buffer);
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
        char Buffer[32];
        Buffer[0] = '\0';
        int NumberCharacters = 0;
        size_t BestInp = 0;
        int current = 0, j = 0;
        char *NewStr = NULL;
        for (size_t i = strlen(str) - 1; i > 0; i--) {
            if (NumberCharacters >= BestInp) {
                BestInp += 32;
                NewStr = realloc(NewStr, BestInp);
                strcat(NewStr, Buffer);
                j = 0;
            }
            current = (int) str[i] * (FirstBase ^ NumberCharacters);
            Buffer[j] += current;
            NumberCharacters++;
            j++;
        }
        strcat(NewStr, Buffer);
        Num = ShiftTen(SecondBase, Num);
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