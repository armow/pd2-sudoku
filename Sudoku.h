#include<iostream>
class Sudoku{
	public:
		void giveQuestion();
		void readIn();
		void changeNum(int a,int b);
		void changeRow(int a,int b);
		void changeCol(int a,int b);
		void rotate(int n);
		void flip(int n);
		void transform();
		void solve();
		Sudoku();
		bool isCorrect();
		int init();
		int getBlank(int site);
		int getBlank1(int site);
		int checkset(int site);
		int checkrow(int site);
		int checkcol(int site);
		int checksqu(int site);
	private:
		int map[81];
		int temp[81];
		int mapsave[81];
	    int i,j;
		int save[81];
		int save1[81];
		int savesite;
		int savesite1;
};
