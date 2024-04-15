#include "stdInterpreter.h"
#include <stdlib.h>

char calu;
int errorGlobal = 0;       // variables pour renforcer la detection des erreurs dans les differentes fonction de non-terminaux
int errorExpression = 0;
int errorTerm = 0;
int errorFactor = 0;

void interpreter()
{ // Fonction global
    int status;
    do
    {
        printf("A vous : ");
        status = analizerAndExtractor();
    } while (status != 1);
    printf("Au revoir...\n");
}

int analizerAndExtractor()
{ // fonction permettant dans un premier temps d'analyser une expression puis d'extraire la valeur si celle ci est correct
    readCharacter();
    if (calu == '.')
        return 1;
    else if (calu == '=')
    {
        printf("La syntaxe de l'expression est erronee\n");
        clearBuffer();
        return 0;
    }
    else
    {
        double expressionValue = 1.0;
        while (calu != '=')
        {
            expressionValue = recognizeExpression();
            if (errorGlobal == 1)
                break;

            // readCharacter(); // cette ligne va mettre un caractere encore non traite dans calu
        }
        if ((errorGlobal == 1) || clearBuffer() != 0) // clearBuffer va nous aider a nous debarasser de tout ce qui est apres le egale et en meme temp mous indique si y a quelque chose apres = pour detecter une erreur
        {
            errorGlobal = 0;
            errorExpression = 0;
            errorTerm = 0;
            errorFactor = 0;
            printf("La syntaxe de l'expression est erronee\n");
        }
        else
        {
            printf("la syntaxe de l'expression est correcte\n");
            printf("sa valeur est %g\n", expressionValue);
        }
        return 0;
    }
}

void readCharacter()
{ // fonction de lecture ameliore utilisant des getchar afin d'obtenir un caractere non blanc depuis le buffer (le tampon)
    do
    {
        calu = getchar();
    } while (calu == ' ' || calu == '\n' || calu == '\t');
}

int clearBuffer()
{
    char temp;
    do
    {
        temp = getchar();
        if (temp != ' ' && temp != '\t' && temp != '\n')
        {
            return -1;
        }
    } while (temp != '\n');
    return 0;
}

double recognizeExpression()
{ // fonction permettant de reconnaitre une expression et d'extraire sa valeur
    double term;
    char sign;
    double expression;
    if ((term = recognizeTerm()) != -1 || errorExpression != 1)
    {
        if ((sign = recognizeAdditiveOperator()) != 0)
        {
            readCharacter(); // fonction de « lecture améliorée »
            if (recognizeAdditiveOperator() != 0)
            {
                errorGlobal = 1;
                errorExpression = 1;
                return -1;
            }

            if (sign == '+')
            {
                if ((expression = recognizeExpression()) != -1 || errorExpression != 1)
                {
                    return (term + expression);
                }
                else
                {
                    errorGlobal = 1;
                    return -1;
                }
            }
            else
            {
                if ((expression = recognizeExpression()) != -1 || errorExpression != 1)
                {
                    return (term - expression);
                }
                else
                {
                    errorGlobal = 1;
                    return -1;
                }
            }
        }
        else
        {
            return term;
        }
    }
    else
    {
        errorGlobal = 1;
        return -1;
    }
}

double recognizeTerm()
{ // fonction permettant dans un premier temps d'analyser un term puis d'extraire la valeur si celle ci est correct
    double facteur;
    char sign;
    double term;
    if ((facteur = recognizeFactor()) != -1 || errorTerm != 1)
    {
        // readCharacter();
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
                if ((term = recognizeTerm()) != -1 || errorTerm != 1)
                {
                    return (facteur * term);
                }
                else
                {
                    errorExpression = 1;
                    return -1;
                }
            }
            else
            {
                if ((term = recognizeTerm()) != -1 || errorTerm != 1)
                {
                    return (facteur / term);
                }
                else
                {
                    errorExpression = 1;
                    return -1;
                }
            }
        }
        else
        {
            return facteur;
        }
    }
    else
    {
        errorExpression = 1; // booleen egale a 1 pour dire oui y a erreur
        return -1;
    }
}

double recognizeFactor()
{ // fonction permettant dans un premier temps d'analyser un facteur puis d'extraire la valeur si celle ci est correct
    double nombre;
    double expression;
    if ((nombre = recognizeNumber()) != -1 || errorFactor != 1)
    {
        return nombre;
    }
    else if (recognizeParentheseOpen() != 0)
    {
        readCharacter();
        expression = recognizeExpression();
        if (recognizeParentheseClose() != 0)
        {
            readCharacter();
            return expression;
        }
        else
        {
            errorTerm = 1;
            return -1;
        }
    }
    else
    {
        errorTerm = 1;
        return -1;
    }
}

double recognizeNumber()
{ // fonction pour reconnaitre un nombre
    char nombre[50] = "";
    int curseurNombre = 0;
    char chiffre;
    int hasComma = 0;
    while (((chiffre = recognizeDigit()) != 0) || (curseurNombre != 0 && (chiffre = recognizeDot()) != 0) || (curseurNombre == 0 && (chiffre = recognizeAdditiveOperator()) != 0))
    {
        if (chiffre == '.')
        {
            if (hasComma == 0)
            {
                hasComma = 1;
            }else{
                errorFactor = 1;
                return -1;
            }
            
        }
        nombre[curseurNombre] = chiffre;
        curseurNombre++;
        readCharacter();
    }
    if (curseurNombre == 0)
    {
        errorFactor = 1;
        return -1;
    }
    else
    {
        return strtod(nombre, NULL); // strtod convertie une chaine de caractere en double
    }
}

char recognizeDigit()
{
    return ((calu >= '0' && calu <= '9') || calu == '.') ? calu : 0;
}
char recognizeDot()
{
    return (calu == '.') ? calu : 0;
}
char recognizeAdditiveOperator()
{
    return (calu == '+' || calu == '-') ? calu : 0;
}
char recognizeMultiplicativeOperator()
{
    return (calu == '*' || calu == '/') ? calu : 0;
}
char recognizeParenthese()
{
    return (calu == '(' || calu == ')') ? calu : 0;
}
char recognizeParentheseOpen()
{
    return (calu == '(') ? calu : 0;
}
char recognizeParentheseClose()
{
    return (calu == ')') ? calu : 0;
}