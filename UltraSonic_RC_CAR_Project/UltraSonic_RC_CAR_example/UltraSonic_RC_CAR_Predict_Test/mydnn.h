#ifndef MYDNN_H
#define MYDNN_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void forward_Y(double *X, double *W, double *B, double *Y, int M, int N);
double calculate_MSE(double *Y, double *T, int N);
void backward_Yb(double *Yb, double *Y, double *T, int N);
void backward_Xb(double *Xb, double *W, double *Yb, int M, int N);
void backward_Wb(double *X, double *Wb, double *Yb, int M, int N);
void backward_Bb(double *Bb, double *Yb, int N);
void learning_W(double *W, double lr, double *Wb, int M, int N);
void learning_B(double *B, double lr, double *Bb, int N);
void sigmoid_Y(double *Y, int N);
void sigmoid_Xb(double *Xb, double *X, int M);
void tanh_Y(double *Y, int N);
void tanh_Xb(double *Xb, double *X, int M);
void relu_Y(double *Y, int N);
void relu_Xb(double *Xb, double *X, int M);
void print(char * s, double *Y, int N);
void print(char * s, double *W, int M, int N);
void softmax_Y(double *Y, int N);
double calculate_CEE(double *Y, double *T, int N);
double randn();
void initialize_weight_He(double *W, int M, int N);
void initialize_weight_Le(double *W, int M, int N);

#endif  // MYDNN_H
