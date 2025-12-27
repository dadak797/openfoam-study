#include "field.h"

void initVariables() {
  phi = new double[internalFieldSize];
  exact = new double[internalFieldSize];
  U = new double[internalFieldSize];
  source = new double[internalFieldSize];
  l = new double[internalFieldSize];
  d = new double[internalFieldSize];
  u = new double[internalFieldSize];

  // Initialize field and coefficients
  for (int i = 0; i < internalFieldSize; ++i) {
    phi[i] = 0.0;
    exact[i] = 0.0;
    U[i] = 1.0;
    source[i] = 0.0;
    l[i] = 0.0;
    d[i] = 0.0;
    u[i] = 0.0;
  }
}

void destroyVariables() {
  delete[] phi;
  delete[] exact;
  delete[] U;
  delete[] source;
  delete[] l;
  delete[] d;
  delete[] u;
}

void correctBC() {
  phiLeft = 0.0;
  phiRight = L;
}