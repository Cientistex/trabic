#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 int escritorio(){

  /* Este é o rascunho do código para as estantes de livro. Ele operará de forma binária, onde os zeros e uns representam se os livros estão na estante
  ou pendendo dela, respectivamente.*/

   int n, m, i, j;
   int igualdade=0;
   int estante[2][2]= {
   {1, 0},
   {0, 1}
   };
   int estante1[2][2]= {
   {1, 0},
   {0, 0}
   };

    for(i=0; i<2; i++){
   for(j=0; j<2; j++){
    printf("|%d|", estante[i][j]);
   }
   printf("\n");
   }
   while(igualdade == 0){
   scanf("%d %d", &n, &m);
    if( estante[n][m]==0)
     estante[n][m]=1;
    else
    estante[n][m]=0;

   for(i=0; i<2; i++){
   for(j=0; j<2; j++){
    printf("|%d|", estante[i][j]);
   }
   printf("\n");
   }
    if (memcmp(estante, estante1, sizeof(estante))== 0)
        igualdade = 1;
   }
   printf(" Puzzel resolvido!\n \n \n \n \n \n");


  getchar();
  /* Agora, a ideia é fazer um programa no qual o usuário consiga interagir com um cadeado trancado, onde ele poderá destrava-lo quando os rotores
  estiverem em um mesma posição.*/
  int senha[7]= {0, 3, 5, 4, 7, 8, 2};
  int rotor[7]= {0, 0, 0, 0, 0, 0, 0};
  int a, b, igl=0, cont=0;
  int *p;
   printf("Senha: \n");

   for(i=0; i<7; i++)
    printf("%d ", senha[i]);

    printf("\n rotor: \n");

   for(j=0; j<7; j++)
    printf("%d ", rotor[j]);

    printf("\n");

   p = rotor;
   while(igl==0){
   scanf("%d", &a);
   printf("%d  %d \n", *(p+a), a);
   scanf("%d", &b);
   *(p+a)=b;

   printf("\n");

    for(i=0; i<7; i++)
   printf("%d ", *(p+i));

    printf("\n");

   cont=0;

   for(j=0; j<7; j++){
    if(senha[j] == *(p+j)){
    cont = cont +1;
    }
    if(cont == 7)
        igl = 1;
   }
   }

    printf("\n Cadeado desbloqueado");
    return 0;
 }