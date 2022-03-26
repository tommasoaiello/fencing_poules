#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>

typedef struct classifica_s{
    int indice;
    struct classifica_s *left, *right;
}classifica;

typedef struct list_of_players_s{
    char name[25];
    int ranking;
    int victories;
    int scored;
    int plusminus;
}list_of_players;

typedef struct girone_s{
    int numberOfFencers;
    int *indexes;
}girone;

int numberOfPlayers;
list_of_players* fencers;
int** poule;
classifica* radice;
classifica* classifica_iniziale;
girone** lista_gironi;
int pos=1;
int gironida7=0;
int gironida6=0;

void printList(){
    int i;
    printf("Fencers list:\n");
    for(i=0;i<numberOfPlayers-1;i++){
        printf("%s , ", fencers[i].name);
    }
    printf("%s\n", fencers[numberOfPlayers-1].name);

}

int compare(int index1, int index2){
    list_of_players fencer1,fencer2;
    fencer1= fencers[index1];
    fencer2= fencers[index2];
    if(fencer1.victories > fencer2.victories)
        return 1;
    else if(fencer1.victories == fencer2.victories && fencer1.plusminus > fencer2.plusminus)
        return 1;
    else if(fencer1.plusminus == fencer2.plusminus && fencer1.scored >= fencer2.scored)
        return 1;
    else
        return 0;
}




classifica* newFencer(int indice){
    classifica* temp= (classifica*) malloc(sizeof(classifica));
    temp->indice=indice;
    temp->left= temp->right= NULL;
    return temp;
}

classifica* insertNewFencer(classifica* root, int indice){
    if(root==NULL)
        return newFencer(indice);
    if(compare(indice,root->indice))
        root->left = insertNewFencer(root->left,indice);
    else if(compare(root->indice,indice))
        root->right = insertNewFencer(root->right,indice);

    return root;
}

void print_fencer(int i){
    printf("%s : VICTORIES %d , SCORED %d , +- %d\n",fencers[i].name, fencers[i].victories , fencers[i].scored, fencers[i].plusminus);
}

void in_order_walk(classifica* root){
    if(root!= NULL){
        in_order_walk(root->left);
        printf("%d ", pos);
        print_fencer(root->indice);
        pos++;
        in_order_walk(root->right);
    }
    return;
}

void calcResults(){
    int i,j;
    printf("++++++++++++++++++++++++RESULTS+++++++++++++++++++++++\n");
    for(i=0; i<numberOfPlayers; i++) {
        for (j = 0; j < numberOfPlayers; j++) {
            if (poule[i][j] == 5)
                fencers[i].victories++;
            fencers[i].scored= fencers[i].scored + poule[i][j];
            fencers[i].plusminus= fencers[i].plusminus + poule[j][i];
        }
        fencers[i].plusminus= fencers[i].scored - fencers[i].plusminus;
    }
    for(i=0; i< numberOfPlayers; i++){
        radice = insertNewFencer(radice,i);
    }
    in_order_walk(radice);
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

//needs to be completed
void calc_gironi(int numberOfPlayers){
    int tmp= numberOfPlayers;
    int i;
    if(tmp%3==0)
        gironida7 = tmp/3;

    //else da completare
    lista_gironi = malloc( tmp * (sizeof (girone*)));
    for(i=0; i<tmp; i++){
        lista_gironi[i]= malloc(sizeof (girone));
        lista_gironi[i]->numberOfFencers=7;
        lista_gironi[i]->indexes=NULL;
    }
}







int main(){
    char command[100];
    int i,j;
    char sep;


    /*GETS THE NUMBER OF FENCERS*/
    if(fgets(command,25,stdin)!=NULL){
        sscanf(command, "%d", &numberOfPlayers);
        fencers= malloc(numberOfPlayers* sizeof(list_of_players));
    }

    /*GETS THE NAME OF THE FENCERS*/
    for(i=0; i<numberOfPlayers; i++){
        if(fgets(command,25,stdin)!=NULL){
            fencers[i].ranking = 0;
            fencers[i].victories = 0;
            fencers[i].scored = 0;
            fencers[i].plusminus = 0;
            for(j=0;j < (strlen(command)-1);j++){
                fencers[i].name[j] = command[j];
            }
        }
    }

    /*INITIALIZES THE CLASSIFICA INIZIALE*/
    for(i=0; i< numberOfPlayers;i++){
        classifica_iniziale=insertNewFencer(classifica_iniziale,i);
    }

    /*CREATES THE POOLES*/
    calc_gironi(numberOfPlayers);


    /*INITIALIZES THE POULE*/
    poule= malloc((numberOfPlayers)*sizeof(int*));
    for(i=0;i<numberOfPlayers;i++){
        poule[i]= malloc((numberOfPlayers)* sizeof(int));
    }

    /*GETS THE RESULT OF THE POULE*/
    while(!feof(stdin)){
        for(i=0;i<numberOfPlayers;i++){
            for(j=0; j<numberOfPlayers;j++){
                scanf("%d%c", &poule[i][j], &sep);
            }
        }
    }





    printf("Fencers attending the competition: %d\n", numberOfPlayers);

    printList();

    calcResults();


    //need to do the free of all
    return 0;
}
