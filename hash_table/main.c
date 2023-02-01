#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/* Programa no qual se implementa uma Tabela Hash cujo tratamento de colisões é Sondagem Linear */

// Elemento em si
typedef struct elemento
{
   int valor;
   int chave;
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
int max = 10;
elem_hash *vetor;

int Gera_chave(int valor)
{
  int chave = valor * pow(11, valor % 4);
  return chave;
}
// Função utilizada para calcular o código hash do elemento
int Cod_hash(int chave)
{
  int ind = chave % max;
  return ind;
}

/* Função responsável por inicializar o vetor com posições nulas */
void Inicializar_vet()
{
  for (int e = 0; e < max; e++)
    {
      vetor[e].sinal = 0;
      vetor[e].dados = NULL;
    }

}

/* Função responsável por inserir um elemento*/
void Inserir(int val)
{
  int index = Cod_hash(Gera_chave(val));
  int n_ind = index;
  

  elem *n_elem = malloc(sizeof(elem));
  n_elem -> valor = val;
  n_elem -> chave = Gera_chave(val);
  printf("\nInsira o nome do elemento de valor %d:\n", val);
  scanf("%s", n_elem -> nome);

  while (vetor[n_ind].sinal == 1)
    {
      if (vetor[n_ind].dados -> chave == Gera_chave(val))
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
  printf("\nInserção da chave %d realizada\n",Gera_chave(val));
  
}

/* Função responsável por inserir um elemento cuja chave é a mesma do parâmetro recebido */
void Remover(int val)
{
  int index = Cod_hash(Gera_chave(val));
  int n_ind = index;

  while (vetor[n_ind].sinal != 0)
    {

      if (vetor[n_ind].sinal == 1 && vetor[n_ind].dados -> chave == Gera_chave(val))
      {
        vetor[n_ind].sinal = 2;
        vetor[n_ind].dados = NULL;
        tam--;
        printf("\n Valor %d foi removido\n", val);
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


elem * Buscar(int val)
{
  int index = Cod_hash(Gera_chave(val));
  int n_ind = index;
  elem * found;

  while (vetor[n_ind].sinal != 0)
    {

      if (vetor[n_ind].sinal == 1 && vetor[n_ind].dados -> chave == Gera_chave(val))
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

void Imprimir()
{
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
        printf("\n");
      }

      else
      {
        printf("\n Posição %d vazia\n", e);
      }
      
    }
}

elem * BuscaNom(char nom[100])
{
  bool equal;
  for (int e = 0; e < max; e++)
    {
      elem *atual = vetor[e].dados;
      equal = true;
      
      if (atual != NULL)
      {
        for (int i = 0; i < 10; i++)
          {
            if (nom[i] == 0)
              break;
            if (nom[i] != atual -> nome[i])
            {
              equal = false;
            }
          }
      }
      if (equal == true)
        return atual;
    }
  return NULL;
}

/* Função através da qual determinados
   valores no arquivo-texto serão lidos
   e retornados*/
void Scrapping (int acao, int linha)
{
  int as_num, valor, ind = 0, n_line = 0;
  FILE *pt_file;
  char carac, ch[5];
  bool is_creating = false, is_scraping = false;
  
  pt_file = fopen("dados.txt","r");
    do
  {  
      carac = fgetc(pt_file);
      // Trecho que possibilita a leitura
      //  e utilização de dados de uma determinada
      // linha 

      if (n_line == linha - 1)
      {
      if (is_creating == false)
      { 
        // Inicio da análise do tipo de cada caracter
        if (carac == (48 + acao))
      {
        is_creating = true;
        continue;
      }
        }
        
      else 
      {
        as_num = carac;
      }

      // Trecho que lê caracteres numéricos e armazena em vetor
      if (48 <= as_num && as_num <= 57)
      { 
        ch[ind] = as_num;
        ind++;
      }
        
      else 
      {
        if (as_num == 40)
        {
          is_scraping = true;
        }

        if (is_scraping == true)
        {
          // Conversão do número de char para int
          if (as_num == 32)
        {
          valor = atoi(ch);
          if (acao == 1)
          {
            Inserir(valor);
          }
          else if (acao == 2)
            Remover(valor);
          ind = 0;
          for (int e = 0; e < 5; e++)
         {
           ch[e] = 0;
         }
        }
        
        else if (as_num == 41)
        {
          valor = atoi(ch);
          is_scraping = false;
          is_creating = false;
          if (acao == 1)
            Inserir(valor);
          else if (acao == 2)
            Remover(valor);
          break;
          }
        }
        }
        }

    else if (carac == 10)
      n_line++;
        
    }
  while (carac != EOF);

   fclose(pt_file);
}

int main(void) {

  // Display de opções
  int opcao, val, cha, buscado_val;
  char buscado_nom[100];
  printf("        Tabela Hash(Sondagem linear para tratamento de colisões)\n");
  printf("\nInsira:\n"
    "0 para sair\n"
    "1 para inicializar tabela hash de 10 elementos\n");
  scanf("%d", &opcao);

  while (1)
  {
    
  if (opcao == 0)
    return 0;

  else if (opcao == 1)
  {
    vetor = (elem_hash*) malloc(max * sizeof(elem_hash));
    Inicializar_vet();
    printf("\n Tabela Hash inicializada\n");
    while (1)
    {
      // Segundo display de opções
      printf("\nInsira:\n"
        "0 para sair\n"
        "1 para inserir elementos do arquivo\n"
        "2 para remover elementos referenciados\n"
        "3 para imprimir tabela\n"
        "4 para buscar elemento pelo valor\n"
        "5 para buscar elemento pelo nome\n");
      scanf("%d", &opcao);
      
      if (opcao == 0)
        return 0;

      else if (opcao == 1)
      {
        //printf("Digite o valor a inserir:\n");
        //scanf("%d", &val);
        Scrapping(1, 1);
      }

      else if (opcao == 2)
      {
        Scrapping(2, 4);
      }

      else if(opcao == 3)
        Imprimir();

      else if (opcao == 4)
      {
        printf("\nDigite o valor a buscar:\n");
        scanf("%d", &buscado_val);
        printf("\nO nome do valor encontrado é:\n");
        for (int i = 0; i < 100; i++)
          {
            printf("%c", Buscar(buscado_val) -> nome[i]);
          }
        printf("\n");
      }
        
      else if (opcao == 5)
      {
        printf("\nDigite o nome a buscar:\n");
        scanf("%s", buscado_nom);
        printf("\nO valor do nome encontrado é %d:\n", BuscaNom(buscado_nom) -> valor);

      }

      else
      {
        printf("\nInsira uma opção válida");
        continue;
      }
        
    }
  }

  else
  {
    printf("\nInsira uma opção válida\n");
    continue;
  }
    
  }
  
}
