#include"libOne.h"
#include"VEC.h"

struct BEETLE {
	struct VEC pos;
	float advSpeed = 0;//進むスピード、アドバンススピード
	float angle = 0;
	float angSpeed = 0;//回転スピード、アンギュラースピード
};

void gmain() {
	window(1920, 1080, full);
	//画像読み込み
	int osuImg = loadImage("assets\\osu.png");
	int mesuImg = loadImage("assets\\mesu.png");
	int backImg = loadImage("assets\\green.png");
	//状態
	const int WALK = 0; 
	const int ROTATE = 1;
	int state = WALK;
	int rotateCnt = 0; 
	//オスデータ
	struct BEETLE osu;
	osu.pos.x = width / 2+500;
	osu.pos.y = height / 2;
	osu.advSpeed = 10;
	//メスデータ
	struct BEETLE mesu;
	mesu.pos.x = width / 2-500;
	mesu.pos.y = height / 2;
	mesu.advSpeed = 10;
	float advAngle = 0;
	//メインループ
	while (notQuit) {
		struct VEC a;//現在向いている方向
		struct VEC b;//向く方向ベクトル
		if (state == WALK) {
			//オスの移動回転
			if (isPress(KEY_D)) { b.x = 1; }
			if (isPress(KEY_A)) { b.x = -1; }
			if (isPress(KEY_S)) { b.y = 1; }
			if (isPress(KEY_W)) { b.y = -1; }
			if (b.x != 0 || b.y != 0) {
				//オス移動
				b = normalize(&b);//正規化
				osu.pos.x += b.x * osu.advSpeed;//正規化した値をスピードで掛ける
				osu.pos.y += b.y * osu.advSpeed;
				//オスの通常回転
				a = vecFromAngle(osu.angle);//現在の角度からベクトルを求める
				osu.angSpeed = angleBetweenTowVecs(&a, &b) /4;
				osu.angle += osu.angSpeed;
				//現在と動く方向のベクトルでなす角を求め分割し足していく（滑らかにするため）
			}

			//メス動く方向とベクトル
			b.x = sin(advAngle);
			b.y = -cos(advAngle)*0.3f;
			advAngle += 0.02f;
			//メス移動
			mesu.pos.x += b.x * mesu.advSpeed;
			mesu.pos.y += b.y * mesu.advSpeed;
			//メスの通常回転
			a = vecFromAngle(mesu.angle);
			mesu.angSpeed = angleBetweenTowVecs(&a, &b) / 4;
			mesu.angle += mesu.angSpeed;

			if (isTrigger(KEY_SPACE)) {
				//オス回転
				b.x = mesu.pos.x - osu.pos.x;
				b.y = mesu.pos.y - osu.pos.y;
				if (magnitude(&b) < 300) {//回転使用範囲
					a = vecFromAngle(osu.angle);
					osu.angSpeed = angleBetweenTowVecs(&a, &b) / 30;
					//メス回転
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