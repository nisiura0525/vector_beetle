#pragma once
struct VEC {
	float x = 0;//C++の機能初期化できる
	float y = 0;
};

float magnitude(struct VEC* v);//大きさ（vectorを求める関数
struct VEC normalize(struct VEC* v);//正規化vectorを求める関数
struct VEC vecFromAngle(float angle);//角度からvectorを求める
float angleBetweenTowVecs(struct VEC* a, struct VEC* b);//なす角