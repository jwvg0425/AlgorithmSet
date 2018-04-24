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