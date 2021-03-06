/**
 * @file action.c
 * @author Paul BONHOMME & Rime LAMRANI (paul.bonhomme@etu.uca.fr & rime.lamrani@etu.uca.fr)
 * @brief fichier .c : fonctions de base pour les actions
 * @version 0.1
 * @date 2022-02-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "action.h"

/* --------------------------------------------------------------------
ListeAction_t : Initialise une liste
 
En entrée: void

En sortie: 

 -------------------------------------------------------------------- */
ListeAction_t initAction(void)
{
    return NULL;
}

/* --------------------------------------------------------------------
videListeAction : Vérifie si une liste est vide
 
En entrée: 
    ListeAction_t liste : la liste d'actions

En sortie: un Boolen, vrai si la liste est vide, faux sinon

 -------------------------------------------------------------------- */
Boolen_t videListeAction(ListeAction_t liste)
{
    Boolen_t resultat = faux;

    if(liste==NULL)
        resultat = vrai;

    return resultat;
}

/* --------------------------------------------------------------------
teteAction : Renvoie le premier maillon de la liste
 
En entrée: 
    ListeAction_t liste : la liste des actions

En sortie: la première action de la liste, sinon exit

 -------------------------------------------------------------------- */
Action_t teteAction(ListeAction_t liste)
{

    if(videListeAction(liste))
    {
        printf("Opération interdite\n");
        exit(1);
    }
    else
    {
        return (liste->action);
    }
}

/* --------------------------------------------------------------------
insererEnTeteAction : Insère une nouvelle action en tête de la liste
 
En entrée: 
    ListeAction_t liste : la liste des actions; 
    Action_t      a : l'action à inserer;

En sortie: La liste avec l'élement en tête

 -------------------------------------------------------------------- */
ListeAction_t insererEnTeteAction(ListeAction_t liste, Action_t a)
{
    MaillonAction_t *act; // maillon dans lequel on va mettre l'action

    act=(MaillonAction_t*)malloc(sizeof(MaillonAction_t)); // allocation d'un maillon
    if (act==NULL)
    {
        printf("Probleme malloc\n");
        exit(1);
    }
    act->action = a; // mise à jour de l'action dans le maillon
    act->suiv=liste; // insertion en tête de la liste en faisant pointer le maillon sur la liste
    return act;
}

/* --------------------------------------------------------------------
insererAction : insère une action en fonction de l'heure et du jour
 
En entrée: 
    ListeAction_t liste : la liste des actions
    Action_t      a : l'action à inserer

En sortie: La liste avec l'élement inséré

 -------------------------------------------------------------------- */
ListeAction_t insererAction(ListeAction_t liste, Action_t a)
{
    Action_t a_aux;

    if(videListeAction(liste))
    {
        return insererEnTeteAction(liste, a); // si la liste est vide, on insère en tête
    }

    a_aux = teteAction(liste); // si la liste n'est pas vide on récupère la tête

    if(a_aux.jour > a.jour)
    {
        return insererEnTeteAction(liste, a); // si jour tete de liste superieure au jour de la semaine à inserer, on insère en tête
    }
    if(a_aux.jour == a.jour && strcmp(a_aux.heure, a.heure) > 0)
    {
        return insererEnTeteAction(liste, a);  // si heure tete de liste superieure à l'heure de la journée à inserer, on insère en tête
    }

    liste->suiv = insererAction(liste->suiv, a);
    return liste;
}

/* --------------------------------------------------------------------
afficherAction : Affiche une action
 
En entrée: 
    Action_t act : une action;

En sortie: void

 -------------------------------------------------------------------- */
void afficherAction(Action_t act)
{
    printf("\nNom de l\'action : %s\nJour : %d\t Heure : %s\n",act.nom, act.jour, act.heure);
}

/* --------------------------------------------------------------------
afficherListeActions : Affiche la liste des actions
 
En entrée: 
    ListeAction_t liste : la liste des actions;

En sortie: void

 -------------------------------------------------------------------- */
void afficherListeActions(ListeAction_t liste)
{
    printf("\n------Liste des actions------\n");
    while(!videListeAction(liste))
    {
        afficherAction(liste->action);
        liste=liste->suiv;
    }
    printf("\n-----------------------------\n");
}

/* --------------------------------------------------------------------
sauvegarderAction : Ecrit les semaines et actions en ligne comme le fichier initial dans un fichier
 
En entrée: 
    File          * flot: fichier dans lequel ecrire
    ListeAction_t liste: la liste des actions
    char          * anneeSem : annee de la liste d'actions  numSem : numero de semaine de la liste d'actions

En sortie: void

 -------------------------------------------------------------------- */
void sauvegarderAction(FILE *flot, ListeAction_t liste, char* anneeSem, char* numSem)
{   
    if(videListeAction(liste)) // si la liste est vide
    {   
        return;
    }
    if(videListeAction(liste->suiv)) // si on se trouve sur le dernier maillon de la liste
    {
        fprintf(flot,"%s%s%d%s%s", anneeSem, numSem, (liste->action).jour,(liste->action).heure,(liste->action).nom);
    }
    else
    {
        fprintf(flot,"%s%s%d%s%s", anneeSem, numSem, (liste->action).jour,(liste->action).heure,(liste->action).nom);
        sauvegarderAction(flot, liste->suiv, anneeSem, numSem); // appel recursif sur le maillon suivant
    }
}

/* --------------------------------------------------------------------
rechAction : recherche une action selon l'heure et le jour
 
En entrée: 
    ListeAction_t liste : la liste des actions;
    int           jour : le jour de l'action à trouver
    char          heure[] : l'heure de l'action à trouver

En sortie: un Boolen, vrai si l'action existe, faux sinon

 -------------------------------------------------------------------- */
Boolen_t rechAction(ListeAction_t liste, int jour, char heure[])
{   
    Boolen_t resultat = faux;

    while(liste!=NULL)
    {
        if((liste->action).jour==jour && strcmp((liste->action).heure, heure) == 0)
        {
            resultat = vrai;
        }
        liste=liste->suiv;
    }
    return resultat;
}

/* --------------------------------------------------------------------
supprimerEnTeteAction : Supprime l'action en tête de la liste
 
En entrée: 
    ListeAction_t liste : la liste des actions

En sortie: La liste avec l'element supprimé

 -------------------------------------------------------------------- */
ListeAction_t supprimerEnTeteAction(ListeAction_t liste)
{
    MaillonAction_t *maillonActionTemp; // Maillon temporaire qui va permettre de supprimer la tête de liste 
    if(videListeAction(liste)) // si la liste est vide on ne peut rien supprimer, c'est un cas d'erreur
    {
        printf("Suppression d'une action sur une liste vide, operation interdite");
        exit(1);
    }
    maillonActionTemp = liste; // recuperation de l'action en tête de liste
    liste = liste->suiv; // on avance la liste sur le maillon suivant
    free(maillonActionTemp); // on libere le maillon en tete
    return liste;
}

/* --------------------------------------------------------------------
supprimerMaillonAction : Supprime l'action en fonction du jour et de l'heure
 
En entrée: 
    ListeAction_t liste : la liste des actions 
    int           jour : numero du jour ; 
    char          * heure : heure de l'action a supprimer 

En sortie: La liste avec l'element supprimé

 -------------------------------------------------------------------- */
ListeAction_t supprimerMaillonAction(ListeAction_t liste, int jour, char* heure)
{   
    Action_t actionTemp = teteAction(liste);

    if(videListeAction(liste)) // si la liste est vide, on retourne la liste
        return liste;
    if(actionTemp.jour > jour) // si le jour en tete est > au jour voulu -> action pas dans la liste
        return liste;
    if(actionTemp.jour == jour && strcmp(actionTemp.heure, heure) > 0) // si le jour en tete est = au jour voulu et l'heure > -> action pas dans la liste
        return liste;
    if(actionTemp.jour == jour && strcmp(actionTemp.heure, heure) == 0) // si la tete vaut l'action voulue
        return supprimerEnTeteAction(liste); // on la supprime

    liste->suiv=supprimerMaillonAction(liste->suiv, jour, heure); // appel recursif
    return liste;
}

/* --------------------------------------------------------------------
libererActions : libère toute la liste des actions en supprimant chaque maillon
 
En entrée: 
    ListeAction_t liste : la liste des actions

En sortie: void

 -------------------------------------------------------------------- */
void libererActions(ListeAction_t liste)
{

    while(!videListeAction(liste))
    {
        liste = supprimerEnTeteAction(liste);
    }
}