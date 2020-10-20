/*--------------------------------------------//
Matrix header
simplifies matrix use
//--------------------------------------------*/
#ifndef MATRIX_H
#define MATRIX_H

/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include <memory.h>
	#include "vector.h"
	#include "angles.h"

/*--------------------------------------------//
Classes
//--------------------------------------------*/
	class Mat2;
	class Mat3;
	class Mat4;
	class Mat2{
		public:
			/*--------------------------------------------//
			Variables
			//--------------------------------------------*/
			double entries[4];

			/*--------------------------------------------//
			Constructor
			//--------------------------------------------*/
				Mat2(){ LoadIdentity(); }
				Mat2(	double e0, double e1,
						double e2, double e3);
				Mat2(const double* rhs);
				Mat2(const double rhs);
				Mat2(const float rhs):Mat2((double)rhs){}
				Mat2(const int rhs):Mat2((double)rhs){}
				Mat2(const Mat2 & rhs);
			/*--------------------------------------------//
			Destructor
			//--------------------------------------------*/
				~Mat2(){}	//empty

			/*--------------------------------------------//
			Functions
			//--------------------------------------------*/
				void SetEntry(int position, double value);
				double GetEntry(int position) const;
				Vec2 GetRow(int position) const;
				Mat2 SetRow(int position, Vec2 row);
				Vec2 GetColumn(int position) const;
				Mat2 SetColumn(int position, Vec2 col);
				
				void LoadIdentity(void);
				void LoadZero(void);
				
			/*--------------------------------------------//
			Operators
			//--------------------------------------------*/
				double operator[](int i) const {return GetEntry(i);}
				Mat2 operator=(const Mat2 &other){memcpy(entries, other.entries, 4*sizeof(double)); return *this;}
				
				Mat2 operator+(void) const {return (*this);}
				Mat2 operator+(const Mat2 & rhs) const;
				Mat2 operator-(void) const;
				Mat2 operator-(const Mat2 & rhs) const;
				Vec2 operator*(const Vec2 rhs) const;
				Mat2 operator*(const Mat2 & rhs) const;
				Mat2 operator*(const double rhs) const;
				Mat2 operator/(const double rhs) const;
				friend Mat2 operator*(double scaleFactor, const Mat2 & rhs);

				bool operator==(const Mat2 & rhs) const;
				bool operator!=(const Mat2 & rhs) const;

				void operator+=(const Mat2 & rhs);
				void operator-=(const Mat2 & rhs);
				void operator*=(const Mat2 & rhs);
				void operator*=(const double rhs);
				void operator/=(const double rhs);

				//cast to pointer to a (float *) for glGetFloatv etc
				operator float* () const {return (float*) this;}
				operator const float* () const {return (const float*) this;}
	};
	class Mat3{
		public:
			/*--------------------------------------------//
			Variables
			//--------------------------------------------*/
			double entries[9];

			/*--------------------------------------------//
			Constructor
			//--------------------------------------------*/
				Mat3(){ LoadIdentity(); }
				Mat3(	double e0, double e1, double e2, 
						double e3, double e4, double e5, 
						double e6, double e7,	double e8);
				Mat3(const double* rhs);
				Mat3(const double rhs);
				Mat3(const float rhs):Mat3((double)rhs){}
				Mat3(const int rhs):Mat3((double)rhs){}
				Mat3(const Mat3 & rhs);
			/*--------------------------------------------//
			Destructor
			//--------------------------------------------*/
				~Mat3(){}	//empty

			/*--------------------------------------------//
			Functions
			//--------------------------------------------*/
				void SetEntry(int position, double value);
				double GetEntry(int position) const;
				Vec3 GetRow(int position) const;
				Mat3 SetRow(int position, Vec3 row);
				Vec3 GetColumn(int position) const;
				Mat3 SetColumn(int position, Vec3 col);
				
				
				void LoadIdentity(void);
				void LoadZero(void);

			/*--------------------------------------------//
			GLM Functions
			//--------------------------------------------*/
				Mat3 Scale(const Vec2& scale);
				Mat3 Rotate(const double& ang);
				Mat3 Translate(const Vec3& trans);
				
			/*--------------------------------------------//
			Operators
			//--------------------------------------------*/
				double operator[](int i) const {return GetEntry(i);}
				Mat3 operator=(const Mat3 &other){memcpy(entries, other.entries, 9*sizeof(double)); return *this;}
				
				Mat3 operator+(void) const {return (*this);}
				Mat3 operator+(const Mat3 & rhs) const;
				Mat3 operator-(void) const;
				Mat3 operator-(const Mat3 & rhs) const;
				Vec3 operator*(const Vec3 rhs) const;
				Mat3 operator*(const Mat3 & rhs) const;
				Mat3 operator*(const double rhs) const;
				friend Mat3 operator*(double scaleFactor, const Mat3 & rhs);
				Mat3 operator/(const double rhs) const;

				bool operator==(const Mat3 & rhs) const;
				bool operator!=(const Mat3 & rhs) const;

				void operator+=(const Mat3 & rhs);
				void operator-=(const Mat3 & rhs);
				void operator*=(const Mat3 & rhs);
				void operator*=(const double rhs);
				void operator/=(const double rhs);

				//cast to pointer to a (float *) for glGetFloatv etc
				operator float* () const {return (float*) this;}
				operator const float* () const {return (const float*) this;}
	};
	class Mat4{
		private:
			/*--------------------------------------------//
			Variables
			//--------------------------------------------*/
				double entries[16];

		public:
			/*--------------------------------------------//
			Constructor
			//--------------------------------------------*/
				Mat4(){ LoadIdentity(); }
				Mat4(	double e0, double e1, double e2, double e3,
						double e4, double e5, double e6, double e7,
						double e8, double e9, double e10, double e11,
						double e12, double e13, double e14, double e15);
				Mat4(const double* rhs);
				Mat4(const double rhs);
				Mat4(const float rhs):Mat4((double)rhs){}
				Mat4(const int rhs):Mat4((double)rhs){}
				Mat4(const Mat4 & rhs);
			/*--------------------------------------------//
			Destructor
			//--------------------------------------------*/
				~Mat4(){}	//empty

			/*--------------------------------------------//
			Functions
			//--------------------------------------------*/
				void SetEntry(int position, double value);
				double GetEntry(int position) const;
				Vec4 GetRow(int position) const;
				Mat4 SetRow(int position, Vec4 row);
				Vec4 GetColumn(int position) const;
				Mat4 SetColumn(int position, Vec4 col);
				
				void LoadIdentity(void);
				void LoadZero(void);

			/*--------------------------------------------//
			GLM Functions
			//--------------------------------------------*/
				Mat4 Scale(const Vec3& scale);
				Mat4 Scale(const Vec4& scale){Scale((Vec3)scale);}
				Mat4 Rotate(const Vec3& axi, const double& ang);
				Mat4 Translate(const Vec3& trans);
				Mat4 Translate(const Vec4& trans){Translate((Vec3)trans);}
				Mat4 LookAt(const Vec3& eye, const Vec3& center, const Vec3& up);
				Mat4 Project(const Vec4& trans);
				Mat4 Ortho(const Vec4& trans);
				Mat4 Frustrum(const Vec4& trans);
				Mat4 Perspective(const Vec4& trans);
			/*--------------------------------------------//
			Old Functions
			//--------------------------------------------*/
				//rotate a 3d vector by rotation part
				void RotateVector3D(Vec3 & rhs) const {rhs=GetRotatedVector3D(rhs);}
				void InverseRotateVector3D(Vec3 & rhs) const {rhs=GetInverseRotatedVector3D(rhs);}

				Vec3 GetRotatedVector3D(const Vec3 & rhs) const;
				Vec3 GetInverseRotatedVector3D(const Vec3 & rhs) const;

				//translate a 3d vector by translation part
				void TranslateVector3D(Vec3 & rhs) const {rhs=GetTranslatedVector3D(rhs);}
				void InverseTranslateVector3D(Vec3 & rhs) const {rhs=GetInverseTranslatedVector3D(rhs);}
				
				Vec3 GetTranslatedVector3D(const Vec3 & rhs) const;
				Vec3 GetInverseTranslatedVector3D(const Vec3 & rhs) const;

				//Other methods
				void Invert(void);
				Mat4 GetInverse(void) const;
				void Transpose(void);
				Mat4 GetTranspose(void) const;
				void InvertTranspose(void);
				Mat4 GetInverseTranspose(void) const;

				//Inverse of a rotation/translation only matrix
				void AffineInvert(void);
				Mat4 GetAffineInverse(void) const;
				void AffineInvertTranspose(void);
				Mat4 GetAffineInverseTranspose(void) const;

				//set to perform an operation on space - removes other entries
				void SetTranslation(const Vec3 & translation);
				void SetScale(const Vec3 & scaleFactor);
				void SetUniformScale(const float scaleFactor);
				void SetRotationAxis(const double angle, const Vec3 & axis);
				void SetRotationX(const double angle);
				void SetRotationY(const double angle);
				void SetRotationZ(const double angle);
				void SetRotationEuler(const double angleX, const double angleY, const double angleZ);
				void SetPerspective(float left, float right, float bottom, float top, float n, float f);
				void SetPerspective(float fovy, float aspect, float n, float f);
				void SetOrtho(float left, float right, float bottom, float top, float n, float f);

				//set parts of the matrix
				void SetTranslationPart(const Vec3 & translation);
				void SetRotationPartEuler(const double angleX, const double angleY, const double angleZ);
				void SetRotationPartEuler(const Vec3 & rotations){ SetRotationPartEuler((double)rotations.x, (double)rotations.y, (double)rotations.z); }
			/*--------------------------------------------//
			Operators
			//--------------------------------------------*/
				double operator[](int i) const {return GetEntry(i);}
				Mat4 operator=(const Mat4 &other){memcpy(entries, other.entries, 16*sizeof(double)); return *this;}
				
				Mat4 operator+(void) const {return (*this);}
				Mat4 operator+(const Mat4 & rhs) const;
				Mat4 operator-(void) const;
				Mat4 operator-(const Mat4 & rhs) const;
				Vec4 operator*(const Vec4 rhs) const;
				Mat4 operator*(const Mat4 & rhs) const;
				Mat4 operator*(const double rhs) const;
				Mat4 operator/(const double rhs) const;
				friend Mat4 operator*(double scaleFactor, const Mat4 & rhs);

				bool operator==(const Mat4 & rhs) const;
				bool operator!=(const Mat4 & rhs) const;

				void operator+=(const Mat4 & rhs);
				void operator-=(const Mat4 & rhs);
				void operator*=(const Mat4 & rhs);
				void operator*=(const double rhs);
				void operator/=(const double rhs);

				//cast to pointer to a (float *) for glGetFloatv etc
				operator float* () const {return (float*) this;}
				operator const float* () const {return (const float*) *this;}
	};

#endif	//Matrix_H