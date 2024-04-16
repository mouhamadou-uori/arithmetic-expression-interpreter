#include "stdInterpreter.h"
#include <stdlib.h>
#include <stdio.h>

char calu;
int errorGlobal = 0;       // variables global pour renforcer la detection des erreurs dans les differentes fonction de non-terminaux 
int errorExpression = 0;   // etant donne qu'on utilise -1 pour detecter les erreurs or -1 peut bel et bien etre la valeur trouvee par la fonction sans erreur
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
        int temp;
        while (calu != '=')
        {
            expressionValue = recognizeExpression();
            if (errorGlobal == 1)
                break;

        }
        temp = clearBuffer();
        if ((errorGlobal == 1) || temp != 0) // temp va nous aider a nous debarasser de tout ce qui est apres le egale et en meme temp nous indique si y a quelque chose apres = pour detecter une erreur
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

void readCharacter() // fonction de « lecture améliorée »
{ // fonction de lecture ameliore utilisant des getchar afin d'obtenir un caractere non blanc depuis le buffer (le tampon)
    do
    {
        calu = getchar();
    } while (calu == ' ' || calu == '\n' || calu == '\t');
}

int clearBuffer()
{ // cette fonction sert a vider le buffer apres detection d'erreur pour passer a la prochaine expression elle sert aussi a voir si il y a quelaue chose apres le egale de chaque expression
    char temp;
    int retour = 0;
    do
    {
        temp = getchar();
        if (temp != ' ' && temp != '\t' && temp != '\n') // vu qu'on appele cette fonction apres avoir rencontre egale si temp est different de l'un de ces caracteres
        {                                               // cela voudrait dire qu'il y a quelque(s) charactere(s) non blanc apres egale et donc cela invalide l'expression
            retour = -1;
        }
    } while (temp != '\n');
    return retour;
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
    char nombre[100] = ""; // variable dans laquelle on mettra les reels un a un avant de les convertir en double
    int curseurNombre = 0;
    char chiffre;
    int hasComma = 0; // variable qui nous servira a detecter les erreurs notement avec les nombre qui ont plus d'un virgule
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

char recognizeDigit() // fonction per;ettant de reconnaitre les terminaux chiffres
{
    return ((calu >= '0' && calu <= '9')) ? calu : 0;
}

char recognizeDot()
{
    return (calu == '.') ? calu : 0;
}

char recognizeAdditiveOperator() // fonction per;ettant de reconnaitre les terminaux 'operateur-additif'
{
    return (calu == '+' || calu == '-') ? calu : 0;
}

char recognizeMultiplicativeOperator()   // fonction per;ettant de reconnaitre les terminaux 'operateur-multiplicatif'
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