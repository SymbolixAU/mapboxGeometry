
#include <Rcpp.h>

#include "point.hpp"

using namespace Rcpp;
using mapbox::geometry::point;

// [[Rcpp::export]]
List rcpp_hello_world() {

    CharacterVector x = CharacterVector::create( "foo", "bar" )  ;
    NumericVector y   = NumericVector::create( 0.0, 1.0 ) ;
    List z            = List::create( x, y ) ;

    return z ;
}

// [[Rcpp::export]]
void rcppPoint() {
	
	point<double> pt(1.0, 0.0);
	double x = pt.x;
	Rcpp::Rcout << "x: " << x << std::endl;
	
}