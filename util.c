#include "stdInterpreter.h"

char calu;

void interpreter(){ //Fonction global
    int status;
    do
    {
        status = analizerAndExtractor();
    } while (status != 1);
    printf("Au revoir...\n");
}

int analizerAndExtractor(){ //fonction permettant dans un premier temps d'analyser une expression puis d'extraire la valeur celle ci si elle est correct
    printf("A vous : ");
    readCharactere();
    if(calu == '.')
        return 1;
    else
    {
        while (calu != '='){
            readCharactere(); // cette ligne va mettre un caractere encore non traite dans calu
            printf("%c", calu);
        }
        cleanAfterEqual();
        return 0;
    }
    
} 
void readCharactere(){ //fonction de lecture ameliore utilisant des getchar afin d'obtenir un caractere non blanc depuis le buffer (le tampon)
    do
    {
        calu = getchar();
    } while (calu == ' ' || calu == '\n' || calu == '\t');
}

void cleanAfterEqual(){
    char temp;
    do
    {
        temp = getchar();
    } while (temp != '\n');
}