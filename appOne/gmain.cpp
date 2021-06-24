#include"libOne.h"
#include"VEC.h"

struct BEETLE {
	struct VEC pos;
	float advSpeed = 0;//�i�ރX�s�[�h�A�A�h�o���X�X�s�[�h
	float angle = 0;
	float angSpeed = 0;//��]�X�s�[�h�A�A���M�����[�X�s�[�h
};

void gmain() {
	window(1920, 1080, full);
	//�摜�ǂݍ���
	int osuImg = loadImage("assets\\osu.png");
	int mesuImg = loadImage("assets\\mesu.png");
	int backImg = loadImage("assets\\green.png");
	//���
	const int WALK = 0; 
	const int ROTATE = 1;
	int state = WALK;
	int rotateCnt = 0; 
	//�I�X�f�[�^
	struct BEETLE osu;
	osu.pos.x = width / 2+500;
	osu.pos.y = height / 2;
	osu.advSpeed = 10;
	//���X�f�[�^
	struct BEETLE mesu;
	mesu.pos.x = width / 2-500;
	mesu.pos.y = height / 2;
	mesu.advSpeed = 10;
	float advAngle = 0;
	//���C�����[�v
	while (notQuit) {
		struct VEC a;//���݌����Ă������
		struct VEC b;//���������x�N�g��
		if (state == WALK) {
			//�I�X�̈ړ���]
			if (isPress(KEY_D)) { b.x = 1; }
			if (isPress(KEY_A)) { b.x = -1; }
			if (isPress(KEY_S)) { b.y = 1; }
			if (isPress(KEY_W)) { b.y = -1; }
			if (b.x != 0 || b.y != 0) {
				//�I�X�ړ�
				b = normalize(&b);//���K��
				osu.pos.x += b.x * osu.advSpeed;//���K�������l���X�s�[�h�Ŋ|����
				osu.pos.y += b.y * osu.advSpeed;
				//�I�X�̒ʏ��]
				a = vecFromAngle(osu.angle);//���݂̊p�x����x�N�g�������߂�
				osu.angSpeed = angleBetweenTowVecs(&a, &b) /4;
				osu.angle += osu.angSpeed;
				//���݂Ɠ��������̃x�N�g���łȂ��p�����ߕ����������Ă����i���炩�ɂ��邽�߁j
			}

			//���X���������ƃx�N�g��
			b.x = sin(advAngle);
			b.y = -cos(advAngle)*0.3f;
			advAngle += 0.02f;
			//���X�ړ�
			mesu.pos.x += b.x * mesu.advSpeed;
			mesu.pos.y += b.y * mesu.advSpeed;
			//���X�̒ʏ��]
			a = vecFromAngle(mesu.angle);
			mesu.angSpeed = angleBetweenTowVecs(&a, &b) / 4;
			mesu.angle += mesu.angSpeed;

			if (isTrigger(KEY_SPACE)) {
				//�I�X��]
				b.x = mesu.pos.x - osu.pos.x;
				b.y = mesu.pos.y - osu.pos.y;
				if (magnitude(&b) < 300) {//��]�g�p�͈�
					a = vecFromAngle(osu.angle);
					osu.angSpeed = angleBetweenTowVecs(&a, &b) / 30;
					//���X��]
					b.x = -b.x;
					b.y = -b.y;
					a = vecFromAngle(mesu.angle);
					mesu.angSpeed = angleBetweenTowVecs(&a, &b) / 30;
					state = ROTATE;
				}
			}
		}
		else if (state == ROTATE){
			if (rotateCnt <= 30) {
				osu.angle += osu.angSpeed;
				mesu.angle += mesu.angSpeed;
				rotateCnt++;
			}
			else {
				if (isTrigger(KEY_W) ||
					isTrigger(KEY_A) ||
					isTrigger(KEY_S) ||
					isTrigger(KEY_D)) {
					rotateCnt = 0;
					state = WALK;
				}
			}
		}
		clear();
		rectMode(CORNER);
		image(backImg, 0, 0);
		rectMode(CENTER);
		fill(255, 255, 255, 125);
		circle(mesu.pos.x, mesu.pos.y, 600);
		image(mesuImg, mesu.pos.x, mesu.pos.y, mesu.angle);
		image(osuImg, osu.pos.x, osu.pos.y,osu.angle);
	}
}