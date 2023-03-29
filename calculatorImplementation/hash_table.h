#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <limits.h>

/* Programa no qual se implementa uma Tabela Hash cujo tratamento de colisões é Sondagem Linear */

// Elemento em si
typedef struct elemento
{
   char tipo[10];
   int valor;
   long chave;
   char nome[100];
}elem;

// Elemento na tabela hash
typedef struct elemento_tabela
{
   int sinal;
   elem *dados;
}elem_hash;

/* Definição de um tamanho para a tabela, uma quantidade máxima de posições e um ponteiro para a estrutura elemento_tabela*/
int tam = 0;
int max = 50;
elem_hash *vetor;

long Gera_chave(char name[100])
{
  long chave = 0;
  int carac_asc = 0;
  for (int e = 0; e < strlen(name); e++)
    {
      carac_asc = name[e];
      chave += carac_asc * pow(2, e);
    }
  return chave;
}

// Função utilizada para calcular o código hash do elemento
int Cod_hash(int chave)
{
  int ind = chave % max;
  return ind;
}


/* Função responsável por inicializar o vetor com posições nulas */
void hash_initialize()
{
  for (int e = 0; e < max; e++)
    {
      vetor[e].sinal = 0;
      vetor[e].dados = NULL;
    }

}

/* Função responsável por inserir um elemento*/
void hash_insert(char name[100], char type[10], int val)
{
  int index = Cod_hash(Gera_chave(name));
  
  int n_ind = index;
  
  elem *n_elem = malloc(sizeof(elem));
  n_elem -> valor = val;
  n_elem -> chave = Gera_chave(name);
  strncpy(n_elem -> nome, name, 100);
  strncpy(n_elem -> tipo, type, 10);

  while (vetor[n_ind].sinal == 1)
    {
      if (vetor[n_ind].dados -> chave == Gera_chave(name))
      {
        vetor[n_ind].dados -> valor = val;
        printf("\nChave já utilizada anteriormente. Valor foi atualizado\n");
        return;
      }

      n_ind = (n_ind + 1) % max;
      if (n_ind == index)
      {
        printf("\nTabela Hash está cheia\n");
        return;
      }
    }

  vetor[n_ind].sinal = 1;
  vetor[n_ind].dados = n_elem;
  tam++;
}

/* Função responsável por inserir um elemento cuja chave é a mesma do parâmetro recebido */
void Remover(char name[100])
{
  int index = Cod_hash(Gera_chave(name));
  int n_ind = index;

  while (vetor[n_ind].sinal != 0)
    {

      if (vetor[n_ind].sinal == 1 && vetor[n_ind].dados -> chave == Gera_chave(name))
      {
        vetor[n_ind].sinal = 2;
        vetor[n_ind].dados = NULL;
        tam--;
        printf("\n %s foi removido\n", name);
        return;
      }

      n_ind = (n_ind + 1) % max;

      if (n_ind == index)
      {
        break;
      }
    }

  printf("\n Chave não encontrada na tabela\n");
}


elem * Buscar(char name[100])
{
  int index = Cod_hash(Gera_chave(name));
  int n_ind = index;
  elem * found;

  while (vetor[n_ind].sinal != 0)
    {

      if (vetor[n_ind].sinal == 1 && vetor[n_ind].dados -> chave == Gera_chave(name))
      {
        found = vetor[n_ind].dados;
        return found;
      }

      n_ind = (n_ind + 1) % max;

      if (n_ind == index)
      {
        break;
      }
    }

  found = NULL;
  
  return found;
}

/* Função responsável pela impressão da Tabela Hash */

void hash_print()
{
  printf("\n");
  printf("---------------Tabela Hash---------------");
  printf("\n");
  for (int e = 0; e < max; e++)
    {
      elem *atual = vetor[e].dados;
      if (atual != NULL)
      {
        printf("\nVetor: Elem %d, chave = %d, valor = %d", e, atual -> chave, atual -> valor);
        printf(", nome = ");
        for (int i = 0; i < 100; i++)
          {
            printf("%c", atual -> nome[i]);
          }
        printf(", tipo = ");
        for (int i = 0; i < 10; i++)
          {
            printf("%c", atual -> tipo[i]);
          }
        printf("\n");
      }

      else
      {
        printf("\n Posição %d vazia\n", e);
      }
      
    }
}

elem * hash_get_elem(char name[100])
{
  int index = Cod_hash(Gera_chave(name));
  elem * atual = vetor[index].dados;
  if (atual != NULL)
    return atual;
  
  return NULL;
}

int hash_get(char nom[100])
{
  int index = Cod_hash(Gera_chave(nom));
  long carac_asc, carac_aux;
  elem * atual = vetor[index].dados;
  if (atual ==  NULL)
  {
    printf("Nome inexistente na tabela\n"
          "Variável recebe INT_MIN\n\n");
        return INT_MIN;
  }
  for (int e = 0; e < strlen(nom); e++)
    {
      carac_asc = nom[e];
      carac_aux = atual->nome[e];
      if (carac_asc != carac_aux)
      {
        printf("Nome inexistente na tabela\n"
          "Variável recebe INT_MIN\n\n");
        return INT_MIN;
        }
    }
  return atual->valor;
}

void hash_update(char name[100], int val)
{
  int x = hash_get(name);
  
  if (x == INT_MIN)
    printf("Não foi possível atualizar, nome inexistente na tabela\n\n");
  else
    vetor[Cod_hash(Gera_chave(name))].dados->valor = val;
}