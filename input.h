/*This is a file to get the input for the GA program*/

void input(FILE *rep_ptr);

void input(FILE *rep_ptr)
{
  int i;
  float cc;

  printf("-------------------------------------------------------------\n\n\n");
  printf("This is a Multi-Objective GA program to solve the constraint problem\n\n");
  printf("-------------------------------------------------------------\n\n");
  printf("Give problem specification\n\n");
  printf("-------------------------------------------------------------\n");
  printf("-------------------------------------------------------------\n");

  /*Asks for number of the variables*/

  printf("Entrer le nombre de variables reelles\n");
  scanf("%d",&nvar);

  printf("Entrer le nombre de variables binaires\n");
  scanf("%d",&nchrom);

  /*Checks if the number of variables are more than specified in the
    program if it fails here goto tunsga1.c file and increase the
    maxvar to the number equal to your requirement*/

    if (nvar > maxvar)
    {
      printf("Le nombre de variables reelles est trop grand. Actuellement le maximum est de %d.\n",maxvar);
      exit(1);
    }

    if (nchrom > maxvar)
    {
      printf("Le nombre de variables binaires est trop grand. Actuellement le maximum est de %d.\n",maxvar);
      exit(1);
    }

  /*Asks for number of the functions*/

  printf("Donner le nombre de fonctions objectif\n");
  scanf("%d",&nfunc);

 /*Checks if the number of functions are more than specified in the
   program if it fails here goto tunsga1.c file and increase the
   maxfun to the number equal to your requirement*/

  if(nfunc > maxfun)
    {
      printf("Le nombre de fonctions objectif est trop grand. Actuellement le maximum est de %d.\n",maxfun);
      exit(1);
    }

  printf("Donner le nombre de containtes\n");
  scanf("%d",&ncons);

  /*Checks if the number of constraints are more than specified in the
    program if it fails here goto tunsga1.c file and increase the
    maxcons to the number equal to your requirement*/

  if(ncons > maxcons)
    {
      printf("Le nombre de contraintes est trop grand. Actuellement le maximum est de %d.\n",maxcons);
      exit(1);
    }

  printf("------------------------------------------------------------\n");
  printf("Give GA parameters\n");
  printf("------------------------------------------------------------\n");

  fflush(stdin);
  /*Asks for number of the individuals in the population*/
  /*Default value = 30 to 100*/

  printf("Donner la taille de la population\n");
  scanf("%d",&popsize);

 /*Checks if the number of individuals in the population  are more
   than specified in the program if it fails here goto tunsga1.c file and
   increase the maxpop to the number equal to your requirement*/


  if(popsize > maxpop)
    {
      printf("Le nombre de la population est trop grand. Actuellement le maximum est de %d\n",maxpop);
      exit(1);
    }

  /*No. of generations for which the GA will let the population evolve
    Default value is 100
    Too large value will take very long time and very small value will
    not let the GA reach the global Pareto front to the problem*/

  printf("Donner le nombre de generations\n");
  scanf("%d",&gener);

  /*No. of generations for which the GA will let the population evolve
    Default value is 100
    Too large value will take very long time and very small value will
    not let the GA reach the global Pareto front to the problem*/

  printf("Donner la probabilite de croisement (entre 0.5 et 1)\n");
  scanf("%f",&pcross);

  if (nvar > 0)
    {
      cc = 1.0/nvar;
      printf("Donner la probabilite de mutation des vecteurs de reels (entre 0 et %f)\n",cc);
      scanf("%f",&pmut_r);

      /*Asks for Distribution Index for Cross-over (Default = 20)*/
      /*For Mutation (Default = 10 to 500)*/

      printf("Donner l'index de distribution du croisement des reels (entre 0.5 et 100)\n");
      scanf("%f",&di);

      printf("Donner l'index de distribution de mutation des reels (entre 0.5 et 500)\n");
      scanf("%f",&dim);

      for(i = 0; i < nvar; i++)
	{
	  /*Specify the limits of the variables*/

	  printf("Donner le minimum et le maximum de la variable reelles %d\n",i+1);
	  scanf("%f %f",&lim_r[i][0],&lim_r[i][1]);
	}

      printf("La limite des variables reelles est-elle rigide ? (1 si oui)\n");
      scanf("%d",&ans);
    }

  chrom = 0;
  if (nchrom > 0)
    {
      /*Asking for Crossover Type*/
      printf("Donner le type de croisement (1 pour simple, 2 pour \"Uniform X-over\")\n");
      scanf("%d",&optype);
      /*Specify the Cross-over Probability for the Simple or Real Coded
	Cross-over suited Range is 0.9 to 0.99*/

      for (i = 0; i < nchrom; i++)
	{
	  /*For Binary Coded Problem
	    Specify the no of bits for each variable
	    Total Sum of the bit value must be equal to
	    chromosome length*/
	  printf("Donner le nombre de bits assigne a la variable %d\n",i+1);
	  scanf("%d",&vlen[i]);
	  chrom += vlen[i];

	  printf("Donner le min et le max de la variable %d\n",i+1);
	  scanf("%f %f",&lim_b[i][0],&lim_b[i][1]);
	}
      if(chrom > maxchrom)
	{
	  printf("La taille de ma population est trop grande. Actuellement le maximum est de %d.\n",maxchrom);
	  exit(1);
	}

      /* Ask for mutation probablity */
      cc = 1.0/chrom;

      printf("Donner la probabilite de mutation pour les binaires(entre 0 et %f)\n",cc);
      scanf("%f",&pmut_b);

    }

  printf("----------------------------------------------------------------\n");

  /*Give the initial seed*/
  printf("\nDonner le \"random seed\"(entre 0 et 1)\n");
  scanf("%f",&seed);

  // end of reading parameters

  /*Print the GA parameters and problem parameters
    in the file output.dat*/

  fprintf(rep_ptr,"GA PARAMETERS\n");
  fprintf(rep_ptr,"-------------------------------------------------------\n");

  fprintf(rep_ptr,"Population Size ->%d\n",popsize);

  fprintf(rep_ptr,"Chromosome Length ->%d\n",chrom);

  fprintf(rep_ptr,"No. of generations ->%d\n",gener);

  fprintf(rep_ptr,"No. of Functions ->%d\n",nfunc);

  fprintf(rep_ptr,"No. of Constraints ->%d\n",ncons);

  if (nchrom > 0)
    fprintf(rep_ptr,"No. of binary-coded variables ->%d\n",nchrom);
  if (nvar > 0)
    fprintf(rep_ptr,"No. of real-coded variables ->%d\n",nvar);

  fprintf(rep_ptr,"Selection Strategy is Tournament Selection\n");

  for(i = 0;i < nchrom;i++)
    {

      fprintf(rep_ptr,"Binary-coded variable No.-> %d\n",i);

      fprintf(rep_ptr,"No. of bits assigned to it ->%d\n",vlen[i]);

      fprintf(rep_ptr,"Lower limits on %dth variable-> %f\n",i,lim_b[i][0]);

      fprintf(rep_ptr,"Upper limits on %dth variable ->%f\n",i,lim_b[i][1]);
    }

  for(i = 0; i < nvar; i++)
    {
      fprintf(rep_ptr,"Real-coded variable No.-> %d\n",i);

      fprintf(rep_ptr,"Lower limits on %dth variable-> %f\n",i,lim_r[i][0]);

      fprintf(rep_ptr,"Upper limits on %dth variable ->%f\n",i,lim_r[i][1]);
      if (ans == 1)
        fprintf(rep_ptr,"Variable bounds are rigid\n");
      else
        fprintf(rep_ptr,"Variable bounds are not rigid\n");
    }

  if (nchrom > 0)
    {
      if(optype == 1)
        fprintf(rep_ptr,"X-over on binary string is SINGLE POINT X-OVER\n");

      else if (optype ==2)
        fprintf(rep_ptr,"X-over on binary strings is UNIFORM X-OVER \n");
    }
  if (nvar > 0)
    fprintf(rep_ptr,"Crossover parameter in the SBX operator is %f\n",di);

  fprintf(rep_ptr,"Cross-over Probability ->%f\n",pcross);

  if (nchrom > 0)
    fprintf(rep_ptr,"Mutation Probability for binary strings -> %f\n",pmut_b);

  if (nvar > 0)
    fprintf(rep_ptr,"Mutation Probability for real-coded vectors -> %f\n",pmut_r);

  fprintf(rep_ptr,"Random Seed ->%f\n",seed);

  return;
}
