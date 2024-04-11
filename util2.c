#include <stdio.h>

int recognizeExpression(int isOnlyTerm){
    int hasTerm = 1;
    int hasAdditiveOperator = 0;
    int hasExpression = 0;
    if (isOnlyTerm != 0)
    {
        if (hasTerm == 1 && hasAdditiveOperator == 0 && hasExpression == 0)
        {
            if (recognizeTerm() == 0)
            {
                return 0;
            }

        }
        if (hasTerm == 1 && hasAdditiveOperator == 1 && hasExpression == 0)
        {
            /* code */
        }
        if (hasTerm == 1 && hasAdditiveOperator == 1 && hasExpression == 1)
        {
            /* code */
        }
    }else
    {
        recognizeTerm();
    }
    
    
    
    
}