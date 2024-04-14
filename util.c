#include "stdInterpreter.h"
#include <stdlib.h>

char calu;
int errorGlobal = 0;
int errorExpression = 0;
int errorTerm = 0;
int errorFactor = 0;

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
    else if (calu == '=')
    {
        printf("La syntaxe de l'expression est erronee\n");
        clearBuffer();
        return 0;
    }else
    {
        int analysisStatus = 1;
        while (calu != '='){
            analysisStatus = secondRecognizeExpression();
            if (errorGlobal == 1)
                break;

            //readCharacter(); // cette ligne va mettre un caractere encore non traite dans calu
        }
        if (errorGlobal == 1)
        {
            errorGlobal = 0;
            errorExpression = 0;
            errorTerm = 0;
            errorFactor = 0;
            printf("La syntaxe de l'expression est erronee\n");
        }else
        {
            printf("la syntaxe de l'expression est correcte\n");
            printf("sa valeur est %d\n", analysisStatus);
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


int secondRecognizeExpression(){ //fonction permettant dans un premier temps d'analyser une expression puis d'extraire la valeur celle ci si elle est correct
    int term;
    char sign;
    int expression;
    if ((term = secondRecognizeTerm()) != -1 || errorExpression != 1)
    {
        if ((sign = recognizeAdditiveOperator()) != 0)
        {
            readCharacter();
            if (recognizeAdditiveOperator() != 0)
            {
                errorGlobal = 1;
                errorExpression = 1;
                return -1;
            }
            
            if (sign == '+')
            {
                if ((expression = secondRecognizeExpression()) != -1 || errorExpression != 1)
                {
                    return (term + expression);
                }else
                {
                    errorGlobal = 1;
                    return -1;
                }
            }else
            {
                if ((expression = secondRecognizeExpression()) != -1 || errorExpression != 1)
                {
                    return (term - expression);
                }else
                {
                    errorGlobal = 1;
                    return -1;
                }
            }
        }else
        {
            return term;
        }
        
    }else
    {
        errorGlobal = 1;
        return -1;
    }

}


int secondRecognizeTerm(){ //fonction permettant dans un premier temps d'analyser une expression puis d'extraire la valeur celle ci si elle est correct
    int facteur;
    char sign;
    int term;
    if ((facteur = recognizeFactor()) != -1 || errorTerm != 1)
    {
        //readCharacter();
        if ((sign = recognizeMultiplicativeOperator()) != 0)
        {
            readCharacter();
            if (recognizeMultiplicativeOperator() != 0)
            {
                errorExpression = 1;
                errorTerm = 1;
                return -1;
            }
            
            if (sign == '*')
            {
                if ((term = secondRecognizeTerm()) != -1 || errorTerm != 1)
                {
                    return (facteur * term);
                }else
                {
                    errorExpression = 1;
                    return -1;
                }
                
            }else
            {
                if ((term = secondRecognizeTerm()) != -1 || errorTerm != 1)
                {
                    return (facteur / term);
                }else
                {
                    errorExpression = 1;
                    return -1;
                }
            }
        }else{
            return facteur;
        }
    }else
    {
        errorExpression = 1;
        return -1;
    }
    
}

int recognizeFactor(){
    int nombre;
    int expression;
    if ((nombre = recognizeNumber()) != -1 || errorFactor != 1)
    {
        return nombre;
    }else if (recognizeParentheseOpen() != 0)
    {
       readCharacter();
       expression = secondRecognizeExpression();
       if (recognizeParentheseClose() != 0)
       {
            readCharacter();
            return expression;
       }else
       {
            errorTerm = 1;
            return -1;
       }
       
    }else
    {
        errorTerm = 1;
        return -1;
    }
    
    
    
}



int recognizeNumber(){
    char nombre[50] = "";
    int curseurNombre = 0;
    char chiffre;
    while (((chiffre = recognizeDigit()) != 0) || (curseurNombre == 0 && (chiffre = recognizeAdditiveOperator()) != 0))
    {
        nombre[curseurNombre] = chiffre;
        curseurNombre++;
        readCharacter();
    }
    if (curseurNombre == 0)
    {
        errorFactor = 1;
        return -1;
    }else
    {
        return atoi(nombre);
    }   
}

char recognizeDigit(){
    return (calu >= '0' && calu <= '9') ? calu : 0;
}
char recognizeAdditiveOperator(){
    return (calu == '+' || calu == '-') ? calu : 0;
  
}
char recognizeMultiplicativeOperator(){
    return (calu == '*' || calu == '/') ? calu : 0;
}
char recognizeParenthese(){
    return (calu == '(' || calu == ')') ? calu : 0;
}
char recognizeParentheseOpen(){
    return (calu == '(') ? calu : 0;
}
char recognizeParentheseClose(){
    return (calu == ')') ? calu : 0;
}

