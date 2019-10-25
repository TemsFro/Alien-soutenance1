#ifndef XOR_H
#define XOR_H

typedef struct input1 input;
struct input1 {
	int 	ent;
	double	poids[4];
};
typedef struct neural1 neural;
struct neural1 {
	double	poid;
	double	biais;
	double	acti;
	input 	fils[2];
};
typedef struct output1 output;
struct output1 {
	double 		activ;
	neural 		fil[4];	
};

double training(int inp1, int inp2);

#endif
