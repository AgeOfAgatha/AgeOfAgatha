/*--------------------------------------------//
Vector definition
This is used to simplify definition of points
//--------------------------------------------*/
#ifndef VECTOR
#define VECTOR
	/*--------------------------------------------//
	Includes
	//--------------------------------------------*/
		#include "vector.h"

	/*--------------------------------------------//
	Misc
	//--------------------------------------------*/
		Vec4::operator Vec3(){
			if(w==0.0f || w==1.0f)
				return Vec3(x, y, z);
			else
				return Vec3(x/w, y/w, z/w);
		}

	/*--------------------------------------------//
	Normalize the vector
	makes the sum of each component equal to one
	//--------------------------------------------*/
		void Vec2::Normalize(){
			int a = abs(this->x)+abs(this->y);
			this->x = this->x/a;
			this->y = this->x/y;
		}
		void Vec3::Normalize(){
			int a = abs(this->x)+abs(this->y)+abs(this->z);
			this->x = this->x/a;
			this->y = this->y/a;
			this->z = this->z/a;
		}
		void Vec4::Normalize(){
			int a = abs(this->x)+abs(this->y)+abs(this->z)+abs(this->w);
			this->x = this->x/a;
			this->y = this->y/a;
			this->z = this->z/a;
			this->w = this->w/a;
		}
		Vec2 Vec2::GetNormalized() const{
			Vec2 result(*this);
			result.Normalize();
			return result;
		}
		Vec3 Vec3::GetNormalized() const{
			Vec3 result(*this);
			result.Normalize();
			return result;
		}
		Vec4 Vec4::GetNormalized() const{
			Vec4 result(*this);
			result.Normalize();
			return result;
		}

	/*--------------------------------------------//
	Distance between two points
	//--------------------------------------------*/
		double Vec2::Distance(Vec2 other) const{
			return (sqrt( pow(this->x - other.x, 2) + pow(this->y - other.y, 2) ));
		}
		double Vec3::Distance(Vec3 other) const{
			return (sqrt( pow(this->x - other.x, 2) + pow(this->y - other.y, 2) + pow(this->z - other.z, 2) ));
		}
		double Vec4::Distance(Vec4 other) const{
			return (sqrt( pow(this->x - other.x, 2) + pow(this->y - other.y, 2) + pow(this->z - other.z, 2) + pow(this->w - other.w, 2) ));
		}

	/*--------------------------------------------//
	dot product of two vectors
	//--------------------------------------------*/
		double Vec2::Dot(Vec2 other) const{
			return (this->x*other.x + this->y*other.y);
		}
		double Vec3::Dot(Vec3 other) const{
			return (this->x*other.x + this->y*other.y + this->z*other.z);
		}
		double Vec4::Dot(Vec4 other) const{
			return (this->x*other.x + this->y*other.y + this->z*other.z + this->w*other.w);
		}

	/*--------------------------------------------//
	Pack
	//--------------------------------------------*/
		void Vec2::PackTo01(){
			(*this)=GetPackedTo01();	
		}
		Vec2 Vec2::GetPackedTo01() const{
			Vec2 temp(*this);
			temp.Normalize();
			temp=temp*0.5f+Vec2(0.5f, 0.5f);
			return temp;
		}

		void Vec3::PackTo01(){
			(*this)=GetPackedTo01();	
		}
		Vec3 Vec3::GetPackedTo01() const{
			Vec3 temp(*this);
			temp.Normalize();
			temp=temp*0.5f+Vec3(0.5f, 0.5f, 0.5f);
			return temp;
		}

		void Vec4::PackTo01(){
			(*this)=GetPackedTo01();	
		}
		Vec4 Vec4::GetPackedTo01() const{
			Vec4 temp(*this);
			temp.Normalize();
			temp=temp*0.5f+Vec4(0.5f, 0.5f, 0.5f, 0.5f);
			return temp;
		}
	/*--------------------------------------------//
	RotateX
	//--------------------------------------------*/
		void Vec3::RotateX(double angle){
			(*this)=GetRotatedX(angle);
		}
		Vec3 Vec3::GetRotatedX(double angle) const{
			if(angle==0.0)
				return (*this);

			float sinAngle=(float)sin(M_PI*angle/180);
			float cosAngle=(float)cos(M_PI*angle/180);

			return Vec3( x, y*cosAngle - z*sinAngle, y*sinAngle + z*cosAngle );
		}

		void Vec4::RotateX(double angle){
			(*this)=GetRotatedX(angle);
		}
		Vec4 Vec4::GetRotatedX(double angle) const{
			Vec3 v3d(x, y, z);
			v3d.RotateX(angle);
			return Vec4(v3d.x, v3d.y, v3d.z, w);
		}

	/*--------------------------------------------//
	RotateY
	//--------------------------------------------*/
		void Vec3::RotateY(double angle){
			(*this)=GetRotatedY(angle);
		}
		Vec3 Vec3::GetRotatedY(double angle) const{
			if(angle==0.0)
				return (*this);

			float sinAngle=(float)sin(M_PI*angle/180);
			float cosAngle=(float)cos(M_PI*angle/180);

			return Vec3( x*cosAngle + z*sinAngle, y, -x*sinAngle + z*cosAngle);
		}

		void Vec4::RotateY(double angle){
			(*this)=GetRotatedY(angle);
		}
		Vec4 Vec4::GetRotatedY(double angle) const{
			Vec3 v3d(x, y, z);
			v3d.RotateY(angle);
			return Vec4(v3d.x, v3d.y, v3d.z, w);
		}

	/*--------------------------------------------//
	RotateZ
	//--------------------------------------------*/
		void Vec3::RotateZ(double angle){
			(*this)=GetRotatedZ(angle);
		}
		Vec3 Vec3::GetRotatedZ(double angle) const{
			if(angle==0.0)
				return (*this);

			float sinAngle=(float)sin(M_PI*angle/180);
			float cosAngle=(float)cos(M_PI*angle/180);
			
			return Vec3(x*cosAngle - y*sinAngle, x*sinAngle + y*cosAngle, z);
		}

		void Vec4::RotateZ(double angle){
			(*this)=GetRotatedZ(angle);
		}
		Vec4 Vec4::GetRotatedZ(double angle) const{
			Vec3 v3d(x, y, z);
			v3d.RotateZ(angle);
			return Vec4(v3d.x, v3d.y, v3d.z, w);
		}

	/*--------------------------------------------//
	RotateAxis
	//--------------------------------------------*/
		void Vec3::RotateAxis(double angle, const Vec3 & axis){
			(*this)=GetRotatedAxis(angle, axis);
		}
		Vec3 Vec3::GetRotatedAxis(double angle, const Vec3 & axis) const{
			if(angle==0.0)
				return (*this);

			Vec3 u=axis.GetNormalized();

			Vec3 rotMatrixRow0, rotMatrixRow1, rotMatrixRow2;

			float sinAngle=(float)sin(M_PI*angle/180);
			float cosAngle=(float)cos(M_PI*angle/180);
			float oneMinusCosAngle=1.0f-cosAngle;

			rotMatrixRow0.x=(u.x)*(u.x) + cosAngle*(1-(u.x)*(u.x));
			rotMatrixRow0.y=(u.x)*(u.y)*(oneMinusCosAngle) - sinAngle*u.z;
			rotMatrixRow0.z=(u.x)*(u.z)*(oneMinusCosAngle) + sinAngle*u.y;

			rotMatrixRow1.x=(u.x)*(u.y)*(oneMinusCosAngle) + sinAngle*u.z;
			rotMatrixRow1.y=(u.y)*(u.y) + cosAngle*(1-(u.y)*(u.y));
			rotMatrixRow1.z=(u.y)*(u.z)*(oneMinusCosAngle) - sinAngle*u.x;
			
			rotMatrixRow2.x=(u.x)*(u.z)*(oneMinusCosAngle) - sinAngle*u.y;
			rotMatrixRow2.y=(u.y)*(u.z)*(oneMinusCosAngle) + sinAngle*u.x;
			rotMatrixRow2.z=(u.z)*(u.z) + cosAngle*(1-(u.z)*(u.z));

			return Vec3( this->Dot(rotMatrixRow0), this->Dot(rotMatrixRow1), this->Dot(rotMatrixRow2));
		}

		void Vec4::RotateAxis(double angle, const Vec3 & axis){
			(*this)=GetRotatedAxis(angle, axis);
		}
		Vec4 Vec4::GetRotatedAxis(double angle, const Vec3 & axis) const{
			Vec3 v3d(x, y, z);
			v3d.RotateAxis(angle, axis);
			return Vec4(v3d.x, v3d.y, v3d.z, w);
		}

#endif