#ifndef MACROSES_H
#define MACROSES_H

#include <QVector>
#include <boost/numeric/odeint.hpp>

using state_type = std::vector<double>;
using TraceContainer = std::vector< std::list< std::vector<double> > >;
using namespace boost::numeric::odeint;

#endif // MACROSES_H
