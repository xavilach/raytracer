#ifndef VEC3_HH_
#define VEC3_HH_

namespace Raytracer
{
class Vec3
{
public:
    Vec3();
    Vec3(double x);
    Vec3(double x, double y, double z);

    double x() const;
    double y() const;
    double z() const;

    double square_length() const;
    double length() const;
    double dot(const Vec3 &v) const;
    Vec3 cross(const Vec3 &v) const;

    Vec3 &normalize();
    Vec3 normalized() const;

    const Vec3 &operator+() const;
    Vec3 operator-() const;

    Vec3 &operator+=(const Vec3 &v);
    Vec3 &operator-=(const Vec3 &v);
    Vec3 &operator*=(const Vec3 &v);
    Vec3 &operator/=(const Vec3 &v);

    Vec3 &operator*=(const double k);
    Vec3 &operator/=(const double k);

private:
    double m_x;
    double m_y;
    double m_z;
};

Vec3 operator+(const Vec3 &v0, const Vec3 &v1);
Vec3 operator-(const Vec3 &v0, const Vec3 &v1);
Vec3 operator*(const Vec3 &v0, const Vec3 &v1);
Vec3 operator/(const Vec3 &v0, const Vec3 &v1);

Vec3 operator*(double k, const Vec3 &v);
Vec3 operator*(const Vec3 &v, double k);
Vec3 operator/(const Vec3 &v, double k);

} // namespace Raytracer

#endif /*VEC3_HH_*/