#include "model.h"
#include "model_data.h"
#include "mydnn.h"

void predict(double * I, double * P) {

  double H[NUM_H];
  double M[NUM_M];
  
  forward_Y(I, WH, BH, H, NUM_I, NUM_H);
  relu_Y(H, NUM_H);

  forward_Y(H, WM, BM, M, NUM_M, NUM_M);
  relu_Y(M, NUM_M);

  forward_Y(M, WO, BO, P, NUM_M, NUM_O);
  sigmoid_Y(P, NUM_O);
}
