

char calu;

void interpreter(){ //Fonction global

}

void analizerAndExtractor(){ //fonction permettant dans un premier temps d'analyser une expression puis d'extraire la valeur celle ci si elle est correct

} 
void readExpression(){ //fonction de lecture ameliore utilisant des getchar afin d'obtenir un caractere non blanc
    do
    {
        calu = getchar();
    } while (calu == ' ' || calu == '\n' || calu == '\t');
    printf("%c", calu);
}
