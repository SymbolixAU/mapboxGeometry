
#ifndef R_MAPBOXGEOMETRY_H
#define R_MAPBOXGEOMETRY_H

#include <RcppCommon.h>

#include <mapbox/geometry.hpp>
#include <mapbox/variant.hpp>

// http://gallery.rcpp.org/articles/custom-templated-wrap-and-as-for-seamingless-interfaces/
// http://gallery.rcpp.org/articles/custom-as-and-wrap-example/

// TODO( handle ZM attributes )

namespace Rcpp {

	// template <typename T > mapbox::geometry::line_string<T> as( SEXP obj );
	
	template <typename T> SEXP wrap(const mapbox::geometry::point<T>& obj);
	template <typename T> SEXP wrap(const mapbox::geometry::multi_point<T>& obj);
	template <typename T> SEXP wrap(const mapbox::geometry::line_string<T>& obj);
	template <typename T> SEXP wrap(const mapbox::geometry::multi_line_string<T>& obj);
	template <typename T> SEXP wrap(const mapbox::geometry::linear_ring<T>& obj);
	template <typename T> SEXP wrap(const mapbox::geometry::polygon<T>& obj);
	template <typename T> SEXP wrap(const mapbox::geometry::multi_polygon<T>& obj);
	
	
} // Rcpp

#include <Rcpp.h>

namespace Rcpp {

// template <typename T>
// mapbox::geometry::line_string<T> as( SEXP obj ) {
// 	//const int RTYPE = Rcpp::traits::r_sexptype_traits<T>::rtype;
// 
// 	//Rcpp::Vector< RTYPE > v = Rcpp::as< Rcpp::Vector< RTYPE > > ( obj );
// 
// 	//mapbox::geometry::point<T> pt({v[0], v[1]});
// 	//return pt;
// 	mapbox::geometry::point<T> pt({1,2});
// 	mapbox::geometry::line_string<T> ls({ pt });
// 	return ls;
// }


template <typename T>
SEXP wrap(const mapbox::geometry::point<T> &obj) {
	const int RTYPE = Rcpp::traits::r_sexptype_traits<T>::rtype;
	return Rcpp::Vector< RTYPE >({ obj.x, obj.y });
};


template <typename T>
SEXP wrap(const mapbox::geometry::multi_point<T> &obj) {
	const int RTYPE = Rcpp::traits::r_sexptype_traits<T>::rtype;

	// a MULTIPOINT is a vector of POINT objects.
	
	//std::vector< mapbox::geometry::point<T> > vec( obj.begin(), obj.end() );
	
	R_xlen_t n = obj.size();
	Rcpp::Matrix< RTYPE > m(n, 2);
	
	R_xlen_t i = 0;
	for( mapbox::geometry::point<T> pt : obj ) {
		Rcpp::Vector< RTYPE > v = Rcpp::wrap( pt );
		m( i, Rcpp::_ ) = v;
		i++;
	}
	return m;
}

template <typename T>
SEXP wrap(const mapbox::geometry::line_string<T> &obj) {
	const int RTYPE = Rcpp::traits::r_sexptype_traits<T>::rtype;
	
	R_xlen_t n = obj.size();
	Rcpp::Matrix< RTYPE > m(n, 2);
	
	R_xlen_t i = 0;
	for( mapbox::geometry::point<T> pt : obj ) {
		Rcpp::Vector< RTYPE > v = Rcpp::wrap( pt );
		m( i, Rcpp::_ ) = v;
		i++;
	}
	return m;
}

template <typename T>
SEXP wrap(const mapbox::geometry::multi_line_string<T> &obj) {

	R_xlen_t n = obj.size();
	Rcpp::List lst(n);
	R_xlen_t i = 0;
	
	for( mapbox::geometry::line_string<T> ls : obj ) {
		lst[i] = Rcpp::wrap( ls );
		i++;
	}
	return lst;
}

template <typename T>
SEXP wrap(const mapbox::geometry::linear_ring<T> &obj) {
	const int RTYPE = Rcpp::traits::r_sexptype_traits<T>::rtype;
	
	R_xlen_t n = obj.size();
	Rcpp::Matrix< RTYPE > m(n, 2);
	
	R_xlen_t i = 0;
	for( mapbox::geometry::point<T> pt : obj ) {
		Rcpp::Vector< RTYPE > v = Rcpp::wrap( pt );
		m( i, Rcpp::_ ) = v;
		i++;
	}
	return m;
}

template <typename T>
SEXP wrap(const mapbox::geometry::polygon<T> &obj) {

	size_t n = obj.size();
	Rcpp::List lst(n);
	R_xlen_t i = 0;

	for( mapbox::geometry::linear_ring<T> lr : obj ) {
		lst[i] = Rcpp::wrap( lr );
		i++;
	}
	return lst;
}

template <typename T>
SEXP wrap(const mapbox::geometry::multi_polygon<T> &obj) {

	size_t n = obj.size();
	Rcpp::List lst(n);
	R_xlen_t i = 0;

	for( mapbox::geometry::polygon<T> pl : obj ) {
		lst[i] = Rcpp::wrap( pl );
		i++;
	}
	return lst;
}

} // Rcpp


#endif

