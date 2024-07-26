#include <Novice.h>
#include "Matrix.h"

const char kWindowTitle[] = "GC2B_02_イトウ_シュンヤ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Matrix matrix;

	Vector3 cameraRotate{ 0.26f,0.0f,0.0f };
	Vector3 cameraPosition = {0.0f,0.f,-6.0f};

	Matrix4x4 cameraMatrix = Matrix::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.26f,0.0f,0.0f }, cameraPosition);
	Matrix4x4 viewMatrix = Matrix::Inverse(cameraMatrix);
	Matrix4x4 projectionMatrix = Matrix::MakePerspectiveFovMatrix(0.45f, float(1280) / float(720), 0.1f, 100.0f);
	Matrix4x4 viewportMatrix = Matrix::MakeViewportMatrix(0, 0, float(1280), float(720), 0.0f, 1.0f);
	Matrix4x4 viewProjectionMatrix = Matrix::Multiply(viewMatrix, projectionMatrix);

	//正射影ベクトルと最近接点
	Matrix::Segment segment{ {0.0f, 0.28f, 0.36f}, {3.0f, -1.0f, 0.0f} };
	Vector3 point{ -1.5f,0.6f,0.6f, };

	Vector3 project = Matrix::Project(Matrix::Subtract(point, segment.origin), segment.diff);
	Vector3 ClosestPoint = Matrix::ClosestPoint(point, segment);

	//線分の描画
	Vector3 start = Matrix::Transform(Matrix::Transform(segment.origin, viewProjectionMatrix), viewportMatrix);
	Vector3 end = Matrix::Transform(Matrix::Transform(Matrix::Add(segment.origin, segment.diff), viewProjectionMatrix), viewportMatrix);

	uint32_t segmentColor = 0xFFFFFFFF;

	Matrix::Triangle triangle = { {{0.0f,0.0f,-1.0f},{0.0f,1.0f,0.0f},{0.0f,0.0f,1.0f}} };
	uint32_t triangleColor = 0xFFFFFFFF;


	bool iscollision = Matrix::IsCollision(segment, triangle);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		cameraMatrix = Matrix::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraPosition);
		viewMatrix = Matrix::Inverse(cameraMatrix);
		projectionMatrix = Matrix::MakePerspectiveFovMatrix(0.45f, float(1280) / float(720), 0.1f, 100.0f);
		viewportMatrix = Matrix::MakeViewportMatrix(0, 0, float(1280), float(720), 0.0f, 1.0f);
		viewProjectionMatrix = Matrix::Multiply(viewMatrix, projectionMatrix);

		project = Matrix::Project(Matrix::Subtract(point, segment.origin), segment.diff);
		ClosestPoint = Matrix::ClosestPoint(point, segment);

		start = Matrix::Transform(Matrix::Transform(segment.origin, viewProjectionMatrix), viewportMatrix);
		end = Matrix::Transform(Matrix::Transform(Matrix::Add(segment.origin, segment.diff), viewProjectionMatrix), viewportMatrix);

		iscollision = Matrix::IsCollision(segment, triangle);
		if (iscollision == true) {
			segmentColor = RED;
		}
		else { segmentColor = WHITE; }

		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraPosition.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);

		ImGui::DragFloat3("Segment origin", &segment.origin.x, 0.01f);
		ImGui::DragFloat3("Segment diff", &segment.diff.x, 0.01f);

		ImGui::DragFloat3("Triangle.v0", &triangle.vertices[0].x, 0.01f);
		ImGui::DragFloat3("Triangle.v1", &triangle.vertices[1].x, 0.01f);
		ImGui::DragFloat3("Triangle.v2", &triangle.vertices[2].x, 0.01f);

		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		matrix.DrawGrid(viewProjectionMatrix, viewportMatrix);
		matrix.DrawTriangle(triangle, viewProjectionMatrix, viewportMatrix, triangleColor);
		Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), segmentColor);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
