#include <stdio.h>
#include <malloc.h>
#include "pvm3.h"
#include "point.h"

struct st_pb {
	point *gauche, *droite;
	int type;
	int nbPointsGauche;
	int nbPointsDroite;
};

typedef struct st_pb pb_t;

/*
 * copie N entiers de src vers dst
 */
void copy_int(dst, src, n)
int *dst, *src, n;
{
	int i;
	
	for (i=0;i<n; i++) dst[i] = src[i];
}

//Un problème est soit un problème de calcul d'enveloppe de 4 points 
//soit un problème de tri d'enveloppe convexe (on ne fusionne pas deux enveloppes si elles ne sont pas adjacentes)

/*
 * (de)allocation d'un probleme
 */
pb_env *pb_alloc()
{
	pb_t *pb;

	pb = (pb_t *)malloc(sizeof(pb_t));
	pb->taille1 = pb->taille2 = pb->type = 0;
	pb->data1 = pb->data2 = NULL;

	return pb;
}

void pb_free(pb)
pb_t *pb;
{
	if (pb->data1) free(pb->data1);
	if (pb->data2) free(pb->data2);
	free(pb);
}

void send_pb(int tid, pb_t *pb){
    pvm_initsend(PvmDataDefault);
    pvm_pkint(&(pb->nbPointsGauche), 1, 1);
    pvm_pkint(&(pb->nbPointsGauche), 1, 1);
    pvm_pkint(&(pb->type), 1, 1);
    for(point *p = pb->gauche; p != null; p = p->next){
        pvm_pkint(&(p->x), 1, 1);
        pvm_pkint(&(p->y), 1, 1);
    }
    for(point *p = pb->droite; p != null; p = p->next){
        pvm_pkint(&(p->x), 1, 1);
        pvm_pkint(&(p->y), 1, 1);
    }
}

pb_t *receive_pb(int tid, int *sender){

}