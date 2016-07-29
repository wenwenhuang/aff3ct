#include "Modulator_BPSK.hpp"

template <typename B, typename R, typename Q>
Modulator_BPSK<B,R,Q>
::Modulator_BPSK(const R sigma)
: two_on_square_sigma((R)2.0 / (sigma * sigma))
{
}

template <typename B, typename R, typename Q>
Modulator_BPSK<B,R,Q>
::~Modulator_BPSK()
{
}

template <typename B, typename R, typename Q>
void Modulator_BPSK<B,R,Q>
::modulate(const mipp::vector<B>& X_N1, mipp::vector<R>& X_N2)
{
	auto size = X_N1.size();
	for (unsigned i = 0; i < size; i++)
		X_N2[i] = 1 - (X_N1[i] + X_N1[i]); // (X_N[i] == 1) ? -1 : +1
}

template <typename B, typename R, typename Q>
void Modulator_BPSK<B,R,Q>
::demodulate(const mipp::vector<Q>& Y_N1, mipp::vector<Q>& Y_N2)
{
	assert(typeid(R) == typeid(Q));
	assert(typeid(Q) == typeid(float) || typeid(Q) == typeid(double));

	auto size = Y_N1.size();
	for (unsigned i = 0; i < size; i++)
		Y_N2[i] = Y_N1[i] * two_on_square_sigma;
}

// ==================================================================================== explicit template instantiation 
#include "../../Tools/types.h"
#ifdef MULTI_PREC
template struct Modulator_BPSK<B_8,R_8,R_8>;
template struct Modulator_BPSK<B_8,R_8,Q_8>;
template struct Modulator_BPSK<B_16,R_16,R_16>;
template struct Modulator_BPSK<B_16,R_16,Q_16>;
template struct Modulator_BPSK<B_32,R_32,R_32>;
template struct Modulator_BPSK<B_64,R_64,R_64>;
#else
template struct Modulator_BPSK<B,R,Q>;
#if !defined(PREC_32_BIT) && !defined(PREC_64_BIT)
template struct Modulator_BPSK<B,R,R>;
#endif
#endif
// ==================================================================================== explicit template instantiation
