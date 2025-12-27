#include "convection.h"
#include <cmath>

void cds_convection() {
  for (int i = 0; i < internalFieldSize; ++i) {
    // Lower triangle
    l[i] += -rho * U[i] * rDeltaX * 0.5;

    // Upper triangle
    u[i] += rho * U[i] * rDeltaX * 0.5;

    // Diagonal
    d[i] = -(l[i] + u[i]);
  }

  // Source term
  source[0] += rho * U[0] * rDeltaX * 0.5 * phiLeft;
  source[internalFieldSize - 1] += -rho * U[internalFieldSize - 1] * rDeltaX * 0.5 * phiRight;
}

void upwind_convection() {
  for (int i = 0; i < internalFieldSize; ++i) {
    // Lower triangle
    l[i] += -std::fmax(rho * U[i], 0.) * rDeltaX;

    // Upper triangle
    u[i] += std::fmin(rho * U[i], 0.) * rDeltaX;

    // Diagonal
    d[i] = -(l[i] + u[i]);
  }

  // Source term
  source[0] += std::fmax(rho * U[0], 0.) * rDeltaX * phiLeft;
  source[internalFieldSize - 1] += -std::fmin(rho * U[internalFieldSize - 1], 0.) * rDeltaX * phiRight;
}
