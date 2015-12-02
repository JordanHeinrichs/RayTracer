#pragma once
//---------------------------------------------------------------------------
//
// CPSC453 -- Introduction to Computer Graphics
// Assignment 2
//
// Classes and functions for manipulating points, vectors, matrices,
// and colors.  You probably won't need to modify anything in these
// two files.
//
// Adapted from CS488 A2 University of Waterloo Computer Graphics Lab / 2003
//
//---------------------------------------------------------------------------

#include <iostream>
#include <algorithm>
#include <cmath>

#define X_INDEX 0
#define Y_INDEX 1
#define Z_INDEX 2
#define W_INDEX 3

class Point2D
{
public:
    Point2D()
    {
        v_[X_INDEX] = 0.0;
        v_[Y_INDEX] = 0.0;
    }
    Point2D(double x, double y)
    {
        v_[X_INDEX] = x;
        v_[Y_INDEX] = y;
    }
    Point2D(const Point2D& other)
    {
        v_[X_INDEX] = other.v_[X_INDEX];
        v_[Y_INDEX] = other.v_[Y_INDEX];
    }

    Point2D& operator =(const Point2D& other)
    {
        v_[X_INDEX] = other.v_[X_INDEX];
        v_[Y_INDEX] = other.v_[Y_INDEX];
        return *this;
    }

    double& operator[](size_t idx)
    {
        return v_[ idx ];
    }
    double operator[](size_t idx) const
    {
        return v_[ idx ];
    }

private:
    double v_[2];
};

class Point3D
{
public:
    Point3D()
    {
        v_[X_INDEX] = 0.0;
        v_[Y_INDEX] = 0.0;
        v_[Z_INDEX] = 0.0;
    }
    Point3D(double x, double y, double z)
    {
        v_[X_INDEX] = x;
        v_[Y_INDEX] = y;
        v_[Z_INDEX] = z;
    }
    Point3D(const Point3D& other)
    {
        v_[X_INDEX] = other.v_[X_INDEX];
        v_[Y_INDEX] = other.v_[Y_INDEX];
        v_[Z_INDEX] = other.v_[Z_INDEX];
    }

    Point2D to2D() const
    {
        return Point2D(v_[X_INDEX], v_[Y_INDEX]);
    }

    Point3D& operator =(const Point3D& other)
    {
        v_[X_INDEX] = other.v_[X_INDEX];
        v_[Y_INDEX] = other.v_[Y_INDEX];
        v_[Z_INDEX] = other.v_[Z_INDEX];
        return *this;
    }

    double& operator[](size_t idx)
    {
        return v_[ idx ];
    }
    double operator[](size_t idx) const
    {
        return v_[ idx ];
    }

private:
    double v_[3];
};

class Vector3D
{
public:
    Vector3D()
    {
        v_[X_INDEX] = 0.0;
        v_[Y_INDEX] = 0.0;
        v_[Z_INDEX] = 0.0;
    }
    Vector3D(double x, double y, double z)
    {
        v_[X_INDEX] = x;
        v_[Y_INDEX] = y;
        v_[Z_INDEX] = z;
    }
    Vector3D(const Vector3D& other)
    {
        v_[X_INDEX] = other.v_[X_INDEX];
        v_[Y_INDEX] = other.v_[Y_INDEX];
        v_[Z_INDEX] = other.v_[Z_INDEX];
    }
    Vector3D(const Point2D& other)
    {
        v_[X_INDEX] = other[X_INDEX];
        v_[Y_INDEX] = other[Y_INDEX];
        v_[Z_INDEX] = 1.0;
    }

    Vector3D& operator =(const Vector3D& other)
    {
        v_[X_INDEX] = other.v_[X_INDEX];
        v_[Y_INDEX] = other.v_[Y_INDEX];
        v_[Z_INDEX] = other.v_[Z_INDEX];
        return *this;
    }

    double& operator[](size_t idx)
    {
        return v_[ idx ];
    }
    double operator[](size_t idx) const
    {
        return v_[ idx ];
    }
    Vector3D operator +(const Vector3D& other)
    {
        return Vector3D(
            v_[X_INDEX] + other.v_[X_INDEX],
            v_[Y_INDEX] + other.v_[Y_INDEX],
            v_[Z_INDEX] + other.v_[Z_INDEX]);
    }
    Vector3D operator -(const Vector3D& other)
    {
        return Vector3D(
            v_[X_INDEX] - other.v_[X_INDEX],
            v_[Y_INDEX] - other.v_[Y_INDEX],
            v_[Z_INDEX] - other.v_[Z_INDEX]);
    }
    double dot(const Vector3D& other) const
    {
        return v_[X_INDEX]*other.v_[X_INDEX] + v_[Y_INDEX]*other.v_[Y_INDEX] + v_[Z_INDEX]*other.v_[Z_INDEX];
    }

    double length2() const
    {
        return v_[X_INDEX]*v_[X_INDEX] + v_[Y_INDEX]*v_[Y_INDEX] + v_[Z_INDEX]*v_[Z_INDEX];
    }
    double length() const
    {
        return sqrt(length2());
    }

    void normalize();

    Vector3D cross(const Vector3D& other) const
    {
        return Vector3D(
            v_[Y_INDEX]*other[Z_INDEX] - v_[Z_INDEX]*other[Y_INDEX],
            v_[Z_INDEX]*other[X_INDEX] - v_[X_INDEX]*other[Z_INDEX],
            v_[X_INDEX]*other[Y_INDEX] - v_[Y_INDEX]*other[X_INDEX]);
    }

    Point2D toPoint() const
    {
        return Point2D(v_[X_INDEX], v_[Y_INDEX]);
    }

private:
    double v_[3];
};

inline Vector3D operator *(double s, const Vector3D& v)
{
    return Vector3D(s*v[X_INDEX], s*v[Y_INDEX], s*v[Z_INDEX]);
}

inline Vector3D operator +(const Vector3D& a, const Vector3D& b)
{
    return Vector3D(a[X_INDEX]+b[X_INDEX], a[Y_INDEX]+b[Y_INDEX], a[Z_INDEX]+b[Z_INDEX]);
}

inline Point3D operator +(const Point3D& a, const Vector3D& b)
{
    return Point3D(a[X_INDEX]+b[X_INDEX], a[Y_INDEX]+b[Y_INDEX], a[Z_INDEX]+b[Z_INDEX]);
}

inline Point3D operator +(const Point3D& a, const Point3D& b)
{
    return Point3D(a[X_INDEX]+b[X_INDEX], a[Y_INDEX]+b[Y_INDEX], a[Z_INDEX]+b[Z_INDEX]);
}

inline Vector3D operator -(const Point3D& a, const Point3D& b)
{
    return Vector3D(a[X_INDEX]-b[X_INDEX], a[Y_INDEX]-b[Y_INDEX], a[Z_INDEX]-b[Z_INDEX]);
}

inline Vector3D operator -(const Vector3D& a, const Vector3D& b)
{
    return Vector3D(a[X_INDEX]-b[X_INDEX], a[Y_INDEX]-b[Y_INDEX], a[Z_INDEX]-b[Z_INDEX]);
}

inline Vector3D operator -(const Vector3D& a)
{
    return Vector3D(-a[X_INDEX], -a[Y_INDEX], -a[Z_INDEX]);
}

inline Point3D operator -(const Point3D& a, const Vector3D& b)
{
    return Point3D(a[X_INDEX]-b[X_INDEX], a[Y_INDEX]-b[Y_INDEX], a[Z_INDEX]-b[Z_INDEX]);
}

inline Vector3D cross(const Vector3D& a, const Vector3D& b)
{
    return a.cross(b);
}

inline std::ostream& operator <<(std::ostream& os, const Point2D& p)
{
    return os << "p<" << p[X_INDEX] << "," << p[Y_INDEX] << ">";
}

inline std::ostream& operator <<(std::ostream& os, const Point3D& p)
{
    return os << "p<" << p[X_INDEX] << "," << p[Y_INDEX] << "," << p[Z_INDEX] << ">";
}

inline std::ostream& operator <<(std::ostream& os, const Vector3D& v)
{
    return os << "v<" << v[X_INDEX] << "," << v[Y_INDEX] << "," << v[Z_INDEX] << ">";
}

class Vector4D
{
public:
    Vector4D()
    {
        v_[X_INDEX] = 0.0;
        v_[Y_INDEX] = 0.0;
        v_[Z_INDEX] = 0.0;
        v_[W_INDEX] = 0.0;
    }
    Vector4D(double x, double y, double z, double w)
    {
        v_[X_INDEX] = x;
        v_[Y_INDEX] = y;
        v_[Z_INDEX] = z;
        v_[W_INDEX] = w;
    }
    Vector4D(const Vector4D& other)
    {
        v_[X_INDEX] = other.v_[X_INDEX];
        v_[Y_INDEX] = other.v_[Y_INDEX];
        v_[Z_INDEX] = other.v_[Z_INDEX];
        v_[W_INDEX] = other.v_[W_INDEX];
    }
    Vector4D(const Point3D& other)
    {
        v_[X_INDEX] = other[X_INDEX];
        v_[Y_INDEX] = other[Y_INDEX];
        v_[Z_INDEX] = other[Z_INDEX];
        v_[W_INDEX] = 1.0;
    }
    Vector4D(const Vector3D& other)
    {
        v_[X_INDEX] = other[X_INDEX];
        v_[Y_INDEX] = other[Y_INDEX];
        v_[Z_INDEX] = other[Z_INDEX];
        v_[W_INDEX] = 0.0;
    }

    Vector4D& operator =(const Vector4D& other)
    {
        v_[X_INDEX] = other.v_[X_INDEX];
        v_[Y_INDEX] = other.v_[Y_INDEX];
        v_[Z_INDEX] = other.v_[Z_INDEX];
        v_[W_INDEX] = other.v_[W_INDEX];
        return *this;
    }

    double& operator[](size_t idx)
    {
        return v_[ idx ];
    }
    double operator[](size_t idx) const
    {
        return v_[ idx ];
    }
    Vector4D operator +(const Vector4D& other)
    {
        return Vector4D(
            v_[X_INDEX] + other.v_[X_INDEX],
            v_[Y_INDEX] + other.v_[Y_INDEX],
            v_[Z_INDEX] + other.v_[Z_INDEX],
            v_[W_INDEX] + other.v_[W_INDEX]);
    }
    Vector4D operator -(const Vector4D& other)
    {
        return Vector4D(
            v_[X_INDEX] - other.v_[X_INDEX],
            v_[Y_INDEX] - other.v_[Y_INDEX],
            v_[Z_INDEX] - other.v_[Z_INDEX],
            v_[W_INDEX] - other.v_[W_INDEX]);
    }
    bool operator ==(const Vector4D& other) const;
    inline bool operator !=(const Vector4D& other) const
    {
        return !(*this == other);
    }

    double length2() const
    {
        // This is the lenth of a Vector3D. W is not considered.
        return v_[X_INDEX]*v_[X_INDEX] + v_[Y_INDEX]*v_[Y_INDEX] + v_[Z_INDEX]*v_[Z_INDEX];
    }
    double length() const
    {
        return sqrt(length2());
    }

    double dot(const Vector4D& other) const
    {
        return v_[X_INDEX]*other.v_[X_INDEX] + v_[Y_INDEX]*other.v_[Y_INDEX] + v_[Z_INDEX]*other.v_[Z_INDEX] + v_[W_INDEX]*other.v_[W_INDEX];
    }
    void normalize();

    Point3D toPoint() const
    {
        return Point3D(v_[X_INDEX], v_[Y_INDEX], v_[Z_INDEX]);
    }

private:
    double v_[4];
};

inline std::ostream& operator <<(std::ostream& os, const Vector4D& v)
{
    return os << "v<" << v[X_INDEX] << "," << v[Y_INDEX] << "," << v[Z_INDEX] << "," << v[W_INDEX] << ">";
}

inline Vector4D operator -(const Vector4D& a)
{
    return Vector4D(-a[X_INDEX], -a[Y_INDEX], -a[Z_INDEX], -a[W_INDEX]);
}

class Matrix4x4
{
public:
    Matrix4x4()
    {
        // Construct an identity matrix
        std::fill(v_, v_+16, 0.0);
        v_[0] = 1.0;
        v_[5] = 1.0;
        v_[10] = 1.0;
        v_[15] = 1.0;
    }
    Matrix4x4(const Matrix4x4& other)
    {
        std::copy(other.v_, other.v_+16, v_);
    }
    Matrix4x4(const Vector4D row1, const Vector4D row2, const Vector4D row3,
                         const Vector4D row4)
    {
        v_[0] = row1[0];
        v_[1] = row1[1];
        v_[2] = row1[2];
        v_[3] = row1[3];

        v_[4] = row2[0];
        v_[5] = row2[1];
        v_[6] = row2[2];
        v_[7] = row2[3];

        v_[8] = row3[0];
        v_[9] = row3[1];
        v_[10] = row3[2];
        v_[11] = row3[3];

        v_[12] = row4[0];
        v_[13] = row4[1];
        v_[14] = row4[2];
        v_[15] = row4[3];
    }
    Matrix4x4(double *vals)
    {
        std::copy(vals, vals + 16, (double*)v_);
    }

    Matrix4x4& operator=(const Matrix4x4& other)
    {
        std::copy(other.v_, other.v_+16, v_);
        return *this;
    }

    Vector4D getRow(size_t row) const
    {
        return Vector4D(v_[4*row], v_[4*row+1], v_[4*row+2], v_[4*row+3]);
    }
    double *getRow(size_t row)
    {
        return (double*)v_ + 4*row;
    }

    Vector4D getColumn(size_t col) const
    {
        return Vector4D(v_[col], v_[4+col], v_[8+col], v_[12+col]);
    }

    Vector4D operator[](size_t row) const
    {
        return getRow(row);
    }
    double *operator[](size_t row)
    {
        return getRow(row);
    }

    Matrix4x4 transpose() const
    {
        return Matrix4x4(getColumn(0), getColumn(1),
                getColumn(2), getColumn(3));
    }
    Matrix4x4 invert() const;

    const double *begin() const
    {
        return (double*)v_;
    }
    const double *end() const
    {
        return begin() + 16;
    }

private:
    double v_[16];
};

inline Matrix4x4 operator *(const Matrix4x4& a, const Matrix4x4& b)
{
    Matrix4x4 ret;

    for(size_t i = 0; i < 4; ++i)
    {
        Vector4D row = a.getRow(i);

        for(size_t j = 0; j < 4; ++j)
        {
            ret[i][j] = row[X_INDEX] * b[X_INDEX][j] + row[Y_INDEX] * b[Y_INDEX][j] +
                row[Z_INDEX] * b[Z_INDEX][j] + row[3] * b[3][j];
        }
    }

    return ret;
}

inline Vector3D operator *(const Matrix4x4& M, const Vector3D& v)
{
    return Vector3D(
        v[X_INDEX] * M[0][0] + v[Y_INDEX] * M[0][1] + v[Z_INDEX] * M[0][2],
        v[X_INDEX] * M[1][0] + v[Y_INDEX] * M[1][1] + v[Z_INDEX] * M[1][2],
        v[X_INDEX] * M[2][0] + v[Y_INDEX] * M[2][1] + v[Z_INDEX] * M[2][2]);
}

inline Vector4D operator *(const Matrix4x4& M, const Vector4D& v)
{
    return Vector4D(
        v[X_INDEX] * M[0][0] + v[Y_INDEX] * M[0][1] + v[Z_INDEX] * M[0][2] + v[W_INDEX] * M[0][3],
        v[X_INDEX] * M[1][0] + v[Y_INDEX] * M[1][1] + v[Z_INDEX] * M[1][2] + v[W_INDEX] * M[1][3],
        v[X_INDEX] * M[2][0] + v[Y_INDEX] * M[2][1] + v[Z_INDEX] * M[2][2] + v[W_INDEX] * M[2][3],
        v[X_INDEX] * M[3][0] + v[Y_INDEX] * M[3][1] + v[Z_INDEX] * M[3][2] + v[W_INDEX] * M[3][3]);
}

inline Vector4D operator -(const Vector4D& v1, const Vector4D& v2)
{
    return Vector4D(v1[X_INDEX] - v2[X_INDEX],
        v1[Y_INDEX] - v2[Y_INDEX],
        v1[Z_INDEX] - v2[Z_INDEX],
        v1[W_INDEX] - v2[W_INDEX]);
}

inline Vector4D operator *(double scaler, const Vector4D& v)
{
    return Vector4D(v[X_INDEX] * scaler,
        v[Y_INDEX] * scaler,
        v[Z_INDEX] * scaler,
        v[W_INDEX] * scaler);
}

inline Point3D operator *(const Matrix4x4& M, const Point3D& p)
{
    return Point3D(
     p[X_INDEX] * M[0][0] + p[Y_INDEX] * M[0][1] + p[Z_INDEX] * M[0][2] + M[0][3],
     p[X_INDEX] * M[1][0] + p[Y_INDEX] * M[1][1] + p[Z_INDEX] * M[1][2] + M[1][2],
     p[X_INDEX] * M[2][0] + p[Y_INDEX] * M[2][1] + p[Z_INDEX] * M[2][2] + M[2][3]);
}

inline Vector3D transNorm(const Matrix4x4& M, const Vector3D& n)
{
    return Vector3D(
        n[X_INDEX] * M[0][0] + n[Y_INDEX] * M[1][0] + n[Z_INDEX] * M[2][0],
        n[X_INDEX] * M[0][1] + n[Y_INDEX] * M[1][1] + n[Z_INDEX] * M[2][1],
        n[X_INDEX] * M[0][2] + n[Y_INDEX] * M[1][2] + n[Z_INDEX] * M[2][2]);
}

inline std::ostream& operator <<(std::ostream& os, const Matrix4x4& M)
{
    return os << "[" << M[0][0] << " " << M[0][1] << " "
        << M[0][2] << " " << M[0][3] << "]" << std::endl
        << "[" << M[1][0] << " " << M[1][1] << " "
        << M[1][2] << " " << M[1][3] << "]" << std::endl
        << "[" << M[2][0] << " " << M[2][1] << " "
        << M[2][2] << " " << M[2][3] << "]" << std::endl
        << "[" << M[3][0] << " " << M[3][1] << " "
        << M[3][2] << " " << M[3][3] << "]";
}

class Color
{
public:
    Color()
        : r_(0.0)
        , g_(0.0)
        , b_(0.0)
    {}
    Color(double r, double g, double b)
        : r_(r)
        , g_(g)
        , b_(b)
    {}
    Color(double c)
        : r_(c)
        , g_(c)
        , b_(c)
    {}
    Color(const Color& other)
        : r_(other.r_)
        , g_(other.g_)
        , b_(other.b_)
    {}

    Color& operator =(const Color& other)
    {
        r_ = other.r_;
        g_ = other.g_;
        b_ = other.b_;
        return *this;
    }

    Color& operator +=(const Color& other)
    {
        r_ = std::max(0.0, std::min(r_ + other.r_, 1.0));
        g_ = std::max(0.0, std::min(g_ + other.g_, 1.0));
        b_ = std::max(0.0, std::min(b_ + other.b_, 1.0));
        return *this;
    }

    double red() const
    {
        return r_;
    }
    double green() const
    {
        return g_;
    }
    double blue() const
    {
        return b_;
    }

private:
    double r_;
    double g_;
    double b_;
};

inline Color operator *(double s, const Color& a)
{
    return Color(s*a.red(), s*a.green(), s*a.blue());
}

inline Color operator *(const Color& a, const Color& b)
{
    return Color(a.red()*b.red(), a.green()*b.green(), a.blue()*b.blue());
}

inline Color operator +(const Color& a, const Color& b)
{
    return Color(std::max(0.0, std::min(a.red() + b.red(), 1.0)),
        std::max(0.0, std::min(a.green() + b.green(), 1.0)),
        std::max(0.0, std::min(a.blue() + b.blue(), 1.0)));
}

inline std::ostream& operator <<(std::ostream& os, const Color& c)
{
    return os << "c<" << c.red() << "," << c.green() << "," << c.blue() << ">";
}
