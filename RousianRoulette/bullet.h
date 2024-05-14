#pragma once
class bullet
{
private:
	  
	
public:
	bullet();

	~bullet();

	void Update();

	void Draw() const;

	void B_INIT();

	void N_Of_Bullet(); 

	void Reload();       

	void Shot();         

	void B_location();   

	int Bullet;
	static int Cylinder[6];
	static int FireC;
	int RandBox;
};

