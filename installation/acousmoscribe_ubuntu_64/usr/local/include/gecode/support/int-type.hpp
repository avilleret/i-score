/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Christian Schulte <schulte@gecode.org>
 *
 *  Copyright:
 *     Christian Schulte, 2008
 *
 *  Last modified:
 *     $Date: 2009-10-05 11:46:27 +0200 (Mon, 05 Oct 2009) $ by $Author: schulte $
 *     $Revision: 9812 $
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

#include <climits>

namespace Gecode { namespace Support {

  /// Description of integer types
  enum IntType {
    IT_CHAR = 0, ///< char integer type
    IT_SHRT = 1, ///< short integer type
    IT_INT  = 2  ///< integer type
  };

  /// Return type required to represent \a n
  IntType u_type(unsigned int n);
  /// Return type required to represent \a n
  IntType s_type(signed int n);

  forceinline IntType
  u_type(unsigned int n) {
    if (n < UCHAR_MAX)
      return IT_CHAR;
    else if (n < USHRT_MAX)
      return IT_SHRT;
    else
      return IT_INT;
  }

  forceinline IntType
  s_type(int n) {
    if ((n > SCHAR_MIN) && (n < SCHAR_MAX))
      return IT_CHAR;
    else if ((n > SHRT_MIN) && (n < SHRT_MAX))
      return IT_SHRT;
    else
      return IT_INT;
  }

}}

// STATISTICS: support-any