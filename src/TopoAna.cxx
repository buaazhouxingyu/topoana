#include "../include/topoana.h"
#include <boost/python.hpp>
using namespace boost::python;

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(cutToSelect_member_function_overloads, cutToSelect, 2, 6)

BOOST_PYTHON_MODULE(TopoAna)
{
  class_<topoana>("topoana")
    .def("makeMapsOnPdata", &topoana::makeMapsOnPdata)
    .def("cutToSelect", &topoana::cutToSelect, cutToSelect_member_function_overloads(args("strDcyBr", "aliasMP", "ccType", "nTBrs", "nCcTBrs", "topoType")));
}
