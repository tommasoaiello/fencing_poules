#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>

typedef struct list_of_players_s{
    char name[25];
    int ranking;
}list_of_players;

int main(){
    char command[100];
    int victories=0, scored=0, received=0, plusminus=0;
    int numberOfPlayers;
    int i,j;
    char sep;
    list_of_players* fencers;
    int** poule;

    if(fgets(command,25,stdin)!=NULL){
        sscanf(command, "%d", &numberOfPlayers);
        fencers= malloc(numberOfPlayers* sizeof(list_of_players));
    }

    for(i=0; i<numberOfPlayers; i++){
        if(fgets(command,25,stdin)!=NULL){
            fencers[i].ranking = 0;
            for(j=0;j < (strlen(command)-1);j++){
                fencers[i].name[j] = command[j];
            }
        }
    }

    poule= malloc(numberOfPlayers*sizeof(int*));
    for(i=0;i<numberOfPlayers;i++){
        poule[i]= malloc(numberOfPlayers* sizeof(int));
    }

    for(i=0;i<numberOfPlayers;i++){
        for(j=0; j<numberOfPlayers;j++){
            poule[i][j]= i+j;
        }
    }

    while(!feof(stdin)){
        for(i=0;i<numberOfPlayers;i++){
            for(j=0; j<numberOfPlayers;j++){
                scanf("%d%c", &poule[i][j], &sep);
            }
        }
    }



    printf("Fencers attending the competition: %d\n", numberOfPlayers);
    printf("Fencers list:\n");
    for(i=0;i<numberOfPlayers;i++){
        printf("%s\n", fencers[i].name);
    }

    for(i=0;i<numberOfPlayers;i++){
        printf("%s: ", fencers[i].name);
        for(j=0; j<numberOfPlayers;j++){
            printf("%d ", poule[i][j]);
        }
        printf("\n");
    }


    return 0;
}