#ifndef __STAN__MCMC__ADAPT__DENSE__E__NUTS__BETA__
#define __STAN__MCMC__ADAPT__DENSE__E__NUTS__BETA__

#include <stan/mcmc/covar_adapter.hpp>
#include <stan/mcmc/dense_e_nuts.hpp>

namespace stan {
  
  namespace mcmc {
    
    // The No-U-Turn Sampler (NUTS) on a
    // Euclidean manifold with dense metric
    // and adaptive stepsize
    
    template <typename M, class BaseRNG>
    class adapt_dense_e_nuts: public dense_e_nuts<M, BaseRNG>, public covar_adapter {
      
    public:
      
      adapt_dense_e_nuts(M &m, BaseRNG& rng): dense_e_nuts<M, BaseRNG>(m, rng),
                                              stepsize_adapter()
      {};
      
      ~adapt_dense_e_nuts() {};
      
      sample transition(sample& init_sample) {
        
        sample s = dense_e_nuts<M, BaseRNG>::transition(init_sample);
        
        if (this->_adapt_flag) {
          
          this->_learn_stepsize(this->_epsilon, s.accept_stat());
          this->_update_L();
          
          this->_learn_covar(this->_z.mInv, this->_z.q);
          
        }
        
        return s;
        
      }
      
    };
    
  } // mcmc
  
} // stan


#endif
