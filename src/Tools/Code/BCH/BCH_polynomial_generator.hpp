#ifndef BCH_POLYNOMIAL_GENERATOR_HPP
#define BCH_POLYNOMIAL_GENERATOR_HPP

#include <vector>

#include "Tools/Math/Galois.hpp"

namespace aff3ct
{
namespace tools
{
class BCH_polynomial_generator : public Galois
{
protected:
	const int t;
	const int d;

	std::vector<int> g; // coefficients of the generator polynomial, g(x)

public:
	BCH_polynomial_generator(const int& K, const int& N, const int& t);
	virtual ~BCH_polynomial_generator();

	int get_d      () const;
	int get_t      () const; // get the correction power
	int get_n_rdncy() const; // get the number of redundancy bits

	const std::vector<int>& get_g() const; // get the coefficients of the generator polynomial

private:
	void compute_polynomial();
};
}
}

#endif /* BCH_POLYNOMIAL_GENERATOR_HPP */
