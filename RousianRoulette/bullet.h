#pragma once
class bullet
{
private:
	int RandBox;
	
	int Bullet_img;
	int Shot_Ui_Img;
	int BulletCur_Img;

public:
	bullet();

	~bullet();

	void Update();

	void Draw() const;

	void B_INIT();

	void N_Of_Bullet(); 

	void Reload();       

/*	void Shot();      */   

	void B_location();   

	
	static int Cylinder[6];
	static int FireC;
	static int Bullet;
	static int Last_Bullet;
};

