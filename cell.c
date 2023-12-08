#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cell.h"
#include "timer.h"

/*----------------------------------------------------------------------------*/
//Creation

t_d_cell *CreateCell(int value, int levels){
    t_d_cell* cell= (t_d_cell*)malloc(sizeof(t_d_cell));
    cell->nexts = (t_d_cell**)malloc(levels* sizeof(t_d_cell*));
    for(int i = levels-1; i>=0; i--){
        cell->nexts[i]= NULL;
    }
    cell->levels = levels;
    cell->value = value;
    return(cell);
}

t_d_list CreateEmptyList(int max_level){
    t_d_list list;
    list.heads = (t_d_cell**)malloc(max_level* sizeof(t_d_cell*));
    for(int i = 0; i<max_level; i++){
        list.heads[i]= NULL;
    }
    list.max_level = max_level;
    return(list);
}

int isEmptyList(t_d_list list){
    if(list.heads[0]==NULL){
        return 1;
    }
    return 0;
}

/*----------------------------------------------------------------------------*/
//Insertion

void insertHeadCell(t_d_list* list, int val, int levels){
    if(levels> list->max_level){
        printf("Erreur: niveau cellule superieur au niveau max de la liste");
        return;
    }
    t_d_cell * cell = CreateCell(val, levels);
    if((isEmptyList(*list))==1) {
        for (int i = levels - 1; i >= 0; i--) {
            list->heads[i] = cell;
        }
        return;
    }
    for (int i = levels - 1; i >= 0; i--) {
        cell->nexts[i]= list->heads[i];
        list->heads[i]= cell;
    }

    return;
}

void insertCell(t_d_list *l, int val, int levels){
    if(levels>l->max_level){
        printf("impossible");
        return;
    }
    if(isEmptyList(*l)==1){
        insertHeadCell(l,val, levels);
        return;
    }else {
        t_d_cell *cell = CreateCell(val, levels);
        for (int i = levels-1; i >= 0; i--) {
            if (l->heads[i] == NULL) {
                l->heads[i] = cell;
            } else {
                if (val <= l->heads[i]->value) {
                    cell->nexts[i] = l->heads[i];
                    l->heads[i] = cell;
                }else{
                    t_d_cell * cur = l->heads[i];
                    int z = 0;
                    while(cur!=NULL&&z!=1){
                        if(cur->value<=val &&(cur->nexts[i]==NULL||cur->nexts[i]->value>val)){
                            cell->nexts[i]= cur->nexts[i];
                            cur->nexts[i] = cell;
                            z=1;
                        }
                        cur = cur->nexts[i];
                    }
                }
            }
        }
    }
    return;
}

/*----------------------------------------------------------------------------*/
//Recherche

int searchValue(t_d_list list,int val){
    if (isEmptyList(list) == 1) {
        printf("Valeur non trouvée, la liste est vide\n");
    } else{
        t_d_cell *tmp = list.heads[0];
        int find = 0;
        while ((tmp != NULL) && (find != 1)) {
            if(tmp->value == val){
                find = 1;
                printf("La valeur %d a ete trouvee\n", val);
                return find;
            }
            tmp = tmp->nexts[0];
        }
        printf("La valeur %d n'a pas ete trouvee\n", val);
        return find;
    }
}

int Dicotomie_searchValue(t_d_list l, int val, t_d_cell* cell, int lev){
    startTimer();
    while(cell!=NULL){
        if(cell->value==val){
            printf("La valeur %d a ete trouvee\n", val);
            return 1;
        }
        if(cell->value < val) {
            if(cell->nexts[lev]==NULL){
                if(lev==0){
                    printf("La valeur %d n'a pas ete trouvee", val);
                    return 0;
                }else{
                    return Dicotomie_searchValue(l, val, cell->nexts[lev-1],lev-1);
                }
            }else{
                if(cell->nexts[lev]->value>val){
                    if(lev==0){
                        printf("La valeur %d n'a pas ete trouvee", val);
                        return 0;
                    }else{
                        return Dicotomie_searchValue(l, val, cell->nexts[lev-1], lev-1);
                    }
                }
            }
        }
        if (cell->value > val) {
            if(lev==0){
                printf("La valeur %d n'a pas ete trouvee", val);
                return 0;
            }
            lev--;
            return Dicotomie_searchValue(l, val, l.heads[lev], lev);
        }
        cell = cell->nexts[lev];
    }
    if(lev==0){
        printf("La valeur %d n'a pas ete trouvee", val);
        return 0;
    }
    return Dicotomie_searchValue(l, val, l.heads[lev-1], lev-1);
}

/*----------------------------------------------------------------------------*/
//Affichage

void displayList(t_d_list list) {
    for (int i = 0; i < list.max_level; i++) {
        if (list.heads[i] == NULL) {
            printf("[list head_%d @-]--> NULL\n", i);
        } else{
            t_d_cell *tmp = list.heads[i];
            printf("[list head_%d @-]-->", i);
            while (tmp != NULL) {
                printf("[ %d|@-]-->", tmp->value);
                tmp = tmp->nexts[i];
            }
            printf("NULL\n");
        }
    }return;

}

void displayListLevel(t_d_list list, int niveau){
    if (niveau >= list.max_level){
        printf("Erreur: niveau cellule superieur au niveau max de la liste");
        return;
    }
    printf("[list head_%d @-]", niveau);
    t_d_cell *tmp = list.heads[0];
    t_d_cell *cell = list.heads[niveau];
    while (tmp != NULL){
        if (tmp == cell){
            printf("-->[%d|@-]",cell->value);
            cell = cell->nexts[niveau];
        }
        else{
            if (tmp->value < 10)
                printf("---------");
            else
                printf("----------");
        }
        tmp = tmp->nexts[0];
    }
    printf("-->NULL\n");
}

void displayAlignedList(t_d_list list) {
    for(int i =0;i<list.max_level;i++){
        displayListLevel(list, i);
    }
}

/*----------------------------------------------------------------------------*/
//Creation de grande liste

int* CreateTab(int n){
    int x = pow(2,n)-1;
    int *tab = malloc(x*sizeof(int));

    for(int i =0; i<x;i++){
        tab[i]=0;
    }
    for(int i=1; i<n;i++ ){
        int z = pow(2,i);
        for(int j=z-1; j<x; j+=z){
            tab[j]++;
        }
    }


    return (tab);
}


t_d_list CreateListNvalue(int n){
    int* tab = CreateTab(n);
    int x = pow(2,n)-1;
    t_d_list l = CreateEmptyList(n);
    for(int i = n-1 ; i>=0; i--){
        for(int j = 0; j< x; j++){
            if(tab[j]==i){
                insertCell(&l,j+1,i+1);
            }
        }
    }
    return l;

}

/*----------------------------------------------------------------------------*/
//Saisie

char *scanString(void){
    char string[100];
    gets(string);
    return string;
}

/*----------------------------------------------------------------------------*/
//Creation de contact

t_c_cell * CreateContact(){
    t_c_cell* cell = (t_c_cell*)malloc(sizeof(t_c_cell));
    cell->nexts = (t_c_cell**)malloc(4*sizeof(t_c_cell*));
    for(int i = 3; i<=0; i--){
        cell->nexts[i]= NULL;
    }
    contacts newcontact;
    printf("Veuillez saisir votre nom-prenom sous la forme nom_prenom:");
    newcontact.nom_prenom = (char*)malloc(20*sizeof(char));
    gets(newcontact.nom_prenom);
    newcontact.rdv = NULL;
    cell->fiche = newcontact;
    return cell;
}

listcontact CreateEmptyContactList(){
    listcontact list;
    list.heads = (t_c_cell**)malloc(4* sizeof(t_c_cell*));
    for(int i = 3; i>=0; i--){
        list.heads[i]= NULL;
    }
    return(list);
}

cellrdv* Creerdv(int jour, int mois, int année, int minute, int heure, int duréeH, int duréeM ){
    cellrdv* rdv = (cellrdv*)malloc(sizeof(cellrdv));
    rdv->next=NULL;
    rdv->rdv.année = année;
    rdv->rdv.duréeH = duréeH;
    rdv->rdv.duréeM = duréeM;
    rdv->rdv.Dheure = heure;
    rdv->rdv.jour = jour;
    rdv->rdv.Dminute = minute;
    rdv->rdv.mois = mois;
    return rdv;

}

void InsertRdv(cellrdv* rdv, t_c_cell* contact){
    cellrdv* tmp = contact->fiche.rdv;
    while(tmp->next!=NULL){
        tmp = tmp->next;
    }
    tmp->next = rdv;
    return;

}

void displayRDV(t_c_cell* contact){
    printf("[%s]",contact->fiche.nom_prenom);
    if(contact->fiche.rdv==NULL){
        printf("---->Aucun RDV");
    }else{
        cellrdv *tmp = contact->fiche.rdv;
        while(tmp!=NULL){
            printf("[Date : %d/ %d/ %d/ %d: %d Durée ");
        }
    }
    return;
}






