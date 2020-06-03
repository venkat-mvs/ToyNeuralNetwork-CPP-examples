#include<iostream>
#include<iomanip>
#include"lib/matrix.hpp"

using namespace std;


long double zeros(long double val){
	return 0;
}
long double asknreturn(long double _){
	long double value;
	cin>>value;
	return value;
}



int main(){
	unsigned int n,m;
	cout<<"n,m: ";
	cin>>n>>m;

	Matrix mat1(n,m);
	Matrix mat2(n,m);

	mat1.fill(1.001L);
	mat1.print();

	mat2.fill(1.001L);
	mat2.print();
	try{
		Matrix res1;
		res1 = mat1 * mat2;
		cout<<"res1";
		res1.print();

		Matrix res2;
		res2 = mat1 + mat2;
		cout<<"res2";
		res2.print();

		Matrix res3;
		res3 = mat1 - mat2;
		cout<<"res3";
		res3.print();

		Matrix res4;
		mat1.fill(255.021762376838783748734287342783427681L);
		res4 = mat1/255.01;
		cout<<"res4:";
		res4.print(20);

		Matrix res5;
		mat2.assign(0,1,10.0101);
		res5 = Matrix::transpose(mat2);
		cout<<"res5:";
		res5.print(); 


	}catch(MatrixException e){
		cout<<e.getError();
	}
}