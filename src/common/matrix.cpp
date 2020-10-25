/*--------------------------------------------//
Matrix header
simplifies matrix use
//--------------------------------------------*/
#ifndef MATRIX
#define MATRIX

/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include "matrix.h"

/*--------------------------------------------//
Constructors
//--------------------------------------------*/
	Mat2::Mat2(	double e0, double e1, 
				double e2, double e3){
		entries[0]=e0;
		entries[1]=e1;
		entries[2]=e2;
		entries[3]=e3;
	}
	Mat2::Mat2(const double rhs){
		entries[0]=rhs;
		entries[1]=entries[2]=0;
		entries[3]=rhs;
	}

	Mat2::Mat2(const Mat2 & rhs){
		memcpy(entries, rhs.entries, 4*sizeof(float));
	}

	Mat2::Mat2(const double* rhs){
		memcpy(entries, rhs, 4*sizeof(float));
	}
	Mat3::Mat3(	double e0, double e1, double e2, 
				double e3, double e4, double e5, 
				double e6, double e7, double e8){
		entries[0]=e0;
		entries[1]=e1;
		entries[2]=e2;
		entries[3]=e3;
		entries[4]=e4;
		entries[5]=e5;
		entries[6]=e6;
		entries[7]=e7;
		entries[8]=e8;
	}
	Mat3::Mat3(const double rhs){
		entries[0]=rhs;
		entries[1]=entries[2]=entries[3]=0;
		entries[4]=rhs;
		entries[5]=entries[6]=entries[7]=0;
		entries[8]=rhs;
	}

	Mat3::Mat3(const Mat3 & rhs){
		memcpy(entries, rhs.entries, 9*sizeof(float));
	}

	Mat3::Mat3(const double* rhs){
		memcpy(entries, rhs, 9*sizeof(float));
	}
	Mat4::Mat4(	double e0, double e1, double e2, double e3,
				double e4, double e5, double e6, double e7,
				double e8, double e9, double e10, double e11,
				double e12, double e13, double e14, double e15){
		entries[0]=e0;
		entries[1]=e1;
		entries[2]=e2;
		entries[3]=e3;
		entries[4]=e4;
		entries[5]=e5;
		entries[6]=e6;
		entries[7]=e7;
		entries[8]=e8;
		entries[9]=e9;
		entries[10]=e10;
		entries[11]=e11;
		entries[12]=e12;
		entries[13]=e13;
		entries[14]=e14;
		entries[15]=e15;
	}
	Mat4::Mat4(const double rhs){
		entries[0]=rhs;
		entries[1]=entries[2]=entries[3]=entries[4]=0;
		entries[5]=rhs;
		entries[6]=entries[7]=entries[8]=entries[9]=0;
		entries[10]=rhs;
		entries[11]=entries[12]=entries[13]=entries[14]=0;
		entries[15]=rhs;
	}
	Mat4::Mat4(const Mat3& rhs){
		LoadIdentity();
		memcpy(entries, rhs.entries, 9*sizeof(float));
	}
	Mat4::Mat4(const Mat4& rhs){
		memcpy(entries, rhs.entries, 16*sizeof(float));
	}
	Mat4::Mat4(const Quat& qu){
		LoadIdentity();
		double qxx = (qu.x * qu.x);
		double qyy = (qu.y * qu.y);
		double qzz = (qu.z * qu.z);
		double qxz = (qu.x * qu.z);
		double qxy = (qu.x * qu.y);
		double qyz = (qu.y * qu.z);
		double qwx = (qu.w * qu.x);
		double qwy = (qu.w * qu.y);
		double qwz = (qu.w * qu.z);

		entries[0] 	= 1 - 2 * (qyy +  qzz);
		entries[1] 	= 2 * (qxy + qwz);
		entries[2] 	= 2 * (qxz - qwy);

		entries[4] 	= 2 * (qxy - qwz);
		entries[5] 	= 1 - 2 * (qxx +  qzz);
		entries[6] 	= 2 * (qyz + qwx);

		entries[8] 	= 2 * (qxz + qwy);
		entries[9] 	= 2 * (qyz - qwx);
		entries[10] = 1 - 2 * (qxx +  qyy);
	}

	Mat4::Mat4(const double* rhs){
		memcpy(entries, rhs, 16*sizeof(float));
	}

/*--------------------------------------------//
Accessors
//--------------------------------------------*/
	void Mat2::SetEntry(int position, double value){
		if(position>=0 && position<=3)
			entries[position]=value;
	}
	void Mat3::SetEntry(int position, double value){
		if(position>=0 && position<=8)
			entries[position]=value;
	}
	void Mat4::SetEntry(int position, double value){
		if(position>=0 && position<=15)
			entries[position]=value;
	}
		
	double Mat2::GetEntry(int position) const {
		if(position>=0 && position<=3)
			return entries[position];

		return 0.0f;
	}
	double Mat3::GetEntry(int position) const {
		if(position>=0 && position<=8)
			return entries[position];

		return 0.0f;
	}
	double Mat4::GetEntry(int position) const {
		if(position>=0 && position<=15)
			return entries[position];

		return 0.0f;
	}

	Vec2 Mat2::GetRow(int position) const {
		if(position==0)
			return Vec2(entries[0], entries[2]);
		
		if(position==1)
			return Vec2(entries[1], entries[3]);
		
		return Vec2(0.0f, 0.0f);
	}
	Vec3 Mat3::GetRow(int position) const {
		if(position==0)
			return Vec3(entries[0], entries[3], entries[6]);
		
		if(position==1)
			return Vec3(entries[1], entries[4], entries[7]);
		
		if(position==2)
			return Vec3(entries[2], entries[5], entries[8]);
		
		return Vec3(0.0f, 0.0f, 0.0f);
	}
	Vec4 Mat4::GetRow(int position) const {
		if(position==0)
			return Vec4(entries[0], entries[4], entries[8], entries[12]);
		
		if(position==1)
			return Vec4(entries[1], entries[5], entries[9], entries[13]);
		
		if(position==2)
			return Vec4(entries[2], entries[6], entries[10], entries[14]);
		
		if(position==3)
			return Vec4(entries[3], entries[7], entries[11], entries[15]);

		return Vec4(0.0f, 0.0f, 0.0f, 0.0f);
	}

	Mat2 Mat2::SetRow(int position, Vec2 row){
		if(position >= 0 && position < 2){
			entries[0+position] = row[0];
			entries[2+position] = row[1];
		}
		return *this;
	}
	Mat3 Mat3::SetRow(int position, Vec3 row){
		if(position >= 0 && position < 3){
			entries[0+position] = row[0];
			entries[3+position] = row[1];
			entries[6+position] = row[2];
		}
		return *this;
	}
	Mat4 Mat4::SetRow(int position, Vec4 row){
		if(position >= 0 && position < 4){
			entries[0+position] = row[0];
			entries[4+position] = row[1];
			entries[8+position] = row[2];
			entries[12+position] = row[3];
		}
		return *this;
	}

	Vec2 Mat2::GetColumn(int position) const {
		if(position==0)
			return Vec2(entries[0], entries[1]);
		
		if(position==1)
			return Vec2(entries[2], entries[3]);
		
		return Vec2(0.0f, 0.0f);
	}
	Vec3 Mat3::GetColumn(int position) const {
		if(position==0)
			return Vec3(entries[0], entries[1], entries[2]);
		
		if(position==1)
			return Vec3(entries[3], entries[4], entries[5]);
		
		if(position==2)
			return Vec3(entries[6], entries[7], entries[8]);
		
		return Vec3(0.0f, 0.0f, 0.0f);
	}
	Vec4 Mat4::GetColumn(int position) const {
		if(position==0)
			return Vec4(entries[0], entries[1], entries[2], entries[3]);
		
		if(position==1)
			return Vec4(entries[4], entries[5], entries[6], entries[7]);
		
		if(position==2)
			return Vec4(entries[8], entries[9], entries[10], entries[11]);
		
		if(position==3)
			return Vec4(entries[12], entries[13], entries[14], entries[15]);

		return Vec4(0.0f, 0.0f, 0.0f, 0.0f);
	}

	Mat2 Mat2::SetColumn(int position, Vec2 col){
		if(position >= 0 && position < 2){
			entries[0+position*2] = col[0];
			entries[1+position*2] = col[1];
		}
		return *this;
	}
	Mat3 Mat3::SetColumn(int position, Vec3 col){
		if(position >= 0 && position < 3){
			entries[0+position*3] = col[0];
			entries[1+position*3] = col[1];
			entries[2+position*3] = col[2];
		}
		return *this;
	}
	Mat4 Mat4::SetColumn(int position, Vec4 col){
		if(position >= 0 && position < 4){
			entries[0+position*4] = col[0];
			entries[1+position*4] = col[1];
			entries[2+position*4] = col[2];
			entries[3+position*4] = col[3];
		}
		return *this;
	}

/*--------------------------------------------//
Functions
//--------------------------------------------*/
	void Mat2::LoadIdentity(void){
		LoadZero();
		entries[0]=1.0f;
		entries[3]=1.0f;
	}
	void Mat3::LoadIdentity(void){
		LoadZero();
		entries[0]=1.0f;
		entries[4]=1.0f;
		entries[8]=1.0f;
	}
	void Mat4::LoadIdentity(void){
		LoadZero();
		entries[0]=1.0f;
		entries[5]=1.0f;
		entries[10]=1.0f;
		entries[15]=1.0f;
	}

	void Mat2::LoadZero(void){
		memset(entries, 0, 4*sizeof(float));
	}
	void Mat3::LoadZero(void){
		memset(entries, 0, 9*sizeof(float));
	}
	void Mat4::LoadZero(void){
		memset(entries, 0, 16*sizeof(float));
	}

/*--------------------------------------------//
GLM based Functions
//--------------------------------------------*/
	Mat3 Mat3::Scale(const Vec2& scale){
		SetColumn(0, GetColumn(0) * scale[0]);
		SetColumn(1, GetColumn(1) * scale[1]);
		return *this;
	}
	Mat4 Mat4::Scale(const Vec3& scale){
		SetColumn(0, GetColumn(0) * scale[0]);
		SetColumn(1, GetColumn(1) * scale[1]);
		SetColumn(2, GetColumn(2) * scale[2]);
		return *this;
	}
	Mat3 Mat3::Rotate(const double& ang){
		const double c = cos(ang);
		const double s = sin(ang);

		Mat3 Result = Mat3(1);
		Result.SetColumn(0, GetColumn(0) * c + GetColumn(1) * s);
		Result.SetColumn(1, GetColumn(0) * -s + GetColumn(1) * c);
		Result.SetColumn(2, GetColumn(2));
		SetColumn(0, GetColumn(0));
		SetColumn(1, GetColumn(1));
		SetColumn(2, GetColumn(2));
		return *this;
	}
	Mat4 Mat4::Rotate(const Vec3& axi, const double& ang){
		double const c = cos(ang);
		double const s = sin(ang);

		Vec3 axis = axi.GetNormalized();
		Vec3 temp = (1 - c) * axis;

		Mat4 Rotate = Mat4(1);
		Rotate.SetEntry(0, c + temp[0] * axis[0]);
		Rotate.SetEntry(1, temp[0] * axis[1] + s * axis[2]);
		Rotate.SetEntry(2, temp[0] * axis[2] - s * axis[1]);

		Rotate.SetEntry(4, temp[1] * axis[0] - s * axis[2]);
		Rotate.SetEntry(5, c + temp[1] * axis[1]);
		Rotate.SetEntry(6, temp[1] * axis[2] + s * axis[0]);

		Rotate.SetEntry(8, temp[2] * axis[0] + s * axis[1]);
		Rotate.SetEntry(9, temp[2] * axis[1] - s * axis[0]);
		Rotate.SetEntry(10, c + temp[2] * axis[2]);

		Mat4 Result = Mat4(1);
		Result.SetColumn(0, GetColumn(0) * Rotate[0] + GetColumn(1) * Rotate[1] + GetColumn(2) * Rotate[2]);
		Result.SetColumn(1, GetColumn(0) * Rotate[4] + GetColumn(1) * Rotate[5] + GetColumn(2) * Rotate[6]);
		Result.SetColumn(2, GetColumn(0) * Rotate[8] + GetColumn(1) * Rotate[9] + GetColumn(2) * Rotate[10]);
		Result.SetColumn(3, GetColumn(3));

		*this = Result;
		return *this;
	}
	Mat3 Mat3::Translate(const Vec3& trans){
		SetColumn(2, GetColumn(0) * trans[0] + GetColumn(1) * trans[1] + GetColumn(2));
		return *this;
	}
	Mat4 Mat4::Translate(const Vec3& trans){
		SetColumn(3, GetColumn(0) * trans[0] + GetColumn(1) * trans[1] + GetColumn(2) * trans[2] + GetColumn(3));
		return *this;
	}
	Mat4 Mat4::LookAt(const Vec3& eye, const Vec3& center, const Vec3& up){
		const Vec3 f = (center - eye).GetNormalized();
		const Vec3 s = f.CrossProduct(up).GetNormalized(); //up cross f for LH
		const Vec3 u = s.CrossProduct(f); // f cross s for LH

		LoadIdentity();
		entries[0] 	= s.x;
		entries[4] 	= s.y;
		entries[8] 	= s.z;
		entries[1] 	= u.x;
		entries[5] 	= u.y;
		entries[9] 	= u.z;
		entries[2] 	=-f.x; // + for LH
		entries[6] 	=-f.y; // + for LH
		entries[10] =-f.z; // + for LH
		entries[12] =-s.Dot(eye);
		entries[13] =-u.Dot(eye);
		entries[14] = f.Dot(eye); // - for LH
		return *this;
	}//trans = vec4(left, right, bottom, top)
	Mat4 Mat4::Ortho(const Vec4& trans){
		entries[0] 	= 2 / (trans[1] - trans[0]);
		entries[4] 	= 2 / (trans[3] - trans[2]);
		entries[9] 	= - 1;
		entries[12] = - (trans[1] + trans[0]) / (trans[1] - trans[0]);
		entries[13] = - (trans[3] + trans[2]) / (trans[3] - trans[2]);
		return *this;
	}//trans = vec4(left, right, bottom, top)
	Mat4 Mat4::Frustrum(const Vec4& trans, double neary, double fary){
		entries[0] =	2 * neary / ( trans[1] - trans[0] );
		entries[4] = 	2 * neary / ( trans[3] - trans[2] );
		entries[8] = 	( trans[1] + trans[0] ) / ( trans[1] - trans[0] );
		entries[9] = 	( trans[3] + trans[2] ) / ( trans[3] - trans[2] );
		entries[10] = - ( fary + neary ) / ( fary - neary );
		entries[11] = - 1;
		entries[14] = - ( 2 * fary * neary ) / ( fary - neary );
		return *this;
	}
	Mat4 Mat4::Perspective(double fovy, double aspect, double zNear, double zFar){
		assert(abs(aspect - std::numeric_limits<double>::epsilon()) > 0);
		const double tanHalfFovy = tan(fovy / 2);

		entries[0] 	= 1 / (aspect * tanHalfFovy);
		entries[5]	= 1 / (tanHalfFovy);
		entries[10] = - (zFar + zNear) / (zFar - zNear);
		entries[11] = - 1;
		entries[14] = - (2 * zFar * zNear) / (zFar - zNear);
		return *this;
	}
	Mat4 Mat4::PerspectiveFov(double fov, double width, double height, double zNear, double zFar){
		assert(width > 0);
		assert(height > 0);
		assert(fov > 0);

		const double rad = fov;
		const double h = cos(0.5 * rad) / sin(0.5 * rad);
		const double w = h * height / width; ///todo max(width , Height) / min(width , Height)?

		LoadZero();
		entries[0] 	= w;
		entries[5] 	= h;
		entries[10] = - (zFar + zNear) / (zFar - zNear);
		entries[11] = - 1;
		entries[14] = - (2 * zFar * zNear) / (zFar - zNear);
		return *this;
	}
	Mat4 Mat4::InfinitePerspective(double fovy, double aspect, double zNear){
		const double range = tan(fovy / 2) * zNear;
		const double left = -range * aspect;
		const double right = range * aspect;
		const double bottom = -range;
		const double top = range;

		LoadZero();
		entries[0] 	= (2 * zNear) / (right - left);
		entries[5] 	= (2 * zNear) / (top - bottom);
		entries[10] = - 1;
		entries[11] = - 1;
		entries[14] = - 2 * zNear;
		return *this;
	}
	Mat4 Mat4::TweakedInfinitePerspective(double fovy, double aspect, double zNear, double ep){
		const double range = tan(fovy / 2) * zNear;
		const double left = -range * aspect;
		const double right = range * aspect;
		const double bottom = -range;
		const double top = range;

		LoadZero();
		entries[0] 	= (2 * zNear) / (right - left);
		entries[5] 	= (2 * zNear) / (top - bottom);
		entries[10] = ep - 1;
		entries[11] = 1;
		entries[14] = (ep - 2) * zNear;
		return *this;
	}
	Mat4 Mat4::TweakedInfinitePerspective(double fovy, double aspect, double zNear){
		return TweakedInfinitePerspective(fovy, aspect, zNear, std::numeric_limits<double>::epsilon());
	}
	Vec3 Mat4::Project(Vec3 const& obj, Mat4 const& model, Mat4 const& proj, Vec4 const& viewport){
		Vec4 tmp = Vec4(obj, 1);
		tmp = model * tmp;
		tmp = proj * tmp;

		tmp /= tmp.w;
		tmp = tmp * 0.5 + 0.5;
		tmp.SetX(tmp[0] * viewport[2] + viewport[0]);
		tmp.SetY(tmp[1] * viewport[3] + viewport[1]);

		return Vec3(tmp);
	}


/*--------------------------------------------//
Old Functions
//--------------------------------------------*/
	Vec3 Mat4::GetRotatedVector3D(const Vec3 & rhs) const {
		return Vec3(entries[0]*rhs.x + entries[4]*rhs.y + entries[8]*rhs.z,
						entries[1]*rhs.x + entries[5]*rhs.y + entries[9]*rhs.z,
						entries[2]*rhs.x + entries[6]*rhs.y + entries[10]*rhs.z);
	}

	Vec3 Mat4::GetInverseRotatedVector3D(const Vec3 & rhs) const {
		//rotate by transpose:
		return Vec3(entries[0]*rhs.x + entries[1]*rhs.y + entries[2]*rhs.z,
						entries[4]*rhs.x + entries[5]*rhs.y + entries[6]*rhs.z,
						entries[8]*rhs.x + entries[9]*rhs.y + entries[10]*rhs.z);
	}

	Vec3 Mat4::GetTranslatedVector3D(const Vec3 & rhs) const {
		return Vec3(rhs.x+entries[12], rhs.y+entries[13], rhs.z+entries[14]);
	}

	Vec3 Mat4::GetInverseTranslatedVector3D(const Vec3 & rhs) const {
		return Vec3(rhs.x-entries[12], rhs.y-entries[13], rhs.z-entries[14]);
	}

	void Mat4::Invert(void){
		*this=GetInverse();
	}

	Mat4 Mat4::GetInverse(void) const {
		Mat4 result=GetInverseTranspose();

		result.Transpose();

		return result;
	}


	void Mat4::Transpose(void){
		*this=GetTranspose();
	}

	Mat4 Mat4::GetTranspose(void) const {
		return Mat4(	entries[ 0], entries[ 4], entries[ 8], entries[12],
							entries[ 1], entries[ 5], entries[ 9], entries[13],
							entries[ 2], entries[ 6], entries[10], entries[14],
							entries[ 3], entries[ 7], entries[11], entries[15]);
	}

	void Mat4::InvertTranspose(void){
		*this=GetInverseTranspose();
	}

	Mat4 Mat4::GetInverseTranspose(void) const {
		Mat4 result;

		double tmp[12];												//temporary pair storage
		double det;													//determinant

		//calculate pairs for first 8 elements (cofactors)
		tmp[0] = entries[10] * entries[15];
		tmp[1] = entries[11] * entries[14];
		tmp[2] = entries[9] * entries[15];
		tmp[3] = entries[11] * entries[13];
		tmp[4] = entries[9] * entries[14];
		tmp[5] = entries[10] * entries[13];
		tmp[6] = entries[8] * entries[15];
		tmp[7] = entries[11] * entries[12];
		tmp[8] = entries[8] * entries[14];
		tmp[9] = entries[10] * entries[12];
		tmp[10] = entries[8] * entries[13];
		tmp[11] = entries[9] * entries[12];

		//calculate first 8 elements (cofactors)
		result.SetEntry(0,		tmp[0]*entries[5] + tmp[3]*entries[6] + tmp[4]*entries[7]
						-	tmp[1]*entries[5] - tmp[2]*entries[6] - tmp[5]*entries[7]);

		result.SetEntry(1,		tmp[1]*entries[4] + tmp[6]*entries[6] + tmp[9]*entries[7]
						-	tmp[0]*entries[4] - tmp[7]*entries[6] - tmp[8]*entries[7]);

		result.SetEntry(2,		tmp[2]*entries[4] + tmp[7]*entries[5] + tmp[10]*entries[7]
						-	tmp[3]*entries[4] - tmp[6]*entries[5] - tmp[11]*entries[7]);

		result.SetEntry(3,		tmp[5]*entries[4] + tmp[8]*entries[5] + tmp[11]*entries[6]
						-	tmp[4]*entries[4] - tmp[9]*entries[5] - tmp[10]*entries[6]);

		result.SetEntry(4,		tmp[1]*entries[1] + tmp[2]*entries[2] + tmp[5]*entries[3]
						-	tmp[0]*entries[1] - tmp[3]*entries[2] - tmp[4]*entries[3]);

		result.SetEntry(5,		tmp[0]*entries[0] + tmp[7]*entries[2] + tmp[8]*entries[3]
						-	tmp[1]*entries[0] - tmp[6]*entries[2] - tmp[9]*entries[3]);

		result.SetEntry(6,		tmp[3]*entries[0] + tmp[6]*entries[1] + tmp[11]*entries[3]
						-	tmp[2]*entries[0] - tmp[7]*entries[1] - tmp[10]*entries[3]);

		result.SetEntry(7,		tmp[4]*entries[0] + tmp[9]*entries[1] + tmp[10]*entries[2]
						-	tmp[5]*entries[0] - tmp[8]*entries[1] - tmp[11]*entries[2]);

		//calculate pairs for second 8 elements (cofactors)
		tmp[0] = entries[2]*entries[7];
		tmp[1] = entries[3]*entries[6];
		tmp[2] = entries[1]*entries[7];
		tmp[3] = entries[3]*entries[5];
		tmp[4] = entries[1]*entries[6];
		tmp[5] = entries[2]*entries[5];
		tmp[6] = entries[0]*entries[7];
		tmp[7] = entries[3]*entries[4];
		tmp[8] = entries[0]*entries[6];
		tmp[9] = entries[2]*entries[4];
		tmp[10] = entries[0]*entries[5];
		tmp[11] = entries[1]*entries[4];

		//calculate second 8 elements (cofactors)
		result.SetEntry(8,		tmp[0]*entries[13] + tmp[3]*entries[14] + tmp[4]*entries[15]
						-	tmp[1]*entries[13] - tmp[2]*entries[14] - tmp[5]*entries[15]);

		result.SetEntry(9,		tmp[1]*entries[12] + tmp[6]*entries[14] + tmp[9]*entries[15]
						-	tmp[0]*entries[12] - tmp[7]*entries[14] - tmp[8]*entries[15]);

		result.SetEntry(10,		tmp[2]*entries[12] + tmp[7]*entries[13] + tmp[10]*entries[15]
						-	tmp[3]*entries[12] - tmp[6]*entries[13] - tmp[11]*entries[15]);

		result.SetEntry(11,		tmp[5]*entries[12] + tmp[8]*entries[13] + tmp[11]*entries[14]
						-	tmp[4]*entries[12] - tmp[9]*entries[13] - tmp[10]*entries[14]);

		result.SetEntry(12,		tmp[2]*entries[10] + tmp[5]*entries[11] + tmp[1]*entries[9]
						-	tmp[4]*entries[11] - tmp[0]*entries[9] - tmp[3]*entries[10]);

		result.SetEntry(13,		tmp[8]*entries[11] + tmp[0]*entries[8] + tmp[7]*entries[10]
						-	tmp[6]*entries[10] - tmp[9]*entries[11] - tmp[1]*entries[8]);

		result.SetEntry(14,		tmp[6]*entries[9] + tmp[11]*entries[11] + tmp[3]*entries[8]
						-	tmp[10]*entries[11] - tmp[2]*entries[8] - tmp[7]*entries[9]);

		result.SetEntry(15,		tmp[10]*entries[10] + tmp[4]*entries[8] + tmp[9]*entries[9]
						-	tmp[8]*entries[9] - tmp[11]*entries[10] - tmp[5]*entries[8]);

		// calculate determinant
		det	=	 entries[0]*result.GetEntry(0)
				+entries[1]*result.GetEntry(1)
				+entries[2]*result.GetEntry(2)
				+entries[3]*result.GetEntry(3);

		if(det==0.0f){
			Mat4 id;
			return id;
		}
		
		result=result/det;

		return result;
	}

	//Invert if only composed of rotations & translations
	void Mat4::AffineInvert(void){
		(*this)=GetAffineInverse();
	}

	Mat4 Mat4::GetAffineInverse(void) const{
		//return the transpose of the rotation part
		//and the negative of the inverse rotated translation part
		return Mat4(	entries[0],
							entries[4],
							entries[8],
							0.0f,
							entries[1],
							entries[5],
							entries[9],
							0.0f,
							entries[2],
							entries[6],
							entries[10],
							0.0f,
							-(entries[0]*entries[12]+entries[1]*entries[13]+entries[2]*entries[14]),
							-(entries[4]*entries[12]+entries[5]*entries[13]+entries[6]*entries[14]),
							-(entries[8]*entries[12]+entries[9]*entries[13]+entries[10]*entries[14]),
							1.0f);
	}

	void Mat4::AffineInvertTranspose(void){
		(*this)=GetAffineInverseTranspose();
	}

	Mat4 Mat4::GetAffineInverseTranspose(void) const{
		//return the transpose of the rotation part
		//and the negative of the inverse rotated translation part
		//transposed
		return Mat4(	entries[0],
							entries[1],
							entries[2],
							-(entries[0]*entries[12]+entries[1]*entries[13]+entries[2]*entries[14]),
							entries[4],
							entries[5],
							entries[6],
							-(entries[4]*entries[12]+entries[5]*entries[13]+entries[6]*entries[14]),
							entries[8],
							entries[9],
							entries[10],
							-(entries[8]*entries[12]+entries[9]*entries[13]+entries[10]*entries[14]),
							0.0f, 0.0f, 0.0f, 1.0f);
	}

	void Mat4::SetTranslation(const Vec3 & translation){
		LoadIdentity();

		SetTranslationPart(translation);
	}

	void Mat4::SetScale(const Vec3 & scaleFactor){
		LoadIdentity();

		entries[0]=scaleFactor.x;
		entries[5]=scaleFactor.y;
		entries[10]=scaleFactor.z;
	}

	void Mat4::SetUniformScale(const float scaleFactor){
		LoadIdentity();

		entries[0]=entries[5]=entries[10]=scaleFactor;
	}

	void Mat4::SetRotationAxis(const double angle, const Vec3 & axis){
		Vec3 u=axis.GetNormalized();

		float sinAngle=(float)sin(PI*angle/180);
		float cosAngle=(float)cos(PI*angle/180);
		float oneMinusCosAngle=1.0f-cosAngle;

		LoadIdentity();

		entries[0]=(u.x)*(u.x) + cosAngle*(1-(u.x)*(u.x));
		entries[4]=(u.x)*(u.y)*(oneMinusCosAngle) - sinAngle*u.z;
		entries[8]=(u.x)*(u.z)*(oneMinusCosAngle) + sinAngle*u.y;

		entries[1]=(u.x)*(u.y)*(oneMinusCosAngle) + sinAngle*u.z;
		entries[5]=(u.y)*(u.y) + cosAngle*(1-(u.y)*(u.y));
		entries[9]=(u.y)*(u.z)*(oneMinusCosAngle) - sinAngle*u.x;
		
		entries[2]=(u.x)*(u.z)*(oneMinusCosAngle) - sinAngle*u.y;
		entries[6]=(u.y)*(u.z)*(oneMinusCosAngle) + sinAngle*u.x;
		entries[10]=(u.z)*(u.z) + cosAngle*(1-(u.z)*(u.z));
	}

	void Mat4::SetRotationX(const double angle){
		LoadIdentity();

		entries[5]=(float)cos(PI*angle/180);
		entries[6]=(float)sin(PI*angle/180);

		entries[9]=-entries[6];
		entries[10]=entries[5];
	}

	void Mat4::SetRotationY(const double angle){
		LoadIdentity();

		entries[0]=(float)cos(PI*angle/180);
		entries[2]=-(float)sin(PI*angle/180);

		entries[8]=-entries[2];
		entries[10]=entries[0];
	}

	void Mat4::SetRotationZ(const double angle){
		LoadIdentity();

		entries[0]=(float)cos(PI*angle/180);
		entries[1]=(float)sin(PI*angle/180);

		entries[4]=-entries[1];
		entries[5]=entries[0];
	}

	void Mat4::SetRotationEuler(const double angleX, const double angleY, const double angleZ){
		LoadIdentity();

		SetRotationPartEuler(angleX, angleY, angleZ);
	}

	void Mat4::SetPerspective( float left, float right, float bottom, float top, float n, float f){
		float nudge=0.999f;		//prevent artifacts with infinite far plane

		LoadZero();

		//check for division by 0
		if(left==right || top==bottom || n==f)
			return;

		entries[0]=(2*n)/(right-left);

		entries[5]=(2*n)/(top-bottom);

		entries[8]=(right+left)/(right-left);
		entries[9]=(top+bottom)/(top-bottom);

		if(f!=-1){
			entries[10]=-(f+n)/(f-n);
		}
		else{//if f==-1, use an infinite far plane
			entries[10]=-nudge;
		}

		entries[11]=-1;

		if(f!=-1)
		{
			entries[14]=-(2*f*n)/(f-n);
		}
		else{//if f==-1, use an infinite far plane
			entries[14]=-2*n*nudge;
		}
	}

	void Mat4::SetPerspective(float fovy, float aspect, float n, float f){
		float left, right, top, bottom;

		//convert fov from degrees to radians
		fovy*=(float)PI/180;

		top=n*tanf(fovy/2.0f);
		bottom=-top;

		left=aspect*bottom;
		right=aspect*top;

		SetPerspective(left, right, bottom, top, n, f);
	}

	void Mat4::SetOrtho( float left, float right, float bottom, float top, float n, float f){
		LoadIdentity();

		entries[0]=2.0f/(right-left);

		entries[5]=2.0f/(top-bottom);

		entries[10]=-2.0f/(f-n);

		entries[12]=-(right+left)/(right-left);
		entries[13]=-(top+bottom)/(top-bottom);
		entries[14]=-(f+n)/(f-n);
	}

	void Mat4::SetTranslationPart(const Vec3 & translation){
		entries[12]=translation.x;
		entries[13]=translation.y;
		entries[14]=translation.z;
	}

	void Mat4::SetRotationPartEuler(const double angleX, const double angleY, const double angleZ){
		double cr = cos( PI*angleX/180 );
		double sr = sin( PI*angleX/180 );
		double cp = cos( PI*angleY/180 );
		double sp = sin( PI*angleY/180 );
		double cy = cos( PI*angleZ/180 );
		double sy = sin( PI*angleZ/180 );

		entries[0] = ( float )( cp*cy );
		entries[1] = ( float )( cp*sy );
		entries[2] = ( float )( -sp );

		double srsp = sr*sp;
		double crsp = cr*sp;

		entries[4] = ( float )( srsp*cy-cr*sy );
		entries[5] = ( float )( srsp*sy+cr*cy );
		entries[6] = ( float )( sr*cp );

		entries[8] = ( float )( crsp*cy+sr*sy );
		entries[9] = ( float )( crsp*sy-sr*cy );
		entries[10] = ( float )( cr*cp );
	}

/*--------------------------------------------//
Operators
//--------------------------------------------*/
	Mat2 Mat2::operator+(const Mat2 & rhs) const {
		return Mat2(	entries[0]+rhs.entries[0],
						entries[1]+rhs.entries[1],
						entries[2]+rhs.entries[2],
						entries[3]+rhs.entries[3]);
	}
	Mat3 Mat3::operator+(const Mat3 & rhs) const {
		return Mat3(	entries[0]+rhs.entries[0],
						entries[1]+rhs.entries[1],
						entries[2]+rhs.entries[2],
						entries[3]+rhs.entries[3],
						entries[4]+rhs.entries[4],
						entries[5]+rhs.entries[5],
						entries[6]+rhs.entries[6],
						entries[7]+rhs.entries[7],
						entries[8]+rhs.entries[8]);
	}
	Mat4 Mat4::operator+(const Mat4 & rhs) const {
		return Mat4(	entries[0]+rhs.entries[0],
						entries[1]+rhs.entries[1],
						entries[2]+rhs.entries[2],
						entries[3]+rhs.entries[3],
						entries[4]+rhs.entries[4],
						entries[5]+rhs.entries[5],
						entries[6]+rhs.entries[6],
						entries[7]+rhs.entries[7],
						entries[8]+rhs.entries[8],
						entries[9]+rhs.entries[9],
						entries[10]+rhs.entries[10],
						entries[11]+rhs.entries[11],
						entries[12]+rhs.entries[12],
						entries[13]+rhs.entries[13],
						entries[14]+rhs.entries[14],
						entries[15]+rhs.entries[15]);
	}

	Mat2 Mat2::operator-(void) const {
		Mat2 result(*this);

		for(int i=0; i<4; i++)
			result.entries[i]=-result.entries[i];

		return result;
	}
	Mat3 Mat3::operator-(void) const {
		Mat3 result(*this);

		for(int i=0; i<9; i++)
			result.entries[i]=-result.entries[i];

		return result;
	}
	Mat4 Mat4::operator-(void) const {
		Mat4 result(*this);

		for(int i=0; i<16; i++)
			result.entries[i]=-result.entries[i];

		return result;
	}
	Mat2 Mat2::operator-(const Mat2 & rhs) const {
		return Mat2(	entries[0]-rhs.entries[0],
						entries[1]-rhs.entries[1],
						entries[2]-rhs.entries[2],
						entries[3]-rhs.entries[3]);
	}
	Mat3 Mat3::operator-(const Mat3 & rhs) const {
		return Mat3(	entries[0]-rhs.entries[0],
						entries[1]-rhs.entries[1],
						entries[2]-rhs.entries[2],
						entries[3]-rhs.entries[3],
						entries[4]-rhs.entries[4],
						entries[5]-rhs.entries[5],
						entries[6]-rhs.entries[6],
						entries[7]-rhs.entries[7],
						entries[8]-rhs.entries[8]);
	}
	Mat4 Mat4::operator-(const Mat4 & rhs) const {
		return Mat4(	entries[0]-rhs.entries[0],
						entries[1]-rhs.entries[1],
						entries[2]-rhs.entries[2],
						entries[3]-rhs.entries[3],
						entries[4]-rhs.entries[4],
						entries[5]-rhs.entries[5],
						entries[6]-rhs.entries[6],
						entries[7]-rhs.entries[7],
						entries[8]-rhs.entries[8],
						entries[9]-rhs.entries[9],
						entries[10]-rhs.entries[10],
						entries[11]-rhs.entries[11],
						entries[12]-rhs.entries[12],
						entries[13]-rhs.entries[13],
						entries[14]-rhs.entries[14],
						entries[15]-rhs.entries[15]);
	}

	Vec2 Mat2::operator*(const Vec2 rhs) const {
		return Vec2(		entries[0]*rhs.x
						+	entries[2]*rhs.y,

							entries[1]*rhs.x
						+	entries[3]*rhs.y);
	}
	Vec3 Mat3::operator*(const Vec3 rhs) const {
		return Vec3(		entries[0]*rhs.x
						+	entries[3]*rhs.y
						+	entries[6]*rhs.z,

							entries[1]*rhs.x
						+	entries[4]*rhs.y
						+	entries[7]*rhs.z,

							entries[2]*rhs.x
						+	entries[5]*rhs.y
						+	entries[9]*rhs.z);
	}
	Vec4 Mat4::operator*(const Vec4 rhs) const {
		//Optimise for matrices in which bottom row is (0, 0, 0, 1)
		if(entries[3]==0.0f && entries[7]==0.0f && entries[11]==0.0f && entries[15]==1.0f){
			return Vec4(entries[0]*rhs.x
						+	entries[4]*rhs.y
						+	entries[8]*rhs.z
						+	entries[12]*rhs.w,

							entries[1]*rhs.x
						+	entries[5]*rhs.y
						+	entries[9]*rhs.z
						+	entries[13]*rhs.w,

							entries[2]*rhs.x
						+	entries[6]*rhs.y
						+	entries[10]*rhs.z
						+	entries[14]*rhs.w,

							rhs.w);
		}
		
		return Vec4(	entries[0]*rhs.x
						+	entries[4]*rhs.y
						+	entries[8]*rhs.z
						+	entries[12]*rhs.w,

							entries[1]*rhs.x
						+	entries[5]*rhs.y
						+	entries[9]*rhs.z
						+	entries[13]*rhs.w,

							entries[2]*rhs.x
						+	entries[6]*rhs.y
						+	entries[10]*rhs.z
						+	entries[14]*rhs.w,

							entries[3]*rhs.x
						+	entries[7]*rhs.y
						+	entries[11]*rhs.z
						+	entries[15]*rhs.w);
	}
	Mat2 Mat2::operator*(const Mat2 & rhs) const {
		return Mat2(	entries[0]*rhs.entries[0]+entries[2]*rhs.entries[1],
						entries[1]*rhs.entries[0]+entries[3]*rhs.entries[1],
						entries[0]*rhs.entries[2]+entries[2]*rhs.entries[3],
						entries[1]*rhs.entries[2]+entries[3]*rhs.entries[3]);
	}
	Mat3 Mat3::operator*(const Mat3 & rhs) const {
		return Mat3(	entries[0]*rhs.entries[0]+entries[3]*rhs.entries[1]+entries[6]*rhs.entries[2],
						entries[1]*rhs.entries[0]+entries[4]*rhs.entries[1]+entries[7]*rhs.entries[2],
						entries[2]*rhs.entries[0]+entries[5]*rhs.entries[1]+entries[8]*rhs.entries[2],
						entries[0]*rhs.entries[3]+entries[3]*rhs.entries[4]+entries[6]*rhs.entries[5],
						entries[1]*rhs.entries[3]+entries[4]*rhs.entries[4]+entries[7]*rhs.entries[5],
						entries[2]*rhs.entries[3]+entries[5]*rhs.entries[4]+entries[8]*rhs.entries[5],
						entries[0]*rhs.entries[6]+entries[3]*rhs.entries[7]+entries[6]*rhs.entries[8],
						entries[1]*rhs.entries[6]+entries[4]*rhs.entries[7]+entries[7]*rhs.entries[8],
						entries[2]*rhs.entries[6]+entries[5]*rhs.entries[7]+entries[8]*rhs.entries[8]);
	}
	Mat4 Mat4::operator*(const Mat4 & rhs) const {
		//Optimise for matrices in which bottom row is (0, 0, 0, 1) in both matrices
		if(	entries[3]==0.0f && entries[7]==0.0f && entries[11]==0.0f && entries[15]==1.0f	&&
			rhs.entries[3]==0.0f && rhs.entries[7]==0.0f &&
			rhs.entries[11]==0.0f && rhs.entries[15]==1.0f){
			return Mat4(	entries[0]*rhs.entries[0]+entries[4]*rhs.entries[1]+entries[8]*rhs.entries[2],
							entries[1]*rhs.entries[0]+entries[5]*rhs.entries[1]+entries[9]*rhs.entries[2],
							entries[2]*rhs.entries[0]+entries[6]*rhs.entries[1]+entries[10]*rhs.entries[2],
							0.0f,
							entries[0]*rhs.entries[4]+entries[4]*rhs.entries[5]+entries[8]*rhs.entries[6],
							entries[1]*rhs.entries[4]+entries[5]*rhs.entries[5]+entries[9]*rhs.entries[6],
							entries[2]*rhs.entries[4]+entries[6]*rhs.entries[5]+entries[10]*rhs.entries[6],
							0.0f,
							entries[0]*rhs.entries[8]+entries[4]*rhs.entries[9]+entries[8]*rhs.entries[10],
							entries[1]*rhs.entries[8]+entries[5]*rhs.entries[9]+entries[9]*rhs.entries[10],
							entries[2]*rhs.entries[8]+entries[6]*rhs.entries[9]+entries[10]*rhs.entries[10],
							0.0f,
							entries[0]*rhs.entries[12]+entries[4]*rhs.entries[13]+entries[8]*rhs.entries[14]+entries[12],
							entries[1]*rhs.entries[12]+entries[5]*rhs.entries[13]+entries[9]*rhs.entries[14]+entries[13],
							entries[2]*rhs.entries[12]+entries[6]*rhs.entries[13]+entries[10]*rhs.entries[14]+entries[14],
							1.0f);
		}

		//Optimise for when bottom row of 1st matrix is (0, 0, 0, 1)
		if(	entries[3]==0.0f && entries[7]==0.0f && entries[11]==0.0f && entries[15]==1.0f){
			return Mat4(	entries[0]*rhs.entries[0]+entries[4]*rhs.entries[1]+entries[8]*rhs.entries[2]+entries[12]*rhs.entries[3],
							entries[1]*rhs.entries[0]+entries[5]*rhs.entries[1]+entries[9]*rhs.entries[2]+entries[13]*rhs.entries[3],
							entries[2]*rhs.entries[0]+entries[6]*rhs.entries[1]+entries[10]*rhs.entries[2]+entries[14]*rhs.entries[3],
							rhs.entries[3],
							entries[0]*rhs.entries[4]+entries[4]*rhs.entries[5]+entries[8]*rhs.entries[6]+entries[12]*rhs.entries[7],
							entries[1]*rhs.entries[4]+entries[5]*rhs.entries[5]+entries[9]*rhs.entries[6]+entries[13]*rhs.entries[7],
							entries[2]*rhs.entries[4]+entries[6]*rhs.entries[5]+entries[10]*rhs.entries[6]+entries[14]*rhs.entries[7],
							rhs.entries[7],
							entries[0]*rhs.entries[8]+entries[4]*rhs.entries[9]+entries[8]*rhs.entries[10]+entries[12]*rhs.entries[11],
							entries[1]*rhs.entries[8]+entries[5]*rhs.entries[9]+entries[9]*rhs.entries[10]+entries[13]*rhs.entries[11],
							entries[2]*rhs.entries[8]+entries[6]*rhs.entries[9]+entries[10]*rhs.entries[10]+entries[14]*rhs.entries[11],
							rhs.entries[11],
							entries[0]*rhs.entries[12]+entries[4]*rhs.entries[13]+entries[8]*rhs.entries[14]+entries[12]*rhs.entries[15],
							entries[1]*rhs.entries[12]+entries[5]*rhs.entries[13]+entries[9]*rhs.entries[14]+entries[13]*rhs.entries[15],
							entries[2]*rhs.entries[12]+entries[6]*rhs.entries[13]+entries[10]*rhs.entries[14]+entries[14]*rhs.entries[15],
							rhs.entries[15]);
		}

		//Optimise for when bottom row of 2nd matrix is (0, 0, 0, 1)
		if(	rhs.entries[3]==0.0f && rhs.entries[7]==0.0f &&
			rhs.entries[11]==0.0f && rhs.entries[15]==1.0f){
			return Mat4(	entries[0]*rhs.entries[0]+entries[4]*rhs.entries[1]+entries[8]*rhs.entries[2],
							entries[1]*rhs.entries[0]+entries[5]*rhs.entries[1]+entries[9]*rhs.entries[2],
							entries[2]*rhs.entries[0]+entries[6]*rhs.entries[1]+entries[10]*rhs.entries[2],
							entries[3]*rhs.entries[0]+entries[7]*rhs.entries[1]+entries[11]*rhs.entries[2],
							entries[0]*rhs.entries[4]+entries[4]*rhs.entries[5]+entries[8]*rhs.entries[6],
							entries[1]*rhs.entries[4]+entries[5]*rhs.entries[5]+entries[9]*rhs.entries[6],
							entries[2]*rhs.entries[4]+entries[6]*rhs.entries[5]+entries[10]*rhs.entries[6],
							entries[3]*rhs.entries[4]+entries[7]*rhs.entries[5]+entries[11]*rhs.entries[6],
							entries[0]*rhs.entries[8]+entries[4]*rhs.entries[9]+entries[8]*rhs.entries[10],
							entries[1]*rhs.entries[8]+entries[5]*rhs.entries[9]+entries[9]*rhs.entries[10],
							entries[2]*rhs.entries[8]+entries[6]*rhs.entries[9]+entries[10]*rhs.entries[10],
							entries[3]*rhs.entries[8]+entries[7]*rhs.entries[9]+entries[11]*rhs.entries[10],
							entries[0]*rhs.entries[12]+entries[4]*rhs.entries[13]+entries[8]*rhs.entries[14]+entries[12],
							entries[1]*rhs.entries[12]+entries[5]*rhs.entries[13]+entries[9]*rhs.entries[14]+entries[13],
							entries[2]*rhs.entries[12]+entries[6]*rhs.entries[13]+entries[10]*rhs.entries[14]+entries[14],
							entries[3]*rhs.entries[12]+entries[7]*rhs.entries[13]+entries[11]*rhs.entries[14]+entries[15]);
		}	
		
		return Mat4(	entries[0]*rhs.entries[0]+entries[4]*rhs.entries[1]+entries[8]*rhs.entries[2]+entries[12]*rhs.entries[3],
						entries[1]*rhs.entries[0]+entries[5]*rhs.entries[1]+entries[9]*rhs.entries[2]+entries[13]*rhs.entries[3],
						entries[2]*rhs.entries[0]+entries[6]*rhs.entries[1]+entries[10]*rhs.entries[2]+entries[14]*rhs.entries[3],
						entries[3]*rhs.entries[0]+entries[7]*rhs.entries[1]+entries[11]*rhs.entries[2]+entries[15]*rhs.entries[3],
						entries[0]*rhs.entries[4]+entries[4]*rhs.entries[5]+entries[8]*rhs.entries[6]+entries[12]*rhs.entries[7],
						entries[1]*rhs.entries[4]+entries[5]*rhs.entries[5]+entries[9]*rhs.entries[6]+entries[13]*rhs.entries[7],
						entries[2]*rhs.entries[4]+entries[6]*rhs.entries[5]+entries[10]*rhs.entries[6]+entries[14]*rhs.entries[7],
						entries[3]*rhs.entries[4]+entries[7]*rhs.entries[5]+entries[11]*rhs.entries[6]+entries[15]*rhs.entries[7],
						entries[0]*rhs.entries[8]+entries[4]*rhs.entries[9]+entries[8]*rhs.entries[10]+entries[12]*rhs.entries[11],
						entries[1]*rhs.entries[8]+entries[5]*rhs.entries[9]+entries[9]*rhs.entries[10]+entries[13]*rhs.entries[11],
						entries[2]*rhs.entries[8]+entries[6]*rhs.entries[9]+entries[10]*rhs.entries[10]+entries[14]*rhs.entries[11],
						entries[3]*rhs.entries[8]+entries[7]*rhs.entries[9]+entries[11]*rhs.entries[10]+entries[15]*rhs.entries[11],
						entries[0]*rhs.entries[12]+entries[4]*rhs.entries[13]+entries[8]*rhs.entries[14]+entries[12]*rhs.entries[15],
						entries[1]*rhs.entries[12]+entries[5]*rhs.entries[13]+entries[9]*rhs.entries[14]+entries[13]*rhs.entries[15],
						entries[2]*rhs.entries[12]+entries[6]*rhs.entries[13]+entries[10]*rhs.entries[14]+entries[14]*rhs.entries[15],
						entries[3]*rhs.entries[12]+entries[7]*rhs.entries[13]+entries[11]*rhs.entries[14]+entries[15]*rhs.entries[15]);
	}
	Mat2 Mat2::operator*(const double rhs) const {
		return Mat2(	entries[0]*rhs,
						entries[1]*rhs,
						entries[2]*rhs,
						entries[3]*rhs);
	}
	Mat3 Mat3::operator*(const double rhs) const {
		return Mat3(	entries[0]*rhs,
						entries[1]*rhs,
						entries[2]*rhs,
						entries[3]*rhs,
						entries[4]*rhs,
						entries[5]*rhs,
						entries[6]*rhs,
						entries[7]*rhs,
						entries[8]*rhs);
	}
	Mat4 Mat4::operator*(const double rhs) const {
		return Mat4(	entries[0]*rhs,
						entries[1]*rhs,
						entries[2]*rhs,
						entries[3]*rhs,
						entries[4]*rhs,
						entries[5]*rhs,
						entries[6]*rhs,
						entries[7]*rhs,
						entries[8]*rhs,
						entries[9]*rhs,
						entries[10]*rhs,
						entries[11]*rhs,
						entries[12]*rhs,
						entries[13]*rhs,
						entries[14]*rhs,
						entries[15]*rhs);
	}

	Mat2 Mat2::operator/(const double rhs) const {
		if (rhs==0.0f || rhs==1.0f)
			return (*this);
			
		double temp=1/rhs;

		return (*this)*temp;
	}
	Mat3 Mat3::operator/(const double rhs) const {
		if (rhs==0.0f || rhs==1.0f)
			return (*this);
			
		double temp=1/rhs;

		return (*this)*temp;
	}
	Mat4 Mat4::operator/(const double rhs) const {
		if (rhs==0.0f || rhs==1.0f)
			return (*this);
			
		double temp=1/rhs;

		return (*this)*temp;
	}

	Mat2 operator*(double scaleFactor, const Mat2& rhs){
		return rhs*scaleFactor;
	}
	Mat3 operator*(double scaleFactor, const Mat3& rhs){
		return rhs*scaleFactor;
	}
	Mat4 operator*(double scaleFactor, const Mat4& rhs){
		return rhs*scaleFactor;
	}

	bool Mat2::operator==(const Mat2 & rhs) const {
		for(int i=0; i<4; i++){
			if(entries[i]!=rhs.entries[i])
				return false;
		}
		return true;
	}
	bool Mat3::operator==(const Mat3 & rhs) const {
		for(int i=0; i<9; i++){
			if(entries[i]!=rhs.entries[i])
				return false;
		}
		return true;
	}
	bool Mat4::operator==(const Mat4 & rhs) const {
		for(int i=0; i<16; i++){
			if(entries[i]!=rhs.entries[i])
				return false;
		}
		return true;
	}
	bool Mat2::operator!=(const Mat2 & rhs) const {
		return !((*this)==rhs);
	}
	bool Mat3::operator!=(const Mat3 & rhs) const {
		return !((*this)==rhs);
	}
	bool Mat4::operator!=(const Mat4 & rhs) const {
		return !((*this)==rhs);
	}

	void Mat2::operator+=(const Mat2 & rhs){
		(*this)=(*this)+rhs;
	}
	void Mat3::operator+=(const Mat3 & rhs){
		(*this)=(*this)+rhs;
	}
	void Mat4::operator+=(const Mat4 & rhs){
		(*this)=(*this)+rhs;
	}
	void Mat2::operator-=(const Mat2 & rhs){
		(*this)=(*this)-rhs;
	}
	void Mat3::operator-=(const Mat3 & rhs){
		(*this)=(*this)-rhs;
	}
	void Mat4::operator-=(const Mat4 & rhs){
		(*this)=(*this)-rhs;
	}
	void Mat2::operator*=(const Mat2 & rhs){
		(*this)=(*this)*rhs;
	}
	void Mat3::operator*=(const Mat3 & rhs){
		(*this)=(*this)*rhs;
	}
	void Mat4::operator*=(const Mat4 & rhs){
		(*this)=(*this)*rhs;
	}
	void Mat2::operator*=(const double rhs){
		(*this)=(*this)*rhs;
	}
	void Mat3::operator*=(const double rhs){
		(*this)=(*this)*rhs;
	}
	void Mat4::operator*=(const double rhs){
		(*this)=(*this)*rhs;
	}
	void Mat2::operator/=(const double rhs){
		(*this)=(*this)/rhs;
	}
	void Mat3::operator/=(const double rhs){
		(*this)=(*this)/rhs;
	}
	void Mat4::operator/=(const double rhs){
		(*this)=(*this)/rhs;
	}
#endif	//Matrix