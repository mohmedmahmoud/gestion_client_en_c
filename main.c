#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Client Client;

struct Client {
    int numero;
    char nom[50];
    char adresse[100];
    Client* next;
};

char nom_fichier[50]="client.txt";
int is_enregistrement_auto_active=0;

Client* creer_noeud(int numero, char* nom, char* adresse) {
    Client* client = (Client*) malloc(sizeof(Client));
    client->numero = numero;
    strcpy(client->nom, nom);
    strcpy(client->adresse, adresse);
    client->next = NULL;
    return client;
}

void inserer_en_tete(Client** tete, Client* client) {
    client->next = *tete;
    *tete = client;
}

void inserer_en_fin(Client** tete, Client* client) {
    if (*tete == NULL) {
        *tete = client;
    } else {
        Client* courant = *tete;
        while (courant->next != NULL) {
            courant = courant->next;
        }
        courant->next = client;
    }
    client->next = NULL;
}


void afficher_clients(Client* tete) {
    printf("Liste des clients :\n");
    while (tete != NULL) {
        printf("  Numéro  : %d\n", tete->numero);
        printf("  Nom     : %s\n", tete->nom);
        printf("  Adresse : %s\n", tete->adresse);
        printf("\n");
        tete = tete->next;
    }
}

void inserer_client(Client** tete, int numero, char* nom, char* adresse) {
    // Création d'un nouveau noeud pour le client
    Client* client = creer_noeud(numero, nom, adresse);

    // Insertion du nouveau noeud en tête de liste
    inserer_en_tete(tete, client);
}



 Client* charger_liste(Client* tete){
    tete=NULL;
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        return tete;
    }
    char ligne[256];
      while (fgets(ligne, 256, fichier) != NULL) {
        int numero;
        char nom[50];
        char adresse[100];

        // Parsing de la ligne
        if (sscanf(ligne, "%d, %49[^,], %99[^\n]", &numero, nom, adresse) != 3) {
            printf("Erreur de syntaxe dans la ligne : %s\n", ligne);
            continue;
        }

        // Création d'un nouveau noeud pour le client
        Client* client = creer_noeud(numero, nom, adresse);

        // Insertion du nouveau noeud en tête de liste
        inserer_en_tete(&tete, client);
    }
   

    fclose(fichier);
    return tete;
}

void enregistrer_liste(Client* tete) {
    FILE* fichier = fopen(nom_fichier, "w");
    if (fichier == NULL) {
        printf("Erreur: impossible d'ouvrir le fichier %s\n", nom_fichier);
        return;
    }
    Client* client = tete;
    while (client != NULL) {
        fprintf(fichier, "%d, %s, %s\n", client->numero, client->nom, client->adresse);
        client = client->next;
    }
    fclose(fichier);
    printf("Liste enregistree dans le fichier %s\n", nom_fichier);
}

void supprimer_client(Client** tete, int numero) {
    Client* prec = NULL;
    Client* cour = *tete;

    while (cour != NULL && cour->numero != numero) {
        prec = cour;
        cour = cour->next;
    }

    if (cour == NULL) {
        printf("Erreur: impossible de trouver le client %d\n", numero);
        return;
    }

    if (prec == NULL) {
        *tete = cour->next;
    } else {
        prec->next = cour->next;
    }

    free(cour);
    printf("Client %d supprime avec succes\n", numero);
}

void modifier_client(Client* tete, int numero, char* nouveau_nom, char* nouvelle_adresse) {
    Client* client = tete;

    while (client != NULL && client->numero != numero) {
        client = client->next;
    }

    if (client == NULL) {
        printf("Erreur: impossible de trouver le client %d\n", numero);
        return;
    }

    strcpy(client->nom, nouveau_nom);
    strcpy(client->adresse, nouvelle_adresse);

    printf("Client %d modifie avec succes\n", numero);
}



// ---------------------------------------------------------MENU-------------------

void menu(Client* tete) {
    int choix = 0;
    do {
       
        printf("\nChoisissez une operation:\n");
        printf("0. Enregistrer les changement dans le fichier\n");
        printf("1. Ajouter a la tete de la list\n");
        printf("2. Ajouter a la fin de la list\n");
        printf("3. Afficher la liste\n");
        printf("4. Charger une liste depuis un fichier\n");
        printf("5. Modifier un utilisateur \n");
        printf("6. suprimmer un Client\n");
        if(is_enregistrement_auto_active==0){
        printf("7. Activer l'enregistrement automatique\n");
        }else{
         printf("7. Desactiver l'enregistrement automatique\n");   
        }
        printf("8. Quitter\n");
        
        scanf("%d", &choix);

        switch (choix) {
            case 0: {
                
                enregistrer_liste(tete);
                break;
            }
            case 1: {
                int numero;
                char nom[50];
                char adresse[100];
                printf("Numero du client: ");
                scanf("%d", &numero);
                printf("Nom du client: ");
                scanf("%s", nom);
                printf("Adresse du client: ");
                scanf("%s", adresse);
                inserer_en_tete(&tete, creer_noeud(numero, nom, adresse));
                break;
            }
            case 2: {
                int numero;
                char nom[50];
                char adresse[100];
                printf("Numero du client: ");
                scanf("%d", &numero);
                printf("Nom du client: ");
                scanf("%s", nom);
                printf("Adresse du client: ");
                scanf("%s", adresse);
                inserer_en_fin(&tete, creer_noeud(numero, nom, adresse));
                break;
            }
            case 3:
                afficher_clients(tete);
                break;
            case 4: {
               
                charger_liste(tete);
                break;
            }
             case 5: {
                int numero;
                char nom[50];
                char adresse[100];
                printf("Numero du client a modifier: ");
                scanf("%d", &numero);
                printf(" le nouveaux Nom du client: ");
                scanf("%s", nom);
                printf(" le nouveaux Adresse du client: ");
                scanf("%s", adresse);
                modifier_client(tete, numero, nom, adresse);
                break;
            }
            case 6: {
                int numero;
                printf("Numero du client: ");
                scanf("%d", &numero);
                supprimer_client(&tete, numero);
                break;
            }
             case 7: {
                if(is_enregistrement_auto_active==0 ) {
                 is_enregistrement_auto_active=1;   
                } else{
                  is_enregistrement_auto_active=0;   
                }
                  break;
            }
            case 8:{
                printf("Au revoir!\n");
                break;
            }
            default:
                printf("Choix invalide\n");
                break;
        }
         if(is_enregistrement_auto_active!=0 ) {
               enregistrer_liste(tete);
         }
    } while (choix != 8);
}








// ---------------------------------------------------------MAIN-------------------

int main() {
   
   

    Client* tete = NULL;
   
    // lire les daonnes de ficher
   tete= charger_liste(tete);
 

    // Affichage des clients les choix 
    menu(tete);
    
    return 0;
}
