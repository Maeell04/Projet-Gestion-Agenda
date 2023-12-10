#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <math.h>
#include "cell.h"
#include "timer.h"
#include "list.h"

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



/*----------------------------------------------------------------------------*/
//Saisie

char *scanString(void) {
    char string[100];
    printf("Veuillez saisir l'objet du rdv : ");
    gets(string);//Utilisation de gets pour les saisies avec espaces
    printf("%s \n",string);
    return string;
}

/*----------------------------------------------------------------------------*/

cellrdv* Createrdv(){
    //On demande toutes les informations nécessaire à la création de notre rdv
    int jour = 0, mois = 0, annee = 0;
    printf("Veuillez saisir la date du rdv (format : jour/mois/annee)\n");
    scanf("%d/%d/%d", &jour, &mois, &annee);

    int heure = 0, minute;
    printf("Veuillez saisir l'heure du rdv (format : heure:minute)\n");
    scanf("%d:%d", &heure, &minute);

    int dureeH = 0, dureeM;
    printf("Veuillez saisir la duree du rdv (format : heure:minute)\n");
    scanf("%d:%d", &dureeH, &dureeM);

    /*char string[100];
    printf("Veuillez saisir l'objet du rdv : ");
    gets(string);
    printf("%s voila",string);*/

    //Création du rdv en remplissant tous les champs
    cellrdv* rdv = (cellrdv*)malloc(sizeof(cellrdv));
    rdv->next=NULL;
    rdv->rdv.jour = jour;
    rdv->rdv.mois = mois;
    rdv->rdv.annee = annee;
    rdv->rdv.heure = heure;
    rdv->rdv.minute = minute;
    rdv->rdv.dureeH = dureeH;
    rdv->rdv.dureeM = dureeM;
    rdv->rdv.objet = "Vide";

    return rdv;
}

void InsertRdv(contacts* x){
    cellrdv* nouv = Createrdv();
    if(x->rdv == NULL){
        x->rdv = nouv;
        return;
    }
    cellrdv* cur = x->rdv;
    cellrdv* prev = cur;

    while((cur->rdv.heure < nouv->rdv.heure) && (cur->rdv.heure < nouv->rdv.heure)){//Vérification de l'emplacement pour l'heure
        prev = cur;
        cur = cur->next;
    }
    prev->next = nouv;
    nouv->next = cur;
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






