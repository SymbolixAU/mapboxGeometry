context("rcpp_wrap")

test_that("Rcpp::wrap() works",{
	
	v <- 1:2
	m <- matrix(1:4, ncol = 2, byrow = T)
	l1 <- list( m )
	l2 <- list( m )
	l3 <- list( l1 )
	
	lst <- mapboxGeometry:::rcpp_wrap_test()
	expect_equal( lst[[1]], v )
	expect_equal( lst[[2]], m )
	expect_equal( lst[[3]], m )
	expect_equal( lst[[4]], l1 )
	expect_equal( lst[[5]], l2 )
	expect_equal( lst[[6]], l3 )
	
	lst_2 <- mapboxGeometry:::rcpp_as_test()
	expect_equal( lst, lst_2 )
	
	mat <- matrix(1:1e5, ncol = 2)
	res <- mapboxGeometry:::rcpp_test_performance( mat )
	expect_equal( mat, res )
	
})