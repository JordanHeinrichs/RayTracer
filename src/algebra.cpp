//---------------------------------------------------------------------------
//
// CPSC453 -- Introduction to Computer Graphics
// Assignment 2
//
// Classes and functions for manipulating points, vectors, matrices,
// and colors. You probably won't need to modify anything in these
// two files.
//
// Adapted from CS488 A2 University of Waterloo Computer Graphics Lab / 2003
//
//---------------------------------------------------------------------------

#include "algebra.h"

namespace
{
    const double EPSILON = 1e-7;
}

void Vector3D::normalize()
{
    const double currentLength = length();
    v_[X_INDEX] /= currentLength;
    v_[Y_INDEX] /= currentLength;
    v_[Z_INDEX] /= currentLength;
}

void Vector4D::normalize()
{
    if (v_[W_INDEX] > EPSILON)
    {
        printf("Error, can not normalize a point\n");
        return;
    }
    const double currentLength = length();
    v_[X_INDEX] /= currentLength;
    v_[Y_INDEX] /= currentLength;
    v_[Z_INDEX] /= currentLength;
}

bool Point3D::operator ==(const Point3D& other) const
{
    bool status = true;
    status &= std::fabs(v_[X_INDEX] - other.v_[X_INDEX]) < EPSILON;
    status &= std::fabs(v_[Y_INDEX] - other.v_[Y_INDEX]) < EPSILON;
    status &= std::fabs(v_[Z_INDEX] - other.v_[Z_INDEX]) < EPSILON;
    return status;
}


bool Vector4D::operator ==(const Vector4D& other) const
{
    bool status = true;
    status &= std::fabs(v_[X_INDEX] - other.v_[X_INDEX]) < EPSILON;
    status &= std::fabs(v_[Y_INDEX] - other.v_[Y_INDEX]) < EPSILON;
    status &= std::fabs(v_[Z_INDEX] - other.v_[Z_INDEX]) < EPSILON;
    status &= std::fabs(v_[W_INDEX] - other.v_[W_INDEX]) < EPSILON;
    return status;
}

/*
 * Define some helper functions for matrix inversion.
 */

static void swaprows(Matrix4x4& a, size_t r1, size_t r2)
{
    std::swap(a[r1][0], a[r2][0]);
    std::swap(a[r1][1], a[r2][1]);
    std::swap(a[r1][2], a[r2][2]);
    std::swap(a[r1][3], a[r2][3]);
}

static void dividerow(Matrix4x4& a, size_t r, double fac)
{
    a[r][0] /= fac;
    a[r][1] /= fac;
    a[r][2] /= fac;
    a[r][3] /= fac;
}

static void submultrow(Matrix4x4& a, size_t dest, size_t src, double fac)
{
    a[dest][0] -= fac * a[src][0];
    a[dest][1] -= fac * a[src][1];
    a[dest][2] -= fac * a[src][2];
    a[dest][3] -= fac * a[src][3];
}

/*
 * invertMatrix
 *
 * I lifted this code from the skeleton code of a raytracer assignment
 * from a different school.    I taught that course too, so I figured it
 * would be okay.
 */
Matrix4x4 Matrix4x4::invert() const
{
    /* The algorithm is plain old Gauss-Jordan elimination
         with partial pivoting. */

    Matrix4x4 a(*this);
    Matrix4x4 ret;

    /* Loop over cols of a from left to right,
         eliminating above and below diag */

    /* Find largest pivot in column j among rows j..3 */
    for(size_t j = 0; j < 4; ++j)
    {
        size_t i1 = j; /* Row with largest pivot candidate */
        for(size_t i = j + 1; i < 4; ++i)
        {
            if(fabs(a[i][j]) > fabs(a[i1][j]))
            {
                i1 = i;
            }
        }

        /* Swap rows i1 and j in a and ret to put pivot on diagonal */
        swaprows(a, i1, j);
        swaprows(ret, i1, j);

        /* Scale row j to have a unit diagonal */
        if(a[j][j] == 0.0)
        {
            // Theoretically throw an exception.
            return ret;
        }

        dividerow(ret, j, a[j][j]);
        dividerow(a, j, a[j][j]);

        /* Eliminate off-diagonal elems in col j of a, doing identical
             ops to b */
        for(size_t i = 0; i < 4; ++i)
        {
            if(i != j)
            {
                submultrow(ret, i, j, a[i][j]);
                submultrow(a, i, j, a[i][j]);
            }
        }
    }

    return ret;
}
