// This file is part of gen, a lightweight C++ template library
// for linear algebra. gen itself is part of the KDE project.
//
// Copyright (C) 2006-2007 Benoit Jacob <jacob@math.jussieu.fr>
//
// gen is free software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation; either version 2 or (at your option) any later version.
//
// gen is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along
// with gen; if not, write to the Free Software Foundation, Inc., 51
// Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
//
// As a special exception, if other files instantiate templates or use macros
// or functions from this file, or you compile this file and link it
// with other works to produce a work based on this file, this file does not
// by itself cause the resulting work to be covered by the GNU General Public
// License. This exception does not invalidate any other reasons why a work
// based on this file might be covered by the GNU General Public License.

#ifndef EI_MATRIX_H
#define EI_MATRIX_H

#include "Util.h"
#include "Numeric.h"
#include "Object.h"
#include "MatrixRef.h"
#include "MatrixStorage.h"

template<typename _Scalar, int _Rows, int _Cols>
class Matrix : public Object<_Scalar, Matrix<_Scalar, _Rows, _Cols> >,
                 public MatrixStorage<_Scalar, _Rows, _Cols>
{
  public:
    friend class Object<_Scalar, Matrix>;
    typedef      Object<_Scalar, Matrix>            Base;
    typedef      MatrixStorage<_Scalar, _Rows, _Cols> Storage;
    typedef      _Scalar                                Scalar;
    typedef      MatrixRef<Matrix>                  Ref;
    typedef      MatrixConstRef<Matrix>             ConstRef;
    friend class MatrixRef<Matrix>;
    friend class MatrixConstRef<Matrix>;
    
    static const int RowsAtCompileTime = _Rows, ColsAtCompileTime = _Cols;
    
    const Scalar* array() const
    { return Storage::m_array; }
    
    Scalar* array()
    { return Storage::m_array; }
    
  private:
    Ref _ref() { return Ref(*this); }
    ConstRef _constRef() const { return ConstRef(*this); }
    
    const Scalar& _read(int row, int col) const
    {
      EI_CHECK_RANGES(*this, row, col);
      return array()[row + col * Storage::_rows()];
    }
    
    Scalar& _write(int row, int col)
    {
      EI_CHECK_RANGES(*this, row, col);
      return array()[row + col * Storage::_rows()];
    }
    
  public:
    template<typename OtherDerived> 
    Matrix& operator=(const Object<Scalar, OtherDerived>& other)
    {
      resize(other.rows(), other.cols());
      return Base::operator=(other);
    }
    
    Matrix& operator=(const Matrix& other)
    {
      resize(other.rows(), other.cols());
      return Base::operator=(other);
    }
    
    EI_INHERIT_ASSIGNMENT_OPERATOR(Matrix, +=)
    EI_INHERIT_ASSIGNMENT_OPERATOR(Matrix, -=)
    EI_INHERIT_SCALAR_ASSIGNMENT_OPERATOR(Matrix, *=)
    EI_INHERIT_SCALAR_ASSIGNMENT_OPERATOR(Matrix, /=)
    
    explicit Matrix(int rows = 1, int cols = 1) : Storage(rows, cols) {}
    template<typename OtherDerived>
    Matrix(const Object<Scalar, OtherDerived>& other) : Storage(other.rows(), other.cols())
    {
      *this = other;
    }
    Matrix(const Matrix& other) : Storage(other.rows(), other.cols())
    {
      *this = other;
    }
    ~Matrix() {}
};

#define EI_MAKE_TYPEDEFS(Type, TypeSuffix, Size, SizeSuffix) \
typedef Matrix<Type, Size, Size> Matrix##SizeSuffix##TypeSuffix; \
typedef Matrix<Type, Size, 1>    Vector##SizeSuffix##TypeSuffix; \
typedef Matrix<Type, 1, Size>    RowVector##SizeSuffix##TypeSuffix;

#define EI_MAKE_TYPEDEFS_ALL_SIZES(Type, TypeSuffix) \
EI_MAKE_TYPEDEFS(Type, TypeSuffix, 2, 2) \
EI_MAKE_TYPEDEFS(Type, TypeSuffix, 3, 3) \
EI_MAKE_TYPEDEFS(Type, TypeSuffix, 4, 4) \
EI_MAKE_TYPEDEFS(Type, TypeSuffix, Dynamic, X)

EI_MAKE_TYPEDEFS_ALL_SIZES(int,                  i)
EI_MAKE_TYPEDEFS_ALL_SIZES(float,                f)
EI_MAKE_TYPEDEFS_ALL_SIZES(double,               d)
EI_MAKE_TYPEDEFS_ALL_SIZES(std::complex<int>,    ci)
EI_MAKE_TYPEDEFS_ALL_SIZES(std::complex<float>,  cf)
EI_MAKE_TYPEDEFS_ALL_SIZES(std::complex<double>, cd)

#undef EI_MAKE_TYPEDEFS_ALL_SIZES
#undef EI_MAKE_TYPEDEFS

#define EI_USING_MATRIX_TYPEDEFS_FOR_TYPE_AND_SIZE(Type, TypeSuffix, Size, SizeSuffix) \
using Eigen::Matrix##SizeSuffix##TypeSuffix; \
using Eigen::Vector##SizeSuffix##TypeSuffix; \
using Eigen::RowVector##SizeSuffix##TypeSuffix;

#define EI_USING_MATRIX_TYPEDEFS_FOR_TYPE(Type, TypeSuffix) \
EI_USING_MATRIX_TYPEDEFS_FOR_TYPE_AND_SIZE(Type, TypeSuffix, 2, 2) \
EI_USING_MATRIX_TYPEDEFS_FOR_TYPE_AND_SIZE(Type, TypeSuffix, 3, 3) \
EI_USING_MATRIX_TYPEDEFS_FOR_TYPE_AND_SIZE(Type, TypeSuffix, 4, 4) \
EI_USING_MATRIX_TYPEDEFS_FOR_TYPE_AND_SIZE(Type, TypeSuffix, Dynamic, X)

#define EI_USING_MATRIX_TYPEDEFS \
EI_USING_MATRIX_TYPEDEFS_FOR_TYPE(int,                  i) \
EI_USING_MATRIX_TYPEDEFS_FOR_TYPE(float,                f) \
EI_USING_MATRIX_TYPEDEFS_FOR_TYPE(double,               d) \
EI_USING_MATRIX_TYPEDEFS_FOR_TYPE(std::complex<int>,    ci) \
EI_USING_MATRIX_TYPEDEFS_FOR_TYPE(std::complex<float>,  cf) \
EI_USING_MATRIX_TYPEDEFS_FOR_TYPE(std::complex<double>, cd)

#include "Eval.h"
#include "MatrixOps.h"
#include "ScalarOps.h"


#endif // EI_MATRIX_H
