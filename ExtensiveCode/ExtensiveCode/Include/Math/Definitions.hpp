#pragma once

#include <cmath>

namespace grim
{
	namespace Math
	{
		// PI definition
		const double Pi = 3.14159265358979323846;

		namespace Equality
		{
			const double LowTolerance = 0.000001;
			const double MediumTolerance = 0.00001;
			const double HighTolerance = 0.0001;
			const double VeryHighTolerance = 0.001;
		}

		template <typename T>
		inline T Absolute(const T &a) { return (a < 0 ? -a : a); }

		template <typename T, typename U>
		inline T Max(T a, U b) { return T(a > b ? a : b); }

		template <typename T, typename U>
		inline T Min(T a, U b) { return T(a < b ? a : b); }

		template <typename T, typename U, typename V>
		inline T Clamp(T current, U a, V b)
		{
			return Max<T, U>(Min<T, V>(current, b), a);
		}

		inline bool NearlyEqual(double a, double b, double EqualityTolerance = Equality::MediumTolerance)
		{
			return Absolute(a - b) <= EqualityTolerance;
		}
	}

	namespace impl
	{
		template <typename T> class BaseVector2;
		template <typename T> class BaseVector3;
	}

	// 2D Vector class templated with <float>
	typedef impl::BaseVector2<float>						Vector2f;
	// 2D Vector class templated with <float>
	typedef impl::BaseVector2<float>						Vector2;
	// 2D Vector class templated with <double>
	typedef impl::BaseVector2<double>						Vector2d;
	// 2D Vector class templated with <short>
	typedef impl::BaseVector2<short int>					Vector2s;
	// 2D Vector class templated with <int>
	typedef impl::BaseVector2<int>							Vector2i;
	// 2D Vector class templated with <long long>
	typedef impl::BaseVector2<long long>					Vector2ll;
	// 2D Vector class templated with <unsigned short>
	typedef impl::BaseVector2<unsigned short>				Vector2us;
	// 2D Vector class templated with <unsigned int>
	typedef impl::BaseVector2<unsigned int>					Vector2ui;
	// 2D Vector class templated with <unsigned long long>
	typedef impl::BaseVector2<unsigned long long>			Vector2ull;

	typedef Vector2ui										Size2i;
	typedef Vector2us										Size2s;
	typedef Vector2f										Size2f;

	// 3D Vector class templated with <float>
	typedef impl::BaseVector3<float>						Vector3f;
	// 3D Vector class templated with <float>
	typedef impl::BaseVector3<float>						Vector3;
	// 3D Vector class templated with <double>
	typedef impl::BaseVector3<double>						Vector3d;
	// 3D Vector class templated with <short>
	typedef impl::BaseVector3<short int>					Vector3s;
	// 3D Vector class templated with <int>
	typedef impl::BaseVector3<int>							Vector3i;
	// 3D Vector class templated with <long long>
	typedef impl::BaseVector3<long long>					Vector3ll;
	// 3D Vector class templated with <unsigned short>
	typedef impl::BaseVector3<unsigned short>				Vector3us;
	// 3D Vector class templated with <unsigned int>
	typedef impl::BaseVector3<unsigned int>					Vector3ui;
	// 3D Vector class templated with <unsigned long long>
	typedef impl::BaseVector3<unsigned long long>			Vector3ull;

	typedef Vector3ui										Size3i;
	typedef Vector3us										Size3s;
	typedef Vector3f										Size3f;
}
