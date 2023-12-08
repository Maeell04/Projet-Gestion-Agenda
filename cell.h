#ifndef STRUCT_PRODUCT
#define STRUCT_PRODUCT

/*----------------------------------------------------------------------------*/
//Structure

typedef struct s_d_cell
{
    int value;
    int levels;
    struct s_d_cell** nexts;
} t_d_cell;

typedef struct s_d_list
{
    t_d_cell** heads;
    int max_level;
} t_d_list;

typedef struct rendezvous
{
    int jour, mois, année;
    int Dheure, Dminute;
    int duréeH, duréeM;
}rendezvous;

typedef struct cellrdv
{
    rendezvous rdv;
    struct cellrdv* next;

}cellrdv;

typedef struct contact
{
    char* nom_prenom;
    cellrdv* rdv

}contacts;


typedef struct s_c_cell
{
    contacts fiche;
    struct s_c_cell** nexts;
} t_c_cell;

typedef struct listcontact
{
    contacts** heads;
}listcontact;


/*----------------------------------------------------------------------------*/
//Prototype

t_d_cell* CreateCell(int, int);
t_d_list CreateEmptyList(int);
int isEmptyList(t_d_list);

void insertHeadCell(t_d_list* list, int val, int levels);
void insertCell(t_d_list* l, int val, int levels);

void displayAlignedList(t_d_list list);
void displayListLevel(t_d_list lst, int level);
void displayAlignedList(t_d_list list);

int searchValue(t_d_list list,int val);
int Dicotomie_searchValue(t_d_list l, int val, t_d_cell* cell, int lev);

t_d_list CreateListNvalue(int n);
int* CreateTab(int n);



char *scanString(void);

t_c_cell * CreateContact();
listcontact CreateEmptyContactList();
cellrdv* Creerdv(int jour, int mois, int année, int minute, int heure, int duréeH, int duréeM );
void InsertRdv(cellrdv* rdv, t_c_cell* contact);
void displayRDV(t_c_cell* contact);


#endif