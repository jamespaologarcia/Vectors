#include "Cents.h"

// a quick and dirty override to output a Cents object
std::ostream& operator<<(std::ostream& out, const Cents& c) {
	out << "$";
	out << c.getValue() / 100.0;
	return out;
}
