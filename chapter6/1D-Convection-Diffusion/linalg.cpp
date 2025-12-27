#include <iomanip>
#include <fstream>
#include <cmath>
#include <iostream>
#include "linalg.h"

void TDMA(
  const double* __restrict__ l,
  const double* __restrict__ d,
  const double* __restrict__ u,
  const int n,
  const double* __restrict__ b,
  double* x
) {
  double* __restrict__ uprime = new double[n];
  double* __restrict__ bprime = new double[n];

  // Forward sweep
  uprime[0] = u[0] / d[0];
  bprime[0] = b[0] / d[0];

  for (int i = 1; i < n - 1; ++i) {
    uprime[i] = u[i] / (d[i] - l[i] * uprime[i - 1]);
  }

  for (int i = 1; i < n; ++i) {
    bprime[i] = (b[i] - l[i] * bprime[i - 1]) / (d[i] - l[i] * uprime[i - 1]);
  }

  // Back substitution
  x[n - 1] = bprime[n - 1];
  for (int i = n - 2; i >= 0; --i) {
    x[i] = bprime[i] - uprime[i] * x[i + 1];
  }

  delete[] uprime;
  delete[] bprime;
  return;
}

void writeCoeffs() {
  std::ofstream os("coeffs.dat");
  for (int i = 0; i < internalFieldSize; ++i) {
    for (int j = 0; j < internalFieldSize; ++j) {
      if (i == j) {
        os << std::setw(10) << d[i];
      } else if (i == j - 1) {
        os << std::setw(10) << u[i];
      } else if (i == j + 1) {
        os << std::setw(10) << l[i];
      } else {
        os << std::setw(10) << " ";
      }
    }
    os << std::endl;
  }
  os.close();
}

void writeSources() {
  std::ofstream os("sources.dat");
  for (int j = 0; j < internalFieldSize; ++j) {
    os << std::setw(10) << source[j] << std::endl;
  }
  os.close();
}

void writeSolutions() {
  double Pe = 0.0;
  if (diffusivity > 0.0) {
    Pe = rho * U[0] * L / diffusivity;
  } else {
    Pe = __DBL_MAX__;
  }
  std::cout << "Peclet number: " << Pe << std::endl;

  for (int i = 0; i < internalFieldSize; ++i) {
    double x = (i + 1) * deltaX;
    if (diffusivity <= 0.0) {
      exact[i] = phiLeft + (phiRight - phiLeft) * x / L;
      continue;
    }
    exact[i] = phiLeft + (exp(x * Pe / L) - 1.0) / (exp(Pe) - 1.0) * (phiRight - phiLeft);
  }

  std::ofstream os("solutions.dat");
  os << "#solution comparison" << std::endl;
  os << std::setw(5) << 0 << " " << std::setw(10) << phiLeft << " " << std::setw(10) << phiLeft << std::endl;
  for (int i = 0; i < internalFieldSize; ++i) {
    double x = (i + 1) * deltaX;
    os << std::setw(5) << x << " " << std::setw(10) << exact[i] << " " << std::setw(10) << phi[i] << std::endl;
  }
  os << std::setw(5) << L << " " << std::setw(10) << phiRight << " " << std::setw(10) << phiRight << std::endl;
  os.close();
}
