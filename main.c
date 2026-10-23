#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

enum{ NB_PARTICIPANTS = 100, NB_CONCOURS = 20, TAILLE_NOM = 30, TAILLE_INPUT = 80};

typedef struct{
    char nom[TAILLE_NOM];
    char prenom[TAILLE_NOM];
    int concours[NB_CONCOURS];
    int numero;
} Participant;

typedef char Concours[TAILLE_NOM];


//Peototype fct°

    //Utile

void Read(const char input[], char piece[], int num_elem);
int nbChiffres(int n);
int puissance(int base, int exposant);
void Actualiser_Classement(const Participant participants[], int concoursIndex, int classement[][NB_PARTICIPANTS]);
void Initialiser_Un(int tab[][NB_PARTICIPANTS], int dimensionX);
void Initialiser_Point_Concours(Participant participans[]);


    //Commandes

void Inscrire(Participant *participants, int *nb_participants, int nb_concours, int classement[][NB_PARTICIPANTS], int classementBilan[][NB_PARTICIPANTS], const char input[]);
void Afficher_participants(const Participant *participant, int nb_Participant);
void Creer(Concours *concours, int *nb_concours, int nb_participants, int classement[][NB_PARTICIPANTS], int classementBilan[][NB_PARTICIPANTS], const char input[]);
void Afficher_coucours(const Concours concours[], const Participant participants[], int nb_concours, int nb_participants);
void Gain(Participant *participants, int nb_concours, int nb_participants, int classement[][NB_PARTICIPANTS],const char input[]);
void Score(const Participant participants[], const Concours concours[], int nb_participants, const char input[]);
void Classement(const Participant participant[], const Concours concours[], int nb_participants, int nb_concours, const char input[]);
void Comparaison(const Participant participant[], const Concours concours[], int nb_participants, int nb_concours, const char input[]);
void Afficher_Classement(int classement[NB_CONCOURS][NB_PARTICIPANTS]);
void Bilan(const Participant participant[], const Concours concours[], int nb_participants, int nb_concours, int classement[][NB_PARTICIPANTS], int classementBilan[][NB_PARTICIPANTS], const char input[]);


int main(void){
    
    Concours concours[NB_CONCOURS];
    Participant participants[NB_PARTICIPANTS];
    Initialiser_Point_Concours(participants);

    int classement[NB_CONCOURS][NB_PARTICIPANTS];
    int classementBilan[NB_CONCOURS][NB_PARTICIPANTS];
    Initialiser_Un(classement, NB_CONCOURS);
    Initialiser_Un(classementBilan, NB_CONCOURS);

    int nbParticipants = 0;
    int nbConcours = 0;

    char input[TAILLE_INPUT];
    char cmd[TAILLE_NOM];

    int end = 0;

    while (!end)
    {
        
        fgets(input, sizeof(input), stdin);

        Read(input, cmd, 1);

        if(!strcmp(cmd, "INSCRIRE")){
            Inscrire(participants, &nbParticipants, nbConcours, classement, classementBilan, input);
        }
        else if(!strcmp(cmd, "PARTICIPANTS")){
            Afficher_participants(participants, nbParticipants);
        }
        else if(!strcmp(cmd, "CREER")){
            Creer(concours, &nbConcours, nbParticipants, classement, classementBilan, input);
        }
        else if(!strcmp(cmd, "CONCOURS")){
            Afficher_coucours(concours, participants, nbConcours, nbParticipants);
        }
        else if(!strcmp(cmd, "GAIN")){
            Gain(participants, nbConcours, nbParticipants, classement, input);
        }
        else if(!strcmp(cmd, "SCORES")){
            Score(participants, concours, nbParticipants, input);
        }
        else if(!strcmp(cmd, "CLASSEMENT")){
            Classement(participants, concours, nbParticipants, nbConcours, input);
        }
        else if(!strcmp(cmd, "COMPARAISON")){
            Comparaison(participants, concours, nbParticipants, nbConcours, input);
        }
        else if(!strcmp(cmd, "BILAN")){
            Bilan(participants, concours, nbParticipants, nbConcours, classement, classementBilan, input);
        }
        else if(!strcmp(cmd, "AC")){
            Afficher_Classement(classement);
        }
        else if(!strcmp(cmd, "AB")){
            Afficher_Classement(classementBilan);
        }
        else if(!strcmp(cmd, "EXIT")){
            ++end;
        }

    }
    
    
   
}


void Read(const char input[], char piece[], int num_elem){
    int count = 1;
    int index1 = 0;
    int index2 = 0;

    while (count <= num_elem && input[index1] != '\0' && input[index1] != '\n')
    {  
        if(count == num_elem && input[index1] != ' '){
            piece[index2] = input[index1];
            ++index2;
        }

        if(input[index1] == ' '){
            ++count;
        }
        ++index1;
    }
    piece[index2] = '\0';

}
int nbChiffres(int n)
{
    int compteur = 0;

    if (n == 0)
        return 1;

    while (n != 0)
    {
        n /= 10;
        compteur++;
    }

    return compteur;
}
int puissance(int base, int exposant) {
    int resultat = 1;
    for (int i = 0; i < exposant; i++) {
        resultat *= base; //
    }
    return resultat;
}
void Actualiser_Classement(const Participant participants[], int concoursIndex, int classement[][NB_PARTICIPANTS]){

    int nb_PC = 0;
    int PC[NB_PARTICIPANTS];

    for(int i = 0; i < NB_PARTICIPANTS; ++i){
        PC[i] = i;
    }

    

    // Tri de la liste d'index de participant en fct° de le score au concours (tri à bulles)
    int temp;
    int numPermut;
    do{
        numPermut = 0;
        for(int i = 0; i < NB_PARTICIPANTS - 1; ++i){
            if(participants[PC[i]].concours[concoursIndex] < participants[PC[i+1]].concours[concoursIndex]){
                temp = PC[i];
                PC[i] = PC[i+1];
                PC[i+1] = temp;
                ++numPermut;
            }
        }
    }while(numPermut);



    int ex = 0;
    int valeurPre = 0;
    for (int i = 0; i < NB_PARTICIPANTS; i++)
    {
        if(participants[PC[i]].concours[concoursIndex] == valeurPre){
            ++ex;
        }
        else{
            ex = 0;
        }

        classement[concoursIndex][PC[i]] = i + 1 - ex;

        valeurPre = participants[PC[i]].concours[concoursIndex];
    }
    
}
void Initialiser_Un(int tab[][NB_PARTICIPANTS], int dimensionX){

    for(int i = 0; i < dimensionX; ++i){
        for(int j = 0; j < NB_PARTICIPANTS; ++j){
            tab[i][j] = 1;
        }
    }
}
void Initialiser_Point_Concours(Participant participans[]){
    for(int i = 0; i < NB_PARTICIPANTS; ++i){
        for(int j = 0; j < NB_CONCOURS; j++){
            participans[i].concours[j] = 0;
        }
    }
}

//----------------------------Commandes------------------------------

void Inscrire(Participant *participants, int *nb_participants, int nb_concours, int classement[][NB_PARTICIPANTS], int classementBilan[][NB_PARTICIPANTS], const char input[]){

    char nom[TAILLE_NOM];
    char prenom[TAILLE_NOM];

    Read(input, nom, 2);
    Read(input, prenom, 3);

    int deja_presant = 0;
    for(int i = 0; i < NB_PARTICIPANTS; ++i){
        if(!strcmp(participants[i].nom, nom) && !strcmp(participants[i].prenom, prenom)){
            ++deja_presant;
        }
    }

    if(deja_presant){
        printf("Nom incorrect\n");
    }
    else{
        //enregiste nom et prenom du participant
        strcpy(participants[*nb_participants].nom, nom);
        strcpy(participants[*nb_participants].prenom, prenom);
        
        //instantie tout les scores des tournois du participant a zero
        for(int i = 0; i < NB_CONCOURS; ++i){
            participants[*nb_participants].concours[i] = 0;
        }

        participants[*nb_participants].numero = *nb_participants + 1;

        for(int i = 0; i < NB_CONCOURS; ++i){
            classementBilan[i][*nb_participants] = classement[i][*nb_participants];
        }
        ++*nb_participants;
        
        
        printf("Inscription enregistree (%d)\n", *nb_participants);
    }
    

}

void Afficher_participants(const Participant *participants, int nb_Participant){
    int nb_concours;
    if(nb_Participant){
        for(int i = 0; i < nb_Participant; ++i){

            //recupère le nb de concours effectuer par le participant a l'indice i
            nb_concours = 0;
            for(int j = 0; j < NB_CONCOURS; ++j){
                if(participants[i].concours[j] > 0){
                    ++nb_concours;
                }
            }

            printf("(%d) %s %s : %d concours\n", i+1, participants[i].nom, participants[i].prenom, nb_concours);
        } 
    }
    else{
        printf("Aucun participant inscrit\n");
    }

}

void Creer(Concours *concours, int *nb_concours, int nb_participants, int classement[][NB_PARTICIPANTS], int classementBilan[][NB_PARTICIPANTS], const char input[]){

    char nomConcours[TAILLE_NOM];

    Read(input, nomConcours, 2);

    int deja_presant = 0;
    for(int i = 0; i < *nb_concours; ++i){
        if(!strcmp(concours[i], nomConcours)){
            ++deja_presant;
        }
    }

    if(deja_presant){
        printf("Nom incorrect\n");
    }
    else{
        strcpy(concours[*nb_concours], nomConcours);

        ++*nb_concours;
        printf("Creation enregistree (%d)\n", *nb_concours);
    }
    


}

void Afficher_coucours(const Concours concours[], const Participant participants[], int nb_concours, int nb_participants){
    int nbP_concours;

    if(nb_concours){

        char pluriel[2];
        for(int i = 0; i < nb_concours; ++i){

            //recupère le nb de participant pour le concour a l'indice i
            nbP_concours = 0;
            for(int j = 0; j < nb_participants; ++j){
                if(participants[j].concours[i] > 0){
                    ++nbP_concours;
                }
            }

            if(nbP_concours > 1){
                strcpy(pluriel, "s");
            }
            else{
                strcpy(pluriel, "");
            }
            

            printf("(%d) %s : %d participant%s\n", i+1, concours[i], nbP_concours, pluriel);
        } 
    }
    else{
        printf("Aucun concours cree\n");
    }
}

void Gain(Participant *participants, int nb_concours, int nb_participants, int classement[][NB_PARTICIPANTS], const char input[]){
    
    char numP[nbChiffres(NB_PARTICIPANTS)];
    char numC[nbChiffres(NB_CONCOURS)];
    char nbrPoints[nbChiffres(puissance(2, sizeof(int) * 4) - 1)];

    Read(input, numP, 2);
    Read(input, numC, 3);
    Read(input, nbrPoints, 4);

    if(atoi(numP) > nb_participants || atoi(numP) < 0){
        printf("Participant incorrect\n");
    }
    else if(atoi(numC) > nb_concours || atoi(numC) < 0){
        printf("Concours incorrect\n");
    }
    else if(atoi(nbrPoints) <= 0){
        printf("Points incorrects\n");
    }
    else{
        participants[atoi(numP) - 1].concours[atoi(numC) - 1] += atoi(nbrPoints);
        Actualiser_Classement(participants, atoi(numC) - 1, classement);
        printf("Gain enregistre\n");
    }
}

void Score(const Participant participants[], const Concours concours[], int nb_participants, const char input[]){

    char numP[nbChiffres(NB_PARTICIPANTS)];
    Read(input, numP, 2);

    if(atoi(numP) > nb_participants || atoi(numP) <= 0){
        printf("Identifiant incorrect\n");
    }
    else{
        int nbr_concours = 0;

        int IndexConcours[NB_CONCOURS];
        int pointConcours[NB_CONCOURS];
        

        for(int i = 0; i < NB_CONCOURS; ++i){
            if(participants[atoi(numP) - 1].concours[i] > 0){

                IndexConcours[nbr_concours] = i;
                pointConcours[nbr_concours] = participants[atoi(numP) - 1].concours[i];
                ++nbr_concours;
            }
        }

        printf("%s %s\n", participants[atoi(numP) - 1].nom, participants[atoi(numP) - 1].prenom);

        char pluriel[2];
        if(!nbr_concours){
            printf("Aucun gain\n");
        }
        else{
            for(int i = 0; i < nbr_concours; ++i){

                if(pointConcours[i] > 1){
                    strcpy(pluriel, "s");
                }
                else{
                    strcpy(pluriel, "");
                }

                printf("(%d) %s : %d point%s\n", IndexConcours[i] + 1, concours[IndexConcours[i]], pointConcours[i], pluriel);
            }
        }
    }



}

void Classement(const Participant participant[], const Concours concours[], int nb_participants, int nb_concours, const char input[]){
    
    char strIndex[nbChiffres(NB_CONCOURS)];
    Read(input, strIndex, 2);
    int concoursIndex = atoi(strIndex) - 1;

    if(concoursIndex < 0 || concoursIndex >= nb_concours){
        printf("Identifiant incorrect\n");
    }
    else{
        int nb_PC = 0;
        int PC[NB_PARTICIPANTS];

        for(int i = 0; i < nb_participants; ++i){
            if(participant[i].concours[concoursIndex]){
                PC[nb_PC] = i;
                ++nb_PC;
            }
        }

        printf("%s\n", concours[concoursIndex]);

        if(!nb_PC){
            printf("Aucun participant\n");
        }
        else{

            // Tri de la liste d'index de participant en fct° de le score au concours (tri à bulles)
            int temp;
            int numPermut;
            do{
                numPermut = 0;
                for(int i = 0; i < nb_PC - 1; ++i){
                    if(participant[PC[i]].concours[concoursIndex] < participant[PC[i+1]].concours[concoursIndex]){
                        temp = PC[i];
                        PC[i] = PC[i+1];
                        PC[i+1] = temp;
                        ++numPermut;
                    }
                }
            }while(numPermut);


            int ex = 0;
            char space[4] = " ";
            int valeurPre = 0;
            char pluriel[2];
            for (int i = 0; i < nb_PC; i++)
            {
                if(participant[PC[i]].concours[concoursIndex] == valeurPre){
                    ++ex;
                    strcpy(space, "ex ");
                }
                else if(i < nb_PC-1 && participant[PC[i]].concours[concoursIndex] == participant[PC[i+1]].concours[concoursIndex]){
                    ex = 0;
                    strcpy(space, "ex ");
                }
                else{
                    ex = 0;
                    strcpy(space, " ");
                }

                if(participant[PC[i]].concours[concoursIndex] > 1){
                    strcpy(pluriel, "s");
                }
                else{
                    strcpy(pluriel, "");
                }


                printf("%d%s-> (%d) %s %s : %d point%s\n",
                     i + 1 - ex,
                     space,
                     participant[PC[i]].numero, 
                     participant[PC[i]].nom,
                     participant[PC[i]].prenom,
                     participant[PC[i]].concours[concoursIndex],
                     pluriel);

                valeurPre = participant[PC[i]].concours[concoursIndex];

            }

        }
    }

}

void Comparaison(const Participant participant[], const Concours concours[], int nb_participants, int nb_concours, const char input[]){ 

    char strIndex1[nbChiffres(NB_CONCOURS)];
    char strIndex2[nbChiffres(NB_CONCOURS)]; 
    Read(input, strIndex1, 2);
    Read(input, strIndex2, 3);
    int indexConcours1 = atoi(strIndex1) - 1;
    int indexConcours2 = atoi(strIndex2) - 1;

    if(indexConcours1 < 0 || indexConcours1 >= nb_concours || indexConcours2 < 0 || indexConcours2 >= nb_concours){
        printf("Identifiant incorrect\n");
    }
    else{
        int incompatible = 0;
        int participe[nb_participants];
        int indexParticipe = 0;

        for(int i = 0; i < nb_participants; ++i){
            if(participant[i].concours[indexConcours1] || participant[i].concours[indexConcours2]){
                participe[indexParticipe] = i;
                ++indexParticipe;
            }
        }

        for(int i = 0; i < indexParticipe; ++i){
            if(!participant[participe[i]].concours[indexConcours1]){
                ++incompatible;
            }
        }

        printf("%s versus %s\n", concours[indexConcours2], concours[indexConcours1]);

        if(!indexParticipe){
            printf("Aucun participant\n");
        }
        else if(incompatible){
            printf("Concours incompatibles\n");
        }
        else{
            float pourcent;
            char pluriel1[2];
            char pluriel2[2];

            for(int i = 0; i < indexParticipe; ++i){
                pourcent = ((float)participant[participe[i]].concours[indexConcours2] / (float)participant[participe[i]].concours[indexConcours1]) * 100;

                if(participant[participe[i]].concours[indexConcours1] > 1){
                    strcpy(pluriel1, "s");
                }
                else{
                    strcpy(pluriel1, "");
                }

                if(participant[participe[i]].concours[indexConcours2] > 1){
                    strcpy(pluriel2, "s");
                }
                else{
                    strcpy(pluriel2, "");
                }
            
                printf("(%d) %s %s : %d point%s/%d point%s : %.2f%c\n", 
                    participant[participe[i]].numero, 
                    participant[participe[i]].nom, 
                    participant[participe[i]].prenom,
                    participant[participe[i]].concours[indexConcours2],
                    pluriel2,
                    participant[participe[i]].concours[indexConcours1],
                    pluriel1,
                    pourcent,
                    '%');
            }
        }
    }
}

void Afficher_Classement(int classement[NB_CONCOURS][NB_PARTICIPANTS]){
    for(int i = 0; i < NB_CONCOURS; ++i){
        for(int j = 0; j < NB_PARTICIPANTS; ++j){
            printf("%d ", classement[i][j]);
        }
        printf("\n");
    }
}

void Bilan(const Participant participant[], const Concours concours[], int nb_participants, int nb_concours, int classement[][NB_PARTICIPANTS], int classementBilan[][NB_PARTICIPANTS], const char input[]){

    char strIndex[nbChiffres(NB_CONCOURS)];
    Read(input, strIndex, 2);
    int concoursIndex = atoi(strIndex) - 1;

    if(concoursIndex < 0 || concoursIndex >= nb_concours){
        printf("Identifiant incorrect\n");
    }
    else{
        int nb_PC = 0;
        int PC[NB_PARTICIPANTS];

        for(int i = 0; i < nb_participants; ++i){
            if(participant[i].concours[concoursIndex]){
                PC[nb_PC] = i;
                ++nb_PC;
            }
        }

        if(!nb_PC){
            printf("Aucun participant\n");
        }
        else{

            // Tri de la liste d'index de participant en fct° du score au concours (tri à bulles)
            int temp;
            int numPermut;
            do{
                numPermut = 0;
                for(int i = 0; i < nb_PC - 1; ++i){
                    if(participant[PC[i]].concours[concoursIndex] < participant[PC[i+1]].concours[concoursIndex]){
                        temp = PC[i];
                        PC[i] = PC[i+1];
                        PC[i+1] = temp;
                        ++numPermut;
                    }
                }
            }while(numPermut);

            printf("%s\n", concours[concoursIndex]);

            int ex = 0;
            char space[4] = " ";
            int valeurPre = 0;

            int nb_place = 0;
            char plusOuMoins[3];
            char place_pluriel[2];
            char point_pluriel[2];

            for (int i = 0; i < nb_PC; i++)
            {
                if(participant[PC[i]].concours[concoursIndex] == valeurPre){
                    ++ex;
                    strcpy(space, "ex ");
                }
                else if(i < nb_PC-1 && participant[PC[i]].concours[concoursIndex] == participant[PC[i+1]].concours[concoursIndex]){
                    ex = 0;
                    strcpy(space, "ex ");
                }
                else{
                    ex = 0;
                    strcpy(space, " ");
                }

                nb_place = classementBilan[concoursIndex][PC[i]] - classement[concoursIndex][PC[i]];

                if(nb_place < 0){
                    strcpy(plusOuMoins, " ");
                }
                else{

                    strcpy(plusOuMoins, " +");
                }

                if(participant[PC[i]].concours[concoursIndex] > 1){
                    strcpy(point_pluriel, "s");
                }
                else{
                    strcpy(point_pluriel, "");
                }

                if(nb_place > 1 || nb_place < -1){
                        strcpy(place_pluriel, "s");
                    }
                    else{
                        strcpy(place_pluriel, "");
                    }


                printf("%d%s-> (%d) %s %s : %d point%s :%s%d place%s\n",
                     i + 1 - ex,
                     space,
                     participant[PC[i]].numero, 
                     participant[PC[i]].nom,
                     participant[PC[i]].prenom,
                     participant[PC[i]].concours[concoursIndex],
                     point_pluriel,
                     plusOuMoins,
                     nb_place,
                     place_pluriel);

                valeurPre = participant[PC[i]].concours[concoursIndex];
                
                classementBilan[concoursIndex][PC[i]] = classement[concoursIndex][PC[i]];


            }

        }
    }
}
