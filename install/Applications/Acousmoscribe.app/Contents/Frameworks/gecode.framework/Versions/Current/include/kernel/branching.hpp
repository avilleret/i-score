/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Christian Schulte <schulte@gecode.org>
 *     Guido Tack <tack@gecode.org>
 *
 *  Copyright:
 *     Christian Schulte, 2004
 *     Guido Tack, 2004
 *
 *  Last modified:
 *     $Date: 2009-02-05 21:48:53 +1100 (Do, 05 Feb 2009) $ by $Author: schulte $
 *     $Revision: 8155 $
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

namespace Gecode {

  /**
   * \defgroup TaskBranchViewVal Generic branching based on view and value selection
   *
   * Implements view-based branching for an array of views and value.
   * \ingroup TaskActor
   */

  //@{
  /// Status returned by member functions of view selection class
  enum ViewSelStatus {
    VSS_BEST,   ///< Current view is a best one
    VSS_BETTER, ///< Current view is better
    VSS_TIE,    ///< Current view is as good as
    VSS_WORSE   ///< Current view is worse
  };

  /// Position information
  class Pos {
  public:
    /// Position of view
    const int pos;
    /// Create position information
    Pos(int p);
  };

  /**
   * \brief Generic branching by view selection
   *
   * Implements a baseclass for view-based branching for an array of views
   * (of type \a ViewSel::View). The behaviour is
   * defined by the class \a ViewSel (which view is selected for branching).
   *
   */
  template <class ViewSel>
  class ViewBranching : public Branching {
  protected:
    /// Views to branch on
    ViewArray<typename ViewSel::View> x;
    /// Unassigned views start at x[start]
    mutable int start;
    /// View selection object
    ViewSel viewsel;
    /// Return position information
    Pos pos(Space& home);
    /// Return view according to position information \a p
    typename ViewSel::View view(const Pos& p) const;
    /// Constructor for cloning \a b
    ViewBranching(Space& home, bool share, ViewBranching& b);
  public:
    /// Constructor for creation
    ViewBranching(Space& home, ViewArray<typename ViewSel::View>& x,
                  ViewSel& vi_s);
    /// Check status of branching, return true if alternatives left
    virtual bool status(const Space& home) const;
    /// Delete branching and return its size
    virtual size_t dispose(Space& home);
  };


  /**
   * \brief Generic branching by view and value selection
   *
   * Implements view-based branching for an array of views (of type
   * \a ViewSel::View) and value (of type \a ValSel::Val). The behaviour is
   * defined by the class \a ViewSel (which view is selected for branching)
   * and the class \a ValSel (which value is selected for branching).
   *
   */
  template <class ViewSel, class ValSel>
  class ViewValBranching : public ViewBranching<ViewSel> {
  protected:
    using ViewBranching<ViewSel>::viewsel;
    using ViewBranching<ViewSel>::x;
    /// Value selection object
    ValSel valsel;
    /// Constructor for cloning \a b
    ViewValBranching(Space& home, bool share, ViewValBranching& b);
  public:
    /// Constructor for creation
    ViewValBranching(Space& home, ViewArray<typename ViewSel::View>& x,
                     ViewSel& vi_s, ValSel& va_s);
    /// Return branching description (of type Gecode::PosValDesc)
    virtual const BranchingDesc* description(Space& home);
    /// Perform commit for branching description \a d and alternative \a a
    virtual ExecStatus commit(Space& home, const BranchingDesc& d,
                              unsigned int a);
    /// Perform cloning
    virtual Actor* copy(Space& home, bool share);
    /// Delete branching and return its size
    virtual size_t dispose(Space& home);
  };


  /// %Branching descriptions storing position
  template <class ViewSel>
  class GECODE_VTABLE_EXPORT PosDesc : public BranchingDesc {
  private:
    /// Position information
    const Pos _pos;
    /// View selection description to be stored
    const typename ViewSel::Desc _viewdesc;
  public:
    /// Initialize description for branching \a b, number of alternatives \a a, position \a p, view selection description \a viewd
    PosDesc(const Branching& b, unsigned int a, const Pos& p,
            const typename ViewSel::Desc& viewd);
    /// Return position in array
    const Pos& pos(void) const;
    /// Return view selection description
    const typename ViewSel::Desc& viewdesc(void) const;
    /// Report size occupied
    virtual size_t size(void) const;
  };

  /// %Branching descriptions storing position and value
  template <class ViewSel, class ValSel>
  class GECODE_VTABLE_EXPORT PosValDesc : public PosDesc<ViewSel> {
  private:
    /// Value description to be stored
    const typename ValSel::Desc _valdesc;
    /// Value to assign to
    const typename ValSel::Val _val;
  public:
    /// Initialize description for branching \a b, position \a p, view description \a viewd, value description \a vald, and value \a n
    PosValDesc(const Branching& b, const Pos& p,
               const typename ViewSel::Desc& viewd,
               const typename ValSel::Desc& vald,
               const typename ValSel::Val& n);
    /// Return stored description
    const typename ValSel::Desc& valdesc(void) const;
    /// Return value to branch with
    const typename ValSel::Val& val(void) const;
    /// Report size occupied
    virtual size_t size(void) const;
  };
  //@}




  /*
   * Position information
   *
   */
  forceinline
  Pos::Pos(int p) : pos(p) {}


  /*
   * Branching descriptions with position
   *
   */
  template <class ViewSel>
  forceinline
  PosDesc<ViewSel>::PosDesc(const Branching& b, unsigned int a, const Pos& p,
                            const typename ViewSel::Desc& viewd)
    : BranchingDesc(b,a), _pos(p), _viewdesc(viewd) {}
  template <class ViewSel>
  forceinline const Pos&
  PosDesc<ViewSel>::pos(void) const {
    return _pos;
  }
  template <class ViewSel>
  forceinline const typename ViewSel::Desc&
  PosDesc<ViewSel>::viewdesc(void) const {
    return _viewdesc;
  }
  template <class ViewSel>
  forceinline size_t
  PosDesc<ViewSel>::size(void) const {
    return sizeof(PosDesc<ViewSel>) + _viewdesc.size();
  }


  /*
   * Branching descriptions with position and value
   *
   */
  template <class ViewSel, class ValSel>
  forceinline
  PosValDesc<ViewSel,ValSel>::PosValDesc(const Branching& b, const Pos& p,
                                         const typename ViewSel::Desc& viewd,
                                         const typename ValSel::Desc& vald,
                                         const typename ValSel::Val& n)
    : PosDesc<ViewSel>(b,ValSel::alternatives,p,viewd),
      _valdesc(vald), _val(n) {}

  template <class ViewSel, class ValSel>
  forceinline const typename ValSel::Desc&
  PosValDesc<ViewSel,ValSel>::valdesc(void) const {
    return _valdesc;
  }

  template <class ViewSel, class ValSel>
  forceinline const typename ValSel::Val&
  PosValDesc<ViewSel,ValSel>::val(void) const {
    return _val;
  }

  template <class ViewSel, class ValSel>
  forceinline size_t
  PosValDesc<ViewSel, ValSel>::size(void) const {
    return sizeof(PosValDesc<ViewSel,ValSel>) + _valdesc.size();
  }


  /*
   * Generic branching based on view selection
   *
   */

  template <class ViewSel>
  forceinline
  ViewBranching<ViewSel>::ViewBranching(Space& home,
                                        ViewArray<typename ViewSel::View>& x0,
                                        ViewSel& vi_s)
    : Branching(home), x(x0), start(0), viewsel(vi_s) {}


  template <class ViewSel>
  forceinline
  ViewBranching<ViewSel>::ViewBranching(Space& home, bool share,
                                        ViewBranching& b)
    : Branching(home,share,b), start(b.start) {
    x.update(home,share,b.x);
    viewsel.update(home,share,b.viewsel);
  }

  template <class ViewSel>
  bool
  ViewBranching<ViewSel>::status(const Space&) const {
    for (int i=start; i < x.size(); i++)
      if (!x[i].assigned()) {
        start = i;
        return true;
      }
    return false;
  }

  template <class ViewSel>
  forceinline Pos
  ViewBranching<ViewSel>::pos(Space& home) {
    assert(!x[start].assigned());
    int i = start;
    int b = i++;
    if (viewsel.init(home,x[b]) != VSS_BEST)
      for (; i < x.size(); i++)
        if (!x[i].assigned())
          switch (viewsel.select(home,x[i])) {
          case VSS_BETTER:              b=i; break;
          case VSS_BEST:                b=i; goto create;
          case VSS_TIE: case VSS_WORSE: break;
          default:                      GECODE_NEVER;
          }
  create:
    Pos p(b);
    return p;
  }

  template <class ViewSel>
  forceinline typename ViewSel::View
  ViewBranching<ViewSel>::view(const Pos& p) const {
    return x[p.pos];
  }

  template <class ViewSel>
  forceinline size_t
  ViewBranching<ViewSel>::dispose(Space& home) {
    viewsel.dispose(home);
    (void) Branching::dispose(home);
    return sizeof(ViewBranching<ViewSel>);
  }



  /*
   * Generic branching based on variable/value selection
   *
   */

  template <class ViewSel, class ValSel>
  forceinline
  ViewValBranching<ViewSel,ValSel>::
  ViewValBranching(Space& home, ViewArray<typename ViewSel::View>& x,
                   ViewSel& vi_s, ValSel& va_s)
    : ViewBranching<ViewSel>(home,x,vi_s), valsel(va_s) {}

  template <class ViewSel, class ValSel>
  forceinline
  ViewValBranching<ViewSel,ValSel>::
  ViewValBranching(Space& home, bool share, ViewValBranching& b)
    : ViewBranching<ViewSel>(home,share,b) {
    valsel.update(home,share,b.valsel);
  }

  template <class ViewSel, class ValSel>
  Actor*
  ViewValBranching<ViewSel,ValSel>::copy(Space& home, bool share) {
    return new (home)
      ViewValBranching<ViewSel,ValSel>(home,share,*this);
  }

  template <class ViewSel, class ValSel>
  const BranchingDesc*
  ViewValBranching<ViewSel,ValSel>::description(Space& home) {
    Pos p = ViewBranching<ViewSel>::pos(home);
    typename ValSel::View v(ViewBranching<ViewSel>::view(p).var());
    return new PosValDesc<ViewSel,ValSel>
      (*this,p,
       viewsel.description(home),
       valsel.description(home),valsel.val(home,v));
  }

  template <class ViewSel, class ValSel>
  ExecStatus
  ViewValBranching<ViewSel,ValSel>
  ::commit(Space& home, const BranchingDesc& d, unsigned int a) {
    const PosValDesc<ViewSel,ValSel>& pvd
      = static_cast<const PosValDesc<ViewSel,ValSel>&>(d);
    typename ValSel::View
      v(ViewBranching<ViewSel>::view(pvd.pos()).var());
    viewsel.commit(home, pvd.viewdesc(), a);
    valsel.commit(home, pvd.valdesc(), a);
    return me_failed(valsel.tell(home,a,v,pvd.val())) ? ES_FAILED : ES_OK;
  }

  template <class ViewSel, class ValSel>
  forceinline size_t
  ViewValBranching<ViewSel,ValSel>::dispose(Space& home) {
    valsel.dispose(home);
    (void) ViewBranching<ViewSel>::dispose(home);
    return sizeof(ViewValBranching<ViewSel,ValSel>);
  }

}

// STATISTICS: kernel-branch