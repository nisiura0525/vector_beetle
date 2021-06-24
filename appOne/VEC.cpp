#include"libOne.h"
#include"VEC.h"
float magnitude(struct VEC* v) {
	return sqrt(v->x * v->x + v->y * v->y);
}//�傫���ivector�����߂�֐�
struct VEC normalize(struct VEC* v) {//�F�X�Ȃ��A���A�h���X���󂯎��
	float mag = magnitude(v);//��ɓn��
	struct VEC tmp;//�ꎞ�I�Ɏg��vector���̊֐��̒������Ŏg���J�[�h
	if (mag > 0) {
		tmp.x = v->x / mag;
		tmp.y = v->y / mag;
	}
	return tmp;
}//���K��vector�����߂�֐�
struct VEC vecFromAngle(float angle) {
	struct VEC tmp;
	tmp.x = sin(angle);
	tmp.y = -cos(angle);
	return tmp;
}//�p�x����x�N�g�������߂�
float angleBetweenTowVecs(struct VEC* a, struct VEC* b) {
	float dot = a->x * b->x + a->y * b->y;
	float cross = a->x * b->y - a->y * b->x;
	return atan2(cross,dot);
}