#include "field.h"
#include "linalg.h"
#include "convection.h"
#include "laplacian.h"

#include "globalVars.h"

int convectionScheme = 0;  // 0: CDS, 1: Upwind
int main(int argc, char** argv) {
  initVariables();
  correctBC();

  if (convectionScheme == 0) {
    cds_convection();
  } else if (convectionScheme == 1) {
    upwind_convection();
  }

  cds_laplacian();

  TDMA(l, d, u, internalFieldSize, source, phi);
  correctBC();

  writeCoeffs();
  writeSources();
  writeSolutions();

  destroyVariables();
  return 0;
}