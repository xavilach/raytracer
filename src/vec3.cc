#include "vec3.hh"

#include <math.h>

Raytracer::Vec3::Vec3() : m_x(0), m_y(0), m_z(0)
{
}

Raytracer::Vec3::Vec3(double x) : m_x(x), m_y(x), m_z(x)
{
}

Raytracer::Vec3::Vec3(double x, double y, double z) : m_x(x), m_y(y), m_z(z)
{
}

double Raytracer::Vec3::x() const
{
    return m_x;
}

double Raytracer::Vec3::y() const
{
    return m_y;
}

double Raytracer::Vec3::z() const
{
    return m_z;
}

double Raytracer::Vec3::square_length() const
{
    return (m_x * m_x) + (m_y * m_y) + (m_z * m_z);
}

double Raytracer::Vec3::length() const
{
    return sqrt((m_x * m_x) + (m_y * m_y) + (m_z * m_z));
}

double Raytracer::Vec3::dot(const Vec3 &v) const
{
    return (m_x * v.m_x) + (m_y * v.m_y) + (m_z * v.m_z);
}

Raytracer::Vec3 Raytracer::Vec3::cross(const Vec3 &v) const
{
    return Vec3(
        (m_y * v.m_z) - (m_z * v.m_y),
        (m_z * v.m_x) - (m_x * v.m_z),
        (m_x * v.m_y) - (m_y * v.m_x));
}

Raytracer::Vec3 &Raytracer::Vec3::normalize()
{
    double l = length();
    if (l > 0)
    {
        double k = 1.0 / l;
        m_x *= k;
        m_y *= k;
        m_z *= k;
    }

    return *this;
}

Raytracer::Vec3 Raytracer::Vec3::normalized() const
{
    double l = length();
    double k = 1.0;

    if (l > 0)
    {
        k = 1.0 / l;
    }

    return Vec3(
        m_x * k,
        m_y * k,
        m_z * k);
}

const Raytracer::Vec3 &Raytracer::Vec3::operator+() const
{
    return *this;
}

Raytracer::Vec3 Raytracer::Vec3::operator-() const
{
    return Vec3(-m_x, m_y, -m_z);
}

Raytracer::Vec3 &Raytracer::Vec3::operator+=(const Vec3 &v)
{
    m_x += v.m_x;
    m_y += v.m_y;
    m_z += v.m_z;

    return *this;
}

Raytracer::Vec3 &Raytracer::Vec3::operator-=(const Vec3 &v)
{
    m_x -= v.m_x;
    m_y -= v.m_y;
    m_z -= v.m_z;

    return *this;
}

Raytracer::Vec3 &Raytracer::Vec3::operator*=(const Vec3 &v)
{
    m_x *= v.m_x;
    m_y *= v.m_y;
    m_z *= v.m_z;

    return *this;
}

Raytracer::Vec3 &Raytracer::Vec3::operator/=(const Vec3 &v)
{
    m_x /= v.m_x;
    m_y /= v.m_y;
    m_z /= v.m_z;

    return *this;
}

Raytracer::Vec3 &Raytracer::Vec3::operator*=(const double k)
{
    m_x *= k;
    m_y *= k;
    m_z *= k;

    return *this;
}

Raytracer::Vec3 &Raytracer::Vec3::operator/=(const double k)
{
    double k_inv = 1.0 / k;

    m_x *= k_inv;
    m_y *= k_inv;
    m_z *= k_inv;

    return *this;
}

Raytracer::Vec3 Raytracer::operator+(const Raytracer::Vec3 &v0, const Raytracer::Vec3 &v1)
{
    return Raytracer::Vec3(
        v0.x() + v1.x(),
        v0.y() + v1.y(),
        v0.z() + v1.z());
}

Raytracer::Vec3 Raytracer::operator-(const Raytracer::Vec3 &v0, const Raytracer::Vec3 &v1)
{
    return Raytracer::Vec3(
        v0.x() - v1.x(),
        v0.y() - v1.y(),
        v0.z() - v1.z());
}

Raytracer::Vec3 Raytracer::operator*(const Raytracer::Vec3 &v0, const Raytracer::Vec3 &v1)
{
    return Raytracer::Vec3(
        v0.x() * v1.x(),
        v0.y() * v1.y(),
        v0.z() * v1.z());
}

Raytracer::Vec3 Raytracer::operator/(const Raytracer::Vec3 &v0, const Raytracer::Vec3 &v1)
{
    return Raytracer::Vec3(
        v0.x() / v1.x(),
        v0.y() / v1.y(),
        v0.z() / v1.z());
}

Raytracer::Vec3 Raytracer::operator*(double k, const Raytracer::Vec3 &v)
{
    return Raytracer::Vec3(
        k * v.x(),
        k * v.y(),
        k * v.z());
}

Raytracer::Vec3 Raytracer::operator*(const Raytracer::Vec3 &v, double k)
{
    return Raytracer::Vec3(
        k * v.x(),
        k * v.y(),
        k * v.z());
}

Raytracer::Vec3 Raytracer::operator/(const Raytracer::Vec3 &v, double k)
{
    return Raytracer::Vec3(
        v.x() / k,
        v.y() / k,
        v.z() / k);
}
