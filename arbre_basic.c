#include <stdlib.h>
#include <stdio.h>

typedef struct noeud
{
    int val;
    struct noeud *fd;
    struct noeud *fg;
} noeud;

typedef noeud arbre;

void affichageNoeud(arbre *tete)
{
    printf("%d", tete->val);
}

// pour l'affichage r=racine d=droite g=gauche
void affichageArbre(arbre *racine, char caaa)
{
    if (racine != NULL)
    {
        printf("%c __%d__", caaa, racine->val);
        affichageArbre(racine->fg, 'g');
        affichageArbre(racine->fd, 'd');
    }
}

void infixe(arbre *arbre)
{
    if (arbre != NULL)
    {
        infixe(arbre->fg);
        printf("__%d__", arbre->val);
        infixe(arbre->fd);
    }
}

int TailleArbre(arbre *racine)
{
    if (racine == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + TailleArbre(racine->fd) + TailleArbre(racine->fg);
    }
}

arbre *CreationNoeud(int val)
{
    arbre *new = malloc(sizeof(arbre));
    new->val = val;
    new->fd = new->fg = NULL;
    return new;
}

arbre *AjoutArbre(arbre *racine, int val)
{
    if (racine == NULL)
    {
        racine = CreationNoeud(val);
        return racine;
    }
    else
    {
        if (TailleArbre(racine->fg) < TailleArbre(racine->fd))
        {
            if (racine->fg == NULL)
            {
                racine->fg = CreationNoeud(val);
                return racine;
            }
            else
            {
                AjoutArbre(racine->fg, val);
            }
        }
        else
        {
            if (racine->fd == NULL)
            {
                racine->fd = CreationNoeud(val);
                return racine;
            }
            else
            {
                AjoutArbre(racine->fd, val);
            }
        }
    }
}

void DetruireArbre(arbre *tete)
{
    if (tete == NULL)
    {
        return;
    }
    else
    {
        DetruireArbre(tete->fg);
        DetruireArbre(tete->fd);
        free(tete);
    }
}

arbre *CreationABR(arbre *ABR, int val)
{
    if (ABR == NULL)
    {
        ABR = CreationNoeud(val);
        return ABR;
    }
    else
    {
        if (val < ABR->val)
        {
            if (ABR->fg == NULL)
            {
                ABR->fg = CreationNoeud(val);
                return ABR;
            }
            else
            {
                CreationABR(ABR->fg, val);
            }
        }
        else
        {
            if (ABR->fd == NULL)
            {
                ABR->fd = CreationNoeud(val);
                return ABR;
            }
            else
            {
                CreationABR(ABR->fd, val);
            }
        }
    }
}

arbre *TransoformationABR(arbre *arbre01, arbre *ABR)
{
    if (arbre01 != NULL)
    {
        ABR = CreationABR(ABR, arbre01->val);
        if (arbre01->fg != NULL)
            TransoformationABR(arbre01->fg, ABR);
        if (arbre01->fd)
            TransoformationABR(arbre01->fd, ABR);
    }

    return ABR;
}

void ChercherValABR(arbre *ABR, int val)
{
    if (ABR == NULL)
    {
        printf("ABR vide");
    }
    else
    {
        if (val == ABR->val)
        {
            printf("---%d", val);
        }
        if (val < ABR->val)
        {

            ChercherValABR(ABR->fg, val);
        }
        else if (val > ABR->val)
        {

            ChercherValABR(ABR->fd, val);
        }
    }
}

int main()
{
    arbre *temp = NULL;
    arbre *tem = NULL;

    temp = AjoutArbre(temp, 5);
    temp = AjoutArbre(temp, 4);
    temp = AjoutArbre(temp, 6);
    temp = AjoutArbre(temp, 9);
    printf("affiche de l'arbre binaire \n");
    affichageArbre(temp, 'r');

    tem = TransoformationABR(temp, tem);

    printf("\naffiche ABR \n");
    affichageArbre(tem, 'r');

    printf("\naffiche ABR decroissant \n");
    infixe(tem);

    DetruireArbre(temp);
    DetruireArbre(tem);
    return 0;
}
