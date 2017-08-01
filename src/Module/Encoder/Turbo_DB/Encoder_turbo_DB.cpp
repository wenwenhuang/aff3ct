#include <vector>
#include <cmath>

#include "Tools/Exception/exception.hpp"

#include "Encoder_turbo_DB.hpp"

using namespace aff3ct;
using namespace aff3ct::module;

template <typename B>
Encoder_turbo_DB<B>
::Encoder_turbo_DB(const int& K, const int& N, const Interleaver<int> &pi,
                   Encoder_RSC_DB<B> &enco_n, Encoder_RSC_DB<B> &enco_i, const int n_frames,
                   const std::string name)
: Encoder<B>(K, N, n_frames, name),
  pi(pi),
  enco_n(enco_n),
  enco_i(enco_i),
  U_K_i(K * n_frames),
  par_n(K * n_frames),
  par_i(K * n_frames)
{
	if (N != 3 * K)
	{
		std::stringstream message;
		message << "'N' has to be equal to 3 * 'K' ('N' = " << N << ", 'K' = " << K << ").";
		throw tools::invalid_argument(__FILE__, __LINE__, __func__, message.str());
	}

	if ((int)pi.get_size() != K)
	{
		std::stringstream message;
		message << "'pi.get_size()' has to be equal to 'K' ('pi.get_size()' = " << pi.get_size()
		        << ", 'K' = " << K << ").";
		throw tools::length_error(__FILE__, __LINE__, __func__, message.str());
	}
}

// [   AB   ][  WnWi  ][  YnYi  ]
template <typename B>
void Encoder_turbo_DB<B>
::encode(const B *U_K, B *X_N)
{
	//pi.interleave(U_K, U_K_i.data(), 0, this->n_frames);

	mipp::vector<int> lut = pi.get_lut();
	mipp::vector<B> U_K_cpy (this->K);
	//std::copy(U_K, U_K + this->K, U_K_cpy);
	for (auto i = 0; i < this->K; i++)
		U_K_cpy[i] = U_K[i];

	for (auto i = 0; i < this->K; i+=4)
		std::swap(U_K_cpy[i], U_K_cpy[i+1]);
	for (auto i = 0; i < this->K; i++)
		U_K_i[ lut[i] ] = U_K_cpy[i];

	enco_n.encode_sys(U_K,          par_n.data());
	enco_i.encode_sys(U_K_i.data(), par_i.data());

	std::copy(U_K, U_K + this->K, X_N);

	auto j = this->K;
	for (auto i = 0; i < this->K; i+=2) // parity y for both constituent encoders
	{
		X_N[j++] = par_n[i];
		X_N[j++] = par_i[i];
	}

	for (auto i = 1; i < this->K; i+=2) // parity w for both constituent encoders
	{
		X_N[j++] = par_n[i];
		X_N[j++] = par_i[i];
	}
}

// ==================================================================================== explicit template instantiation 
#include "Tools/types.h"
#ifdef MULTI_PREC
template class aff3ct::module::Encoder_turbo_DB<B_8>;
template class aff3ct::module::Encoder_turbo_DB<B_16>;
template class aff3ct::module::Encoder_turbo_DB<B_32>;
template class aff3ct::module::Encoder_turbo_DB<B_64>;
#else
template class aff3ct::module::Encoder_turbo_DB<B>;
#endif
// ==================================================================================== explicit template instantiation
