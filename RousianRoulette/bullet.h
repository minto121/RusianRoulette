#pragma once
class bullet
{
private:
	int Bullet;     
	int Cylinder[6];   
	int FireC;     
	int RandBox;    
	
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
};

