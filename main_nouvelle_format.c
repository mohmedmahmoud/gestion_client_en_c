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

char nom_fichier[50]="client_nouvelle_format.txt";
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

// ---------------------------------------------------------nouvelle format-------------------


void enregistrer_listeNouvelleFormat(Client* tete) {
    FILE* fichier = fopen(nom_fichier, "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    // Parcourir la liste des clients et écrire chaque client dans le fichier
    Client* courant = tete;
    while (courant != NULL) {
        fprintf(fichier, " %d, %s, %s:", courant->numero, courant->nom, courant->adresse);
        courant = courant->next;
    }

    fclose(fichier);
    printf("Liste des clients enregistrée avec succès dans le fichier %s.\n", nom_fichier);
}

Client* chargerNouvelleFormat(Client* tete) {
    // Ouverture du fichier en mode lecture
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        return tete;
    }

    // Lecture du contenu du fichier dans une chaîne de caractères
    char chaine[1000];
    if (fgets(chaine, 1000, fichier) == NULL) {
        printf("Erreur de lecture du fichier\n");
        fclose(fichier);
         return tete;
    }

    // Fermeture du fichier
    fclose(fichier);

   
    char* token = strtok(chaine, ":");
    while (token != NULL) {
        int numero;
        char nom[50];
        char adresse[100];
        sscanf(token, " %d, %[^,], %s", &numero, nom, adresse);
        inserer_en_fin(&tete, creer_noeud(numero, nom, adresse));
        token = strtok(NULL, ":");
    }
     return tete;
}

void trier_clients_par_num(Client* tete) {
    Client* courant = tete;
    Client* suivant = NULL;
    int temp_numero;
    char temp_nom[50];
    char temp_adresse[100];

    if (tete == NULL) {
        printf("La liste est vide.\n");
        return;
    }

    while (courant != NULL) {
        suivant = courant->next;
        while (suivant != NULL) {
            if (courant->numero > suivant->numero) {
                temp_numero = courant->numero;
                strcpy(temp_nom, courant->nom);
                strcpy(temp_adresse, courant->adresse);
                courant->numero = suivant->numero;
                strcpy(courant->nom, suivant->nom);
                strcpy(courant->adresse, suivant->adresse);

                suivant->numero = temp_numero;
                strcpy(suivant->nom, temp_nom);
                strcpy(suivant->adresse, temp_adresse);
            }
            suivant = suivant->next;
        }
        courant = courant->next;
    }

    printf("Liste des clients triee selon leur numero.\n");
    afficher_clients(tete);
}

void trier_clients_par_nom(Client* tete) {
    Client* courant = tete;
    Client* suivant = NULL;
    int temp_numero;
    char temp_nom[50];
    char temp_adresse[100];

    if (tete == NULL) {
        printf("La liste est vide.\n");
        return;
    }

    while (courant != NULL) {
        suivant = courant->next;
        while (suivant != NULL) {
            if (strcmp(courant->nom, suivant->nom) > 0) {
                temp_numero = courant->numero;
                strcpy(temp_nom, courant->nom);
                strcpy(temp_adresse, courant->adresse);
                courant->numero = suivant->numero;
                strcpy(courant->nom, suivant->nom);
                strcpy(courant->adresse, suivant->adresse);

                suivant->numero = temp_numero;
                strcpy(suivant->nom, temp_nom);
                strcpy(suivant->adresse, temp_adresse);
            }
            suivant = suivant->next;
        }
        courant = courant->next;
    }

    printf("Liste des clients triee selon leur nom.\n");
    afficher_clients(tete);
}

void trier_clients_par_adresse(Client* tete) {
    Client* courant = tete;
    Client* suivant = NULL;
    int temp_numero;
    char temp_nom[50];
    char temp_adresse[100];

    if (tete == NULL) {
        printf("La liste est vide.\n");
        return;
    }

    while (courant != NULL) {
        suivant = courant->next;
        while (suivant != NULL) {
            if (strcmp(courant->adresse, suivant->adresse) > 0) {
                temp_numero = courant->numero;
                strcpy(temp_nom, courant->nom);
                strcpy(temp_adresse, courant->adresse);
                courant->numero = suivant->numero;
                strcpy(courant->nom, suivant->nom);
                strcpy(courant->adresse, suivant->adresse);

                suivant->numero = temp_numero;
                strcpy(suivant->nom, temp_nom);
                strcpy(suivant->adresse, temp_adresse);
            }
            suivant = suivant->next;
        }
        courant = courant->next;
    }

    printf("Liste des clients triee selon leur adresse.\n");
    afficher_clients(tete);
}

void sizeOfClients(Client* tete){
    Client* courant = tete;
    int size=0;
     if (tete == NULL) {
        printf("La liste est vide. size : 0\n");
        return;
    }
    while(courant!=NULL){
        size++;
        courant=courant->next;
    }

     printf("le nombre des clients size : %d\n", size);

    
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
        printf("8. Liste des clients selon leur numero\n");
        printf("9. Liste des clients selon leur nom\n");
        printf("10. Liste des clients selon leur addresse\n");
        printf("11. le nombre de client \n");
        printf("12. Quitter\n");
        
        scanf("%d", &choix);

        switch (choix) {
            case 0: {
                
                enregistrer_listeNouvelleFormat(tete);
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
               
                chargerNouvelleFormat(tete);
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
                trier_clients_par_num(tete);
                break;
            }
             case 9:{
                trier_clients_par_nom(tete);
                break;
            }
             case 10:{
                trier_clients_par_adresse(tete);
                break;
            }
             case 11:{
                sizeOfClients(tete);
                break;
            }
            case 12:{
                printf("Au revoir!\n");
                break;
            }
            default:
                printf("Choix invalide\n");
                break;
        }
         if(is_enregistrement_auto_active!=0 ) {
               enregistrer_listeNouvelleFormat(tete);
         }
    } while (choix != 12);
}








// ---------------------------------------------------------MAIN-------------------

int main() {
   
    Client* tete = NULL;
   
    // lire les daonnes de ficher
   tete= chargerNouvelleFormat(tete);
   
 

    // Affichage des clients les choix 
    menu(tete);
    
    return 0;
}
