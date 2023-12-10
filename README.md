# Projet-Gestion-Agenda

Partie I et II :
Fonctions réalisées :
Création de cellule (t_d_cell *CreateCell(int value, int levels))
Création d’une liste à niveau vide (t_d_list CreateEmptyList(int max_level))
Insertion d’une cellule à niveau en tête de liste (void insertHeadCell(t_d_list* list, int val, int levels))
Afficher l’ensembles des cellules de la liste pour un niveau donné (void displayListLevel(t_d_list list, int niveau))
Afficher tous les niveaux de la liste en alignant les cellules (void displayAlignedList(t_d_list list))
Insérer une cellule à niveau dans la liste, au bon endroit (void insertCell(t_d_list *l, int val, int levels))
Fonction de calcul du temps d'exécution pour un nombre de recherches (void CalculTimer())
Création d’une liste à n niveaux (t_d_list CreateListNvalue(int n))

Partie III :
Fonctions réalisées :
Création des structures (rendez-vous, contacts, …)
Fonction pour les saisies utilisateurs (scanString)
Création d’un contact (t_c_cell * CreateContact())

Fonctions à finaliser :
Création d’un rendez-vous (cellrdv* Createrdv())
Insertion d’un rendez-vous pour un contact (void InsertRdv(contacts* x))
Affichage des rendez-vous d’un contact (void displayRDV(t_c_cell* contact))
Affichage du menu (PrintMenu)

Fonctions à créer :
Recherche d’un contact
Suppression d’un rendez-vous
Sauvegarder le fichier de tous les rendez-vous
Charger un fichier de rendez-vous
