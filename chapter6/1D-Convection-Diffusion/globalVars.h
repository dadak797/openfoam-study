#pragma once

// Domain parameters
const double L = 1.0;

// Mesh properties
const int nodeSize = 11;
const int internalFieldSize = nodeSize - 2;
const double deltaX = L / (nodeSize - 1);
const double rDeltaX = 1.0 / deltaX;

// Physical properties
const double rho = 1.0;
const double diffusivity = 0.02;

// Field variables
double* phi;
double* U;
double* exact;

// Matrix coeffs and sources
double* source;
double* d;
double* l;
double* u;
double* internalField;

// Boundaries
double phiLeft;
double phiRight;