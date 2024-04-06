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
    readCharacter();
    if(calu == '.')
        return 1;
    else
    {
        while (calu != '='){
            readCharacter(); // cette ligne va mettre un caractere encore non traite dans calu
        }
        cleanAfterEqual();
        return 0;
    }
    
} 
void readCharacter(){ //fonction de lecture ameliore utilisant des getchar afin d'obtenir un caractere non blanc depuis le buffer (le tampon)
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


// recognize

void recognizeExpression(){}
void recognizeTerm(){}
void recognizeFactor(){}
void recognizeNumber(){}
void recognizeDigit(){}
void recognizeAdditiveOperator(){}
void recognizeMultiplicativeOperator(){}