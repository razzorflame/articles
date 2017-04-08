#pragma once

#include "Definitions.hpp"

namespace grim
{
	namespace impl
	{
		template <typename T>
		class BaseVector3
		{
		public:
			T x, y, z;

			////// Function: Vector3 (default constructor)
			//// Parameters: <none>
			//// Brief: This is a Vector3's default constructor
			///////////////////////////////////////////////////////////////
			BaseVector3();

			////// Function: Vector3 (constructor)
			//// Parameters:
			//// 	1) xValue: 	Float32 		- x component of a vector
			//// 	2) yValue: 	Float32 		- y component of a vector
			//// 	2) zValue: 	Float32 		- z component of a vector
			//// Brief: Initializes vector from components
			///////////////////////////////////////////////////////////////
			BaseVector3(const T &xValue, const T &yValue, const T &zValue);

			////// Function: Vector3 (copy constructor)
			//// Parameters:
			////	1) other	Vector3&		- other instance to copy from
			//// Brief: This is a Vector3's copy constructor
			///////////////////////////////////////////////////////////////
			template <typename U>
			explicit BaseVector3(const BaseVector3<U> &v);

			////// Function: Vector3 (destructor)
			//// Parameters: <none>
			//// Brief: This is a Vector3's destructor [= default]
			///////////////////////////////////////////////////////////////
			~BaseVector3() = default;

			////// Function: Set
			//// Parameters:
			//// 	1) xValue: 	Float32 		- x component of a vector
			//// 	2) yValue: 	Float32 		- y component of a vector
			//// 	3) yValue: 	Float32 		- z component of a vector
			//// Return: 			void 		- does not return anything
			//// Brief: Sets vector components
			///////////////////////////////////////////////////////////////
			void Set(const T &xValue, const T &yValue, const T &zValue);

			////// Function: Length
			//// Parameters: <none>
			//// Return: 			Float32 	- length of vector
			//// Brief: returns vector length = sqrt(x*x + y*y + z*z)
			///////////////////////////////////////////////////////////////
			float Length() const;

			////// Function: LengthSquared
			//// Parameters: <none>
			//// Return: 			Float32 	- squared length of vector
			//// Brief: return vector length squared = (x*x + y*y + z*z)
			///////////////////////////////////////////////////////////////
			float LengthSquared() const;

			////// Function: Distance
			//// Parameters:
			////	1) other	Vector3&		- other vector (to compute distance)
			//// Return: 		Float32 	- distance to vector
			//// Brief: return distance to other vector
			//// Distance = (A-B).Length()
			///////////////////////////////////////////////////////////////
			template <typename U>
			float Distance(const BaseVector3<U> &v) const;

			////// Function: DistanceSquared
			//// Parameters:
			////	1) other	Vector3&		- other vector (to compute distance)
			//// Return: 			Float32 	- squared distance to vector
			//// Brief: return squared distance to other vector
			//// Distance = (A-B).LengthSquared()
			///////////////////////////////////////////////////////////////
			template <typename U>
			float DistanceSquared(const BaseVector3<U> &v) const;

			////// Function: Dot (product)
			//// Parameters:
			////	1) other	Vector3&		- other vector (to compute dot product)
			//// Return: 			Float32 	- dot product of vectors
			//// Brief: return dot product of two vectors (self and 'other')
			//// Dot product = (x * other.x) + (y * other.y) + (z * other.z)
			///////////////////////////////////////////////////////////////
			template <typename U>
			float Dot(const BaseVector3<U> &v) const;

			////// Function: Cross (product)
			//// Parameters:
			////	1) other	Vector3&		- other vector (to compute cross product)
			//// Return: 		Vector3 		- cross product of vectors
			//// Brief: return cross product of two vectors (self and 'other')
			//// Cross product:
			//// Vector3U(left.y * right.z - left.z * right.y,
			////	left.z * right.x - left.x * right.z,
			////	left.x * right.y - left.y * right.x);
			//// Cross (Right, Forward) = Up
			///////////////////////////////////////////////////////////////
			template <typename U>
			BaseVector3<T> Cross(const BaseVector3<U> &v) const;

			////// Function: Reflect (vector) [const]
			//// Parameters:
			////	1) normal	Vector3		- wall normal to be reflected from
			//// Return: 		Vector3 	- reflected copy vector
			//// Brief: return reflected copy of self
			//// Reflected vector is used in for instance ball bouncing
			//// Reflected vector = self - (2 * (Normal * Dot(Normal, self)))
			///////////////////////////////////////////////////////////////
			template <typename U>
			BaseVector3<T> Reflect(const BaseVector3<U> &Normal) const;

			////// Function: ReflectSelf
			//// Parameters:
			////	1) normal	Vector3		- wall normal to be reflected from
			//// Return: 		Vector3& 	- self as reflected vector
			//// Brief: return self as reflected vector from normal
			//// THIS METHOD MODIFIES SELF VECTOR
			//// Reflected vector is used in for instance ball bouncing
			//// Reflected vector = self - (2 * (Normal * Dot(Normal, self)))
			///////////////////////////////////////////////////////////////
			template <typename U>
			BaseVector3<T> & ReflectSelf(const BaseVector3<U> &Normal);

			////// Function: NormalizeSelf
			//// Parameters: <none>
			//// Return: 		Vector3& 	- self as normalized vector
			//// Brief: return self as normalized vector
			//// THIS METHOD MODIFIES SELF VECTOR
			//// Normalization = self / self.Length()
			///////////////////////////////////////////////////////////////
			BaseVector3<T> & NormalizeSelf();

			////// Function: Normalize
			//// Parameters: <none>
			//// Return: 		Vector3 	- normalized copy of self
			//// Brief: return normalized copy of self
			//// Normalization = self / self.Length()
			///////////////////////////////////////////////////////////////
			BaseVector3<T> Normalize() const;

			template <typename U>
			inline bool Equals(const BaseVector3<U> &Other, const double EqualityTolerance = Math::Equality::LowTolerance) const
			{
				return (Math::Absolute(static_cast<double>(x) - static_cast<double>(Other.x)) <= EqualityTolerance
					&&	Math::Absolute(static_cast<double>(y) - static_cast<double>(Other.y)) <= EqualityTolerance
					&&	Math::Absolute(static_cast<double>(z) - static_cast<double>(Other.z)) <= EqualityTolerance);
			}

			template <typename V, typename U>
			inline static BaseVector3<V> Min(const BaseVector3<V> &MinVec, const BaseVector3<U> &MaxVec)
			{
				return BaseVector3<V>(Math::Min(MinVec.x, MaxVec.x), Math::Min(MinVec.y, MaxVec.y), Math::Min(MinVec.z, MaxVec.z));
			}
			template <typename V, typename U>
			inline static BaseVector3<V> Max(const BaseVector3<V> &MinVec, const BaseVector3<U> &MaxVec)
			{
				return BaseVector3<V>(Math::Max(MinVec.x, MaxVec.x), Math::Max(MinVec.y, MaxVec.y), Math::Max(MinVec.z, MaxVec.z));
			}

			template <typename V, typename U>
			inline static void MinMax(BaseVector3<V> &MinVec, BaseVector3<U> &MaxVec)
			{
				MinVec = BaseVector3<V>::Min(MinVec, MaxVec);
				MaxVec = BaseVector3<U>::Max(MinVec, MaxVec);
			}

			template <typename U>
			inline BaseVector3<U> As() const { return BaseVector3<U>(*this); }

			//////////// OPERATORS /////////////



			////// Operator: Assign
			//// Brief: Assign value of other vector to self
			///////////////////////////////////////////////////////////////
			template <typename U>
			inline BaseVector3<T> & operator = (const BaseVector3<U> &Right) { x = T(Right.x); y = T(Right.y); z = T(Right.z); return *this; }

			////// Operator: Negate
			//// Brief: Returns negated copy vector
			///////////////////////////////////////////////////////////////
			inline BaseVector3<T> operator - () const { return BaseVector3<T>(-x, -y, -z); }

			////// Operator: Equality test
			//// Brief: Checks if self and other vector are the same
			///////////////////////////////////////////////////////////////
			template <typename U>
			inline bool operator == (const BaseVector3<U> &Right) const { return Equals(Right); }

			////// Operator: Inequality test
			//// Brief: Checks if self and other vector are NOT the same
			///////////////////////////////////////////////////////////////
			template <typename U>
			inline bool operator != (const BaseVector3<U> &Right) const { return !Equals(Right); }


			////////////////////////////////////////////////////////////////////////////////////////////////////


			////// Operator: Addition
			//// Brief: Creates a copy of (self + other)
			///////////////////////////////////////////////////////////////
			template <typename U>
			inline BaseVector3<T> operator + (const BaseVector3<U> &Right) const { return BaseVector3<T>(x + T(Right.x), y + T(Right.y), z + T(Right.z)); }

			////// Operator: Subtraction
			//// Brief: Creates a copy of (self - other)
			///////////////////////////////////////////////////////////////
			template <typename U>
			inline BaseVector3<T> operator - (const BaseVector3<U> &Right) const { return BaseVector3<T>(x - T(Right.x), y - T(Right.y), z - T(Right.z)); }

			////// Operator: Multiplication
			//// Brief: Creates a copy of (self * other)
			///////////////////////////////////////////////////////////////
			template <typename U>
			inline BaseVector3<T> operator * (const BaseVector3<U> &Right) const { return BaseVector3<T>(x * T(Right.x), y * T(Right.y), z * T(Right.z)); }

			////// Operator: Division
			//// Brief: Creates a copy of (self / other)
			//// BE CAREFUL! IF 'other.x' OR 'other.y' OR 'other.z' EQUALS 0
			//// IT WILL CAUSE EXCEPTION
			///////////////////////////////////////////////////////////////
			template <typename U>
			inline BaseVector3<T> operator / (const BaseVector3<U> &Right) const { return BaseVector3<T>(x / T(Right.x), y / T(Right.y), z / T(Right.z)); }


			////////////////////////////////////////////////////////////////////////////////////////////////////


			////// Operator: Addition (to self)
			//// Brief: Adds a vector to self
			///////////////////////////////////////////////////////////////
			template <typename U>
			inline BaseVector3<T> & operator += (const BaseVector3<U> &Right) { x += T(Right.x); y += T(Right.y); z += T(Right.z); return *this; }

			////// Operator: Subtraction (from self)
			//// Brief: Subtracts a vector from self
			///////////////////////////////////////////////////////////////
			template <typename U>
			inline BaseVector3<T> & operator -= (const BaseVector3<U> &Right) { x -= T(Right.x); y -= T(Right.y); z -= T(Right.z); return *this; }

			////// Operator: Multiplication (self by other)
			//// Brief: Multiplies self by other
			///////////////////////////////////////////////////////////////
			template <typename U>
			inline BaseVector3<T> & operator *= (const BaseVector3<U> &Right) { x *= T(Right.x); y *= T(Right.y); z *= T(Right.z); return *this; }

			////// Operator: Division (self by other)
			//// Brief: Divides self by other vector
			//// BE CAREFUL! IF 'other.x' OR 'other.y' OR 'other.z' EQUALS 0
			//// IT WILL CAUSE EXCEPTION
			///////////////////////////////////////////////////////////////
			template <typename U>
			inline BaseVector3<T> & operator /= (const BaseVector3<U> &Right) { x /= T(Right.x); y /= T(Right.y); z /= T(Right.z); return *this; }


			////////////////////////////////////////////////////////////////////////////////////////////////////


			////// Operator: Addition (scalar to self) (return copy)
			//// Brief: Adds a scalar to all components (x, y, z)
			///////////////////////////////////////////////////////////////
			inline BaseVector3<T> operator + (const float &Right) const { return BaseVector3<T>(x + T(Right), y + T(Right), z + T(Right)); }

			////// Operator: Subtraction (scalar from self) (return copy)
			//// Brief: Suybtracts a scalar from all components (x, y, z)
			///////////////////////////////////////////////////////////////
			inline BaseVector3<T> operator - (const float &Right) const { return BaseVector3<T>(x - T(Right), y - T(Right), z - T(Right)); }

			////// Operator: Multiplication (self by scalar) (return copy)
			//// Brief: Multiplies both components (x, y, z) by scalar
			///////////////////////////////////////////////////////////////
			inline BaseVector3<T> operator * (const float &Right) const { return BaseVector3<T>(x * T(Right), y * T(Right), z * T(Right)); }

			////// Operator: Division (self by scalar) (return copy)
			//// Brief: Divides all components (x, y, z) by scalar
			//// BE CAREFUL! IF scalar EQUALS 0 [ZERO]
			//// IT WILL CAUSE EXCEPTION
			///////////////////////////////////////////////////////////////
			inline BaseVector3<T> operator / (const float &Right) const { return BaseVector3<T>(x / T(Right), y / T(Right), z / T(Right)); }


			////////////////////////////////////////////////////////////////////////////////////////////////////


			////// Operator: Addition (scalar to self) (return copy)
			//// Brief: Adds a scalar to all components (x, y, z)
			///////////////////////////////////////////////////////////////
			inline BaseVector3<T> & operator += (const float &Right) { x += T(Right); y += T(Right); z += T(Right); return *this; }

			////// Operator: Subtraction (scalar from self)
			//// Brief: Subtracts a scalar from all components (x, y, z)
			///////////////////////////////////////////////////////////////
			inline BaseVector3<T> & operator -= (const float &Right) { x -= T(Right); y -= T(Right); z -= T(Right); return *this; }

			////// Operator: Multiplication (self by scalar)
			//// Brief: Multiplies all components (x, y, z) by scalar
			///////////////////////////////////////////////////////////////
			inline BaseVector3<T> & operator *= (const float &Right) { x *= T(Right); y *= T(Right); z *= T(Right); return *this; }

			////// Operator: Division (self by scalar)
			//// Brief: Divides self by scalar
			//// BE CAREFUL! IF scalar EQUALS 0 [ZERO]
			//// IT WILL CAUSE EXCEPTION
			inline BaseVector3<T> & operator /= (const float &Right) { x /= T(Right); y /= T(Right); z /= T(Right); return *this; }

		};

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		BaseVector3<T>::BaseVector3() : x(0), y(0), z(0) { }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		BaseVector3<T>::BaseVector3(const T &xValue, const T &yValue, const T &zValue) : x(xValue), y(yValue), z(zValue) { }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		template <typename U>
		BaseVector3<T>::BaseVector3(const BaseVector3<U> & v) : x(T(v.x)), y(T(v.y)), z(T(v.z)) { }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		void BaseVector3<T>::Set(const T &xValue, const T &yValue, const T &zValue) { x = xValue; y = yValue; z = zValue; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		float BaseVector3<T>::Length() const { return sqrt(static_cast<float>(x*x + y*y + z*z)); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		float BaseVector3<T>::LengthSquared() const { return static_cast<float>(x*x + y*y + z*z); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		template <typename U>
		float BaseVector3<T>::Distance(const BaseVector3<U> &v) const { return (v - (*this)).Length(); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		template <typename U>
		float BaseVector3<T>::DistanceSquared(const BaseVector3<U> &v) const { return (v - (*this)).LengthSquared(); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		template <typename U>
		float BaseVector3<T>::Dot(const BaseVector3<U> &v) const { return x * T(v.x) + y * T(v.y) + z * T(v.z); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		template <typename U>
		BaseVector3<T> BaseVector3<T>::Cross(const BaseVector3<U> & v) const
		{
			return BaseVector3<T>(y * T(v.z) - z * T(v.y),
				z * T(v.x) - x * T(v.z),
				x * T(v.y) - y * T(v.x));
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		template <typename U>
		BaseVector3<T> BaseVector3<T>::Reflect(const BaseVector3<U> &Normal) const
		{
			Normal.Normalize();
			return BaseVector3<T>(this) - ((Normal.template As<T>() * (Normal.template As<T>.Dot(*this))) * 2.f);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		template <typename U>
		BaseVector3<T>& BaseVector3<T>::ReflectSelf(const BaseVector3<U> &Normal)
		{
			*this = (Reflect(Normal));
			return *this;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		BaseVector3<T> & BaseVector3<T>::NormalizeSelf()
		{
			if (Length() != 0)
			{
				float length = Length();
				x /= length; y /= length; z /= length;
				return *this;
			}

			Set(0, 0, 0);
			return *this;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		BaseVector3<T> BaseVector3<T>::Normalize() const
		{
			BaseVector3<T> ret = *this;
			if (Length() != 0)
			{
				float length = Length();
				ret.x /= length; ret.y /= length; ret.z /= length;
				return ret;
			}

			ret.Set(0, 0, 0);
			return ret;
		}

	}
}
