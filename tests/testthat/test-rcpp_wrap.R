context("rcpp_wrap")

test_that("Rcpp::wrap() works",{
	
	v <- 1:2
	m <- matrix(1:4, ncol = 2, byrow = T)
	l1 <- list( m )
	l2 <- list( l1 )
	
	lst <- mapboxGeometry:::rcpp_wrap_test()
	expect_equal( lst[[1]], v )
	expect_equal( lst[[2]], m )
	expect_equal( lst[[3]], m )
	expect_equal( lst[[4]], l1 )
	expect_equal( lst[[5]], l2 )
	
})