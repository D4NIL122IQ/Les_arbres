#include <stdio.h>
#include <stdlib.h>

typedef struct employe
{
    char nom[25], prenom[25];
    int age;
    char sexe;
    int nbrHrAssureJr[7];
} employe;

typedef struct noeud
{
    employe *personne;
    struct arbre *fd;
    struct arbre *fg;
} noeud;

typedef noeud arbre;

void affichage_info_prs(employe *prs)
{
    printf("\n-------- information employe ----------\n");
    printf("nom : %s\n", prs->nom);
    printf("prenom : %s\n", prs->prenom);
    printf("sexe : %c\n", prs->sexe);
    printf("nombre d'heure assure par jour\n");
    for (int i = 1; i <= 7; i++)
    {
        printf("| %d. %d ", i, prs->nbrHrAssureJr[i]);
    }
}

void affichageArbre(arbre *racine)
{
    if (racine != NULL)
    {
        affichage_info_prs(racine->personne);
        affichageArbre(racine->fg);
        affichageArbre(racine->fd);
    }
}

int TailleArbre(arbre *arbre)
{
    if (arbre == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + TailleArbre(arbre->fd) + TailleArbre(arbre->fg);
    }
}

void AffichageDecroissantABR(arbre *racine)
{
    if (racine != NULL)
    {

        AffichageDecroissantABR(racine->fd);
        affichage_info_prs(racine->personne);
        AffichageDecroissantABR(racine->fg);
    }
}

int CalcSalaireHebdo(int tab[7])
{
    int nbrH = 0;
    for (int i = 1; i <= 7; i++)
    {
        nbrH = nbrH + tab[i];
    }
    return nbrH * 1200;
}

employe *new_employe(employe *prs)
{
    employe *new = NULL;
    int i;
    new = malloc(sizeof(employe));
    if (new != NULL)
    {
        printf("nom : ");
        scanf("%s", new->nom);
        printf("prenom : ");
        scanf("%s", new->prenom);
        printf("sexe (M/F): ");
        scanf("%s", &new->sexe);
        printf("entrez le nombre d'heure assure par jour 1=dimanche jusqu'a 7=samedi\n");
        for (i = 1; i <= 7; i++)
        {
            printf("%d. ", i);
            scanf("%d", &new->nbrHrAssureJr[i]);
        }
    }
    return new;
}

arbre *NoveauNoeud(arbre *tete, employe *prs)
{
    arbre *temp = malloc(sizeof(arbre));
    temp->personne = prs;
    temp->fd = temp->fg = NULL;

    return temp;
}

arbre *AjoutArbreComplet(arbre *racine, employe *prs)
{
    if (racine == NULL)
    {
        arbre *temp = malloc(sizeof(arbre));
        temp->personne = prs;
        temp->fd = temp->fg = NULL;
        racine = temp;
        return racine;
    }
    else
    {
        if (TailleArbre(racine->fg) < TailleArbre(racine->fd))
        {
            if (racine->fg == NULL)
            {
                arbre *temp = malloc(sizeof(arbre));
                temp->personne = prs;
                temp->fd = temp->fg = NULL;
                racine->fg = temp;
                return racine;
            }
            else
            {
                AjoutArbreComplet(racine->fg, prs);
            }
        }
        else
        {
            if (racine->fd == NULL)
            {
                arbre *temp = malloc(sizeof(arbre));
                temp->personne = prs;
                temp->fd = temp->fg = NULL;
                racine->fd = temp;
                return racine;
            }
            else
            {
                AjoutArbreComplet(racine->fd, prs);
            }
        }
    }
}

int CalculWeekEnd(arbre *racine)
{
    if (racine != NULL)
    {
        if (racine->personne->nbrHrAssureJr[6] > 0 || racine->personne->nbrHrAssureJr[7] > 0)
        {
            return 1 + CalculWeekEnd(racine->fd) + CalculWeekEnd(racine->fg);
        }
        else
        {
            return CalculWeekEnd(racine->fd) + CalculWeekEnd(racine->fg);
        }
    }
    else
    {
        return 0;
    }
}

arbre *Insere(arbre *ABR, employe *prs)
{
    if (ABR == NULL)
    {
        ABR = NoveauNoeud(ABR, prs);
        return ABR;
    }
    else
    {
        if (CalcSalaireHebdo(prs->nbrHrAssureJr) < CalcSalaireHebdo(ABR->personne->nbrHrAssureJr))
        {
            if (ABR->fg == NULL)
            {
                ABR->fg = NoveauNoeud(ABR->fg, prs);
                return ABR;
            }
            else
            {
                Insere(ABR->fg, prs);
            }
        }
        else
        {
            if (ABR->fg == NULL)
            {
                ABR->fd = NoveauNoeud(ABR->fd, prs);
                return ABR;
            }
            else
            {
                Insere(ABR->fd, prs);
            }
        }
    }
}

arbre *CreerABR(arbre *ABR, arbre *racine)
{
    if (racine != NULL)
    {
        ABR = Insere(ABR, racine->personne);
        if (racine->fg != NULL)
            CreerABR(ABR, racine->fg);
        if (racine->fd != NULL)
            CreerABR(ABR, racine->fd);
    }
    return ABR;
}

int main()
{
    employe *new = NULL;
    arbre *racine = NULL;
    arbre *ABR = NULL;

    int rep = 1;
    printf("----------ENREGISTREMENT----------\n");
    while (rep == 1)
    {
        new = new_employe(new);

        racine = AjoutArbreComplet(racine, new);
        printf("\n pour continuer taper 1 sinon autre : ");
        scanf("%d", &rep);
    }
    affichageArbre(racine);

    printf("\nle nombre d'employer qui travaille le week-end :  %D\n", CalculWeekEnd(racine));

    CreerABR(ABR, racine);
    AffichageDecroissantABR(ABR);
    return 0;
}