#include"libOne.h"
#include"VEC.h"
float magnitude(struct VEC* v) {
	return sqrt(v->x * v->x + v->y * v->y);
}//大きさ（vectorを求める関数
struct VEC normalize(struct VEC* v) {//色々なｘ、ｙアドレスを受け取る
	float mag = magnitude(v);//上に渡す
	struct VEC tmp;//一時的に使うvectorこの関数の中だけで使うカード
	if (mag > 0) {
		tmp.x = v->x / mag;
		tmp.y = v->y / mag;
	}
	return tmp;
}//正規化vectorを求める関数
struct VEC vecFromAngle(float angle) {
	struct VEC tmp;
	tmp.x = sin(angle);
	tmp.y = -cos(angle);
	return tmp;
}//角度からベクトルを求める
float angleBetweenTowVecs(struct VEC* a, struct VEC* b) {
	float dot = a->x * b->x + a->y * b->y;
	float cross = a->x * b->y - a->y * b->x;
	return atan2(cross,dot);
}