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

void recognizeExpression(){
    char *term, signe, expression;
}
void recognizeTerm(){
    char *facteur, signe, *term;
}
void recognizeFactor(){
    char *number, expression;
    int hasParentheseOAndC;
}
void recognizeNumber(){}
char recognizeDigit(){
    return (calu >= '0' && calu <= '9') ? calu : (char)0;
}
char recognizeAdditiveOperator(){
    return (calu == '+' || calu == '-') ? calu : (char)0;
}
char recognizeMultiplicativeOperator(){
    return (calu == '*' || calu == '/') ? calu : (char)0;
    
}
char recognizeParenthese(){
    return (calu == '(' || calu == ')') ? calu : (char)0;
}