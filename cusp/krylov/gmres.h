/*
 *  Copyright 2011 The Regents of the University of California
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/*! \file gmres.h
 *  \brief Generalized Minimum Residual (GMRES) method
 */

#pragma once

#include <cusp/detail/config.h>

namespace cusp
{
namespace krylov
{

/*! \addtogroup iterative_solvers Iterative Solvers
 *  \addtogroup krylov_methods Krylov Methods
 *  \ingroup iterative_solvers
 *  \{
 */

/* \cond */
/*! \p gmres : GMRES method
 *
 * Solves the nonsymmetric, linear system A x = b
 * using the default convergence criteria.
 */
template <class LinearOperator, class Vector>
void gmres(LinearOperator& A,
           Vector& x,
           Vector& b,
           const size_t restart);

/*! \p gmres : GMRES method
 *
 * Solves the nonsymmetric, linear system A x = b without preconditioning.
 */
template <class LinearOperator,
         class Vector,
         class Monitor>
void gmres(LinearOperator& A,
           Vector& x,
           Vector& b,
           const size_t restart,
           Monitor& monitor);
/* \endcond */

/**
 * \brief GMRES method
 *
 * \tparam LinearOperator is a matrix or subclass of \p linear_operator
 * \tparam Vector vector
 * \tparam Monitor is a monitor such as \p default_monitor or \p verbose_monitor
 * \tparam Preconditioner is a matrix or subclass of \p linear_operator
 *
 * \param A matrix of the linear system
 * \param x approximate solution of the linear system
 * \param b right-hand side of the linear system
 * \param restart the method every restart inner iterations
 * \param monitor montiors iteration and determines stopping conditions
 * \param M preconditioner for A
 *
 * \par Overview
 * Solves the nonsymmetric, linear system A x = b
 * with preconditioner \p M.
 *
 * \par Example
 *
 *  The following code snippet demonstrates how to use \p gmres to
 *  solve a 10x10 Poisson problem.
 *
 *  \code
 *  #include <cusp/csr_matrix.h>
 *  #include <cusp/monitor.h>
 *  #include <cusp/krylov/gmres.h>
 *  #include <cusp/gallery/poisson.h>
 *
 *  int main(void)
 *  {
 *      // create an empty sparse matrix structure (CSR format)
 *      cusp::csr_matrix<int, float, cusp::device_memory> A;
 *
 *      // initialize matrix
 *      cusp::gallery::poisson5pt(A, 10, 10);
 *
 *      // allocate storage for solution (x) and right hand side (b)
 *      cusp::array1d<float, cusp::device_memory> x(A.num_rows, 0);
 *      cusp::array1d<float, cusp::device_memory> b(A.num_rows, 1);
 *
 *      // set stopping criteria:
 *      //  iteration_limit    = 100
 *      //  relative_tolerance = 1e-6
 *      //  absolute_tolerance = 0
 *      //  verbose            = true
 *      cusp::monitor<float> monitor(b, 100, 1e-6, 0, true);
 *      int restart = 50;
 *
 *      // set preconditioner (identity)
 *      cusp::identity_operator<float, cusp::device_memory> M(A.num_rows, A.num_rows);
 *
 *      // solve the linear system A x = b
 *      cusp::krylov::gmres(A, x, b,restart, monitor, M);
 *
 *      return 0;
 *  }
 *  \endcode

 *  \see \p monitor
 *
 */
template <class LinearOperator,
         class Vector,
         class Monitor,
         class Preconditioner>
void gmres(LinearOperator& A,
           Vector& x,
           Vector& b,
           const size_t restart,
           Monitor& monitor,
           Preconditioner& M);
/*! \}
*/

} // end namespace krylov
} // end namespace cusp

#include <cusp/krylov/detail/gmres.inl>

