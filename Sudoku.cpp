#include<iostream>
#include<vector>
#include<cstdlib>
#include"Sudoku.h"
using namespace std;
Sudoku::Sudoku(){
	map[81];
	mapsave[81];
	save[81];
	save1[81];
	savesite=0;
	savesite1=0;
}
void Sudoku::giveQuestion(){
	int map[81]=
	{1,8,0,0,0,9,0,0,0,
	 0,0,0,0,5,0,0,0,4,
	 0,0,0,2,0,1,0,6,0,
	 4,2,0,0,0,5,0,0,0,
	 7,0,0,0,0,0,0,0,1,
	 0,0,0,9,0,0,0,3,8,
	 0,4,0,3,0,8,0,0,0,
	 3,0,0,0,7,0,0,0,0,
	 0,0,0,4,0,0,0,2,3
	};
	for(i=0;i<81;i++){
		cout << map[i] << ' ';
		if((i+1)%9==0){
			cout << endl;
		}
	}
}
void Sudoku::readIn(){
	for(i=0;i<81;i++){
		cin >> map[i];
	}
}
void Sudoku::changeNum(int a,int b){
	for(i=0;i<81;i++){
		if(map[i]==a){
			map[i]=b;
		}
		else if(map[i]==b){
			map[i]=a;
		}
	}
}
void Sudoku::changeRow(int a,int b){
	for(i=(a*27);i<((a+1)*27);i++){
		temp[i+27*(b-a)]=map[i];
		map[i]=map[i+27*(b-a)];
	}
	for(i=(b*27);i<((b+1)*27);i++){
		map[i]=temp[i];
	}
}
void Sudoku::changeCol(int a,int b){
	for(i=0;i<73;i+=9){
		for(j=(a*3);j<(3*(a+1));j++){
			temp[j+i+3*(b-a)]=map[j+i]; 
			map[i+j]=map[j+i+3*(b-a)];
		}
	}
	for(i=0;i<73;i+=9){
		for(j=(b*3);j<(3*(b+1));j++){
			map[i+j]=temp[i+j];
		}	
	} 
}
void Sudoku::flip(int n){
	if(n==0){
		for(i=0;i<73;i+=9){
			for(j=0;j<9;j++){
				temp[72-i+j]=map[i+j];
				map[i+j]=map[72-i+j];
			}
		}
		for(i=45;i<81;i++){
			map[i]=temp[i];
		}
	}
	else if(n==1){
		for(i=0;i<9;i++){
			for(j=0;j<73;j+=9){
				temp[8-i+j]=map[i+j];
				map[i+j]=map[8-i+j];
			}
		}
		for(i=5;i<81;i+=9){
			for(j=0;j<4;j++){
				map[i+j]=temp[i+j];
			}
		}
	}
}
void Sudoku::rotate(int n){
	int p=0;
	while(p<n){
		for(i=0;i<73;i+=9){
			for(j=0;j<9;j++){
				temp[i+j+8+(8*j)-10*(i/9)]=map[i+j];
				map[i+j]=map[i+j+8-10*(i/9)+(8*j)];
			}
		}
		for(i=0;i<81;i++){
			map[i]=temp[i];
		}
		p+=1;
	}
}
void Sudoku::transform(){
	 srand(time(NULL));
	 changeNum(rand()%10,rand()%10);
	 changeRow(rand()%3,rand()%3);
	 changeCol(rand()%3,rand()%3);
	 rotate(rand()%101);
	 flip(rand()%2);
 	 for(i=0;i<81;i++){
		cout << map[i] << ' ';
		if((i+1)%9==0){
			cout << endl;
		}
	}
}
bool Sudoku::isCorrect(){	//確認是否行,列,九宮格都沒有重複的數字
	for(int site=0;site<81;site++){
		if( map[site]!=0){
			if(checkrow(site)!=0) return false;
			if(checkcol(site)!=0) return false;
			if(checksqu(site)!=0) return false;
		}
	}
	return true;
}
int Sudoku::getBlank(int site){	//找空格
	do{
		site++;
	}while(site<81 && map[site]!=0 );	//當找到0,則回傳該位置
	save[++savesite]=site;
	return(site);
}
int Sudoku::getBlank1(int site){
	do{
		site++;
	}while(site<81 && map[site]!=0 );
	map[site]=10;
	save1[++savesite1]=site;
	return(site);
}
int Sudoku::checkset(int site){	//測試有沒有重複
	int p=0;
	p=checkrow(site);
	if(p!=0) return p;
	p=checkcol(site);
	if(p!=0) return p;
	p=checksqu(site);
	return p;
}
int Sudoku::checkrow(int site){
	int p=0,site1;
	for(int i=0;i<9;i++){
		site1=(site/9)*9+i;
		if(site!=site1 && map[site]==map[site1])
			p++;
	}
	return p;
}
int Sudoku::checkcol(int site){	//對同一行做測試
	int p=0,site1;
	for(int i=0;i<9;i++){
		site1=site%9+i*9;
		if(site!=site1 && map[site]==map[site1])
			p++;
	}
	return p;
}
int Sudoku::checksqu(int site){	//對九宮格做測試
	int p=0,site1;
	for(int i=0;i<9;i++){
		site1=((site/9)/3)*27+((site%9)/3)*3+(i/3)*9+i%3;
		if(site!=site1 && map[site]==map[site1])
			p++;
	}
	return p;
}
void Sudoku::solve(){
	for(int i=0;i<81;i++){
		mapsave[i]=map[i];}
	for(int i=0;i<81;i++){
		if(map[i]!=0&&checkset(i)!= 0) 								            
		{
			cout<<"0"<<endl;						
			return ;   
		}
	}
	vector<int>map1(81);    
	vector<int>map2(81);
	int site=getBlank(-1); 
	do{
		map[site]++;    
		if(map[site]>9){    
			map[site]=0;    
			site=save[--savesite];} 
		else{ 
			if(checkset(site)==0){ 
				site=getBlank(site);}} 
	}while(site>=0 && site<81);
	for(int i=0;i<81;i++){
		if(map[i]==0){
			cout<<"0"<<endl;
			return ;}
	} 
	for(int i=0;i<81;i++){  
		map1.at(i)=map[i];}
	for(int i=0;i<81;i++){  
		map[i]=mapsave[i];}
	site=getBlank1(-1); 
	do{
		map[site]--;
		if(map[site]<1){
			map[site]=0;
			site=save1[--savesite1];}
		else 
		{
			if(checkset(site)==0){   
				site=getBlank1(site);}}
	}while(site>=0 && site<81);
	for(int j=0;j<81;j++){  
		map2.at(j)=map[j];}
	if(map1!=map2){
		cout<<'2'<<endl;}
	else {
		cout<<'1'<<endl;  
		for(int j=0;j<81;j++){    
			cout<<map[j]<<" ";
			if((j+1)%9==0)
				cout<<endl;
		}
	}
}

