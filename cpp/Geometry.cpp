template<typename T>
struct point
{
    point() = default;
    point(T x_, T y_) : x(x_), y(y_) {}

    T x, y;

    double distance(const point<T>& s, const point<T>& e) const
    {
        double ldx = e.x - s.x;
        double ldy = e.y - s.y;

        double length = sqrt(ldx * ldx + ldy * ldy);

        return abs(ldx * (s.y - y) - (s.x - x) * ldy) / length;
    }
};

using ipoint = point<int>;
using i64point = point<i64>;
using dpoint = point<double>;

i64 ccw(ii64 p1, ii64 p2, ii64 p3)
{
    i64 tmp = p1.xx * p2.yy + p2.xx * p3.yy + p3.xx * p1.yy;
    tmp -= p1.yy * p2.xx + p2.yy * p3.xx + p3.yy * p1.xx;

    if (tmp > 0)
        return 1;

    if (tmp < 0)
        return -1;

    return 0;
}
