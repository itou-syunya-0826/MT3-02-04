#include "Matrix.h"
#include <cassert>

using namespace std;

Matrix::Matrix() {}

Matrix4x4 Matrix::Add(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result{};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}

	return result;
}

Vector3 Matrix::Add(const Vector3& a, const Vector3& b)
{
	return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Matrix4x4 Matrix::Subtract(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result{};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}

	return result;
}

Vector2 Matrix::Subtract(const Vector2& v1, const Vector2& v2)
{
	return { v1.x - v2.x, v1.y - v2.y };
}

Vector3 Matrix::Subtract(const Vector3& a, const Vector3& b)
{
	return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Matrix4x4 Matrix::Multiply(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result{};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = 0;
			for (int k = 0; k < 4; k++) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}

	return result;
}

Vector3 Matrix::Multiply(float scalar, const Vector3& vector)
{
	return Vector3{ scalar * vector.x, scalar * vector.y, scalar * vector.z };
}

Matrix4x4 Matrix::Inverse(const Matrix4x4& matrix)
{
	Matrix4x4 result{};

	float Inverse =
		matrix.m[0][0] * (
			matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3] +
			matrix.m[2][1] * matrix.m[3][2] * matrix.m[1][3] +
			matrix.m[3][1] * matrix.m[1][2] * matrix.m[2][3] -
			matrix.m[3][1] * matrix.m[2][2] * matrix.m[1][3] -
			matrix.m[2][1] * matrix.m[1][2] * matrix.m[3][3] -
			matrix.m[1][1] * matrix.m[3][2] * matrix.m[2][3]) -
		matrix.m[0][1] * (matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3] +
			matrix.m[2][0] * matrix.m[3][2] * matrix.m[1][3] +
			matrix.m[3][0] * matrix.m[1][2] * matrix.m[2][3] -
			matrix.m[3][0] * matrix.m[2][2] * matrix.m[1][3] -
			matrix.m[2][0] * matrix.m[1][2] * matrix.m[3][3] -
			matrix.m[1][0] * matrix.m[3][2] * matrix.m[2][3]) +
		matrix.m[0][2] * (matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3] +
			matrix.m[2][0] * matrix.m[3][1] * matrix.m[1][3] +
			matrix.m[3][0] * matrix.m[1][1] * matrix.m[2][3] -
			matrix.m[3][0] * matrix.m[2][1] * matrix.m[1][3] -
			matrix.m[2][0] * matrix.m[1][1] * matrix.m[3][3] -
			matrix.m[1][0] * matrix.m[3][1] * matrix.m[2][3]) -
		matrix.m[0][3] * (matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2] +
			matrix.m[2][0] * matrix.m[3][1] * matrix.m[1][2] +
			matrix.m[3][0] * matrix.m[1][1] * matrix.m[2][2] -
			matrix.m[3][0] * matrix.m[2][1] * matrix.m[1][2] -
			matrix.m[2][0] * matrix.m[1][1] * matrix.m[3][2] -
			matrix.m[1][0] * matrix.m[3][1] * matrix.m[2][2]);

	if (Inverse != 0) {
		result.m[0][0] = (matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3] +
			matrix.m[2][1] * matrix.m[3][2] * matrix.m[1][3] +
			matrix.m[3][1] * matrix.m[1][2] * matrix.m[2][3] -
			matrix.m[3][1] * matrix.m[2][2] * matrix.m[1][3] -
			matrix.m[2][1] * matrix.m[1][2] * matrix.m[3][3] -
			matrix.m[1][1] * matrix.m[3][2] * matrix.m[2][3]) /
			Inverse;

		result.m[0][1] = -(matrix.m[0][1] * matrix.m[2][2] * matrix.m[3][3] +
			matrix.m[2][1] * matrix.m[3][2] * matrix.m[0][3] +
			matrix.m[3][1] * matrix.m[0][2] * matrix.m[2][3] -
			matrix.m[3][1] * matrix.m[2][2] * matrix.m[0][3] -
			matrix.m[2][1] * matrix.m[0][2] * matrix.m[3][3] -
			matrix.m[0][1] * matrix.m[3][2] * matrix.m[2][3]) /
			Inverse;

		result.m[0][2] = (matrix.m[0][1] * matrix.m[1][2] * matrix.m[3][3] +
			matrix.m[1][1] * matrix.m[3][2] * matrix.m[0][3] +
			matrix.m[3][1] * matrix.m[0][2] * matrix.m[1][3] -
			matrix.m[3][1] * matrix.m[1][2] * matrix.m[0][3] -
			matrix.m[1][1] * matrix.m[0][2] * matrix.m[3][3] -
			matrix.m[0][1] * matrix.m[3][2] * matrix.m[1][3]) /
			Inverse;

		result.m[0][3] = -(matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][3] +
			matrix.m[1][1] * matrix.m[2][2] * matrix.m[0][3] +
			matrix.m[2][1] * matrix.m[0][2] * matrix.m[1][3] -
			matrix.m[2][1] * matrix.m[1][2] * matrix.m[0][3] -
			matrix.m[1][1] * matrix.m[0][2] * matrix.m[2][3] -
			matrix.m[0][1] * matrix.m[2][2] * matrix.m[1][3]) /
			Inverse;


		result.m[1][0] = -(matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3] +
			matrix.m[2][0] * matrix.m[3][2] * matrix.m[1][3] +
			matrix.m[3][0] * matrix.m[1][2] * matrix.m[2][3] -
			matrix.m[3][0] * matrix.m[2][2] * matrix.m[1][3] -
			matrix.m[2][0] * matrix.m[1][2] * matrix.m[3][3] -
			matrix.m[1][0] * matrix.m[3][2] * matrix.m[2][3]) /
			Inverse;

		result.m[1][1] = (matrix.m[0][0] * matrix.m[2][2] * matrix.m[3][3] +
			matrix.m[2][0] * matrix.m[3][2] * matrix.m[0][3] +
			matrix.m[3][0] * matrix.m[0][2] * matrix.m[2][3] -
			matrix.m[3][0] * matrix.m[2][2] * matrix.m[0][3] -
			matrix.m[2][0] * matrix.m[0][2] * matrix.m[3][3] -
			matrix.m[0][0] * matrix.m[3][2] * matrix.m[2][3]) /
			Inverse;

		result.m[1][2] = -(matrix.m[0][0] * matrix.m[1][2] * matrix.m[3][3] +
			matrix.m[1][0] * matrix.m[3][2] * matrix.m[0][3] +
			matrix.m[3][0] * matrix.m[0][2] * matrix.m[1][3] -
			matrix.m[3][0] * matrix.m[1][2] * matrix.m[0][3] -
			matrix.m[1][0] * matrix.m[0][2] * matrix.m[3][3] -
			matrix.m[0][0] * matrix.m[3][2] * matrix.m[1][3]) /
			Inverse;

		result.m[1][3] = (matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][3] +
			matrix.m[1][0] * matrix.m[2][2] * matrix.m[0][3] +
			matrix.m[2][0] * matrix.m[0][2] * matrix.m[1][3] -
			matrix.m[2][0] * matrix.m[1][2] * matrix.m[0][3] -
			matrix.m[1][0] * matrix.m[0][2] * matrix.m[2][3] -
			matrix.m[0][0] * matrix.m[2][2] * matrix.m[1][3]) /
			Inverse;


		result.m[2][0] = (matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3] +
			matrix.m[2][0] * matrix.m[3][1] * matrix.m[1][3] +
			matrix.m[3][0] * matrix.m[1][1] * matrix.m[2][3] -
			matrix.m[3][0] * matrix.m[2][1] * matrix.m[1][3] -
			matrix.m[2][0] * matrix.m[1][1] * matrix.m[3][3] -
			matrix.m[1][0] * matrix.m[3][1] * matrix.m[2][3]) /
			Inverse;

		result.m[2][1] = -(matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][3] +
			matrix.m[2][0] * matrix.m[3][1] * matrix.m[0][3] +
			matrix.m[3][0] * matrix.m[0][1] * matrix.m[2][3] -
			matrix.m[3][0] * matrix.m[2][1] * matrix.m[0][3] -
			matrix.m[2][0] * matrix.m[0][1] * matrix.m[3][3] -
			matrix.m[0][0] * matrix.m[3][1] * matrix.m[2][3]) /
			Inverse;

		result.m[2][2] = (matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][3] +
			matrix.m[1][0] * matrix.m[3][1] * matrix.m[0][3] +
			matrix.m[3][0] * matrix.m[0][1] * matrix.m[1][3] -
			matrix.m[3][0] * matrix.m[1][1] * matrix.m[0][3] -
			matrix.m[1][0] * matrix.m[0][1] * matrix.m[3][3] -
			matrix.m[0][0] * matrix.m[3][1] * matrix.m[1][3]) /
			Inverse;

		result.m[2][3] = -(matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][3] +
			matrix.m[1][0] * matrix.m[2][1] * matrix.m[0][3] +
			matrix.m[2][0] * matrix.m[0][1] * matrix.m[1][3] -
			matrix.m[2][0] * matrix.m[1][1] * matrix.m[0][3] -
			matrix.m[1][0] * matrix.m[0][1] * matrix.m[2][3] -
			matrix.m[0][0] * matrix.m[2][1] * matrix.m[1][3]) /
			Inverse;

		result.m[3][0] = -(matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2] +
			matrix.m[2][0] * matrix.m[3][1] * matrix.m[1][2] +
			matrix.m[3][0] * matrix.m[1][1] * matrix.m[2][2] -
			matrix.m[3][0] * matrix.m[2][1] * matrix.m[1][2] -
			matrix.m[2][0] * matrix.m[1][1] * matrix.m[3][2] -
			matrix.m[1][0] * matrix.m[3][1] * matrix.m[2][2]) /
			Inverse;

		result.m[3][1] = (matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][2] +
			matrix.m[2][0] * matrix.m[3][1] * matrix.m[0][2] +
			matrix.m[3][0] * matrix.m[0][1] * matrix.m[2][2] -
			matrix.m[3][0] * matrix.m[2][1] * matrix.m[0][2] -
			matrix.m[2][0] * matrix.m[0][1] * matrix.m[3][2] -
			matrix.m[0][0] * matrix.m[3][1] * matrix.m[2][2]) /
			Inverse;

		result.m[3][2] = -(matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][2] +
			matrix.m[1][0] * matrix.m[3][1] * matrix.m[0][2] +
			matrix.m[3][0] * matrix.m[0][1] * matrix.m[1][2] -
			matrix.m[3][0] * matrix.m[1][1] * matrix.m[0][2] -
			matrix.m[1][0] * matrix.m[0][1] * matrix.m[3][2] -
			matrix.m[0][0] * matrix.m[3][1] * matrix.m[1][2]) /
			Inverse;

		result.m[3][3] = (matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] +
			matrix.m[1][0] * matrix.m[2][1] * matrix.m[0][2] +
			matrix.m[2][0] * matrix.m[0][1] * matrix.m[1][2] -
			matrix.m[2][0] * matrix.m[1][1] * matrix.m[0][2] -
			matrix.m[1][0] * matrix.m[0][1] * matrix.m[2][2] -
			matrix.m[0][0] * matrix.m[2][1] * matrix.m[1][2]) /
			Inverse;
	}

	return result;

}

Matrix4x4 Matrix::Transpose(const Matrix4x4& matrix)
{
	Matrix4x4 result{};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = matrix.m[j][i];
		}
	}

	return result;
}

Matrix4x4 Matrix::MakeIdentity4x4()
{
	Matrix4x4 result{};

	result =
	{ 1,0,0,0,
	  0,1,0,0,
	  0,0,1,0,
	  0,0,0,1
	};

	return result;
}

Matrix4x4 Matrix::MakeTranslateMatrix(const Vector3& translate)
{

	Matrix4x4 result =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		translate.x,translate.y,translate.z,1
	};

	return result;

}

Matrix4x4 Matrix::MakeScaleMatrix(const Vector3& scale)
{

	Matrix4x4 result =
	{
		scale.x,0,0,0,
		0,scale.y,0,0,
		0,0,scale.z,0,
		0,0,0,1
	};

	return result;
}

Vector3 Matrix::Transform(const Vector3& vector, const Matrix4x4& matrix)
{

	Vector3 tranceform = {};
	tranceform.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	tranceform.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	tranceform.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	/*assert(w != 0.0f);*/
	tranceform.x /= w;
	tranceform.y /= w;
	tranceform.z /= w;
	return tranceform;

}

Matrix4x4 Matrix::MakeRotateXMatrix(float radian) {

	Matrix4x4 result =
	{
		1, 0, 0, 0,
		0, cosf(radian), sin(radian), 0,
		0, -sinf(radian), cosf(radian), 0,
		0, 0, 0, 1
	};

	return result;
}

Matrix4x4 Matrix::MakeRotateYMatrix(float radian) {

	Matrix4x4 result = {
		cosf(radian), 0, -sinf(radian), 0,
		0, 1, 0, 0,
		sinf(radian), 0, cosf(radian), 0,
		0, 0, 0, 1
	};

	return result;
}

Matrix4x4 Matrix::MakeRotateZMatrix(float radian) {

	Matrix4x4 result =
	{
		cosf(radian), sinf(radian), 0, 0,
		-sinf(radian), cosf(radian), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1,
	};

	return result;
}

Matrix4x4 Matrix::MakeRotateXYZMatrix(Vector3 radian)
{
	Matrix4x4 result = Multiply(Multiply(MakeRotateXMatrix(radian.x), MakeRotateYMatrix(radian.y)), MakeRotateZMatrix(radian.z));

	return result;
}

Matrix4x4 Matrix::MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate)
{
	return Multiply(Multiply(MakeScaleMatrix(scale), MakeRotateXYZMatrix(rotate)), MakeTranslateMatrix(translate));
}

float Matrix::Cot(float theta) {

	float result = 1 / tanf(theta);

	return result;
}

Matrix4x4 Matrix::MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farclip)
{

	Matrix4x4 result = {
		Cot(fovY / 2) * (1 / aspectRatio),0,0,0,
		0,Cot(fovY / 2),0,0,
		0,0,(farclip - nearClip) / farclip,1,
		0,0,(-nearClip * farclip) / (farclip - nearClip),0
	};

	return result;
}

Matrix4x4 Matrix::MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip)
{
	Matrix4x4 result = {
		2 / (right - left),0,0,0,
		0,2 / (top - bottom),0,0,
		0,0,1 / farClip - nearClip,0,
		(left + right) / (left - right),(top + bottom) / (bottom - top)  ,nearClip / (nearClip - farClip),1
	};

	return result;

}

Matrix4x4 Matrix::MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth)
{

	Matrix4x4 result = {
		width / 2 ,0,0,0,
		0, height / -2,0,0,
		0,0,maxDepth - minDepth,0,
		left + (width / 2) , top + (height / 2),minDepth,1
	};

	return result;
}

Vector3 Matrix::Cross(const Vector3& v1, const Vector3& v2)
{
	Vector3 result = {
		(v1.y * v2.z) - (v1.z * v2.y),
		(v1.z * v2.x) - (v1.x * v2.z),
		(v1.x * v2.y) - (v1.y * v2.x)
	};

	return result;
}

void Matrix::DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfWidth = 2.0f; // グリッドの半分の幅
	const uint32_t kSubdivision = 10; // 分割数
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision); // 一つ分の長さ
	uint32_t color = 0xAAAAAAFF; // グリッド線の色(薄い灰色)
	uint32_t originColor = 0x000000FF; // 原点の色

	Vector3 start[11] = { 0,0,0,0,0,0,0,0,0,0,0 };
	Vector3 end[11] = { 0,0,0,0,0,0,0,0,0,0,0 };
	Vector3 ScreenStart[11] = { 0,0,0,0,0,0,0,0,0,0,0 };
	Vector3 ScreenEnd[11] = { 0,0,0,0,0,0,0,0,0,0,0 };

	// 奥から手前への線を順々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		// 上の情報を使ってワールド座標系と終点を求める
		start[xIndex] = { (-(float)kSubdivision / 2.0f + (float)xIndex) * kGridEvery, 0.0f, -kGridHalfWidth };
		end[xIndex] = { (-(float)kSubdivision / 2.0f + (float)xIndex) * kGridEvery, 0.0f,  kGridHalfWidth };

		// スクリーン座標系まで変換をかける
		ScreenStart[xIndex] = Transform(Transform(start[xIndex], viewProjectionMatrix), viewportMatrix);
		ScreenEnd[xIndex] = Transform(Transform(end[xIndex], viewProjectionMatrix), viewportMatrix);

		// 線の色を設定
		uint32_t lineColor = (xIndex == kSubdivision / 2) ? originColor : color;

		// 変換した座標を使って表示
		Novice::DrawLine(static_cast<int>(ScreenStart[xIndex].x), static_cast<int>(ScreenStart[xIndex].y),
			static_cast<int>(ScreenEnd[xIndex].x), static_cast<int>(ScreenEnd[xIndex].y),
			lineColor);
	}

	// 左から右も同じように順々に引いていく
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {

		start[zIndex] = { -kGridHalfWidth,0.0f,(-(float)kSubdivision / 2.0f + (float)zIndex) * kGridEvery };
		end[zIndex] = { kGridHalfWidth,0.0f, (-(float)kSubdivision / 2.0f + (float)zIndex) * kGridEvery };

		// ワールド座標系からスクリーン座標系への変換
		ScreenStart[zIndex] = Transform(Transform(start[zIndex], viewProjectionMatrix), viewportMatrix);
		ScreenEnd[zIndex] = Transform(Transform(end[zIndex], viewProjectionMatrix), viewportMatrix);

		// 線の色を設定
		uint32_t lineColor = (zIndex == kSubdivision / 2) ? originColor : color;

		// 線を描画
		Novice::DrawLine(static_cast<int>(ScreenStart[zIndex].x), static_cast<int>(ScreenStart[zIndex].y),
			static_cast<int>(ScreenEnd[zIndex].x), static_cast<int>(ScreenEnd[zIndex].y), lineColor);
	}
}

void Matrix::DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	float pi = std::numbers::pi_v<float>;
	const uint32_t kSubdivision = 12;
	// 経度分割1つ分の角度
	const float kLonEvery = pi * 2.0f / float(kSubdivision);
	// 緯度分割1つ分の角度
	const float kLatEvery = pi / float(kSubdivision);
	// 緯度の方向に分割
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -pi / 2.0f + kLatEvery * latIndex;
		// 経度の方向に分割しながら線を描く
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;
			Vector3 a = {
			  sphere.center.x + sphere.radius * std::cos(lat) * std::cos(lon),
			  sphere.center.y + sphere.radius * std::sin(lat),
			  sphere.center.z + sphere.radius * std::cos(lat) * std::sin(lon) };
			Vector3 b = {
			  sphere.center.x + sphere.radius * std::cos(lat + kLatEvery) * std::cos(lon),
			  sphere.center.y + sphere.radius * std::sin(lat + kLatEvery),
			  sphere.center.z + sphere.radius * std::cos(lat + kLatEvery) * std::sin(lon) };
			Vector3 c = {
			  sphere.center.x + sphere.radius * std::cos(lat) * std::cos(lon + kLonEvery),
			  sphere.center.y + sphere.radius * std::sin(lat),
			  sphere.center.z + sphere.radius * std::cos(lat) * std::sin(lon + kLonEvery) };
			// 線を描く
			Vector3 screenA = Transform(Transform(a, viewProjectionMatrix), viewportMatrix);
			Vector3 screenB = Transform(Transform(b, viewProjectionMatrix), viewportMatrix);
			Vector3 screenC = Transform(Transform(c, viewProjectionMatrix), viewportMatrix);
			Novice::DrawLine(int(screenA.x), int(screenA.y), int(screenB.x), int(screenB.y), color);
			Novice::DrawLine(int(screenA.x), int(screenA.y), int(screenC.x), int(screenC.y), color);
		}
	}
}

float Matrix::Dot(const Vector3& v1, const Vector3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 Matrix::Project(const Vector3& v1, const Vector3& v2)
{
	float v2SqLength = Dot(v2, v2);
	float dot = Dot(v1, v2);
	return Multiply(dot / v2SqLength, v2);
}

Vector3 Matrix::ClosestPoint(const Vector3& point, const Segment& segment) {
	Vector3 v = Subtract(point, segment.origin);
	float t = Dot(v, segment.diff) / Dot(segment.diff, segment.diff);
	t = std::clamp(t, 0.0f, 1.0f);
	return Add(segment.origin, Multiply(t, segment.diff));
}

float Matrix::Length(const Vector3& vec) {
	return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}


bool Matrix::IsCollision(const Sphere& s1, const Sphere& s2) {
	// 2つの球の中心点間の距離を求める
	Vector3 diff = { s2.center.x - s1.center.x, s2.center.y - s1.center.y, s2.center.z - s1.center.z };
	float distance = Length(diff);

	// 半径の合計よりも短ければ衝突
	if (distance <= s1.radius + s2.radius) {
		// 当たった処理を諸々
		return true;
	}

	return false;
}

bool Matrix::IsCollision(const Sphere& sphere, const Plane& plane) {
	// 球体の中心と平面の距離を計算
	float distance = Dot(plane.normal, sphere.center) + plane.distance;

	// 衝突判定（距離が球体の半径以下なら衝突している）
	return std::abs(distance) <= sphere.radius;
}

bool Matrix::IsCollision(const Segment& segment, const Plane& plane)
{
	// まず垂直判定を行うために、法線と線の内積を求める
	float dot = Dot(plane.normal, segment.diff);

	// 垂直＝平行であるので、衝突しているはずがない
	if (dot == 0.0f) {
		return false;
	}

	// tを求める
	float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;

	// tの値と線の種類によって衝突しているかを判断する
	// セグメントの場合、tは[0, 1]の範囲内でなければならない
	if (t >= 0.0f && t <= 1.0f) {
		return true;
	}

	return false;
}

Vector3 Matrix::Perpendicular(const Vector3& vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return { -vector.y,vector.x,0.0f };
	}
	return { 0.0f,-vector.z,vector.y };
}

Vector3 Matrix::Normalize(const Vector3& v)
{
	float length = Length(v);
	if (length == 0.0f) {
		return v; // ゼロベクトルの場合はそのまま返す
	}
	return { v.x / length, v.y / length, v.z / length };
}

void Matrix::DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	// 平面の中心を計算
	Vector3 center = Multiply(plane.distance, plane.normal);// 1
	// 平面に垂直なベクトルを計算
	Vector3 perpendiculars[4];
	perpendiculars[0] = Normalize(Perpendicular(plane.normal));// 2
	perpendiculars[1] = { -perpendiculars[0].x,-perpendiculars[0].y,-perpendiculars[0].z };// 3
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]);// 4
	perpendiculars[3] = { -perpendiculars[2].x,-perpendiculars[2].y,-perpendiculars[2].z };// 5
	// 6
	Vector3 points[4];
	for (int32_t index = 0; index < 4; ++index) {
		Vector3 extend = Multiply(2.0f, perpendiculars[index]);
		Vector3 point = Add(center, extend);
		points[index] = Transform(Transform(point, viewProjectionMatrix), viewportMatrix);
	}

	// DrawLine関数を使って線を描画
	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[2].x, (int)points[2].y, color);
	Novice::DrawLine((int)points[1].x, (int)points[1].y, (int)points[2].x, (int)points[2].y, color);
	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[3].x, (int)points[3].y, color);
	Novice::DrawLine((int)points[1].x, (int)points[1].y, (int)points[3].x, (int)points[3].y, color);
	
}








