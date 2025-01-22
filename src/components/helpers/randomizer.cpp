#include "randomizer.hpp"

namespace tk
{
	//-------------------------------------------------------------------------
	int Randomizer::getInt(int min, int max) {
		std::uniform_int_distribution<int> generator{ min, max };
		return generator(m_engine);
	}

	//-------------------------------------------------------------------------
	int Randomizer::getIntRange(int min, int range) {
		return getInt(min, min + range);
	}

	//-------------------------------------------------------------------------
	double Randomizer::getReal(double min, double max) {
		std::uniform_real_distribution<double> generator{ min, max };
		return generator(m_engine);
	}

	//-------------------------------------------------------------------------
	double Randomizer::getRealRange(double min, double range) {
		return getReal(min, min + range);
	}

} // namespace tk
