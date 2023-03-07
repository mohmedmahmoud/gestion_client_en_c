

void ajouter_client_fichier(int numero, char* nom, char* adresse) {
    FILE* fichier = fopen(nom_ficher, "a");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return;
    }
    
    fprintf(fichier, "%d, %s, %s\n", numero, nom, adresse);
    
    fclose(fichier);
}


void ajouter_tout_les_client_fichier(Client* client) {
    
    FILE* fichier = fopen(nom_ficher, "a");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return;
    }
    while (client!=NULL)
    {
       fprintf(fichier, "%d, %s, %s\n",client->numero , client->nom, client->adresse);
       client=client->next;
    }

    printf("fin insertion \n");
    fclose(fichier);
}

void inserer(Client** tete, Client* client, int position) {
    switch (position) {
        case 0:
            inserer_en_tete(tete, client);
            break;
        case 1:
            inserer_en_fin(tete, client);
            break;
        default:
            printf("Position d'insertion invalide\n");
            break;
    }
}