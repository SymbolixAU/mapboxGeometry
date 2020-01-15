
#include "mapbox/geometry.hpp"

#include "r_mapboxgeometry.hpp"
#include <Rcpp.h>

// [[Rcpp::depends(mapboxVariant)]]

// TODO( R-objects from geometry.hpp objects )

// [[Rcpp::export]]
void test( Rcpp::NumericVector obj ) {

	// testing going from R, to mapbox, to R
	
	//mapbox::geometry::point< double > pt = Rcpp::as< mapbox::geometry::point< double > >( obj );
	//Rcpp::NumericVector res = Rcpp::wrap( pt );
	//return res;
	
	mapbox::geometry::point< double > pt(1.2, 2.1);
	Rcpp::NumericVector res = Rcpp::wrap( pt );
	Rcpp::Rcout << "res: " << res << std::endl;
	mapbox::geometry::point< double > pt2;
	pt2.x = res[0];
	pt2.y = res[1];
	
	Rcpp::NumericVector nv(2);
	nv[0] = 1;
	nv[1] = 2;
	
	//mapbox::geometry::point< double > pt3 = Rcpp::as< mapbox::geometry::point< double > >( nv );
	
	// Rcpp::NumericVector res2 = Rcpp::as< Rcpp::NumericVector >( pt2 );
	// Rcpp::Rcout << "res2: " << res2 << std::endl;

}

// [[Rcpp::export]]
SEXP rcpp_wrap_test() {
	
	mapbox::geometry::point< double > pt1(1,2);
	mapbox::geometry::point< double > pt2(3,4);
	mapbox::geometry::multi_point< double > mp({pt1, pt2});
	mapbox::geometry::line_string< double > ls({pt1, pt2});
	mapbox::geometry::polygon< double > pl({ls});
	mapbox::geometry::multi_polygon< double > mpl({pl});
	
	Rcpp::List res(5);
	res[0] = Rcpp::wrap( pt1 );
	res[1] = Rcpp::wrap( mp );
	res[2] = Rcpp::wrap( ls );
	res[3] = Rcpp::wrap( pl );
	res[4] = Rcpp::wrap( mpl );
	
	return res;
	
}
