#include "mobilidade.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Criar nova Mobilidade
Mobilidade* criarmobilidade(Mobilidade* inicio, int cod, char tipo[], char geocodigo[], float bat, float aut) 
{
 if(!existeMobilidade(inicio, cod))
 {Mobilidade * novo = malloc(sizeof(struct meio));
  if (novo != NULL)
  {novo->codigo = cod;
   strcpy(novo->tipo,tipo);
   strcpy(novo->geocodigo,geocodigo);
   novo->bateria = bat;
   novo->autonomia = aut;
   novo->seguinte = inicio;
   return (novo);
  } 
 } else return(inicio);
}

// Existe Mobilidade?
int existeMobilidade(Mobilidade* inicio, int cod)
{while(inicio!=NULL)
  {if (inicio->codigo == cod) return(1);
   inicio = inicio->seguinte;
  }
 return(0);
}

// Remover uma Mobilidade a partir do seu codogo
Mobilidade* remover_mobilidade(Mobilidade* inicio, int cod) 
{
 Mobilidade *anterior=inicio, *atual=inicio, *aux;

 if (atual==NULL) return(NULL);
 else if (atual-> codigo == cod) // remove o 1º registo
 {aux = atual->seguinte;
  free(atual);
  return(aux);
 }
 else
 {while ((atual!=NULL)&&(atual->codigo!=cod)) 
  {anterior = atual;
   atual = atual->seguinte;
  }
  if (atual==NULL) return(inicio);
  else
  {anterior->seguinte = atual->seguinte;
   free(atual);
   return(inicio);
  }
 }
}

// listar na consola o conteúdo da lista ligada de Mobilidades
void listarMobilidades(Mobilidade * inicio)
{while (inicio != NULL)
 {
    printf("CODIGO:%d; TIPO:%s; GEOCODIGO:%s; BATERIA:%.2f; AUTONOMIA:%.2f\n",inicio->codigo, inicio->tipo, inicio->geocodigo, inicio->bateria, inicio->autonomia);
    inicio = inicio->seguinte;
 }
}

// Ler Mobilidades
Mobilidade * lerMobilidades()
{
    FILE* fp;
    int cod;
    char tipo[50], geocodigo[50];
    float bat, aut;
    Mobilidade* aux = NULL;

    fp = fopen("mobilidades.txt", "r");
    if (fp != NULL) 
    {while (!feof(fp))
     { fscanf(fp, "%d;%[^\n]s;%[^\n]s;%f;%f\n", &cod, tipo, geocodigo, &bat, &aut);
       aux = criarmobilidade(aux, cod, tipo, geocodigo, bat, aut);
     }
        fclose(fp);
    }
    return(aux);
}

//Guardar Mobilidade
int guardarMobilidade(Mobilidade* inicio)
{FILE* fp;
 fp = fopen("mobilidades.txt","w");
 if (fp!=NULL)
 {
 Mobilidade* aux = inicio;
 while (aux != NULL)
 {
  fprintf(fp,"CODIGO:%d; TIPO:%s; GEOCODIGO:%s; BATERIA:%.2f; AUTONOMIA:%.2f\n", aux->codigo, aux->tipo, aux->geocodigo, aux->bateria, aux->autonomia);
  aux = aux->seguinte;
 }
 fclose(fp);
 return(1);
 }
 else return(0);
}

int guardarMobilidade_Bin(Mobilidade *inicio)
{
    FILE *fp;
    fp = fopen("mobilidades.bin", "wb");
    if (fp != NULL)
    {
        Mobilidade *aux = inicio;
        while (aux != NULL)
        {
            fwrite(aux, sizeof(Mobilidade), 1, fp);
            aux = aux->seguinte;
        }
        fclose(fp);
        return (1);
    }
    return (0);
}


Mobilidade* listarMobilidadesPorGeocodigo(Mobilidade* inicio, char geocodigo[])
{
    Mobilidade* atual = inicio;

    while (atual != NULL)
    {
        if (strcmp(atual->geocodigo, geocodigo) == 0)
        {
            printf("Codigo: %d; Tipo: %s; Geocodigo: %s; Bateria: %.2f; Autonomia: %.2f\n",
                   atual->codigo, atual->tipo, atual->geocodigo, atual->bateria, atual->autonomia);
        }
        atual = atual->seguinte;
    }

    return (inicio);
}