#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "xor.h"

static double sigmoid(double x){return 1.0/(1.0+exp(-x));}
/*double weight[4] = {0.1, 0.01, 0.01, 0.02};
double poids1[4] = {0.01, 0.02, 0.01, 0.05};
double poids2[4] = {0.003, 0.02, 0.01, 0.05};
double biais1 = 1;
double biais2 = 1;
double biais3 = 1;
double biais4 = 1;
double ea1 = 0.2;
double biaisxor = 0;
neural cc[4] = 
{
	{weight[0], biais1, 0, {premier, second}},
	{weight[1], biais2, 0, {premier, second}},
	{weight[2], biais3, 0, {premier, second}},
	{weight[3], biais4, 0, {premier, second}}
};
fclose(file);*/
/*double actcach(input fils[], int j)
{
	int i = 0;
	double verif=0;
	while (i<2)
	{
		verif += fils[i].poids[j] * fils[i].ent;
		i+=1;
	}
	verif = sigmoid(verif);		
	return verif;
}*/
/*float activation(int act,float poids,float bias)
{
	biais1 = (float) act*poids;
	if biais1>biais:
		return 1;
	return 0;
}*/
/*float calcul(neural fils[], double biai[], double weight[])
{
	int i=0;
	double res=0.0;
	int res1;
	while (i<4)
	{
		res1=weight[i]*fils[i].acti;
		if (res1>=biai[i])
			res+= res1;
		i+=1;
	}
	return res;
}*/
double training(int inp1, int inp2)
{
	double stockdelta[5];
	double apprentissage = 0.1;
	srand(time(NULL));
	double weight[4] = {(float)rand()/(float)(RAND_MAX),(float)rand()/(float)(RAND_MAX),(float)rand()/(float)(RAND_MAX), (float)rand()/(float)(RAND_MAX)};
	double poids1[4] = {(float)rand()/(float)(RAND_MAX), (float)rand()/(float)(RAND_MAX), (float)rand()/(float)(RAND_MAX), (float)rand()/(float)(RAND_MAX)};
	/*double poids2[4] = {0.01, 0.02, 0.01, 0.05};*/
	int tmp=0;
	double biai[5] = {0, 0, 0, 1, 0.2};
	while (tmp<500000)
	{
		for (int j = 0; j < 4; ++j)
		{
			int input1=j/2;
			int input2=j%2;
			int res = (input1+input2)%2;
			input premier = {input1, {poids1[0],poids1[1] , poids1[2], poids1[3]}};
			input second = {input2, {poids1[0],poids1[1] , poids1[2], poids1[3]}};
			neural cc[4] = 
			{
				{weight[0], biai[0], 0, {premier, second}},
				{weight[1], biai[1], 0, {premier, second}},
				{weight[2], biai[2], 0, {premier, second}},
				{weight[3], biai[3], 0, {premier, second}}
			};		
			output retour = {0.0, {cc[0], cc[1], cc[2], cc[3]}};
			for (int i = 0; i < 4; ++i)
			{
				cc[i].acti=sigmoid(premier.ent*poids1[i]+second.ent*poids1[i]);
			}
			for (int i = 0; i<4; i++)
			{
				retour.activ+=cc[i].acti*weight[i];
			}
			retour.activ=sigmoid(retour.activ);
			stockdelta[4]=(res-retour.activ)*retour.activ*(1-retour.activ);
			for (int i = 0; i < 4; ++i)
			{
				stockdelta[i]=cc[i].acti*stockdelta[4]*apprentissage;
			}
			for (int i = 0; i < 4; ++i)
			{
				/*stockdelta[i]=0;
				for (int j = 0; j < 4; ++j)
				{
					stockdelta[i]+=stockdelta[4]*weight[j];
				}
				stockdelta[i]=(1-cc[i].acti)*cc[i].acti*stockdelta[i];*/
				stockdelta[i]=(weight[i]*stockdelta[4]);
			}
			for (int i = 0; i < 4; ++i)
			{
				weight[i]=weight[i]+apprentissage*stockdelta[4]*sigmoid(cc[i].acti);
			}
			for (int i = 0; i < 4; ++i)
			{
				poids1[i]=poids1[i]+(apprentissage*stockdelta[i]*sigmoid(cc[i].acti));
			}	
		}
		tmp+=1;
	}
	input premier = {inp1, {poids1[0],poids1[1] , poids1[2], poids1[3]}};
	input second = {inp2, {poids1[0],poids1[1] , poids1[2], poids1[3]}};
	neural cc[4] = 
	{
		{weight[0], biai[0], 0, {premier, second}},
		{weight[1], biai[1], 0, {premier, second}},
		{weight[2], biai[2], 0, {premier, second}},
		{weight[3], biai[3], 0, {premier, second}}
	};
	output retour = {0.0, {cc[0], cc[1], cc[2], cc[3]}};
	for (int i = 0; i < 4; ++i)
	{
		cc[i].acti=sigmoid(premier.ent*poids1[i]+second.ent*poids1[i]);
	}
	for (int i = 0; i<4; i++)
	{
		retour.activ+=cc[i].acti*weight[i];
	}
	retour.activ=sigmoid(retour.activ);
	return retour.activ;
}
/*double actcach(double biais, input fils[], int j)
{
	int i = 0;
	double verif=0;
	while (i<2)
	{
		verif += fils[i].poids[j] * fils[i].ent;
		i+=1;
	}
	verif = sigmoid(verif);		
	if (verif>=biais)
		return 1;
	return 0;
}*/
/*float activation(int act,float poids,float bias)
{
	biais1 = (float) act*poids;
	if biais1>biais:
		return 1;
	return 0;
}*/
/*float calcul(neural fils[])
{
	int i=0;
	double res=0.0;
	int res1;
	while (i<4)
	{
		res1=fils[i].poid*fils[i].acti;
		if (res1>=fils[i].biais)
			res+= res1;
		i+=1;
	}
	return res;
}*/
/*int xor(int input1, int input2)
{
	input premier = {input1, poids1[]};
	input second = {input2, poids2[]};
	neural cc[4] = 
	{
		{weight[0], biais1, 0, {premier, second}},
		{weight[1], biais2, 0, {premier, second}},
		{weight[2], biais3, 0, {premier, second}},
		{weight[3], biais4, 0, {premier, second}}
	};
	cc.acti=actcach(c1.biais, c1.fils, 0);
	cc.acti=actcach(c2.biais, c2.fils, 1);
	cc.acti=actcach(c3.biais, c3.fils, 2);
	cc.acti=actcach(c4.biais, c4.fils, 3);
	output retour = {0.0, {cc[0], cc[1], cc[2], cc[3]}};
	retour.activ= calcul(retour.fil);
	printf("%d\n", retour.activ);
	if (retour.activ>biaisxor)
		return 1;
	return 0;
}*/

