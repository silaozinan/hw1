#include <iostream>
#include <string>
#include <vector>
#include "randgen.h"
#include "strutils.h"
using namespace std;
/*
CS204 Homework #1 – Minesweeper
SILA OZINAN- 28161

INTRODUCTION 
The aim of this code is design a basic minesweeper game. Firstly, user is asked to give the dimensions of the matrix( rows, columns), then the number of bombs are asked. 
After taking these values number of bombs are checked. Then the matrix with the given dimensions is printed to user in version that all cells are represented by X's. 
Then, game serves 3 options for user to chose repeatedly (a valid option should be entered otherwise game asks again and again):
1. If you want to find out the surrounding of a cell
2. If you want to open the cell
3. If you want to exit.
If user selects 1. option, game asks for coordinates (valid coordinates should be entered otherwise game asks again and again) to show the number of bombs surronding the given coordinates. This options shows the number of bombs temporarily and works even this cell has a bomb.
If user selects 2. option, game asks for coordinates (valid coordinates should be entered otherwise game asks again and again) to open that cell. 
There are two ways: if the selected cell is a bombed-cell, "B" (representing bomb)showed in that cell and game over, program shows the all bombs and cells, program ends.
If the selected cell is a not bombed-cell program shows the number of bombs around that cell. If all non-bombed cells are opened, player win the game and game congratulate the player and ends.
If user selects 3. option, game print the "Program exiting ..." and ends.
*/
string press() //function which shows the options for playing and ask user for one 
{
	string user_chose;
	cout<<endl;
	cout<<"Press: "<<endl;
	cout<<"1. If you want to find out the surrounding of a cell"<<endl;
	cout<<"2. If you want to open the cell"<<endl;
	cout<<"3. If you want to exit."<<endl;
	cin>> user_chose; //taking user choice as a string
	while (user_chose!="1" && user_chose!="2" && user_chose!="3")// checking if the user choice is valid and if it is not ask again until it is valid
	{
		cout<<"Your input is wrong. Please select one of the options: 1, 2 or 3."<<endl;
		cin>> user_chose;
	}
	return user_chose; //"press" function returns the user choice of playing to process
}
void printer(vector<vector<string>> minesweeper, int coor1, int coor2, int r1, int sur_bomb)
/* function that prints the matrix, shows the number of bombs around the given cell(since parameters are not reference parameters it will show only once and then go back to old value) 
parameters coor1 and coor2 are taken for determine the which cell will be processed- minesweeper vector is taken since it will give the playing area and will be used during printing-
sur_bomb is taken because it will show the number of bombs placed surronding
*/
{
	int size02 = minesweeper[0].size();
	for (int s = 0; s < r1; s++)//alter the given coordinates cell from initial value to value that gives the number of bombs around it.
	{
		if( s == coor1)
		{
			for (int y = 0; y < size02; y++)
			{
				if(y == coor2)
				{
					minesweeper[s][y] = itoa(sur_bomb);// the value of sur_bomb is int but this matrix stores string value so the transformation(int-> string should be used)
				} 
			}
		}
	}
	for (int a = 0; a < r1; a++)// printing the matrix which has the changed values(this change is not permanent)
	{
		for (int b = 0; b< size02; b++)
		{
			cout << minesweeper[a][b] << " " ;
		}
		cout<<endl;
	}
}
void validcoord(int r1, int c1, int &coor1, int &coor2)// a function that control whether the taken( taken from user) coordinates to open cell or count the number of bombs placed surronding of it are valid or not 
{
		while (r1<=coor1 || c1<=coor2 || coor1<0 || coor2<0)// check if the coordinates are valid( should be bigger than zero and smaller than the given rows and columns)
		{
			cout<<"It is out of range. Please give a valid coordinates: ";// if coordinates are not valid, a valid one is asked continually until getting valid coordinates
			cin>> coor1>> coor2;
		}// return nothing
}
int surrounding_control(int coor1, int coor2, int r1, int c1, vector<vector<int>> randomchecker )// a function to control and count the bombs which place at the surronding of the given cell (in order to reach given cell coor1 and coor2 are taken- to determine the rectangle that the playing area r1 and c1 are taken- to determine the places of bombs randomchecker matrix is taken)
{
	int count_of_bombedcell=0;// a counter for bomb number around the given cell
	if(coor1==(r1-1) && coor2==(c1-1)) //checking the surronding of right bottom cell one by one 
	{
		if(randomchecker[coor1-1][coor2-1]==1)
		{
			count_of_bombedcell++;// counter is increased one if the controlled cell has a bomb
		}
		if(randomchecker[coor1-1][coor2]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1][coor2-1]==1)
		{
			count_of_bombedcell++;
		}
	}
	else if(coor1>0 && coor1< r1-1 && coor2== c1-1) //checking the surronding of cells between right bottom and right top
	{
		if(randomchecker[coor1+1][coor2]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1-1][coor2]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1-1][coor2-1]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1][coor2-1]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1+1][coor2-1]==1)
		{
			count_of_bombedcell++;
		}
	}
	else if(coor1==0 && coor2==c1-1) //checking the surronding of right top cell
	{
		if(randomchecker[coor1][coor2-1]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1+1][coor2-1]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1+1][coor2]==1)
		{
			count_of_bombedcell++;
		}
	}
	else if(coor1==0 && coor2>0 && coor2<c1-1) //checking the surronding of cells between left top and right top
	{
		if(randomchecker[coor1][coor2-1]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1][coor2+1]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1+1][coor2-1]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1+1][coor2]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1+1][coor2+1]==1)
		{
			count_of_bombedcell++;
		}
	}
	else if(coor1==0 && coor2==0)//checking the surronding of left top cell
	{
		if(randomchecker[coor1+1][coor2+1]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1+1][coor2]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1][coor2+1]==1)
		{
			count_of_bombedcell++;
		}
	}
	else if(coor1>0 && coor1<r1-1 && coor2==0)//checking the surronding of cells between left top and left bottom
	{
		if(randomchecker[coor1+1][coor2]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1-1][coor2]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1][coor2+1]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1+1][coor2+1]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1-1][coor2+1]==1)
		{
			count_of_bombedcell++;
		}
	}
	else if(coor1==r1-1 && coor2==0)//checking the surronding of left bottom cell
	{
		if(randomchecker[coor1-1][coor2]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1-1][coor2+1]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1][coor2+1]==1)
		{
			count_of_bombedcell++;
		}
	}
	else if(coor1== r1-1 && coor2>0 && coor2<c1-1)//checking the surronding of cells between right bottom and left bottom
	{
		if(randomchecker[coor1][coor2+1]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1][coor2-1]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1-1][coor2-1]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1-1][coor2]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1-1][coor2+1]==1)
		{
			count_of_bombedcell++;
		}
	}
	else// checking the cells at the inside
	{
		if(randomchecker[coor1-1][coor2+1]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1-1][coor2]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1-1][coor2-1]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1+1][coor2-1]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1+1][coor2]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1+1][coor2+1]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1][coor2+1]==1)
		{
			count_of_bombedcell++;
		}
		if(randomchecker[coor1][coor2-1]==1)
		{
			count_of_bombedcell++;
		}
	}
	return count_of_bombedcell;// return the counter for the bomb number around the given cell to show at the next steps
}
void select1(int r1,int c1, vector<vector<int>> randomchecker, vector<vector<string>> minesweeper)// function that maintain the process when user choose the option 1 to play
{
	int coor1, coor2, sur_bomb;
	cout<<"Give the coordinates: ";// taking coordinates from user to play
	cin>> coor1>> coor2;
	validcoord(r1, c1, coor1, coor2);// checking if the values are valid
	cout<<endl;
	cout<< "Displaying the surrounding of ("<<coor1<<","<<coor2<<"): "<<endl;// showing the surronding of taken cell
	sur_bomb= surrounding_control( coor1,coor2, r1,c1,randomchecker );// reaching the number of bombs surronding the taken cell, with a function
	printer(minesweeper,coor1,coor2,r1,sur_bomb);// printing the gaming area with showing the cell's surronding bomb number just for taken cell(if some cell is opened(not checked opened with option 2) beforehand it will be showed too)
	cout<<"Around ("<<coor1<<","<<coor2<<") you have "<<sur_bomb<<" bomb(s)"<<endl;
}
int select2(int r1,int c1, vector<vector<int>> randomchecker, vector<vector<string>> & minesweeper)// function that maintain the process when user choose the option 2 to play
{
	int tester=35;// an int is set to a number to use at the next steps(as a checking value)
	int coor1, coor2;
	cout<<"Give the coordinates: ";// taking coordinates from user to play
	cin>> coor1>> coor2;
	validcoord(r1, c1, coor1, coor2);// checking if the values are valid
	cout<<endl;
	cout<<"Opening cell ("<<coor1<<","<<coor2<<"): "<<endl;// opening the given cell permanently
	int size1 = minesweeper[0].size();
	if (randomchecker[coor1][coor2]==1)// checking if the given cell is a bomb or not
	{
		minesweeper[coor1][coor2]="B";// if it is a bomb, its initial value will be changed to "B" string
		tester= 34;// and tester will changed to another number to show that a bomb is selected(this info will be used later)
		for (int z = 0; z < r1; z++)// printing the playing area with altered values
		{
			for (int x = 0; x < size1; x++)
			{
				cout<<minesweeper[z][x]<<" ";
			}
			cout<<endl;
		}
	}
	else// condition that selected cell is not a bomb, if it is not a bomb the number of bombs around it will be showed and stay open permanently
	{
		int neig;
		neig = surrounding_control(coor1,coor2, r1,c1, randomchecker);//not bomb cell will be show the number of bombs around it (and this value is stored in neig)
		minesweeper[coor1][coor2]= itoa(neig);// while printing the number of bombs around a cell which is int, int-> string transformation is needed because this matrix's type is string
		for (int z = 0; z < r1; z++)// // printing the playing area with altered values
		{
			for (int x = 0; x < size1; x++)
			{
				cout<<minesweeper[z][x]<<" ";
			}
			cout<<endl;
		}
	}
	return tester;// tester will be returned to show if the bomb is opened or not
}
int main()
{
	int r1,c1,bomb_num;
	cout<<"Give the dimensions of the matrix: "; //taking the dimension values from the user in order to use as numbers of rows and columns
	cin>>r1>>c1;
	cout<< "How many bombs: "; // taking the bomb number from the user
	cin>> bomb_num;
	while(bomb_num>(r1*c1-1)|| bomb_num<1) //checking whether the bomb number is in the given interval 
	{
		if(bomb_num>(r1*c1-1)) //bomb number cannot be equal or more than the number of cells
		{
			cout<<"The number of bombs can not be greater than the whole number of cells minus one. Please give the number of bombs again: ";
			cin>> bomb_num;
		}
		else if(bomb_num<1)// bomb number cannot be zero or negative
		{
			cout<<"The number of bombs could not be less than one. Please give the number of bombs again: ";
			cin>> bomb_num;
		}
	}
	cout<<endl;
	vector<vector<string>> minesweeper(r1, vector<string>(c1, "X"));// definening a matrix to store given rectangle (rows(r1)xcolumns(c1)) (every cell is represented as "X"(string))
	for (int k = 0; k < r1; k++)// a loop to print defined matrix to show user the playing area
	{
		for (int i = 0; i < c1; i++)
		{
			cout<< minesweeper[k][i];
			cout<< " ";	
		}
		cout<<endl;
	}
	RandGen rand;// random generator will be used to place bombs randomly
	int m=0;
	vector<vector<int>> randomchecker(r1, vector<int>(c1, 0));// a matrix to store the places of the bombs as 1 and the others as 0.
	while (m<bomb_num)
	{
		int randomr = rand.RandInt(0,r1-1);// randomly determines the rows of bombs
		int randomc= rand.RandInt(0,c1-1);// randomly determines the columns of bombs
		if(randomchecker[randomr][randomc]==0)// controlling the cell if there was a bomb beforehand (aim is the place all bombs into the different places)
		{	
			randomchecker[randomr][randomc]=1;
			m=m+1;
		}	
	}
	string chosen= press();// serving the options to the user, user choice is stored as chosen
	int tester=35;// test value for deciding if a bomb is opened or not
	int num_opened_cell=0;// number of cells which are opened during the playing process
	while ((chosen=="1" || chosen=="2") && tester==35 && num_opened_cell!=(r1*c1-bomb_num))// if option 1 or 2 are chosen, bombs are not opened(tester=35), user didn't open all the non-bombed cells code will continue to asking for options
	{
		if(chosen=="1")
		{
			select1(r1,c1, randomchecker,minesweeper);// if option 1 is selected this function will be processed
		}
		else if(chosen=="2")
		{
			tester= select2(r1,c1,randomchecker, minesweeper);// if option 2 is selected this function will be processed and return tester value to show if bomb is selected or not
			if (tester==35)
			{
				num_opened_cell++;// if bomb is not selected the number of opened cell will be increased by one
			}
		}
		if (tester==35 && num_opened_cell!=(r1*c1-bomb_num))
		{
			chosen= press();//bombs are not opened(tester=35), user didn't open all the non-bombed cells code will continue to asking for options
		}
	}
	if(chosen=="3")// if option 3 is selected this prompt will be printed and code will stop.
	{
		cout<<endl<<"Program exiting ..."<<endl;
	}
	else if (tester==34)// tester=34 means a bomb is opened so game over
	{
		cout <<endl<< "Unfortunately, you stepped on a mine" << endl;
        cout << "Arrangement of mines:" <<endl ;
		int size4 = randomchecker[0].size();
		for (int l = 0; l < r1; l++)// bomb is selected so all places should be released, the all opened version of gaming area will be printed
		{
			for (int m = 0; m < size4; m++)
			{
				if (randomchecker[l][m]==1)// bombs will be represented by "B" string
				{
					cout<<"B"<<" ";
				}
				else if(randomchecker[l][m]==0)
				{
					int counter=surrounding_control( l,  m,  r1,  c1,  randomchecker );
					cout<<itoa(counter)<<" "; // others will be represented by the number of bombs around them (number is int but matrix is in the type of string so transformation is needed)
				}
			}
			cout<<endl;
		}
        cout << endl << ">>>>> Game Over! <<<<<" << endl;
	}
	else if (num_opened_cell==(r1*c1-bomb_num))// this equation means all cells except bombs are opened so game over and user won
	{
		cout << "Congratulations! All the non-mined cells opened successfully" << endl;
        cout << "You won!" << endl;
        cout << endl << ">>>>> Game Over! <<<<<" << endl;		
	}
	return 0;
}