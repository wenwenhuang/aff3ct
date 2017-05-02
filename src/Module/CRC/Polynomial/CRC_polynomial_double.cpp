#include <stdexcept>

#include "CRC_polynomial_double.hpp"

using namespace aff3ct::module;

template <typename B>
CRC_polynomial_double<B>
::CRC_polynomial_double(const int K, std::string poly_key, const int cut_index, const int size, const int n_frames,
                        const std::string name)
: CRC_polynomial<B>(K, poly_key, size, n_frames, name), cut_index(cut_index)
{
	if (n_frames > 1)
		throw std::invalid_argument("aff3ct::module::CRC_polynomial_double: \"n_frames\" has to be equal to 1.");

	if ((this->K - 2 * this->get_size()) <= (cut_index - this->get_size()))
		throw std::invalid_argument("aff3ct::module::CRC_polynomial_double: \"K\" is wrong.");

	if (this->K <= 2 * this->get_size())
		throw std::invalid_argument("aff3ct::module::CRC_polynomial_double: \"K\" has to be greater "
		                            "than 2 * \"size\".");
}

template <typename B>
void CRC_polynomial_double<B>
::_build(B *U_K)
{
	for (unsigned i = unsigned(this->K - 2 * this->get_size() -1); i >= (unsigned)cut_index - this->get_size(); i--)
		U_K[i + this->get_size()] = U_K[i];

	this->_generate(U_K, U_K, 0, cut_index - this->get_size(), cut_index - this->get_size());
	this->_generate(U_K, U_K, 0, this->K   - this->get_size(),   this->K - this->get_size());
}

// ==================================================================================== explicit template instantiation 
#include "Tools/types.h"
#ifdef MULTI_PREC
template class aff3ct::module::CRC_polynomial_double<B_8>;
template class aff3ct::module::CRC_polynomial_double<B_16>;
template class aff3ct::module::CRC_polynomial_double<B_32>;
template class aff3ct::module::CRC_polynomial_double<B_64>;
#else
template class aff3ct::module::CRC_polynomial_double<B>;
#endif
// ==================================================================================== explicit template instantiation
