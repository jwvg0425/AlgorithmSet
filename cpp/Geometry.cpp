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

i64 ccw(i64 x1, i64 y1, i64 x2, i64 y2, i64 x3, i64 y3)
{
	i64 cross = (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);

	if (cross > 0)
		return 1;

	if (cross < 0)
		return -1;

	return 0;
}


bool intersect(i64 x1, i64 y1, i64 x2, i64 y2, i64 x3, i64 y3, i64 x4, i64 y4)
{
	int l1l2 = ccw(x1, y1, x2, y2, x3, y3) * ccw(x1, y1, x2, y2, x4, y4);
	int l2l1 = ccw(x3, y3, x4, y4, x1, y1) * ccw(x3, y3, x4, y4, x2, y2);

	if (l1l2 == 0 && l2l1 == 0)
	{
		if (ii64(x2, y2) < ii64(x1, y1))
		{
			swap(x1, x2);
			swap(y1, y2);
		}

		if (ii64(x4, y4) < ii64(x3, y3))
		{
			swap(x3, x4);
			swap(y3, y4);
		}

		return ii64(x3, y3) <= ii64(x2, y2) && ii64(x1, y1) <= ii64(x4, y4);
	}

	return l1l2 <= 0 && l2l1 <= 0;
}
