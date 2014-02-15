#pragma once
template  <typename T> class OrderedPair
{

private:

	T X;
	T Y;

public:

	OrderedPair();

	OrderedPair(T x, T y);

	inline T getX() { return X; }

	inline T getY() { return Y; }
};

template <typename T> OrderedPair<T>::OrderedPair()
{
	X = NULL;
	Y = NULL;
}

template <typename T> OrderedPair<T>::OrderedPair(T x, T y)
{
	X = x;
	Y = y;
}
