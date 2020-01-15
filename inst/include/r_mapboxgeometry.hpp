
#ifndef R_MAPBOXGEOMETRY_H
#define R_MAPBOXGEOMETRY_H

#include <RcppCommon.h>

#include <mapbox/geometry.hpp>
#include <mapbox/variant.hpp>

// http://gallery.rcpp.org/articles/custom-templated-wrap-and-as-for-seamingless-interfaces/
// http://gallery.rcpp.org/articles/custom-as-and-wrap-example/

// TODO( handle ZM attributes )

namespace Rcpp {

	template <typename T> SEXP wrap(const mapbox::geometry::point<T>& obj);
	template <typename T> SEXP wrap(const mapbox::geometry::multi_point<T>& obj);
	template <typename T> SEXP wrap(const mapbox::geometry::line_string<T>& obj);
	template <typename T> SEXP wrap(const mapbox::geometry::multi_line_string<T>& obj);
	template <typename T> SEXP wrap(const mapbox::geometry::linear_ring<T>& obj);
	template <typename T> SEXP wrap(const mapbox::geometry::polygon<T>& obj);
	template <typename T> SEXP wrap(const mapbox::geometry::multi_polygon<T>& obj);
	
namespace traits {
  // https://cran.r-project.org/web/packages/Rcpp/vignettes/Rcpp-extending.pdf
  // "The signature of Rcpp::as does not allow partial specialization. 
  // When exposing a templated class to Rcpp::as, the programmer must 
  // specialize the Rcpp::traits::exporter template class.
	template <typename T> class Exporter< mapbox::geometry::point<T> >;
	template <typename T> class Exporter< mapbox::geometry::multi_point<T> >;
	template <typename T> class Exporter< mapbox::geometry::line_string<T> >;
	template <typename T> class Exporter< mapbox::geometry::multi_line_string<T> >;
	template <typename T> class Exporter< mapbox::geometry::linear_ring<T> >;
	template <typename T> class Exporter< mapbox::geometry::polygon<T> >;
	template <typename T> class Exporter< mapbox::geometry::multi_polygon<T> >;
	
} // traits

} // Rcpp

#include <Rcpp.h>

namespace Rcpp {

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
	
	
	namespace traits {
	
		template <typename T> class Exporter< mapbox::geometry::point<T> > {
			typedef typename mapbox::geometry::point<T> pt;
			
			const static int RTYPE = Rcpp::traits::r_sexptype_traits< T >::rtype;
			Rcpp::Vector< RTYPE > vec;
			
			public:
			Exporter( SEXP x ) : vec( x ) {
				if ( TYPEOF( x ) != RTYPE ) {
					throw std::invalid_argument("mapboxgeometry - invalid R object for creating a mapbox point");
				}
			}
			
			pt get() {
				pt x({ vec[0], vec[1] });
				return x;
			}
		};
		
		template <typename T> class Exporter< mapbox::geometry::multi_point<T> > {
			typedef typename mapbox::geometry::multi_point<T> mpt;
			
			const static int RTYPE = Rcpp::traits::r_sexptype_traits< T >::rtype;
			Rcpp::Matrix< RTYPE > mat;
			
			public:
			Exporter( SEXP x ) : mat( x ) {
				if ( TYPEOF( x ) != RTYPE ) {
					throw std::invalid_argument("mapboxgeometry - invalid R object for creating a mapbox point");
				}
			}
			
			mpt get() {
				R_xlen_t n_row = mat.nrow();
				mpt x( n_row );
				R_xlen_t i;
				for( i = 0; i< n_row; i++ ) {
					Rcpp::Vector< RTYPE > v = mat( i, Rcpp::_ );
					x[i] = Rcpp::as< mapbox::geometry::point<T> >( v );
				}
				return x;
			}
		};
		
		template <typename T> class Exporter< mapbox::geometry::line_string<T> > {
			typedef typename mapbox::geometry::line_string<T> ls;
			
			const static int RTYPE = Rcpp::traits::r_sexptype_traits< T >::rtype;
			Rcpp::Matrix< RTYPE > mat;
			
			public:
			Exporter( SEXP x ) : mat( x ) {
				if ( TYPEOF( x ) != RTYPE ) {
					throw std::invalid_argument("mapboxgeometry - invalid R object for creating a mapbox point");
				}
			}
			
			ls get() {
				R_xlen_t n_row = mat.nrow();
				ls x( n_row );
				R_xlen_t i;
				for( i = 0; i< n_row; i++ ) {
					Rcpp::Vector< RTYPE > v = mat( i, Rcpp::_ );
					x[i] = Rcpp::as< mapbox::geometry::point<T> >( v );
				}
				return x;
			}
		};
		
		template <typename T> class Exporter< mapbox::geometry::multi_line_string<T> > {
			typedef typename mapbox::geometry::multi_line_string<T> mls;
			
			const static int RTYPE = Rcpp::traits::r_sexptype_traits< T >::rtype;
			Rcpp::List lst;
			
		public:
			Exporter( SEXP x ) : lst( x ) { }
			
			mls get() {
				R_xlen_t n = lst.size();
				mls x( n );
				R_xlen_t i;
				for( i = 0; i< n; i++ ) {
					Rcpp::Matrix< RTYPE > ls = lst[ i ];
					x[i] = Rcpp::as< mapbox::geometry::line_string<T> >( ls );
				}
				return x;
			}
		};
		
		template <typename T> class Exporter< mapbox::geometry::polygon<T> > {
			typedef typename mapbox::geometry::polygon<T> pl;
			
			const static int RTYPE = Rcpp::traits::r_sexptype_traits< T >::rtype;
			Rcpp::List lst;
			
		public:
			Exporter( SEXP x ) : lst( x ) { }
			
			pl get() {
				R_xlen_t n = lst.size();
				pl x( n );
				R_xlen_t i;
				for( i = 0; i< n; i++ ) {
					Rcpp::Matrix< RTYPE > ls = lst[ i ];
					x[i] = Rcpp::as< mapbox::geometry::line_string<T> >( ls );
				}
				return x;
			}
		};
		
		template <typename T> class Exporter< mapbox::geometry::multi_polygon<T> > {
			typedef typename mapbox::geometry::multi_polygon<T> mpl;
			
			const static int RTYPE = Rcpp::traits::r_sexptype_traits< T >::rtype;
			Rcpp::List lst;
			
		public:
			Exporter( SEXP x ) : lst( x ) { }
			
			mpl get() {
				R_xlen_t n = lst.size();
				mpl x( n );
				R_xlen_t i;
				for( i = 0; i< n; i++ ) {
					SEXP s = lst[ i ];
					x[i] = Rcpp::as< mapbox::geometry::polygon<T> >( s );
				}
				return x;
			}
		};
	
	} // traits
} // Rcpp


#endif

