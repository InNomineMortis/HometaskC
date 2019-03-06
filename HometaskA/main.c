#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* Shift(int FirstBase, int SecondBase, char*);
char* GetLine();

int main() {
    int P; // Input number system
    int Q; // Output number system
    scanf("%d%d",&P,&Q);
    printf("%s", Shift(P, Q, GetLine()));
    return 0;
}
char* GetLine(){
    const size_t Length = 32;
    const size_t Incr = 32;
    char Buffer[Length];
    char* FinalInp = NULL;
    size_t NumberCharacters = 0;
    size_t CurrentInp = 0;
    size_t BestInp = 0;

    while(fgets(Buffer, Length, stdin)){
        NumberCharacters = strlen(Buffer);
        CurrentInp += NumberCharacters;

        if (CurrentInp >= BestInp){                 // Reallocating memory if needed
            BestInp += Incr;
            FinalInp = realloc(FinalInp, BestInp);
            strcat(FinalInp, Buffer);
        }

        if (Buffer[NumberCharacters - 1] == '\n')
            break;

        if (ferror(stdin)){
            if (FinalInp)
                free(FinalInp);
            printf("[error]\n");
            exit(0);                                // In case there is Input Error, we stop program with exit + std::Error
        }

    }

    return FinalInp;
}
char* Shift(int FirstBase, int SecondBase, char* str){
    char* NewStr = NULL;
    const size_t Length = strlen(str);
    char Buffer[Length];
    const size_t Incr = 32;
    size_t CurrentLen = 0;
    if (FirstBase == 10){
        size_t i = 0;
        while(((int)str) >= SecondBase){
            str = ((int)str)/SecondBase;
            Buffer[i] = ((int)str)%SecondBase;
            i++;
            CurrentLen += Incr;
            NewStr = realloc(NewStr, CurrentLen);
            strcat(NewStr, Buffer);
            }
    }
    return NewStr;
}