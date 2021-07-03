template <typename P>
class BoundingBox {
	P _lo;
	P _hi;

public:
	BoundingBox(P const p0, P const p1) 
		: _lo{std::min(p0.x, p1.x), std::min(p0.y, p1.y)}
		, _hi{std::max(p0.x, p1.x), std::max(p0.y, p1.y)}
	{}

	inline P const& lo() const
	{
		return _lo;
	}

	inline P const& hi() const
	{
		return _hi;
	}

	inline auto& expand_to_contain(P const p)
	{
		_lo.x = std::min(_lo.x, p.x);
		_lo.y = std::min(_lo.y, p.y);

		_hi.x = std::max(_hi.x, p.x);
		_hi.y = std::max(_hi.y, p.y);

		return *this;
	}

	inline auto& clip_within(Image const& image)
	{
		_lo.x = std::clamp(_lo.x, 0, image.width() - 1);
		_lo.y = std::clamp(_lo.y, 0, image.height() - 1);

		_hi.x = std::clamp(_hi.x, 0, image.width() - 1);
		_hi.y = std::clamp(_hi.y, 0, image.height() - 1);

		return *this;
	}

	template <typename Functor>
	inline void for_each(Functor && functor) const
	{
		P p;
		for (p.y = _lo.y; p.y <= _hi.y; p.y++) {
			for (p.x = _lo.x; p.x <= _hi.x; p.x++) {
				functor(const_cast<P const&>(p));
			}
		}
	}
};