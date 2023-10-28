#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define TABLE_SIZE 20000

typedef struct {
    int distanza;
    int numero_macchine;
    int autonomie_macchine[513];
    int max_autonomia;
    struct Stazione *next;
}Stazione;


typedef struct {
    int distanza;
    struct NodoBST *destra;
    struct NodoBST *sinistra;
}NodoBST;


NodoBST *root;

int numero_nodi = 0;

 int hash_function(int key, int table_size) {

     if(key % table_size == 0 )
         return 1;
     else
         return key % table_size;

}

void aggiungi_nodo_BST(int distanza){

    NodoBST *nuovo_nodo = malloc(sizeof(NodoBST));
    nuovo_nodo->distanza = distanza;
    nuovo_nodo->destra = NULL;
    nuovo_nodo->sinistra = NULL;

    if(root == NULL){
        root = nuovo_nodo;
    }
    else if(root != NULL){
        NodoBST *precedente = NULL;
        NodoBST *corrente = root;

        while(corrente != NULL){
            precedente = corrente;
            if(distanza < corrente->distanza){
                corrente = (NodoBST *) corrente->sinistra;
            }
            else{
                corrente = (NodoBST *) corrente->destra;
            }
        }
        if(distanza < precedente->distanza){
            precedente->sinistra = (struct NodoBST *) nuovo_nodo;
        }
        else if(distanza > precedente->distanza){
            precedente->destra = (struct NodoBST *) nuovo_nodo;
        }
    }
}

void aggiungi_stazione(Stazione *hash_table[TABLE_SIZE], int distanza, int numero_macchine, int *autonomie_macchine,int max_autonomia) {
    bool trovato = false;
    int hash_key = hash_function(distanza, TABLE_SIZE);

    if (hash_table[hash_key] != NULL) {

        Stazione *testa;
        testa = hash_table[hash_key];

        while (testa != NULL) {
            if (testa->distanza == distanza) {
                trovato = true;
                break;
            }
            testa = (Stazione *) testa->next;
        }
    }

    if(hash_table[hash_key] == NULL) {
        Stazione *stazione = malloc(sizeof(Stazione));
        stazione->distanza = distanza;
        stazione->numero_macchine = numero_macchine;
        stazione->max_autonomia = max_autonomia;
        memcpy(stazione->autonomie_macchine, autonomie_macchine, (stazione->numero_macchine + 1) * sizeof(int));
        stazione->next = NULL;
        aggiungi_nodo_BST(distanza);
        hash_table[hash_key] = stazione;
        printf("aggiunta\n");
        numero_nodi++;
    }
    else if(hash_table[hash_key]!= NULL){
        if(trovato == false){
            Stazione *stazione = malloc(sizeof(Stazione));
            Stazione *testa = hash_table[hash_key];
            while (testa->next != NULL) {
                testa = (Stazione *) testa->next;
            }
            stazione->distanza = distanza;
            stazione->numero_macchine = numero_macchine;
            stazione->max_autonomia = max_autonomia;
            memcpy(stazione->autonomie_macchine, autonomie_macchine, (stazione->numero_macchine + 1) * sizeof(int));
            stazione->next = NULL;
            aggiungi_nodo_BST(distanza);
            testa->next = (struct Stazione *) stazione;
            printf("aggiunta\n");
            numero_nodi++;
        }
        else if (trovato == true){
            printf("non aggiunta\n");
        }
    }
}

void demolisci_stazione(Stazione *hash_table[TABLE_SIZE], int sta_cancellare){

    bool trovato = false;
     int hash_key = hash_function(sta_cancellare,TABLE_SIZE);


    if(hash_table[hash_key]!= NULL){

        Stazione *testa;
        testa = hash_table[hash_key];

        while( testa != NULL){
            if( testa->distanza == sta_cancellare){
                trovato = true;
                break;
            }
            testa = (Stazione *) testa->next;
        }
    }

    if(hash_table[hash_key] == NULL){
        printf("non demolita\n");
        return;
    }
    else if (hash_table[hash_key] != NULL){
        if(trovato == false){
            printf("non demolita\n");
            return;
        }
        else if(trovato == true){
            printf("demolita\n");
            Stazione *precedente = NULL;
            Stazione *elemento_testa = hash_table[hash_key];
            while (elemento_testa!= NULL){
                if(elemento_testa->distanza == sta_cancellare){
                    if(precedente == NULL){
                        if(elemento_testa->next != NULL){
                            hash_table[hash_key] = (Stazione *) elemento_testa->next;
                            break;
                        }
                        else if ( elemento_testa->next == NULL){
                            hash_table[hash_key] = NULL;
                            break;
                        }
                    }
                    else{
                        precedente->next = elemento_testa->next;
                        break;
                    }
                }
                precedente = elemento_testa;
                elemento_testa = (Stazione *) elemento_testa->next;
            }
            numero_nodi--;
        }
    }
}

void aggiungi_auto(Stazione *hash_table[TABLE_SIZE], int distanza, int autonomia_auto) {

    bool trovato = false;

    unsigned int hash_key = hash_function(distanza,TABLE_SIZE);

    if(hash_table[hash_key]!= NULL){

        Stazione *testa;
        testa = hash_table[hash_key];

        while( testa != NULL){
            if( testa->distanza == distanza){
                trovato = true;
                break;
            }
            testa = (Stazione *) testa->next;
        }
    }

    if (hash_table[hash_key] != NULL && trovato == true) {
        Stazione *stazione_testa = hash_table[hash_key];
        while (stazione_testa->distanza != distanza) {
            stazione_testa = (Stazione *) stazione_testa->next;
        }
        int *vettore_autonomie;

        vettore_autonomie = stazione_testa->autonomie_macchine;
        if (stazione_testa->numero_macchine != 0){
            while (*vettore_autonomie!= -2 && *vettore_autonomie != -1) {
                vettore_autonomie++;
            }
            if(*vettore_autonomie == -2) {
                *vettore_autonomie = autonomia_auto;
                vettore_autonomie++;
                *vettore_autonomie = -2;
            }
            else{
                *vettore_autonomie = autonomia_auto;
            }
            stazione_testa->numero_macchine++;

            printf("aggiunta\n");
        }
        else if(*vettore_autonomie == -1 || *vettore_autonomie == -2){
            if(*vettore_autonomie == -2){
                vettore_autonomie[0] = autonomia_auto;
                vettore_autonomie++;
                *vettore_autonomie = -2;
            }
            else if( *vettore_autonomie == -1){
                *vettore_autonomie = autonomia_auto;
            }

            stazione_testa->numero_macchine++;
            printf("aggiunta\n");

        }
        if (autonomia_auto > stazione_testa->max_autonomia) {
            stazione_testa->max_autonomia = autonomia_auto;
        }
    }
    else
        printf("non aggiunta\n");
}

void rottama_auto(Stazione *hash_table[TABLE_SIZE], int distanza, int autonomia_auto){

    bool trovato = false;
    int hash_key = hash_function(distanza,TABLE_SIZE);

    if(hash_table[hash_key]!= NULL){

        Stazione *testa;
        testa = hash_table[hash_key];

        while( testa != NULL){
            if( testa->distanza == distanza){
                trovato = true;
                break;
            }
            testa = (Stazione *) testa->next;
        }
    }

    if(hash_table[hash_key]!= NULL && trovato == true){
        int tmp_max_autonomia = 0;
        int *autonomie;

        Stazione* stazione_testa = hash_table[hash_key];
        while( stazione_testa->distanza != distanza){
            stazione_testa = (Stazione *) stazione_testa->next;
        }
        autonomie = stazione_testa->autonomie_macchine;
        while(*autonomie != -2){
            if( *autonomie == autonomia_auto ){
                *autonomie = -1;
                printf("rottamata\n");
                stazione_testa->numero_macchine--;
                break;
            }
            autonomie++;
        }
        if(*autonomie != -2){
            if( autonomia_auto == stazione_testa->max_autonomia) {
                autonomie = stazione_testa->autonomie_macchine;
                tmp_max_autonomia = 0;
                while (*autonomie != -2) {
                    if (*autonomie >= tmp_max_autonomia) {
                        tmp_max_autonomia = *autonomie;
                    }
                    autonomie++;
                }
                stazione_testa->max_autonomia = tmp_max_autonomia;
                }
            }
        else
            printf("non rottamata\n");
        }
        else
            printf("non rottamata\n");

}

void init_hash_table(Stazione *hash_table[TABLE_SIZE]){
    for( int i = 0 ; i < TABLE_SIZE; i ++){
        hash_table[i] = NULL;
    }
}

Stazione *trova_stazione_da_nodo(Stazione *hash_table[TABLE_SIZE],int distanza_stazione){
    Stazione *stazione = hash_table[hash_function(distanza_stazione,TABLE_SIZE)];
    while(stazione!= NULL){
        if( stazione->distanza == distanza_stazione){
            break;
        }
        stazione = (Stazione *) stazione->next;
    }
    return stazione;
}

bool controlla_inizio_fine(int stazione_iniziale,int stazione_finale,Stazione *hash_table[TABLE_SIZE]){

    bool trovata_iniziale = false;
    bool trovata_finale = false;

    Stazione *stazione_inizio = hash_table[hash_function(stazione_iniziale,TABLE_SIZE)];
    Stazione *stazione_fine = hash_table[hash_function(stazione_finale,TABLE_SIZE)];


    if(stazione_inizio == NULL){
        trovata_iniziale = false;
    }
    else if (stazione_inizio!= NULL){
        while(stazione_inizio != NULL){
            if(stazione_inizio->distanza == stazione_iniziale){
                trovata_iniziale = true;
                break;
            }
            stazione_inizio = (Stazione *) stazione_inizio->next;
        }
    }

    if(stazione_fine == NULL){
        trovata_finale = false;
    }
    else if (stazione_fine!= NULL){
        while(stazione_fine != NULL){
            if(stazione_fine->distanza == stazione_finale){
                trovata_finale = true;
                break;
            }
            stazione_fine = (Stazione *) stazione_fine->next;
        }
    }

    if(trovata_iniziale == true && trovata_finale == true){
        return  true;
    }
    else
        return false;
}

void pianifica_percorso_crescente(NodoBST* radice,int stazione_iniziale, int stazione_finale, Stazione *hash_table[TABLE_SIZE]) {
    NodoBST* stack[10000];
    int i = 0;

    int top = -1;
    bool iniziato_pianifica = false;
    int *queue;
    int *vettore_distanze;
    int *vettore_distanza_nodo_origine;
    int fronte = -1;
    int retro = -1;
    int tmp_distanza = 0;
    int max_raggiungibile = 0;
    bool trovato_percorso = false;
    bool trovato_percorso_minimo = false;
    int *percorso_trovato;
    int minore = 0;
    int distanza_obbiettivo = 0;
    int copia_retro = 0;

    queue = (int *) malloc(numero_nodi * sizeof(int));
    percorso_trovato = (int *) malloc(200 * sizeof(int));
    vettore_distanze = (int *) malloc(2 * numero_nodi * sizeof(int));
    vettore_distanza_nodo_origine = (int *) malloc(2 * numero_nodi * sizeof(int));
    vettore_distanze[i] = stazione_iniziale;
    vettore_distanza_nodo_origine[i] = tmp_distanza;
    tmp_distanza++;
    i = i + 1;
    queue = (int *) malloc(numero_nodi * sizeof(int));

    Stazione *hash_stazione_iniziale = trova_stazione_da_nodo(hash_table,stazione_iniziale);

    max_raggiungibile = stazione_iniziale + hash_stazione_iniziale->max_autonomia;

    fronte = 0;
    retro = 0;
    queue[retro] = stazione_iniziale;

    while (radice != NULL || top != -1) {
        while (radice != NULL) {
            top = top +1;
            stack[top] = radice;

            if(radice->distanza == stazione_iniziale){
                iniziato_pianifica = true;
                break;
            }
            radice = (NodoBST *) radice->sinistra;
        }

        radice = stack[top];
        top = top - 1;

        if(iniziato_pianifica == true ) {

            Stazione *check_esistenza = trova_stazione_da_nodo(hash_table, radice->distanza);
            if(check_esistenza!= NULL){
            if (max_raggiungibile >= radice->distanza && radice != NULL && radice->distanza != queue[fronte]) {
                retro = retro + 1;
                queue[retro] = radice->distanza;
                if (radice->distanza == stazione_finale) {
                    trovato_percorso = true;
                    vettore_distanze[i] = queue[retro];
                    vettore_distanza_nodo_origine[i] = tmp_distanza;
                    distanza_obbiettivo = tmp_distanza;
                    if (queue[fronte] == stazione_iniziale) {
                        trovato_percorso_minimo = true;
                    }
                    break;
                }
                vettore_distanze[i] = queue[retro];
                vettore_distanza_nodo_origine[i] = tmp_distanza;
                i++;
            } else if (max_raggiungibile < radice->distanza && radice != NULL && radice->distanza != queue[fronte]) {
                tmp_distanza = tmp_distanza + 1;
                if (fronte < retro) {
                    fronte = fronte + 1;
                    copia_retro = retro;
                    while (fronte != retro) {
                        Stazione *stazione2 = trova_stazione_da_nodo(hash_table, queue[fronte]);
                        if (stazione2->max_autonomia + queue[fronte] > max_raggiungibile) {
                            max_raggiungibile = stazione2->max_autonomia + queue[fronte];
                        }
                        fronte = fronte + 1;
                    }
                    Stazione *stazione3 = trova_stazione_da_nodo(hash_table, queue[fronte]);
                    if (stazione3->max_autonomia + queue[fronte] > max_raggiungibile) {
                        max_raggiungibile = stazione3->max_autonomia + queue[fronte];
                    }
                    if (max_raggiungibile >= radice->distanza) {
                        retro = retro + 1;
                        queue[retro] = radice->distanza;
                        vettore_distanze[i] = queue[retro];
                        vettore_distanza_nodo_origine[i] = tmp_distanza;
                        if (radice->distanza == stazione_finale) {
                            trovato_percorso = true;
                            distanza_obbiettivo = tmp_distanza;
                            break;
                        }
                        i = i + 1;
                    }
                    if (copia_retro == retro) {
                        percorso_trovato = false;
                        break;
                    }
                } else if (fronte == retro) {
                    Stazione *stazione3 = trova_stazione_da_nodo(hash_table, queue[fronte]);
                    if (stazione3->max_autonomia + queue[fronte] > max_raggiungibile) {
                        max_raggiungibile = stazione3->max_autonomia + queue[fronte];
                        if (max_raggiungibile >= radice->distanza) {
                            retro = retro + 1;
                            queue[retro] = radice->distanza;
                            vettore_distanze[i] = queue[retro];
                            vettore_distanza_nodo_origine[i] = tmp_distanza;
                            if (radice->distanza == stazione_finale) {
                                trovato_percorso = true;
                                distanza_obbiettivo = tmp_distanza;
                                break;
                            }
                        } else if (max_raggiungibile < radice->distanza) {
                            trovato_percorso = false;
                            printf("nessun percorso\n");
                            return;
                        }
                    } else {
                        trovato_percorso = false;
                        printf("nessun percorso\n");
                        return;
                    }
                }
            }
        }
        }
        radice = (NodoBST *) radice->destra;
    }

    if(trovato_percorso_minimo == true){
        printf("%d %d\n",stazione_iniziale,stazione_finale);
        return;
    }

    if(trovato_percorso == true){
        int stazione_precedente;
        int z = 0;
        stazione_precedente = stazione_finale;
        percorso_trovato[0] = stazione_finale;
        z++;
        int *indice;
        int *indice_distanze_nodo_origine;
        indice = &vettore_distanze[i];
        indice_distanze_nodo_origine = &vettore_distanza_nodo_origine[i];
        minore = stazione_finale;
        while (*indice != stazione_iniziale) {
            minore = *indice;
            while (*indice_distanze_nodo_origine == tmp_distanza) {
                if (*indice_distanze_nodo_origine != distanza_obbiettivo){
                    Stazione *stazione = trova_stazione_da_nodo(hash_table,*indice);
                    bool check_avanti = (*indice + stazione->max_autonomia) >= stazione_precedente;
                    if(check_avanti){
                        if (*indice < minore) {
                            minore = *indice;
                        }
                    }
                }
                indice--;
                indice_distanze_nodo_origine--;
            }
            percorso_trovato[z] = minore;
            z++;
            stazione_precedente = minore;
            tmp_distanza--;
        }
        percorso_trovato[z] = stazione_iniziale;
        z++;
        percorso_trovato[z] = '\0';
        z--;
        while (z != 0) {
            if(percorso_trovato[z]!= stazione_finale){
                printf("%d ", percorso_trovato[z]);
            }
            else
                printf("%d", percorso_trovato[z]);
            z--;
        }
        printf("\n");
    }
    else if(trovato_percorso == false){
        printf("nessun percorso\n");
    }
}

void pianifica_percorso_decrescente(NodoBST* radice,int stazione_iniziale, int stazione_finale, Stazione *hash_table[TABLE_SIZE]) {
    NodoBST* stack[10000];
    int i = 0;

    int top = -1;
    bool iniziato_pianifica = false;
    int *queue;
    int *vettore_distanze;
    int *vettore_distanza_nodo_origine;
    int fronte = -1;
    int retro = -1;
    int tmp_distanza = 0;
    int max_raggiungibile = 0;
    bool trovato_percorso = false;
    bool trovato_percorso_minimo = false;
    int *percorso_trovato;
    int minore = 0;
    int distanza_obbiettivo = 0;
    int copia_retro = 0;


    queue = (int *) malloc(numero_nodi * sizeof(int));
    percorso_trovato = (int *) malloc(200 * sizeof(int));
    vettore_distanze = (int *) malloc(2 * numero_nodi * sizeof(int));
    vettore_distanza_nodo_origine = (int *) malloc(2 * numero_nodi * sizeof(int));
    vettore_distanze[i] = stazione_iniziale;
    vettore_distanza_nodo_origine[i] = tmp_distanza;
    tmp_distanza++;
    i = i + 1;
    queue = (int *) malloc(numero_nodi * sizeof(int));

    Stazione *hash_stazione_iniziale = trova_stazione_da_nodo(hash_table,stazione_iniziale);

    max_raggiungibile = stazione_iniziale - hash_stazione_iniziale->max_autonomia;

    fronte = 0;
    retro = 0;
    queue[retro] = stazione_iniziale;

    while (radice != NULL || top != -1) {
        while (radice != NULL) {
            top = top +1;
            stack[top] = radice;

            if(radice->distanza == stazione_iniziale){
                iniziato_pianifica = true;
                break;
            }
            radice = (NodoBST *) radice->destra;
        }

        radice = stack[top];
        top = top - 1;
        if(iniziato_pianifica == true ) {
            Stazione *check_esistenza = trova_stazione_da_nodo(hash_table, radice->distanza);
            if(check_esistenza!= NULL){
            if (max_raggiungibile <= radice->distanza && radice != NULL && radice->distanza != queue[fronte]) {
                retro = retro + 1;
                queue[retro] = radice->distanza;
                if (radice->distanza == stazione_finale) {
                    trovato_percorso = true;
                    vettore_distanze[i] = queue[retro];
                    vettore_distanza_nodo_origine[i] = tmp_distanza;
                    distanza_obbiettivo = tmp_distanza;
                    if (queue[fronte] == stazione_iniziale) {
                        trovato_percorso_minimo = true;
                    }
                    break;
                }

                vettore_distanze[i] = queue[retro];
                vettore_distanza_nodo_origine[i] = tmp_distanza;
                i++;
            } else if (max_raggiungibile > radice->distanza && radice != NULL && radice->distanza != queue[fronte]) {
                tmp_distanza = tmp_distanza + 1;
                if (fronte < retro) {

                    fronte = fronte + 1;
                    copia_retro = retro;

                    while (fronte != retro) {
                        Stazione *stazione2 = trova_stazione_da_nodo(hash_table, queue[fronte]);

                        if (queue[fronte] - stazione2->max_autonomia < max_raggiungibile) {
                            max_raggiungibile = queue[fronte] - stazione2->max_autonomia;
                        }
                        fronte = fronte + 1;
                    }
                    Stazione *stazione3 = trova_stazione_da_nodo(hash_table, queue[fronte]);
                    if (queue[fronte] - stazione3->max_autonomia < max_raggiungibile) {
                        max_raggiungibile = queue[fronte] - stazione3->max_autonomia;
                    }

                    if (max_raggiungibile <= radice->distanza) {
                        retro = retro + 1;
                        queue[retro] = radice->distanza;
                        vettore_distanze[i] = queue[retro];
                        vettore_distanza_nodo_origine[i] = tmp_distanza;
                        if (radice->distanza == stazione_finale) {
                            trovato_percorso = true;
                            distanza_obbiettivo = tmp_distanza;
                            break;
                        }
                        i = i + 1;
                    }
                    if (copia_retro == retro) {
                        percorso_trovato = false;
                        break;
                    }
                } else if (fronte == retro) {

                    Stazione *stazione3 = trova_stazione_da_nodo(hash_table, queue[fronte]);

                    if (queue[fronte] - stazione3->max_autonomia < max_raggiungibile) {
                        max_raggiungibile = queue[fronte] - stazione3->max_autonomia;
                        if (max_raggiungibile <= radice->distanza) {
                            retro = retro + 1;
                            queue[retro] = radice->distanza;
                            vettore_distanze[i] = queue[retro];
                            vettore_distanza_nodo_origine[i] = tmp_distanza;
                            if (radice->distanza == stazione_finale) {
                                trovato_percorso = true;
                                distanza_obbiettivo = tmp_distanza;
                                break;
                            }
                        } else if (max_raggiungibile > radice->distanza) {
                            trovato_percorso = false;
                            printf("nessun percorso\n");
                            return;
                        }
                    } else {
                        trovato_percorso = false;
                        printf("nessun percorso\n");
                        return;
                    }

                }

            }

        }
        }
        radice = (NodoBST *) radice->sinistra;
    }

    if(trovato_percorso_minimo == true){
        printf("%d %d\n",stazione_iniziale,stazione_finale);
        return;
    }

    if(trovato_percorso == true){
        int stazione_precedente;
        int z = 0;
        stazione_precedente = stazione_finale;
        percorso_trovato[0] = stazione_finale;
        z++;

        int *indice;
        int *indice_distanze_nodo_origine;
        indice = &vettore_distanze[i];
        indice_distanze_nodo_origine = &vettore_distanza_nodo_origine[i];

        minore = stazione_finale;
        while (*indice != stazione_iniziale) {
            minore = *indice;
            bool minore_falso = false;
            bool prima_interazione = true;
            while (*indice_distanze_nodo_origine == tmp_distanza) {
                if (*indice_distanze_nodo_origine != distanza_obbiettivo){

                    Stazione *stazione = trova_stazione_da_nodo(hash_table,*indice);
                    bool check_indietro = (*indice - stazione->max_autonomia) <= stazione_precedente;

                    if(prima_interazione == true){
                        if(!check_indietro){
                            minore_falso = true;
                        }
                        prima_interazione = false;
                    }
                    if(check_indietro){
                        if (*indice < minore) {
                            minore = *indice;
                            minore_falso = false;
                        }
                        else if (*indice > minore && minore_falso == true){

                            minore = *indice;
                            minore_falso = false;
                        }
                    }
                }
                indice--;
                indice_distanze_nodo_origine--;

            }
            percorso_trovato[z] = minore;
            z++;
            stazione_precedente = minore;
            tmp_distanza--;
        }
        percorso_trovato[z] = stazione_iniziale;
        z++;
        percorso_trovato[z] = '\0';
        z--;

        while (z != 0) {
            if(percorso_trovato[z]!= stazione_finale){
                printf("%d ", percorso_trovato[z]);
            }
            else
                printf("%d", percorso_trovato[z]);
            z--;
        }
        printf("\n");
    }
    else if(trovato_percorso == false){
        printf("nessun percorso\n");
    }
}


int main() {

    bool com_nullo = true;
    char c;
    char comando[20] = {'\0'};
    char tmp_distanza[32] = {'\0'};
    char tmp_num_macchine[32] = {'\0'};
    char tmp_autonomia[32] = {'\0'};
    int automia;
    int autonomie[512] = {'\0'};
    int max_autonomia = 0;
    int  num_macchine = 0;
    int distanza;
    int i = 0;
    int j = 0;
    int z ;

    Stazione *hash_table[TABLE_SIZE];
    int stazione_partenza;
    int stazione_finale;
    root = NULL;

    init_hash_table(hash_table);

    while(true){

        if( com_nullo == true){
            i = 0;
        }

        c = getchar_unlocked();
        if(c != '\n') {
            comando[i] = c;
            com_nullo = false;
        }

        if (strcmp(comando, "aggiungi-s") == 0) {
            memset(comando, 0, sizeof comando);
            memset(tmp_num_macchine, 0, sizeof tmp_num_macchine);
            memset(autonomie, 0, sizeof autonomie);
            memset(tmp_distanza, 0, sizeof tmp_distanza);
            memset(tmp_autonomia,0,sizeof tmp_autonomia);
            com_nullo = true;
            max_autonomia = 0;
            while (c != ' ') {
                c = getchar_unlocked();
            }
            c = getchar_unlocked();

            while (c != ' ') {
                tmp_distanza[j] = c;
                j++;
                c = getchar_unlocked();
                if (c == '\n') {
                    break;
                }
            }
            distanza = atoi(tmp_distanza);
            c = getchar_unlocked();
            j = 0;
            while (c != ' ') {
                tmp_num_macchine[j] = c;
                j++;
                c = getchar_unlocked();
                if (c == '\n' || c == '\377' || c == -1) {
                    break;
                }
            }
            num_macchine = atoi(tmp_num_macchine);

            if (num_macchine == 0) {
                z = 0;
                autonomie[z] = -2;
                memset(tmp_autonomia, 0, sizeof(tmp_autonomia));
                i = 0;
                j = 0;

                aggiungi_stazione(hash_table, distanza, num_macchine, autonomie, max_autonomia);
            } else{
                j = 0;
                z = 0;
                c = getchar_unlocked();

                while (c != '\n' && c != EOF) {
                    if (c != ' ') {
                        tmp_autonomia[j] = c;
                        j++;
                    } else if (c == ' ') {
                        j = 0;
                        autonomie[z] = atoi(tmp_autonomia);
                        if (autonomie[z] > max_autonomia) {
                            max_autonomia = autonomie[z];
                        }
                        memset(tmp_autonomia, 0, sizeof(tmp_autonomia));
                        z++;
                    }
                    c = getchar_unlocked();
                }

                i = 0;
                j = 0;
                if (c == '\n' || c == '\377' || c == -1 ) {
                    autonomie[z] = atoi(tmp_autonomia);
                    if (autonomie[z] > max_autonomia) {
                        max_autonomia = autonomie[z];
                    }
                    z++;
                    autonomie[z] = -2;
                    memset(tmp_autonomia, 0, sizeof(tmp_autonomia));

                }
                aggiungi_stazione(hash_table, distanza, num_macchine, autonomie, max_autonomia);
            }
        }
        else if(strcmp(comando, "demolisci-stazione") == 0){
            memset(comando,0,sizeof comando);
            memset(tmp_distanza,0,sizeof tmp_distanza);

            com_nullo = true;
            c = getchar_unlocked();
            c = getchar_unlocked();
            j = 0;

            while ( c != '\n'){
                tmp_distanza[j] = c;
                j++;
                c = getchar_unlocked();
                if (c == '\n' || c == '\377' || c == -1) {
                    break;
                }
            }
            distanza = atoi(tmp_distanza);
            demolisci_stazione(hash_table,distanza);
            j = 0;
            i = 0;
        }
        else if(strcmp(comando, "aggiungi-auto") == 0){

            memset(comando,0,sizeof comando);
            memset(tmp_distanza,0,sizeof tmp_distanza);
            memset(tmp_autonomia,0,sizeof tmp_autonomia);

            com_nullo = true;

            c = getchar_unlocked();
            c = getchar_unlocked();

            j = 0;

            while ( c != ' ' ){
                tmp_distanza[j] = c;
                j++;
                c = getchar_unlocked();
                if( c == '\n'){
                    break;
                }
            }
            distanza = atoi(tmp_distanza);
            c = getchar_unlocked();
            j = 0;

            while ( c != '\n' ){
                tmp_autonomia[j] = c;
                j++;
                c = getchar_unlocked();
                if (c == '\n' || c == '\377' || c == -1) {
                    break;
                }
            }
            automia = atoi(tmp_autonomia);
            aggiungi_auto(hash_table,distanza,automia);
            j = 0;
            z = 0;
        }
        else if(strcmp(comando, "rottama-auto") == 0){
            c = getchar_unlocked();
            c = getchar_unlocked();
            com_nullo = true;
            memset(comando,0,sizeof comando);
            memset(tmp_distanza,0,sizeof tmp_distanza);
            memset(tmp_autonomia,0,sizeof tmp_autonomia);

            while ( c != ' ' ){
                tmp_distanza[j] = c;
                j++;
                c = getchar_unlocked();
                if( c == '\n'){
                    break;
                }
            }
            distanza = atoi(tmp_distanza);
            c = getchar_unlocked();
            j = 0;

            while ( c != '\n' ){
                tmp_autonomia[j] = c;
                j++;
                c = getchar_unlocked();
                if (c == '\n' || c == '\377' || c == -1) {
                    break;
                }
            }
            automia = atoi(tmp_autonomia);
            rottama_auto(hash_table,distanza,automia);
            j = 0;
            z = 0;
            i = 0;

        }
        else if(strcmp(comando, "pianifica-percorso") == 0){

            memset(comando,0,sizeof comando);
            com_nullo = true;

            c = getchar_unlocked();
            c = getchar_unlocked();
            memset(tmp_distanza,0,sizeof tmp_distanza);

            while ( c != ' ' ){
                tmp_distanza[j] = c;
                j++;
                c = getchar_unlocked();
                if( c == '\n'){
                    break;
                }
            }
            stazione_partenza = atoi(tmp_distanza);
            c = getchar_unlocked();
            j = 0;

            memset(tmp_distanza,0,sizeof tmp_distanza);


            while ( c != '\n' ){
                tmp_distanza[j] = c;
                j++;
                c = getchar_unlocked();
                if (c == '\n' || c == '\377' || c == -1) {
                    break;
                }
            }
            stazione_finale = atoi(tmp_distanza);
            bool calcola_percorso = false;
            calcola_percorso = controlla_inizio_fine(stazione_partenza,stazione_finale,hash_table);
            if(calcola_percorso == true){
                if(stazione_finale > stazione_partenza) {
                    pianifica_percorso_crescente(root, stazione_partenza, stazione_finale, hash_table);
                }
                else if(stazione_finale < stazione_partenza){
                    pianifica_percorso_decrescente(root,stazione_partenza,stazione_finale,hash_table);
                }
                else if( stazione_partenza == stazione_finale){
                    printf("%d\n",stazione_partenza);
                }

            }
            else{
                printf("nessun percorso\n");
            }
            j = 0;
            z = 0;
        }

        if(c==EOF){
            break;
        }
        i++;
    }
    return 0;
}

