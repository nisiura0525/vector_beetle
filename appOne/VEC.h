#pragma once
struct VEC {
	float x = 0;//C++�̋@�\�������ł���
	float y = 0;
};

float magnitude(struct VEC* v);//�傫���ivector�����߂�֐�
struct VEC normalize(struct VEC* v);//���K��vector�����߂�֐�
struct VEC vecFromAngle(float angle);//�p�x����vector�����߂�
float angleBetweenTowVecs(struct VEC* a, struct VEC* b);//�Ȃ��p