#include "laplacian.h"

void cds_laplacian() {
  for (int i = 0; i < internalFieldSize; ++i) {
    // Lower triangle
    l[i] += -diffusivity * rDeltaX * rDeltaX;

    // Upper triangle
    u[i] += -diffusivity * rDeltaX * rDeltaX;

    // Diagonal
    d[i] = -(l[i] + u[i]);
  }

  // Source term
  source[0] += diffusivity * rDeltaX * rDeltaX * phiLeft;
  source[internalFieldSize - 1] += diffusivity * rDeltaX * rDeltaX * phiRight;
}
