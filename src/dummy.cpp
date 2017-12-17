
#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::depends(mapboxVariant)]]

#include <mapbox/geometry/geometry.hpp>
#include <mapbox/variant.hpp>
#include <iostream>

using mapbox::geometry::geometry_collection;
using mapbox::geometry::geometry;
using mapbox::geometry::point;

using point_type = point<double>;


struct printer
{
	printer() {}
	
	void operator()(point_type const& pt) const
	{
		std::clog << "x: " << pt.x << " y: " << pt.y << "\n";
	}
	
	template <typename T>
	void operator()(T const& g) const
	{
		std::clog << "encountered non-point geometry\n";
	}
};

// [[Rcpp::export]]
void testGeometry() {
	
	geometry_collection<double> gc;
	gc.emplace_back(point_type(1.0,0.0));
	gc.emplace_back(point_type(1.0,1.0));
	geometry<double> const& geom = gc.at(0);
	
	Rcpp::Rcout << gc.size() << std::endl;
	
	printer visitor;
	mapbox::util::apply_visitor(visitor,geom);
	
}