/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2006 Torus Knot Software Ltd
Also see acknowledgements in Readme.html

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.

You may alternatively use this source under the terms of a specific version of
the OGRE Unrestricted License provided you have obtained such a license from
Torus Knot Software Ltd.
-----------------------------------------------------------------------------
*/

/*
--------------------------------------------------------------------------------
Modified OgreVector3.h version.
Forced double-precision Vector3

Copyright (C) 2009 Xavier Verguín González <xavierverguin@hotmail.com>
                                           <xavyiy@gmail.com>
--------------------------------------------------------------------------------
*/

#ifndef _SkyX_Double3_H_
#define _SkyX_Double3_H_

#include "Prerequisites.h"

namespace SkyX
{

	using namespace Ogre;

    /** Standard 3-dimensional vector.
        @remarks
            A direction in 3D space represented as distances along the 3
            orthoganal axes (x, y, z). Note that positions, directions and
            scaling factors can be represented by a vector, depending on how
            you interpret the values.
    */
    class DllExport Double3
    {
    public:
		double x, y, z;

    public:
        inline Double3()
        {
        }

        inline Double3( const double fX, const double fY, const double fZ )
            : x( fX ), y( fY ), z( fZ )
        {
        }

        inline explicit Double3( const double afCoordinate[3] )
            : x( afCoordinate[0] ),
              y( afCoordinate[1] ),
              z( afCoordinate[2] )
        {
        }

        inline explicit Double3( const int afCoordinate[3] )
        {
            x = (double)afCoordinate[0];
            y = (double)afCoordinate[1];
            z = (double)afCoordinate[2];
        }

        inline explicit Double3( double* const r )
            : x( r[0] ), y( r[1] ), z( r[2] )
        {
        }

        inline explicit Double3( const double scaler )
            : x( scaler )
            , y( scaler )
            , z( scaler )
        {
        }

		inline explicit Double3( const Vector3 or )
            : x( (double)or.x )
            , y( (double)or.y )
            , z( (double)or.z )
        {
        }

		inline double operator [] ( const size_t i ) const
        {
            assert( i < 3 );

            return *(&x+i);
        }

		inline double& operator [] ( const size_t i )
        {
            assert( i < 3 );

            return *(&x+i);
        }
		/// Pointer accessor for direct copying
		inline double* ptr()
		{
			return &x;
		}
		/// Pointer accessor for direct copying
		inline const double* ptr() const
		{
			return &x;
		}

        /** Assigns the value of the other vector.
            @param
                rkVector The other vector
        */
        inline Double3& operator = ( const Double3& rkVector )
        {
            x = rkVector.x;
            y = rkVector.y;
            z = rkVector.z;

            return *this;
        }

        inline Double3& operator = ( const double fScaler )
        {
            x = fScaler;
            y = fScaler;
            z = fScaler;

            return *this;
        }

        inline bool operator == ( const Double3& rkVector ) const
        {
            return ( x == rkVector.x && y == rkVector.y && z == rkVector.z );
        }

        inline bool operator != ( const Double3& rkVector ) const
        {
            return ( x != rkVector.x || y != rkVector.y || z != rkVector.z );
        }

        // arithmetic operations
        inline Double3 operator + ( const Double3& rkVector ) const
        {
            return Double3(
                x + rkVector.x,
                y + rkVector.y,
                z + rkVector.z);
        }

        inline Double3 operator - ( const Double3& rkVector ) const
        {
            return Double3(
                x - rkVector.x,
                y - rkVector.y,
                z - rkVector.z);
        }

        inline Double3 operator * ( const double fScalar ) const
        {
            return Double3(
                x * fScalar,
                y * fScalar,
                z * fScalar);
        }

        inline Double3 operator * ( const Double3& rhs) const
        {
            return Double3(
                x * rhs.x,
                y * rhs.y,
                z * rhs.z);
        }

        inline Double3 operator / ( const double fScalar ) const
        {
            assert( fScalar != 0.0 );

            double fInv = 1.0 / fScalar;

            return Double3(
                x * fInv,
                y * fInv,
                z * fInv);
        }

        inline Double3 operator / ( const Double3& rhs) const
        {
            return Double3(
                x / rhs.x,
                y / rhs.y,
                z / rhs.z);
        }

        inline const Double3& operator + () const
        {
            return *this;
        }

        inline Double3 operator - () const
        {
            return Double3(-x, -y, -z);
        }

        // overloaded operators to help Double3
        inline friend Double3 operator * ( const double fScalar, const Double3& rkVector )
        {
            return Double3(
                fScalar * rkVector.x,
                fScalar * rkVector.y,
                fScalar * rkVector.z);
        }

        inline friend Double3 operator / ( const double fScalar, const Double3& rkVector )
        {
            return Double3(
                fScalar / rkVector.x,
                fScalar / rkVector.y,
                fScalar / rkVector.z);
        }

        inline friend Double3 operator + (const Double3& lhs, const double rhs)
        {
            return Double3(
                lhs.x + rhs,
                lhs.y + rhs,
                lhs.z + rhs);
        }

        inline friend Double3 operator + (const double lhs, const Double3& rhs)
        {
            return Double3(
                lhs + rhs.x,
                lhs + rhs.y,
                lhs + rhs.z);
        }

        inline friend Double3 operator - (const Double3& lhs, const double rhs)
        {
            return Double3(
                lhs.x - rhs,
                lhs.y - rhs,
                lhs.z - rhs);
        }

        inline friend Double3 operator - (const double lhs, const Double3& rhs)
        {
            return Double3(
                lhs - rhs.x,
                lhs - rhs.y,
                lhs - rhs.z);
        }

        // arithmetic updates
        inline Double3& operator += ( const Double3& rkVector )
        {
            x += rkVector.x;
            y += rkVector.y;
            z += rkVector.z;

            return *this;
        }

        inline Double3& operator += ( const double fScalar )
        {
            x += fScalar;
            y += fScalar;
            z += fScalar;
            return *this;
        }

        inline Double3& operator -= ( const Double3& rkVector )
        {
            x -= rkVector.x;
            y -= rkVector.y;
            z -= rkVector.z;

            return *this;
        }

        inline Double3& operator -= ( const double fScalar )
        {
            x -= fScalar;
            y -= fScalar;
            z -= fScalar;
            return *this;
        }

        inline Double3& operator *= ( const double fScalar )
        {
            x *= fScalar;
            y *= fScalar;
            z *= fScalar;
            return *this;
        }

        inline Double3& operator *= ( const Double3& rkVector )
        {
            x *= rkVector.x;
            y *= rkVector.y;
            z *= rkVector.z;

            return *this;
        }

        inline Double3& operator /= ( const double fScalar )
        {
            assert( fScalar != 0.0 );

            double fInv = 1.0 / fScalar;

            x *= fInv;
            y *= fInv;
            z *= fInv;

            return *this;
        }

        inline Double3& operator /= ( const Double3& rkVector )
        {
            x /= rkVector.x;
            y /= rkVector.y;
            z /= rkVector.z;

            return *this;
        }


        /** Returns the length (magnitude) of the vector.
            @warning
                This operation requires a square root and is expensive in
                terms of CPU operations. If you don't need to know the exact
                length (e.g. for just comparing lengths) use squaredLength()
                instead.
        */
        inline double length () const
        {
            return Math::Sqrt( x * x + y * y + z * z );
        }

        /** Returns the square of the length(magnitude) of the vector.
            @remarks
                This  method is for efficiency - calculating the actual
                length of a vector requires a square root, which is expensive
                in terms of the operations required. This method returns the
                square of the length of the vector, i.e. the same as the
                length but before the square root is taken. Use this if you
                want to find the longest / shortest vector without incurring
                the square root.
        */
        inline double squaredLength () const
        {
            return x * x + y * y + z * z;
        }

        /** Returns the distance to another vector.
            @warning
                This operation requires a square root and is expensive in
                terms of CPU operations. If you don't need to know the exact
                distance (e.g. for just comparing distances) use squaredDistance()
                instead.
        */
        inline double distance(const Double3& rhs) const
        {
            return (*this - rhs).length();
        }

        /** Returns the square of the distance to another vector.
            @remarks
                This method is for efficiency - calculating the actual
                distance to another vector requires a square root, which is
                expensive in terms of the operations required. This method
                returns the square of the distance to another vector, i.e.
                the same as the distance but before the square root is taken.
                Use this if you want to find the longest / shortest distance
                without incurring the square root.
        */
        inline double squaredDistance(const Double3& rhs) const
        {
            return (*this - rhs).squaredLength();
        }

        /** Calculates the dot (scalar) product of this vector with another.
            @remarks
                The dot product can be used to calculate the angle between 2
                vectors. If both are unit vectors, the dot product is the
                cosine of the angle; otherwise the dot product must be
                divided by the product of the lengths of both vectors to get
                the cosine of the angle. This result can further be used to
                calculate the distance of a point from a plane.
            @param
                vec Vector with which to calculate the dot product (together
                with this one).
            @returns
                A float representing the dot product value.
        */
        inline double dotProduct(const Double3& vec) const
        {
            return x * vec.x + y * vec.y + z * vec.z;
        }

        /** Calculates the absolute dot (scalar) product of this vector with another.
            @remarks
                This function work similar dotProduct, except it use absolute value
                of each component of the vector to computing.
            @param
                vec Vector with which to calculate the absolute dot product (together
                with this one).
            @returns
                A double representing the absolute dot product value.
        */
        inline double absDotProduct(const Double3& vec) const
        {
            return Math::Abs(x * vec.x) + Math::Abs(y * vec.y) + Math::Abs(z * vec.z);
        }

        /** Normalises the vector.
            @remarks
                This method normalises the vector such that it's
                length / magnitude is 1. The result is called a unit vector.
            @note
                This function will not crash for zero-sized vectors, but there
                will be no changes made to their components.
            @returns The previous length of the vector.
        */
        inline double normalise()
        {
            double fLength = Math::Sqrt( x * x + y * y + z * z );

            // Will also work for zero-sized vectors, but will change nothing
            if ( fLength > 1e-08 )
            {
                double fInvLength = 1.0 / fLength;
                x *= fInvLength;
                y *= fInvLength;
                z *= fInvLength;
            }

            return fLength;
        }

        /** Calculates the cross-product of 2 vectors, i.e. the vector that
            lies perpendicular to them both.
            @remarks
                The cross-product is normally used to calculate the normal
                vector of a plane, by calculating the cross-product of 2
                non-equivalent vectors which lie on the plane (e.g. 2 edges
                of a triangle).
            @param
                vec Vector which, together with this one, will be used to
                calculate the cross-product.
            @returns
                A vector which is the result of the cross-product. This
                vector will <b>NOT</b> be normalised, to maximise efficiency
                - call Double3::normalise on the result if you wish this to
                be done. As for which side the resultant vector will be on, the
                returned vector will be on the side from which the arc from 'this'
                to rkVector is anticlockwise, e.g. UNIT_Y.crossProduct(UNIT_Z)
                = UNIT_X, whilst UNIT_Z.crossProduct(UNIT_Y) = -UNIT_X.
				This is because OGRE uses a right-handed coordinate system.
            @par
                For a clearer explanation, look a the left and the bottom edges
                of your monitor's screen. Assume that the first vector is the
                left edge and the second vector is the bottom edge, both of
                them starting from the lower-left corner of the screen. The
                resulting vector is going to be perpendicular to both of them
                and will go <i>inside</i> the screen, towards the cathode tube
                (assuming you're using a CRT monitor, of course).
        */
        inline Double3 crossProduct( const Double3& rkVector ) const
        {
            return Double3(
                y * rkVector.z - z * rkVector.y,
                z * rkVector.x - x * rkVector.z,
                x * rkVector.y - y * rkVector.x);
        }
       
        /** Returns true if this vector is zero length. */
        inline bool isZeroLength(void) const
        {
            double sqlen = (x * x) + (y * y) + (z * z);
            return (sqlen < (1e-06 * 1e-06));

        }

        /** As normalise, except that this vector is unaffected and the
            normalised vector is returned as a copy. */
        inline Double3 normalisedCopy(void) const
        {
            Double3 ret = *this;
            ret.normalise();
            return ret;
        }

        /** Calculates a reflection vector to the plane with the given normal .
        @remarks NB assumes 'this' is pointing AWAY FROM the plane, invert if it is not.
        */
        inline Double3 reflect(const Double3& normal) const
        {
            return Double3( *this - ( 2 * this->dotProduct(normal) * normal ) );
        }

        /** Function for writing to a stream.
        */
        inline _OgreExport friend std::ostream& operator <<
            ( std::ostream& o, const Double3& v )
        {
            o << "Double3(" << v.x << ", " << v.y << ", " << v.z << ")";
            return o;
        }

		/** Get as Ogre::Vector3
		 */
		inline const Ogre::Vector3 getVector3() const
		{
			return Ogre::Vector3((float)x, (float)y, (float)z);
		}
    };

}
#endif
