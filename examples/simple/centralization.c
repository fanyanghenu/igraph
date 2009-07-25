
#include <igraph.h>
#include <math.h>

int main() {

  igraph_t g;
  igraph_real_t cent;
  igraph_arpack_options_t arpack_options;

  /****************************/
  /* in-star */
  igraph_star(&g, 10, IGRAPH_STAR_IN, /*center=*/ 0);
  
  igraph_centralization_degree(&g, /*res=*/ 0,
			       /*mode=*/ IGRAPH_IN, IGRAPH_NO_LOOPS,
			       &cent, /*theoretical_max=*/ 0, 
			       /*normalized=*/ 1);
  if (cent != 1.0) { 
    fprintf(stderr, "in-star, degree: %g\n", cent); 
    return 1; 
  }

  igraph_centralization_betweenness(&g, /*res=*/ 0,
				    IGRAPH_UNDIRECTED, &cent, 
				    /*theoretical_max=*/ 0,
				    /*normalized=*/ 1);
  if (cent != 1.0) { 
    fprintf(stderr, "in-star, betweenness: %g\n", cent); 
    return 2; 
  }

  igraph_centralization_closeness(&g, /*res=*/ 0,
				  IGRAPH_IN, &cent, 
				  /*theoretical_max=*/ 0,
				  /*normalization=*/ 1);
  
  if (cent != 1.0) {
    fprintf(stderr, "in-star, closeness: %g\n", cent);
    return 3;
  }

  igraph_arpack_options_init(&arpack_options);
  igraph_centralization_eigenvector_centrality(&g, /*vector=*/ 0, 
					       /*value=*/ 0, 
					       /*directed=*/ 1,
					       /*scale=*/ 1,
					       &arpack_options, &cent,
					       /*theoretical_max=*/ 0,
					       /*normalization=*/ 1);
  
  if (cent != 1.0) {
    fprintf(stderr, "out-star, eigenvector centrality: %g\n", cent);
    return 14;
  }

  igraph_destroy(&g);
  
  /****************************/
  /* out-star */
  igraph_star(&g, 10, IGRAPH_STAR_OUT, /*center=*/ 0);
  
  igraph_centralization_degree(&g, /*res=*/ 0,
			       /*mode=*/ IGRAPH_OUT, IGRAPH_NO_LOOPS,
			       &cent, /*theoretical_max=*/ 0,
			       /*normalized=*/ 1);
  if (cent != 1.0) { 
    fprintf(stderr, "out-star, degree: %g\n", cent); 
    return 11; 
  }

  igraph_centralization_betweenness(&g, /*res=*/ 0,
				    IGRAPH_UNDIRECTED, &cent,
				    /*theoretical_max=*/ 0,
				    /*normalized=*/ 1);
  if (cent != 1.0) { 
    fprintf(stderr, "out-star, betweenness: %g\n", cent); 
    return 12; 
  }

  igraph_centralization_closeness(&g, /*res=*/ 0,
				  IGRAPH_OUT, &cent, 
				  /*theoretical_max=*/ 0,
				  /*normalization=*/ 1);
  
  if (cent != 1.0) {
    fprintf(stderr, "out-star, closeness: %g\n", cent);
    return 13;
  }

  igraph_destroy(&g);
  
  /****************************/
  /* undricted star */
  igraph_star(&g, 10, IGRAPH_STAR_UNDIRECTED, /*center=*/ 0);
  
  igraph_centralization_degree(&g, /*res=*/ 0,
			       /*mode=*/ IGRAPH_ALL, IGRAPH_NO_LOOPS,
			       &cent, /*theoretical_max=*/ 0,
			       /*normalized=*/ 1);
  if (cent != 1.0) { 
    fprintf(stderr, "undirected star, degree: %g\n", cent); 
    return 21; 
  }

  igraph_centralization_betweenness(&g, /*res=*/ 0,
				    IGRAPH_UNDIRECTED, &cent,
				    /*theoretical_max=*/ 0,
				    /*normalized=*/ 1);
  if (cent != 1.0) { 
    fprintf(stderr, "undirected star, betweenness: %g\n", cent); 
    return 22; 
  }

  igraph_centralization_closeness(&g, /*res=*/ 0,
				  IGRAPH_ALL, &cent, 
				  /*theoretical_max=*/ 0,
				  /*normalization=*/ 1);
  
  if (cent != 1.0) {
    fprintf(stderr, "undirected star, closeness: %g\n", cent);
    return 23;
  }
  
  igraph_destroy(&g);

  /****************************/
  /* single dyad */
  
  igraph_small(&g, /*n=*/ 10, /*directed=*/ 0, 
	       0,1, -1);
  
  igraph_centralization_eigenvector_centrality(&g, /*vector=*/ 0,
					       /*value=*/ 0, 
					       /*directed=*/ 1,
					       /*scale=*/ 1,
					       &arpack_options, &cent,
					       /*theoretical_max=*/ 0,
					       /*normalization=*/ 1);
  
  if (cent != 1.0) {
    fprintf(stderr, "dyad, eigenvector centrality: %g\n", cent);
    return 24;
  }

  igraph_centralization_eigenvector_centrality(&g, /*vector=*/ 0,
					       /*value=*/ 0, 
					       /*directed=*/ 1,
					       /*scale=*/ 0,
					       &arpack_options, &cent,
					       /*theoretical_max=*/ 0,
					       /*normalization=*/ 1);
  
  if (fabs(cent - 1.0) > 1e-15) {
    fprintf(stderr, "dyad, eigenvector centrality, not scaled: %g\n", cent);
    return 25;
  }
    
  igraph_destroy(&g);
  
  return 0;
}