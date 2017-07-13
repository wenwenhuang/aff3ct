#ifndef FACTORY_ENCODER_BCH_HPP
#define FACTORY_ENCODER_BCH_HPP

#include <string>

#include "Module/Encoder/Encoder.hpp"
#include "Tools/Math/Galois.hpp"

#include "../Factory_encoder.hpp"

namespace aff3ct
{
namespace tools
{
struct Factory_encoder_BCH : public Factory_encoder
{
	template <typename B = int>
	static module::Encoder<B>* build(const Factory_encoder::parameters &params, const Galois &GF);

	static void build_args(Arguments_reader::arg_map &req_args, Arguments_reader::arg_map &opt_args);
	static void store_args(const Arguments_reader& ar, Factory_encoder::parameters &params);
	static void group_args(Arguments_reader::arg_grp& ar);

	static void header(params_list& head_enc, const Factory_encoder::parameters& params);
};
}
}

#endif /* FACTORY_ENCODER_BCH_HPP */
