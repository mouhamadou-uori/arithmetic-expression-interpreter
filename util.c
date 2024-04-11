#include "stdInterpreter.h"
#include <stdlib.h>

char calu;
char nombre[100] = {""};
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
        int analysisStatus = 1;
        if (calu == '=')
        {
            analysisStatus = -1;
        }
        
        while (calu != '='){
            if ((analysisStatus = recognizeExpression()) == -1)
                break;
            readCharacter(); // cette ligne va mettre un caractere encore non traite dans calu
        }
        if (analysisStatus == -1)
        {
            printf("La syntaxe de l'expression est erronee\n");
            analysisStatus = 1;
        }
        clearBuffer();
        return 0;
    }
    
} 
void readCharacter(){ //fonction de lecture ameliore utilisant des getchar afin d'obtenir un caractere non blanc depuis le buffer (le tampon)
    do
    {
        calu = getchar();
    } while (calu == ' ' || calu == '\n' || calu == '\t');
}

void clearBuffer(){
    char temp;
    do
    {
        temp = getchar();
    } while (temp != '\n');
}


// recognize
int termOfExpression = 0; // 0 juste comme ca parcequ'on en a besoin, non plutot parcequ'on magouille jusqu'au resultat :)
char additiveOperatorOfExpression = 'r'; //r pour random parcequ'on en a pas vraiment besoin au debut mais il faut l'initialiser
int expression;
int isOnlyExpression = 1;
int termOfExpressionTemp = 0;
char signTemp;
int valeur = -1;
int recognizeExpression(){
    
    termOfExpressionTemp = termOfExpression;
    if (((termOfExpression = recognizeTerm()) != -1) && (isOnlyExpression == 1))
    {
        termOfExpressionTemp = termOfExpression;
        return termOfExpression;
        
    }else if ((additiveOperatorOfExpression = recognizeAdditiveOperator()) != 0)
    {
        if (termOfExpressionTemp != 0)
        {
            isOnlyExpression = 0;
        }
        signTemp = additiveOperatorOfExpression;
        termOfExpression = termOfExpressionTemp;
        strcpy(nombre, "");
        return termOfExpression;
    }else if(isOnlyExpression == 1)
    {
        return -1;
    }
    isOnlyExpression = 1;
    strcpy(nombre, "");
    int localTermOfExpressionTemp = termOfExpressionTemp;
    termOfExpressionTemp = 0;
    if (signTemp == '+')
    {
        if ((expression = recognizeExpression()) != -1)
        {
            printf("termOfExpressionTemp=%d\n", localTermOfExpressionTemp);
            printf("expression=%d\n", expression);
            valeur = localTermOfExpressionTemp + expression;
            printf("valeur=%d\n", valeur);
        }else
        {
            return -1;
        }
    }else
    {
        if ((expression = recognizeExpression()) != -1)
        {
            printf("termOfExpressionTemp=%d\n", termOfExpressionTemp);
            printf("expression=%d\n", expression);
            valeur = localTermOfExpressionTemp - expression;
            printf("valeur=%d\n", valeur);
        }else
        {
            return -1;
        }
    }
    return valeur;
}

int factorOfTerm = 0; // oui je magouilles
char multiplicativeOperatorOfTerm = 'r'; // tu magouilles, nous magouillons
int term;
int isOnlyTerm = 1;
char signTemp;
int factorOfTermTemp = 1;

int recognizeTerm(){
    int valeur;
    
    
    factorOfTermTemp = factorOfTerm;
    if (((factorOfTerm = recognizeFactor()) != -1) && (isOnlyTerm == 1))
    {
        factorOfTermTemp = factorOfTerm;
        return factorOfTerm;
        
    }else if ((multiplicativeOperatorOfTerm = recognizeMultiplicativeOperator()) != 0)
    {
        if (factorOfTermTemp != 1)
        {
            isOnlyTerm = 0;
        }
        
        strcpy(nombre, "");
        factorOfTerm = factorOfTermTemp;
        signTemp = multiplicativeOperatorOfTerm;
        return factorOfTerm;
    }
    else if (isOnlyTerm == 1)
    {
        return -1;
    }
    isOnlyTerm = 1;
    strcpy(nombre, "");
    int localFactorOfTermTemp = factorOfTermTemp;
    factorOfTermTemp = 1;
    if (signTemp == '*')
    {
        if ((term = recognizeTerm()) != -1)
        {
            printf("localFactorOfTermTemp=%d\n", localFactorOfTermTemp);
            printf("term=%d\n", term);
            valeur = localFactorOfTermTemp * term;
            printf("valeur=%d\n", valeur);
        }else
        {
            return -1;
        }
    }else
    {
        if ((term = recognizeTerm()) != -1)
        {
            printf("localFactorOfTermTemp=%d\n", localFactorOfTermTemp);
            printf("term=%d\n", term);
            valeur = localFactorOfTermTemp / term;
            printf("valeur=%d\n", valeur);
        }else
        {
            return -1;
        }
    }
    return valeur;
}

int numberOfFactor = 0;
int tempFactor;
int expressionOfFactor;
int isNombre = 1;

int recognizeFactor(){
    if ((tempFactor = recognizeNumber()) != -1 && isNombre == 1)
    {
        numberOfFactor = tempFactor;
        return numberOfFactor;
    }else if (recognizeParenthese() != 0)
    {
        strcpy(nombre, "");
        isNombre = 0;
        return 0;
    }else if (recognizeAdditiveOperator() != 0 || recognizeMultiplicativeOperator() != 0)
    {
        return -1;
    }else if ((calu >= 'A' && calu <= 'Z') || (calu >= 'a' && calu <= 'z'))
    {
        return -1;
    }
    else if ((expressionOfFactor = recognizeExpression()) != -1)
    {
        return expressionOfFactor;
    }else
    {
        return -1;
    }
   
    
}
char chiffre[1];
int recognizeNumber(){
    
    if ((chiffre[0] = recognizeDigit()) != 0)
    {
        
        strcat(nombre, chiffre);
        return atoi(nombre);
    }else
    {
        return -1;
    }
}
char recognizeDigit(){
    if (calu < '0' || calu > '9') return 0; // le 0 signifie juste une erreur ici
    return calu;
}
signed char recognizeAdditiveOperator(){
    if (calu != '+' && calu != '-') return 0;
    return calu;
}
signed char recognizeMultiplicativeOperator(){
    if (calu != '*' && calu != '/') return 0;
    return calu;
    
}
char recognizeParenthese(){
    if (calu != '(' && calu != ')') return 0;
    return calu;
}
void resetTab(int *tab){
    for (int i = 0; i < 3; i++)
    {
        tab[i] = 0;
    }
    
}