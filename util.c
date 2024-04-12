#include "stdInterpreter.h"
#include <stdlib.h>

char calu;

void interpreter(){ //Fonction global
    int status;
    do
    {
        printf("A vous : ");
        status = analizerAndExtractor();
    } while (status != 1);
    printf("Au revoir...\n");
}

int analizerAndExtractor(){ //fonction permettant dans un premier temps d'analyser une expression puis d'extraire la valeur celle ci si elle est correct
    readCharacter();
    if(calu == '.')
        return 1;
    else
    {
        int analysisStatus = 1;
        while (calu != '='){
            if ((analysisStatus = secondRecognizeExpression()) != -1)
                break;

            //readCharacter(); // cette ligne va mettre un caractere encore non traite dans calu
        }
        if (analysisStatus == -1)
        {
            analysisStatus = 1;
            printf("La syntaxe de l'expression est erronee");
        }else
        {
            printf("valeur=%d\n", analysisStatus);
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
int isOnlyTerm;
int termOfExpression = 0;
char signOfExpression;
int expressionOfExpression;
int recognizeExpression(){
    int localTermOfExpression = termOfExpression;
    if ((termOfExpression = recognizeTerm()) != -1 && isOnlyTerm == 1)
    {
        return termOfExpression;
    }else if ((signOfExpression = recognizeAdditiveOperator()) != 0)
    {
        termOfExpression = localTermOfExpression;
        isOnlyTerm = 0;
        return termOfExpression;
    }else if (isOnlyTerm == 1)
    {
        return -1;
    }
    int terme = termOfExpression;
    if (signOfExpression == '+')
    {
        return terme + recognizeExpression();
    }else
    {
        return terme - recognizeExpression();
    }
 
     
}

int secondRecognizeExpression(){ //fonction permettant dans un premier temps d'analyser une expression puis d'extraire la valeur celle ci si elle est correct
    int term;
    char sign;
    int expression;
    if ((term = secondRecognizeTerm()) != -1)
    {
        printf("term = %d\n", term);
        //readCharacter();
        if ((sign = recognizeAdditiveOperator()) != 0)
        {
            //printf("signe = %c\n", sign);
            readCharacter();
            if (sign == '+')
            {
                if ((expression = secondRecognizeExpression()) != -1)
                {
                    //return (term + expression);
                    printf("la valeur de votre expression est %d\n", (term + expression));
                }else
                {
                    return -1;
                }
            }else
            {
                if ((expression = secondRecognizeExpression()) != -1)
                {
                    return (term - expression);
                }else
                {
                    return -1;
                }
            }
        }else
        {
            //printf("signe = %c\n", sign);
            return term;
        }
        
    }else
    {
        return -1;
    }

}

int facteurOfTerm = 0;
char signOfFactor;
int termOfTerm;
int secondRecognizeTerm(){ //fonction permettant dans un premier temps d'analyser une expression puis d'extraire la valeur celle ci si elle est correct
    int facteur;
    char sign;
    int term;
    if ((facteur = recognizeFactor()) != -1)
    {
        //readCharacter();
        if ((sign = recognizeMultiplicativeOperator()) != 0)
        {
            readCharacter();
            if (sign == '*')
            {
                if ((term = secondRecognizeTerm()) != -1)
                {
                    return (facteur * term);
                }else
                {
                    return -1;
                }
                
            }else
            {
                if ((term = secondRecognizeTerm()) != -1)
                {
                    return (facteur / term);
                }else
                {
                    return -1;
                }
            }
        }else{
            return facteur;
        }
    }else
    {
        return -1;
    }
    
}

int recognizeTerm(){
    
}

int numberOfFactor;
int recognizeFactor(){
    int nombre;
    int expression;
    if ((numberOfFactor = recognizeNumber()) != -1)
    {
        return numberOfFactor;
    }else if (recognizeParenthese() != 0)
    {
       readCharacter();
       expression = secondRecognizeExpression();
    }
    
    
}



int recognizeNumber(){
    char nombre[50] = "";
    int curseurNombre = 0;
    char chiffre;
    while ((chiffre = recognizeDigit()) != 0)
    {
        nombre[curseurNombre] = chiffre;
        curseurNombre++;
        readCharacter();
    }
    if (curseurNombre == 0)
    {
        return -1;
    }else
    {
        return atoi(nombre);
    }   
}
/* void resetNombre(){
    for (int i = 0; i < 50; i++)
    {
        nombre[i] = "\0";
    }
    curseurNombre = 0;
}
 */
char recognizeDigit(){
    return (calu >= '0' && calu <= '9') ? calu : 0;
}
char recognizeAdditiveOperator(){
    //return (calu == '+' || calu == '-') ? calu : 0;
    if (calu == '+' || calu == '-')
    {
        return calu;
    }else
    {
        return 0;
    }
  
}
char recognizeMultiplicativeOperator(){
    return (calu == '*' || calu == '/') ? calu : 0;
}
char recognizeParenthese(){
    return (calu == '(' || calu == ')') ? calu : 0;
}
