#pragma once

// Domain parameters
extern const double L;

// Mesh properties
extern const int nodeSize;
extern const int internalFieldSize;
extern const double deltaX;
extern const double rDeltaX;

// Physical properties
extern const double rho;
extern const double diffusivity;

// Field variables
extern double* phi;
extern double* U;
extern double* exact;

// Matrix coeffs and sources
extern double* source;
extern double* d;
extern double* l;
extern double* u;
extern double* internalField;

// Boundaries
extern double phiLeft;
extern double phiRight;

void TDMA(
  const double* __restrict__ l,
  const double* __restrict__ d,
  const double* __restrict__ u,
  const int n,
  const double* __restrict__ b,
  double* x
);

void writeCoeffs();
void writeSources();
void writeSolutions();
