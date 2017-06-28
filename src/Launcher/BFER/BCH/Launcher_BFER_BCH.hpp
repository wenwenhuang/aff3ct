#ifndef LAUNCHER_BFER_BCH_HPP_
#define LAUNCHER_BFER_BCH_HPP_

#include "../Launcher_BFER.hpp"

namespace aff3ct
{
namespace launcher
{
template <typename B = int, typename R = float, typename Q = R>
class Launcher_BFER_BCH : public Launcher_BFER<B,R,Q>
{
public:
	Launcher_BFER_BCH(const int argc, const char **argv, std::ostream &stream = std::cout);
	virtual ~Launcher_BFER_BCH() {};

protected:
	virtual void build_args();
	virtual void store_args();
	virtual void group_args();

	virtual simulation::Simulation* build_simu();

	virtual std::vector<std::pair<std::string,std::string>> header_code();
};
}
}

#endif /* LAUNCHER_BFER_BCH_HPP_ */
