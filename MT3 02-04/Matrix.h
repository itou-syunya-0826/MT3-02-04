#pragma once
#include <Matrix4x4.h>
#include <Vector3.h>
#include <Vector2.h>
#include <Novice.h>
#include <cmath>
#include <numbers>
#include <imgui.h>
#include <algorithm>
#define PI 3.14159265358979323846


class Matrix
{
public:

	/// <summary>
	/// 球
	/// </summary>
	struct Sphere {
		Vector3 center;
		float radius;
	};
	/// <summary>
	/// 直線
	/// </summary>
	struct Line {
		Vector3 origin;// 終点
		Vector3 deff;// 終点への差分ベクトル
	};
	/// <summary>
	/// 半直線
	/// </summary>
	struct Ray {
		Vector3 origin;// 終点
		Vector3 deff;// 終点への差分ベクトル
	};
	/// <summary>
	/// 線分
	/// </summary>
	struct Segment {
		Vector3 origin;// 終点
		Vector3 diff;// 終点への差分ベクトル
	};

	struct Plane {
		Vector3 normal;// 法線
		float distance;// 距離
	};

public:

	Matrix();

	/// <summary>
	/// 行列の加法
	/// </summary>
	/// <param name="m1"></param>
	/// <param name="m2"></param>
	/// <returns></returns>
	static Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
	/// <summary>
	/// Vector3の加算
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns></returns>
	static Vector3 Add(const Vector3& a, const Vector3& b);
	/// <summary>
	/// 行列の減法
	/// </summary>
	/// <param name="m1"></param>
	/// <param name="m2"></param>
	/// <returns></returns>
	static Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);
	/// <summary>
	/// Vector2の減算
	/// </summary>
	/// <param name="v1"></param>
	/// <param name="v2"></param>
	/// <returns></returns>
	static Vector2 Subtract(const Vector2& v1, const Vector2& v2);
	/// <summary>
	/// Vector3の減算
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns></returns>
	static Vector3 Subtract(const Vector3& a, const Vector3& b);
	/// <summary>
	/// 行列の積
	/// </summary>
	/// <param name="m1"></param>
	/// <param name="m2"></param>
	/// <returns></returns>
	static Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
	/// <summary>
	/// Vector3の積
	/// </summary>
	/// <param name="scalar"></param>
	/// <param name="vector"></param>
	/// <returns></returns>
	static Vector3 Multiply(float scalar, const Vector3& vector);
	/// <summary>
	/// 逆行列
	/// </summary>
	/// <param name="m"></param>
	/// <returns></returns>
	static Matrix4x4 Inverse(const Matrix4x4& matrix);
	/// <summary>
	/// 転置行列
	/// </summary>
	/// <param name="m"></param>
	/// <returns></returns>
	static Matrix4x4 Transpose(const Matrix4x4& matrix);
	/// <summary>
	/// 単位行列の作成
	/// </summary>
	/// <returns></returns>
	static Matrix4x4 MakeIdentity4x4();

	/// <summary>
	/// 1.平行移動行列
	/// </summary>
	/// <param name="translate">トランスレート</param>
	/// <returns></returns>
	static Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
	/// <summary>
	/// 2.拡大縮小行列
	/// </summary>
	/// <param name="scale">大きさ</param>
	/// <returns></returns>
	static Matrix4x4 MakeScaleMatrix(const Vector3& scale);
	/// <summary>
	/// 3.座標変換
	/// </summary>
	/// <param name="vector">ベクトル</param>
	/// <param name="matrix">行列</param>
	/// <returns></returns>
	static Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

	/// <summary>
	/// 1.X軸回転行列
	/// </summary>
	/// <param name="radian"></param>
	/// <returns></returns>
	static Matrix4x4 MakeRotateXMatrix(float radian);
	/// <summary>
	/// 2.Y軸回転行列
	/// </summary>
	/// <param name="radian"></param>
	/// <returns></returns>
	static Matrix4x4 MakeRotateYMatrix(float radian);
	/// <summary>
	/// 3.Z軸回転行列
	/// </summary>
	/// <param name="radian"></param>
	/// <returns></returns>
	static Matrix4x4 MakeRotateZMatrix(float radian);
	/// <summary>
	/// 4.XYZ軸回転行列
	/// </summary>
	/// <param name="radian"></param>
	/// <returns></returns>
	static Matrix4x4 MakeRotateXYZMatrix(Vector3 radian);

	/// <summary>
	/// 1.3次元アフィン変換行列
	/// </summary>
	/// <param name="scale"></param>
	/// <param name="rotate"></param>
	/// <param name="translate"></param>
	/// <returns></returns>
	static Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

	/// <summary>
	/// cotangent(コタンジェント)
	/// </summary>
	/// <param name="theta"></param>
	/// <returns></returns>
	static float Cot(float theta);
	/// <summary>
	/// 1.透視投影行列
	/// </summary>
	/// <param name="fovY"></param>
	/// <param name="aspectRatio"></param>
	/// <param name="nearClip"></param>
	/// <param name="farclip"></param>
	/// <returns></returns>
	static Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farclip);
	/// <summary>
	/// 2.正射影行列
	/// </summary>
	/// <param name="left"></param>
	/// <param name="top"></param>
	/// <param name="right"></param>
	/// <param name="bottom"></param>
	/// <param name="nearClip"></param>
	/// <param name="farClip"></param>
	/// <returns></returns>
	static Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);
	/// <summary>
	/// 3.ビューポート変換行列
	/// </summary>
	/// <param name="left"></param>
	/// <param name="top"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="minDepth"></param>
	/// <param name="maxDepth"></param>
	/// <returns></returns>
	static Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);



	/// <summary>
	/// 1.クロス式
	/// </summary>
	/// <param name="v1"></param>
	/// <param name="v2"></param>
	/// <returns></returns>
	static Vector3 Cross(const Vector3& v1, const Vector3& v2);



	/// <summary>
	/// グリッド線の表示
	/// </summary>
	/// <param name="viewProjectionMatrix"></param>
	/// <param name="viewportMatrix"></param>
	static void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

	/// <summary>
	/// 球の表示
	/// </summary>
	/// <param name="sphere"></param>
	/// <param name="viewProjectionMatrix"></param>
	/// <param name="viewportMatrix"></param>
	/// <param name="color"></param>
	static void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

	static float Dot(const Vector3& v1, const Vector3& v2);

	static Vector3 Project(const Vector3& v1, const Vector3& v2);
	/// <summary>
	///  最近接点を求める
	/// </summary>
	/// <param name="point"></param>
	/// <param name="segment"></param>
	/// <returns></returns>
	static Vector3 ClosestPoint(const Vector3& point, const Segment& segment);

	/// <summary>
	/// 長さ
	/// </summary>
	/// <param name="vec"></param>
	/// <returns></returns>
	static float Length(const Vector3& vec);

	/// <summary>
	/// 球と球の衝突判定
	/// </summary>
	/// <param name="s1"></param>
	/// <param name="s2"></param>
	/// <returns></returns>
	static bool IsCollision(const Sphere& s1, const Sphere& s2);

	/// <summary>
	/// 球と平面の衝突判定
	/// </summary>
	/// <param name="s1"></param>
	/// <param name="s2"></param>
	/// <returns></returns>
	static bool IsCollision(const Sphere& sphere, const Plane& plane);
	
	/// <summary>
	/// 線と平面の衝突判定
	/// </summary>
	/// <param name="segment"></param>
	/// <param name="plane"></param>
	/// <returns></returns>
	static bool IsCollision(const Segment& segment, const Plane& plane);

	/// <summary>
	/// 垂直ベクトルの生成
	/// </summary>
	/// <param name="vector"></param>
	/// <returns></returns>
	static Vector3 Perpendicular(const Vector3& vector);

	static Vector3 Normalize(const Vector3& v);

	/// <summary>
	/// 平面の描画
	/// </summary>
	/// <param name="plane"></param>
	/// <param name="viewProjectionMatrix"></param>
	/// <param name="viewportMatrix"></param>
	/// <param name="color"></param>
	static void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

};

