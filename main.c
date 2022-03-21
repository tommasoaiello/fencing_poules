#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>

typedef struct list_of_players_s{
    char name[25];
    int ranking;
    int victories;
    int scored;
    int plusminus;
}list_of_players;

int numberOfPlayers;
list_of_players* fencers;
int** poule;

void printList(){
    int i;
    printf("Fencers list:\n");
    for(i=0;i<numberOfPlayers;i++){
        printf("%s , ", fencers[i].name);
    }
    printf("\n");
}


void calcResults(){
    int i,j;
    printf("++++++++++++++++++++++++RESULTS+++++++++++++++++++++++\n");
    for(i=0; i<numberOfPlayers; i++) {
        printf("%s: ", fencers[i].name);
        for (j = 0; j < numberOfPlayers; j++) {
            if (poule[i][j] == 5)
                fencers[i].victories++;
            fencers[i].scored= fencers[i].scored + poule[i][j];
            fencers[i].plusminus= fencers[i].plusminus + poule[j][i];
        }
        fencers[i].plusminus= fencers[i].scored - fencers[i].plusminus;
        printf("VICTORIES %d , SCORED %d , +- %d\n", fencers[i].victories , fencers[i].scored, fencers[i].plusminus);
    }
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
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

    return 0;
}