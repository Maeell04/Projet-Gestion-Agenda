#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <math.h>
#include "cell.h"
#include "timer.h"
#include "list.h"


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
//Recherche

int searchValue(t_d_list list,int val){
    if (isEmptyList(list) == 1) {
        //printf("Valeur non trouvée, la liste est vide\n");
    } else{
        t_d_cell *tmp = list.heads[0];//Recherche au niveau 0
        int find = 0;
        while ((tmp != NULL) && (find != 1)) {//Parcours du niveau 0 le temps que la valeur n'est pas trouvée
            if(tmp->value == val){
                find = 1;
                //printf("La valeur %d a ete trouvee\n", val);
                return find;
            }
            tmp = tmp->nexts[0];
        }
        //printf("La valeur %d n'a pas ete trouvee\n", val);
        return find;
    }
}

int Dicotomie_searchValue(t_d_list l, int val, t_d_cell* cell, int lev){
    startTimer();
    while(cell!=NULL){
        if(cell->value==val){
            //printf("La valeur %d a ete trouvee\n", val);
            return 1;
        }
        if(cell->value < val) {
            if(cell->nexts[lev]==NULL){
                if(lev==0){
                    //printf("La valeur %d n'a pas ete trouvee", val);
                    return 0;
                }else{
                    return Dicotomie_searchValue(l, val, cell->nexts[lev-1],lev-1);
                }
            }else{
                if(cell->nexts[lev]->value>val){
                    if(lev==0){
                        //printf("La valeur %d n'a pas ete trouvee", val);
                        return 0;
                    }else{
                        return Dicotomie_searchValue(l, val, cell->nexts[lev-1], lev-1);
                    }
                }
            }
        }
        if (cell->value > val) {
            if(lev==0){
                //printf("La valeur %d n'a pas ete trouvee", val);
                return 0;
            }
            lev--;
            return Dicotomie_searchValue(l, val, l.heads[lev], lev);
        }
        cell = cell->nexts[lev];
    }
    if(lev==0){
        //printf("La valeur %d n'a pas ete trouvee", val);
        return 0;
    }
    return Dicotomie_searchValue(l, val, l.heads[lev-1], lev-1);
}

/*----------------------------------------------------------------------------*/
//Affichage

void displayList(t_d_list list) {
    for (int i = 0; i < list.max_level; i++) {//Parcours du niveau 0 au niveau max
        if (list.heads[i] == NULL) {//Liste vide
            printf("[list head_%d @-]--> NULL\n", i);
        } else{
            t_d_cell *tmp = list.heads[i];
            printf("[list head_%d @-]-->", i);//Début affichage avec le niveau i
            while (tmp != NULL) {
                printf("[ %d|@-]-->", tmp->value);//Affichage des valeurs au niveau i
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
    //Parcours de la liste au niveau 0 et i pour effectuer des comparaisons et detecter les décalages
    t_d_cell *tmp = list.heads[0];
    t_d_cell *cell = list.heads[niveau];
    while (tmp != NULL){
        if (tmp == cell){
            printf("-->[%d|@-]",cell->value);//Affichage des valeurs
            cell = cell->nexts[niveau];
        }
        else{
            if (tmp->value < 10)
                printf("---------");//Création des décalages
            else
                printf("----------");//Création des décalages
        }
        tmp = tmp->nexts[0];
    }
    printf("-->NULL\n");
}

void displayAlignedList(t_d_list list) {
    for(int i =0;i<list.max_level;i++){//Utilisation de la fonction précedente avec tout les niveaux pour l'affichage
        displayListLevel(list, i);
    }
}

/*----------------------------------------------------------------------------*/
//Creation de grande liste

int* CreateTab(int n) {
    uint32_t x = (uint32_t)(pow(2, n) - 1);
    int *tab = (int*)malloc(x * sizeof(int));
    if (tab == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }
    for (uint32_t i = 0; i < x; i++) {
        tab[i] = 0;
    }
    for (uint32_t i = 1; i < n; i++) {
        uint32_t z = (uint32_t)(pow(2, i));
        for (uint32_t j = z - 1; j < x; j += z) {
            tab[j]++;
        }
    }
    return tab;
}

t_d_list CreateListNvalue(int n) {
    int *tab = CreateTab(n);
    uint32_t x = (uint32_t)(pow(2, n) - 1);
    t_d_list l = CreateEmptyList(n);
    for (int i = n - 1; i >= 0; i--) {
        for (uint32_t j = 0; j < x; j++) {
            if (tab[j] == i) {
                insertCell(&l, j + 1, i + 1);
            }
        }
    }
    return l;
}

/*----------------------------------------------------------------------------*/
//Creation de liste avec contact

listcontact CreateEmptyContactList(){
    listcontact list;
    list.heads = (t_c_cell**)malloc(4* sizeof(t_c_cell*));
    for(int i = 3; i>=0; i--){
        list.heads[i]= NULL;
    }
    return(list);
}