
#include "mapbox/geometry.hpp"

#include "r_mapboxgeometry.hpp"
#include <Rcpp.h>

// [[Rcpp::depends(mapboxVariant)]]

// [[Rcpp::export]]
SEXP rcpp_wrap_test() {
	
	mapbox::geometry::point< double > pt1(1,2);
	mapbox::geometry::point< double > pt2(3,4);
	mapbox::geometry::multi_point< double > mp({pt1, pt2});
	mapbox::geometry::line_string< double > ls({pt1, pt2});
	mapbox::geometry::multi_line_string< double > mls({ls});
	mapbox::geometry::polygon< double > pl({ls});
	mapbox::geometry::multi_polygon< double > mpl({pl});
	
	Rcpp::NumericVector nv_pt = Rcpp::wrap( pt1 );
	Rcpp::NumericMatrix mat_mp = Rcpp::wrap( mp );
	Rcpp::NumericMatrix mat_ls = Rcpp::wrap( ls );
	Rcpp::List ls_mls = Rcpp::wrap( mls );
	Rcpp::List ls_p = Rcpp::wrap( pl );
	Rcpp::List ls_mp = Rcpp::wrap( mpl );
	
	Rcpp::List res(6);
	
	res[0] = nv_pt;
	res[1] = mat_mp;
	res[2] = mat_ls;
	res[3] = ls_mls;
	res[4] = ls_p;
	res[5] = ls_mp;
	
	return res;
	
}

// [[Rcpp::export]]
SEXP rcpp_as_test() {
	
	Rcpp::NumericVector vec({1,2});
	Rcpp::NumericVector mat = {1,3,2,4};
	mat.attr("dim") = Rcpp::Dimension(2,2);
	Rcpp::List l(1);
	l[0] = mat;
	Rcpp::List l2(1);
	l2[0] = l;
	
	mapbox::geometry::point< double > pt = Rcpp::as< mapbox::geometry::point< double > >( vec );
	mapbox::geometry::multi_point< double > mpt = Rcpp::as< mapbox::geometry::multi_point< double > >( mat );
	mapbox::geometry::line_string< double > ls = Rcpp::as< mapbox::geometry::line_string< double > >( mat );
	mapbox::geometry::multi_line_string< double > mls = Rcpp::as< mapbox::geometry::multi_line_string< double > >( l );
	mapbox::geometry::polygon< double > pl = Rcpp::as< mapbox::geometry::polygon< double > >( l );
	mapbox::geometry::multi_polygon< double > mpl = Rcpp::as< mapbox::geometry::multi_polygon< double > >( l2 );

	Rcpp::List res(6);
	
	res[0] = Rcpp::wrap( pt );
	res[1] = Rcpp::wrap( mpt );
	res[2] = Rcpp::wrap( ls );
	res[3] = Rcpp::wrap( mls );
	res[4] = Rcpp::wrap( pl );
	res[5] = Rcpp::wrap( mpl );
	
	return res;
}

//[[Rcpp::export]]
SEXP rcpp_test_performance( Rcpp::NumericMatrix x ) {
	mapbox::geometry::line_string< double > ls = Rcpp::as< mapbox::geometry::line_string< double > >( x );
	Rcpp::NumericMatrix res = Rcpp::wrap( ls );
	return res;
}

