/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Mikael Lagerkvist <lagerkvist@gecode.org>
 *     Christian Schulte <schulte@gecode.org>
 *
 *  Copyright:
 *     Mikael Lagerkvist, 2005
 *     Christian Schulte, 2009
 *
 *  Last modified:
 *     $Date: 2009-10-05 14:07:04 +0200 (Mon, 05 Oct 2009) $ by $Author: schulte $
 *     $Revision: 9815 $
 *
 *  This file is part of Gecode, the generic constraint
 *  development environment:
 *     http://www.gecode.org
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef __GECODE_SCHEDULING_HH__
#define __GECODE_SCHEDULING_HH__

#include <gecode/int.hh>

/*
 * Configure linking
 *
 */
#if !defined(GECODE_STATIC_LIBS) && \
    (defined(__CYGWIN__) || defined(__MINGW32__) || defined(_MSC_VER))

#ifdef GECODE_BUILD_SCHEDULING
#define GECODE_SCHEDULING_EXPORT __declspec( dllexport )
#else
#define GECODE_SCHEDULING_EXPORT __declspec( dllimport )
#endif

#else

#ifdef GECODE_GCC_HAS_CLASS_VISIBILITY
#define GECODE_SCHEDULING_EXPORT __attribute__ ((visibility("default")))
#else
#define GECODE_SCHEDULING_EXPORT
#endif

#endif

// Configure auto-linking
#ifndef GECODE_BUILD_SCHEDULING
#define GECODE_LIBRARY_NAME "Scheduling"
#include <gecode/support/auto-link.hpp>
#endif

/**
 * \namespace Gecode::Scheduling
 * \brief Scheduling constraints and branchers
 *
 */

namespace Gecode {

  /**
   * \defgroup TaskModelScheduling Scheduling constraints and branchers
   * \ingroup TaskModel
   */
  //@{
  /**
   * \brief Post propagators for the cumulatives constraint
   *
   * This function creates propagators for the cumulatives constraint
   * presented in <em> "A new multi-resource cumulatives constraint
   * with negative heights"</em>, Nicolas Beldiceanu and Mats
   * Carlsson, Principles and Practice of Constraint Programming 2002.
   *
   * The constraint models a set of machines and a set of tasks that
   * should be assigned to the machines. The machines have a positive
   * resource limit and the tasks each have a resource usage that can
   * be either positive, negative, or zero. The constraint is enforced
   * over each point in time for a machine where there is at least one
   * task assigned.
   *
   * The limit for a machine is either the maximum amount available at
   * any given time (\a at_most = true), or else the least amount to
   * be used (\a at_most = false).
   *
   * \param home current space
   * \param machine \f$ machine_i \f$ is the machine assigned to task \f$ i \f$
   * \param start \f$ start_i \f$ is the start date assigned to task \f$ i \f$
   * \param duration \f$ duration_i \f$ is the duration of task \f$ i \f$
   * \param end \f$ end_i \f$ is the end date assigned to task \f$ i \f$
   * \param height \f$ height_i \f$ is the height is the amount of
   *               resources consumed by task \f$ i \f$
   * \param limit \f$ limit_r \f$ is the amount of resource available
   *              for machine \f$ r \f$
   * \param at_most \a at_most tells if the amount of resources used
   *                for a machine should be less than the limit (\a at_most
   *                = true) or greater than the limit (\a at_most = false)
   * \param icl Supports value-consistency only (\a icl = ICL_VAL, default).
   *
   * \exception Int::ArgumentSizeMismatch thrown if the sizes 
   *            of the arguments representing tasks does not match.
   * \exception Int::OutOfLimits thrown if any numerical argument is
   *            larger than Int::Limits::max or less than
   *            Int::Limits::min.
   */
  GECODE_SCHEDULING_EXPORT void
  cumulatives(Space& home, const IntVarArgs& machine,
              const IntVarArgs& start, const IntVarArgs& duration,
              const IntVarArgs& end, const IntVarArgs& height,
              const IntArgs& limit, bool at_most,
              IntConLevel icl=ICL_DEF);
  /** \brief Post propagators for the cumulatives constraint.
   *
   * \copydoc cumulatives()
   */
  GECODE_SCHEDULING_EXPORT void
  cumulatives(Space& home, const IntArgs& machine,
              const IntVarArgs& start, const IntVarArgs& duration,
              const IntVarArgs& end, const IntVarArgs& height,
              const IntArgs& limit, bool at_most,
              IntConLevel icl=ICL_DEF);
  /** \brief Post propagators for the cumulatives constraint.
   *
   * \copydoc cumulatives()
   */
  GECODE_SCHEDULING_EXPORT void
  cumulatives(Space& home, const IntVarArgs& machine,
              const IntVarArgs& start, const IntArgs& duration,
              const IntVarArgs& end, const IntVarArgs& height,
              const IntArgs& limit, bool at_most,
              IntConLevel icl=ICL_DEF);
  /** \brief Post propagators for the cumulatives constraint.
   *
   * \copydoc cumulatives()
   */
  GECODE_SCHEDULING_EXPORT void
  cumulatives(Space& home, const IntArgs& machine,
              const IntVarArgs& start, const IntArgs& duration,
              const IntVarArgs& end, const IntVarArgs& height,
              const IntArgs& limit, bool at_most,
              IntConLevel icl=ICL_DEF);
  /** \brief Post propagators for the cumulatives constraint.
   *
   * \copydoc cumulatives()
   */
  GECODE_SCHEDULING_EXPORT void
  cumulatives(Space& home, const IntVarArgs& machine,
              const IntVarArgs& start, const IntVarArgs& duration,
              const IntVarArgs& end, const IntArgs& height,
              const IntArgs& limit, bool at_most,
              IntConLevel icl=ICL_DEF);
  /** \brief Post propagators for the cumulatives constraint.
   *
   * \copydoc cumulatives()
   */
  GECODE_SCHEDULING_EXPORT void
  cumulatives(Space& home, const IntArgs& machine,
              const IntVarArgs& start, const IntVarArgs& duration,
              const IntVarArgs& end, const IntArgs& height,
              const IntArgs& limit, bool at_most,
              IntConLevel icl=ICL_DEF);
  /** \brief Post propagators for the cumulatives constraint.
   *
   * \copydoc cumulatives()
   */
  GECODE_SCHEDULING_EXPORT void
  cumulatives(Space& home, const IntVarArgs& machine,
              const IntVarArgs& start, const IntArgs& duration,
              const IntVarArgs& end, const IntArgs& height,
              const IntArgs& limit, bool at_most,
              IntConLevel icl=ICL_DEF);
  /** \brief Post propagators for the cumulatives constraint.
   *
   * \copydoc cumulatives()
   */
  GECODE_SCHEDULING_EXPORT void
  cumulatives(Space& home, const IntArgs& machine,
              const IntVarArgs& start, const IntArgs& duration,
              const IntVarArgs& end, const IntArgs& height,
              const IntArgs& limit, bool at_most,
              IntConLevel icl=ICL_DEF);

  /** \brief Post propagators for scheduling tasks on unary resources
   *
   * Schedule tasks with start times \a s and processing times \a p
   * on a unary resource. The propagator uses the algorithms from:
   *   Petr Vil�m, Global Constraints in Scheduling, PhD thesis, 
   *   Charles University, Prague, Czech Republic, 2007.
   * 
   * The propagator performs overload checking, detectable precendence
   * propagation, not-first-not-last propagation, and edge finding.
   *
   *  - Throws an exception of type Int::ArgumentSizeMismatch, if \a s 
   *    and \a p are of different size.
   *  - Throws an exception of type Int::ArgumentSame, if \a s contains
   *    the same unassigned variable multiply.
   *  - Throws an exception of type Int::OutOfLimits, if \a p contains
   *    an integer that is not strictly positive or that could generate
   *    an overflow.
   */
  GECODE_SCHEDULING_EXPORT void
  unary(Space& home, const IntVarArgs& s, const IntArgs& p);

  /** \brief Post propagators for scheduling optional tasks on unary resources
   *
   * Schedule optional tasks with start times \a s, processing times \a p,
   * and whether a task is mandatory \a m (a task is mandatory if the
   * Boolean variable is 1) on a unary resource. The propagator uses the 
   * algorithms from:
   *   Petr Vil�m, Global Constraints in Scheduling, PhD thesis, 
   *   Charles University, Prague, Czech Republic, 2007.
   * 
   * The propagator performs overload checking, detectable precendence
   * propagation, not-first-not-last propagation, and edge finding.
   *
   *  - Throws an exception of type Int::ArgumentSizeMismatch, if \a s,
   *    \a p, or \a m are of different size.
   *  - Throws an exception of type Int::ArgumentSame, if \a s contains
   *    the same unassigned variable multiply.
   *  - Throws an exception of type Int::OutOfLimits, if \a p contains
   *    an integer that is not strictly positive or that could generate
   *    an overflow.
   */
  GECODE_SCHEDULING_EXPORT void
  unary(Space& home, const IntVarArgs& s, const IntArgs& p, 
        const BoolVarArgs& m);
  //@}
}

#endif

// STATISTICS: scheduling-post
