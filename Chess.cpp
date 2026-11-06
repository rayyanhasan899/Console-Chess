#include "ConsoleInput.h"
#include<iostream>
#include<iomanip>
#include<conio.h>
#include<windows.h>
#include<cstdlib>
#include<ctime>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

void intialize_Pieces();
void deal_Pieces(int pieces1[],int pieces2[]);
bool isValid_Play(int choice1,int choice_Number1,int choice2,int choice_Number2,int current_Player,int board[][8]);
void Playturn(int pieces1[],int pieces2[],int board[][8]);
void print_Board(int pieces1[],int pieces2[],int board[][8]);
int check_White_King(int board[][8]);
int check_Empty(int board[][8]);
int check_Black_King(int board[][8]);
bool callCheck(int current_Player,int board[][8],int choice2,int choice_Number2);
int available_Moves(int board[][8],int current_Player);
void clearScreen();
// Color codes
const int BLACK   = 0;
const int BLUE    = 1;
const int GREEN   = 2;
const int CYAN    = 3;
const int RED     = 4;
const int MAGENTA = 5;
const int YELLOW  = 6;
const int WHITE   = 7;
// Function to set console text and background color
void setColor(int textColor, int bgColor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}
int main()
{
	intialize_Pieces();
    return 0;
}
void intialize_Pieces()
{
	int pieces1[16],pieces2[16];
	for(int i=0;i<16;i++)
	{
		if(i<8)
		{
			pieces1[i]=10+1;
			pieces2[i]=20+1;
		}
		else
		{
			pieces1[i]=10+(i-6);
			pieces2[i]=20+(i-6);
		}
	}
	deal_Pieces(pieces1,pieces2);
}
void deal_Pieces(int pieces1[],int pieces2[])
{
	int board[8][8];
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(i==0)
			{
				board[i][j]=pieces1[8+j];
			}
			else if(i==1)
			{
				board[i][j]=pieces1[j];
			}
			else if(i==6)
			{
				board[i][j]=pieces2[j];
			}
			else if(i==7)
			{
				board[i][j]=pieces2[8+j];
			}
			else
			{
				board[i][j]=0;
			}
		}
	}
	Playturn(pieces1,pieces2, board);
}
void Playturn(int pieces1[],int pieces2[],int board[][8])
{
	int current_Player=1;
	int moving1=0,moving2=0;
	while(true)
	{
		int choice_Number1,choice_Number2;
		int choice1,choice2; 
		print_Board(pieces1,pieces2,board);
		cout<<endl<<current_Player;
		cout<<endl<<"Available moves: "<<available_Moves(board,current_Player)<<endl;
		if(available_Moves(board,current_Player)<=1&&callCheck(current_Player,board,check_Empty(board)%10,check_Empty(board)/10))
		{
			current_Player=(current_Player==1)?2:1;
			cout<<"\nPlayer "<<current_Player<<" WINS\nCHECKMATE";
			break;
		}
		else if(available_Moves(board,current_Player)<=1)
		{
			cout<<"\nNO Player WINS\nSTALEMATE";
			break;
		}
		while(true)
		{
			if(callCheck(current_Player,board,check_Empty(board)%10,check_Empty(board)/10))
			{
				cout<<"\nPlayer ";
				cout<<current_Player;
				cout<<" is Checked";
			}
            if (!readSquare(cin, cout, "\nWHICH BOX DO YOU WANT TO MOVE FROM: ", 8, choice1, choice_Number1) ||
                !readSquare(cin, cout, "\nWHICH BOX DO YOU WANT TO MOVE TO: ", 8, choice2, choice_Number2)) return;
			clearScreen();
			int type=board[choice_Number1][choice1]%10;
			int color=board[choice_Number1][choice1]/10;
			if(isValid_Play(choice1,choice_Number1,choice2,choice_Number2,current_Player,board)&&color==current_Player)
			{
				int temp=board[choice_Number2][choice2];
				board[choice_Number2][choice2]= board[choice_Number1][choice1];
				board[choice_Number1][choice1]=0;
				if(callCheck(current_Player,board, choice2, choice_Number2))
				{
					board[choice_Number1][choice1]=board[choice_Number2][choice2];
					board[choice_Number2][choice2]=temp;
				}
				else
				{
					if(board[choice_Number2][choice2]==25||board[choice_Number2][choice2]==29||board[choice_Number2][choice2]==22)moving2++;
					else if(board[choice_Number2][choice2]==15||board[choice_Number2][choice2]==19||board[choice_Number2][choice2]==12)moving1++;
					break;
				}
			}
			else if(type==5)
			{
				if(((choice1 <= 4&&choice2==choice1+2&&board[choice_Number1][choice1+1]==0&&board[choice_Number1][choice1+2]==0&&board[choice_Number1][choice1+3]==0)
				||(choice1 >= 2&&choice2==choice1-2&&board[choice_Number1][choice1-1]==0&&board[choice_Number1][choice1-2]==0))
				&&choice_Number1==choice_Number2&&color==current_Player&&((current_Player==1&&moving1==0)||(current_Player==2&&moving2==0)))
				{
					board[choice_Number2][choice2]=board[choice_Number1][choice1];
					board[choice_Number1][choice1]=0;
					if(choice2>choice1)
					{
						board[choice_Number2][choice2-1]=board[choice_Number1][7];
						board[choice_Number1][7]=0;
					}
					else
					{
						board[choice_Number2][choice2+1]=board[choice_Number1][0];
						board[choice_Number1][0]=0;
					}
					if(callCheck(current_Player,board, choice2, choice_Number2))
					{
						board[choice_Number1][3]=board[choice_Number2][choice2];
						board[choice_Number2][choice2]=0;
						if(choice2>choice1)
						{
							board[choice_Number1][7]=board[choice_Number2][choice2-1];
							board[choice_Number2][choice2-1]=0;
						}
						else
						{
							board[choice_Number1][0]=board[choice_Number2][choice2+1];
							board[choice_Number2][choice2+1]=0;
						}
					}
					else
					{
						break;
					}
				}
			}
			print_Board(pieces1,pieces2,board);
			cout<<"\nWRONG MOVE ENTER AGAIN ";
		}
		if((choice_Number2==7&&board[choice_Number2][choice2]==11)||(choice_Number2==0&&board[choice_Number2][choice2]==21))
		{
			int transformation;
			while(true)
			{
				cout<<"\n1.Queen\n2.Rook\n3.Knight\nWhat do you Want to become: ";
				cin>>transformation;
				if(transformation==1)
				{
					board[choice_Number2][choice2]=(current_Player==1)?16:26;
					break;
				}
				else if(transformation==2)
				{
					board[choice_Number2][choice2]=(current_Player==1)?12:22;
					break;
				}
				else if(transformation==3)
				{
					board[choice_Number2][choice2]=(current_Player==1)?13:23;
					break;
				}
				else
				{
					cout<<"\n INVALID Enter again";
				}
			}
		}
		current_Player=(current_Player==1)?2:1;
		cout<<endl<<current_Player<<endl;
	}
	
}
bool isValid_Play(int choice1,int choice_Number1,int choice2,int choice_Number2,int current_Player,int board[][8])
{
    if (choice1 < 0 || choice1 >= 8 || choice2 < 0 || choice2 >= 8 ||
        choice_Number1 < 0 || choice_Number1 >= 8 || choice_Number2 < 0 || choice_Number2 >= 8) return false;

	int color=board[choice_Number1][choice1]/10;
	int enemy_Color=board[choice_Number2][choice2]/10;
	int piece_Type=board[choice_Number1][choice1]%10;
	bool isValid = false;
	if(piece_Type!=0)
	{
		if(piece_Type==1)
		{
			if(current_Player==1)
			{
				if((choice2==choice1 && choice_Number2==choice_Number1+1 && board[choice_Number2][choice2]==0)
				||((choice2==choice1+1||choice2==choice1-1)&&choice_Number2==choice_Number1+1&&enemy_Color!=color&&enemy_Color!=0)
				||((choice2==choice1 && choice_Number2==choice_Number1+2 && board[choice_Number2][choice2]==0&& choice_Number1==1 )))
				{
					isValid=true;
				}
			}
			else if(current_Player==2)
			{
				if((choice2==choice1 && choice_Number2==choice_Number1-1 && board[choice_Number2][choice2]==0)
				||((choice2==choice1+1||choice2==choice1-1 )&&choice_Number2==choice_Number1-1&&enemy_Color!=color&&enemy_Color!=0)
				||((choice2==choice1 && choice_Number2==choice_Number1-2 && board[choice_Number2][choice2]==0&& choice_Number1==6 )))
				{
					isValid=true;
				}
			}
		}
		else if(piece_Type==2||piece_Type==9)
		{
			bool inBetween=false,inMiddle=false;
			if(choice_Number2>choice_Number1||choice2>choice1)
			{
				
				for(int i=choice_Number1+1;i<choice_Number2;i++)
				{
					if(board[i][choice1]!=0)
					{
						inBetween=true;
						break;
					}
				}
				for(int i=choice1+1;i<choice2;i++)
				{
					if(board[choice_Number1][i]!=0)
					{
						inMiddle=true;
						break;
					}
				}
			}
			else
			{
				for(int i=choice_Number1-1;i>choice_Number2;i--)
				{
					if(board[i][choice1]!=0)
					{
						inBetween=true;
						break;
					}
				}
				for(int i=choice1-1;i>choice2;i--)
				{
					if(board[choice_Number1][i]!=0)
					{
						inMiddle=true;
						break;
					}
				}
			}
			if((choice2==choice1&&choice_Number2!=choice_Number1&&!inBetween&&enemy_Color!=color)
			||(choice2!=choice1&&choice_Number2==choice_Number1&&!inMiddle&&enemy_Color!=color))
			{
				isValid=true;
			}
		}
		else if(piece_Type==3||piece_Type==8)
		{
			if(((choice2==choice1+1&&choice_Number2==choice_Number1+2)
			  ||(choice2==choice1-1&&choice_Number2==choice_Number1+2)
			  ||(choice2==choice1+1&&choice_Number2==choice_Number1-2)
			  ||(choice2==choice1-1&&choice_Number2==choice_Number1-2)
			  ||(choice2==choice1+2&&choice_Number2==choice_Number1+1)
			  ||(choice2==choice1-2&&choice_Number2==choice_Number1+1)
			  ||(choice2==choice1+2&&choice_Number2==choice_Number1-1)
			  ||(choice2==choice1-2&&choice_Number2==choice_Number1-1))&&enemy_Color!=color)
			  {
				isValid=true;
			  }
		}
		else if(piece_Type==4||piece_Type==7)
		{
			bool inSide = false;
			int difference=choice_Number2-choice_Number1;
			int diff=choice2-choice1;
			(choice2-choice1<0)?diff*=-1:diff*=1;
			(choice_Number2-choice_Number1<0)?difference*=-1:difference*=1;
			if(choice2>choice1&&choice_Number2>choice_Number1)
			{
				for(int i=1;i<diff;i++)
				{
					if(board[choice_Number1+i][choice1+i]!=0)
					{
						inSide=true;
						break;
					}
				}
			}
			else if(choice2>choice1&&choice_Number2<choice_Number1)
			{
				for(int i=1;i<diff;i++)
				{
					if(board[choice_Number1-i][choice1+i]!=0)
					{
						inSide=true;
						break;
					}
				}
			}
			else if(choice2<choice1&&choice_Number2>choice_Number1)
			{
				for(int i=1;i<diff;i++)
				{
					if(board[choice_Number1+i][choice1-i]!=0)
					{
						inSide=true;
						break;
					}
				}
			}
			else if(choice2<choice1&&choice_Number2<choice_Number1)
			{
				for(int i=1;i<diff;i++)
				{
					if(board[choice_Number1-i][choice1-i]!=0)
					{
						inSide=true;
						break;
					}
				}
			}
			if(diff==difference&&!inSide&&enemy_Color!=color)
			{
				isValid=true;				
			}
		}
		else if(piece_Type==6)
		{
			bool inSide = false;
			int difference=choice_Number2-choice_Number1;
			int diff=choice2-choice1;
			(choice2-choice1<0)?diff*=-1:diff*=1;
			(choice_Number2-choice_Number1<0)?difference*=-1:difference*=1;
			if(choice2>choice1&&choice_Number2>choice_Number1)
			{
				for(int i=1;i<diff;i++)
				{
					if(board[choice_Number1+i][choice1+i]!=0)
					{
						inSide=true;
						break;
					}
				}
			}
			else if(choice2>choice1&&choice_Number2<choice_Number1)
			{
				for(int i=1;i<diff;i++)
				{
					if(board[choice_Number1-i][choice1+i]!=0)
					{
						inSide=true;
						break;
					}
				}
			}
			else if(choice2<choice1&&choice_Number2>choice_Number1)
			{
				for(int i=1;i<diff;i++)
				{
					if(board[choice_Number1+i][choice1-i]!=0)
					{
						inSide=true;
						break;
					}
				}
			}
			else if(choice2<choice1&&choice_Number2<choice_Number1)
			{
				for(int i=1;i<diff;i++)
				{
					if(board[choice_Number1-i][choice1-i]!=0)
					{
						inSide=true;
						break;
					}
				}
			}
			bool inBetween=false,inMiddle=false;
			if(choice_Number2>choice_Number1||choice2>choice1)
			{
				
				for(int i=choice_Number1+1;i<choice_Number2;i++)
				{
					if(board[i][choice1]!=0)
					{
						inBetween=true;
						break;
					}
				}
				for(int i=choice1+1;i<choice2;i++)
				{
					if(board[choice_Number1][i]!=0)
					{
						inMiddle=true;
						break;
					}
				}
			}
			else
			{
				for(int i=choice_Number1-1;i>choice_Number2;i--)
				{
					if(board[i][choice1]!=0)
					{
						inBetween=true;
						break;
					}
				}
				for(int i=choice1-1;i>choice2;i--)
				{
					if(board[choice_Number1][i]!=0)
					{
						inMiddle=true;
						break;
					}
				}
			}
			if((choice2==choice1&&choice_Number2!=choice_Number1&&!inBetween&&enemy_Color!=color)
			||(choice2!=choice1&&choice_Number2==choice_Number1&&!inMiddle&&enemy_Color!=color)
			||(diff==difference&&!inSide&&enemy_Color!=color))
			{
				isValid=true;
			}
		}
		else if(piece_Type==5)
		{
			if(((choice2==choice1  && choice_Number2==choice_Number1+1 &&enemy_Color!=color)
			||(choice2==choice1   && choice_Number2==choice_Number1-1 &&enemy_Color!=color)
			||(choice2==choice1+1 && choice_Number2==choice_Number1   &&enemy_Color!=color)
			||(choice2==choice1-1 && choice_Number2==choice_Number1   &&enemy_Color!=color)
			||(choice2==choice1+1 && choice_Number2==choice_Number1+1 &&enemy_Color!=color)
			||(choice2==choice1-1 && choice_Number2==choice_Number1+1 &&enemy_Color!=color)
			||(choice2==choice1+1 && choice_Number2==choice_Number1-1 &&enemy_Color!=color)
			||(choice2==choice1-1 && choice_Number2==choice_Number1-1 &&enemy_Color!=color)))
			{
				isValid=true;
			}	
		}
	}
	else
	{
		return false;	
	}
	if(isValid)return true;
	else return false;
	
}
void print_Board(int pieces1[],int pieces2[],int board[][8])
{
	int color=0;
	for(int i=0;i<8;i++)
	{
		cout<<"   ";
		if(i%2==0){color=0;}
		else{color=1;}
		for(int j=0;j<8;j++)
		{
			if(color==0)
			{
				setColor(WHITE,WHITE);
				color=1;
			}
			else
			{
				setColor(BLACK,BLACK);
				color=0;
			}

			cout<<"------------";
		}
		setColor(BLACK,BLACK);
		cout<<"1";
		cout<<endl;
		cout<<"   ";
		for(int j=0;j<8;j++)
		{
			if(color==0)
			{
				setColor(WHITE,WHITE);
				color=1;
			}
			else
			{
				setColor(BLACK,BLACK);
				color=0;
			}
			if(board[i][j]==11||board[i][j]==21)
			{
				cout<<"-    ";
				if(board[i][j]==11)setColor(BLACK,WHITE);
				else setColor(WHITE,BLACK);
				cout<<"/\\";
				if(color==0)setColor(BLACK,BLACK);
				else setColor(WHITE,WHITE);
				cout<<"-   -";
			}
			else if(board[i][j]==12||board[i][j]==22||board[i][j]==19||board[i][j]==29)
			{
				cout<<"-  ";
				if(board[i][j]==12||board[i][j]==19)setColor(BLACK,WHITE);
				else setColor(WHITE,BLACK);
				cout<<"|_|_|";
				if(color==0)setColor(BLACK,BLACK);
				else setColor(WHITE,WHITE);
				cout<<"-  -";
			}
			else if(board[i][j]==13||board[i][j]==23||board[i][j]==18||board[i][j]==28)
			{
				string playerpiece;
				if(board[i][j]==13||board[i][j]==18)
					playerpiece = "White";
				else
					playerpiece = "Black";
				cout<<"-  ";
				if(color==0)
				{
					setColor(WHITE,BLACK);
					cout<< playerpiece;
					setColor(BLACK,BLACK);
				}
				else
				{
					setColor(BLACK,WHITE);
					cout<< playerpiece;
					setColor(WHITE,WHITE);
				}
				cout<<"   -";			
			}
			else if(board[i][j]==14||board[i][j]==24||board[i][j]==17||board[i][j]==27)
			{
				cout<<"-   ";
				if(board[i][j]==14||board[i][j]==17)setColor(BLACK,WHITE);
				else setColor(WHITE,BLACK);
				cout<<"|_|";
				if(color==0)setColor(BLACK,BLACK);
				else setColor(WHITE,WHITE);
				cout<<"-   -";
			}
			else if(board[i][j]==16||board[i][j]==26)
			{
				cout<<"-";
				if(board[i][j]==16)setColor(BLACK,WHITE);
				else setColor(WHITE,BLACK);
				cout<<"|_| |_||_|";
				if(color==0)setColor(BLACK,BLACK);
				else setColor(WHITE,WHITE);
				cout<<"-";
			}
			else if(board[i][j]==15||board[i][j]==25)
			{
				cout<<"-   ";
				if(board[i][j]==15)setColor(BLACK,WHITE);
				else setColor(WHITE,BLACK);
				cout<<"| |";
				if(color==0)setColor(BLACK,BLACK);
				else setColor(WHITE,WHITE);
				cout<<"-   -";
			}
			
			else cout<<"-          -";
		}
		setColor(BLACK,BLACK);
		cout<<"1";
		cout<<endl;
		setColor(WHITE,BLACK);
		cout<<" "<<i+1<<" ";
		for(int j=0;j<8;j++)
		{
			if(color==0)
			{
				setColor(WHITE,WHITE);
				color=1;
			}
			else
			{
				setColor(BLACK,BLACK);
				color=0;
			}
			if(board[i][j]==0)
			{
				cout<<"-          -";				
			}
			else if(board[i][j]==11||board[i][j]==21)
			{
				cout<<"-   ";
				if(board[i][j]==11)setColor(BLACK,WHITE);
				else setColor(WHITE,BLACK);
				cout<<"/__\\";
				if(color==0)setColor(BLACK,BLACK);
				else setColor(WHITE,WHITE);
				cout<<"-  -";
			}
			else if(board[i][j]==12||board[i][j]==22||board[i][j]==19||board[i][j]==29)
			{
				cout<<"-  ";
				if(board[i][j]==12||board[i][j]==19)setColor(BLACK,WHITE);
				else setColor(WHITE,BLACK);
				cout<<"|   |";
				if(color==0)setColor(BLACK,BLACK);
				else setColor(WHITE,WHITE);
				cout<<"-  -";
			}
			else if(board[i][j]==13||board[i][j]==23||board[i][j]==18||board[i][j]==28)
			{
				cout<<"-  ";
				if(color==0)
				{
					setColor(WHITE,BLACK);
					cout<< "KNIGHT";
					setColor(BLACK,BLACK);
				}
				else
				{
					setColor(BLACK,WHITE);
					cout<< "KNIGHT";
					setColor(WHITE,WHITE);
				}
				cout<<"  -";			
			}
			else if(board[i][j]==14||board[i][j]==24||board[i][j]==17||board[i][j]==27)
			{
				cout<<"-  ";
				if(board[i][j]==14||board[i][j]==17)setColor(BLACK,WHITE);
				else setColor(WHITE,BLACK);
				cout<<"/   \\";
				if(color==0)setColor(BLACK,BLACK);
				else setColor(WHITE,WHITE);
				cout<<"-  -";
			}
			else if(board[i][j]==16||board[i][j]==26)
			{
				cout<<"-";
				if(board[i][j]==16)setColor(BLACK,WHITE);
				else setColor(WHITE,BLACK);
				cout<<"|\\  /\\  /|";
				if(color==0)setColor(BLACK,BLACK);
				else setColor(WHITE,WHITE);
				cout<<"-";
			}
			else if(board[i][j]==15||board[i][j]==25)
			{
				cout<<" ";
				if(board[i][j]==15)setColor(BLACK,WHITE);
				else setColor(WHITE,BLACK);
				cout<<"|__| |__|";
				if(color==0)setColor(BLACK,BLACK);
				else setColor(WHITE,WHITE);
				cout<<"--";
			}			
			else
			{
			cout<<"-    ";
			if(color==0)
			{
				setColor(WHITE,BLACK);
				cout<< fixed << setprecision(2) <<board[i][j];
				setColor(BLACK,BLACK);
			}
			else
			{
				setColor(BLACK,WHITE);
				cout<<board[i][j];
				setColor(WHITE,WHITE);
			}
				cout<<"    -";			
			}
		}
		setColor(BLACK,BLACK);
		cout<<"1";
		cout<<endl;
		cout<<"   ";
		for(int j=0;j<8;j++)
		{
			if(color==0)
			{
				setColor(WHITE,WHITE);
				color=1;
			}
			else
			{
				setColor(BLACK,BLACK);
				color=0;
			}
			if(board[i][j]==11||board[i][j]==21)
			{
				cout<<"-  ";
				if(board[i][j]==11)setColor(BLACK,WHITE);
				else setColor(WHITE,BLACK);
				cout<<"|____|";
				if(color==0)setColor(BLACK,BLACK);
				else setColor(WHITE,WHITE);
				cout<<"- -";
			}
			else if(board[i][j]==12||board[i][j]==22||board[i][j]==19||board[i][j]==29)
			{
				cout<<"-  ";
				if(board[i][j]==12||board[i][j]==19)setColor(BLACK,WHITE);
				else setColor(WHITE,BLACK);
				cout<<"|___|";
				if(color==0)setColor(BLACK,BLACK);
				else setColor(WHITE,WHITE);
				cout<<"-  -";
			}
			else if(board[i][j]==14||board[i][j]==24||board[i][j]==17||board[i][j]==27)
			{
				cout<<"- ";
				if(board[i][j]==14||board[i][j]==17)setColor(BLACK,WHITE);
				else setColor(WHITE,BLACK);
				cout<<"|_____|";
				if(color==0)setColor(BLACK,BLACK);
				else setColor(WHITE,WHITE);
				cout<<"- -";
			}
			else if(board[i][j]==16||board[i][j]==26)
			{
				cout<<"-";
				if(board[i][j]==16)setColor(BLACK,WHITE);
				else setColor(WHITE,BLACK);
				cout<<"| \\/  \\/ |";
				if(color==0)setColor(BLACK,BLACK);
				else setColor(WHITE,WHITE);
				cout<<"-";
			}
			else if(board[i][j]==15||board[i][j]==25)
			{
				cout<<"   -";
				if(board[i][j]==15)setColor(BLACK,WHITE);
				else setColor(WHITE,BLACK);
				cout<<"| |";
				if(color==0)setColor(BLACK,BLACK);
				else setColor(WHITE,WHITE);
				cout<<"-   -";
			}
			else cout<<"-          -";
		}
		setColor(BLACK,BLACK);
		cout<<"1";
		cout<<endl;
		cout<<"   ";
		for(int j=0;j<8;j++)
		{
			if(color==0)
			{
				setColor(WHITE,WHITE);
				color=1;
			}
			else
			{
				setColor(BLACK,BLACK);
				color=0;
			}
			if(board[i][j]==12||board[i][j]==22||board[i][j]==19||board[i][j]==29)
			{
				cout<<"- ";
				if(board[i][j]==12||board[i][j]==19)setColor(BLACK,WHITE);
				else setColor(WHITE,BLACK);
				cout<<"/_____\\";
				if(color==0)setColor(BLACK,BLACK);
				else setColor(WHITE,WHITE);
				cout<<"- -";
			}
			else if(board[i][j]==14||board[i][j]==24||board[i][j]==17||board[i][j]==27)
			{
				cout<<"-";
				if(board[i][j]==14||board[i][j]==17)setColor(BLACK,WHITE);
				else setColor(WHITE,BLACK);
				cout<<"/_______\\";
				if(color==0)setColor(BLACK,BLACK);
				else setColor(WHITE,WHITE);
				cout<<"--";
			}
			else if(board[i][j]==16||board[i][j]==26)
			{
				cout<<"-";
				if(board[i][j]==16)setColor(BLACK,WHITE);
				else setColor(WHITE,BLACK);
				cout<<"|________|";
				if(color==0)setColor(BLACK,BLACK);
				else setColor(WHITE,WHITE);
				cout<<"-";
			}
			else if(board[i][j]==15||board[i][j]==25)
			{
				cout<<"   -";
				if(board[i][j]==15)setColor(BLACK,WHITE);
				else setColor(WHITE,BLACK);
				cout<<"| |";
				if(color==0)setColor(BLACK,BLACK);
				else setColor(WHITE,WHITE);
				cout<<"-   -";
			}
			else cout<<"------------";
		}
		setColor(BLACK,BLACK);
		cout<<"1";
		cout<<endl;
	}
	setColor(WHITE,BLACK);	
	cout<<"        A           B           C           D           E           F           G           H";
	
	
	
	
	
}
int check_White_King(int board[][8])
{
	int place = -1;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(board[i][j]==15)
			{
				place=i*10+j;
			}
		}
	}
	return place;
}
int check_Black_King(int board[][8])
{
	int place = -1;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(board[i][j]==25)
			{
				place=i*10+j;
			}
		}
	}
	return place;		
}
int check_Empty(int board[][8])
{
	int place = -1;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(board[i][j]==0)
			{
				place=i*10+j;
			}
		}
	}
	return place;		
}
bool callCheck(int current_Player,int board[][8],int choice2,int choice_Number2)
{
	int white_kingplace=check_White_King(board);
	int row_white=white_kingplace/10;
	int column_white=white_kingplace%10;
	int black_kingplace=check_Black_King(board);
    if (white_kingplace < 0 || black_kingplace < 0) return true;
    const bool targetInBounds = choice2 >= 0 && choice2 < 8 && choice_Number2 >= 0 && choice_Number2 < 8;
	int row_black=black_kingplace/10;
	int column_black = black_kingplace%10;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			int color=board[i][j]/10;
			int type=board[i][j]%10;
			if(current_Player==1)
			{
				if(targetInBounds && board[choice_Number2][choice2]==15)
				{
					current_Player=2;
				}
				if(type==1)
				{
					if(color==2&&isValid_Play(j,i,column_white,row_white,2,board))
					{
						return true;
					}
				}
				else
				{
					if(color==2&&isValid_Play(j,i,column_white,row_white,current_Player,board))
					{
						return true;
					}
				}
				current_Player=1;
			}
			else
			{
				if(targetInBounds && board[choice_Number2][choice2]==25)
				{
					current_Player=1;
				}
				if(type==1)
				{
					if(color==1&&isValid_Play(j,i,column_black,row_black,1,board))
					{
						return true;
					}
				}
				else
				{
					if(color==1&&isValid_Play(j,i,column_black,row_black,current_Player,board))
					{
						return true;
					}
				}
				current_Player=2;
			}
		}
	}
	
	return false;
}
int available_Moves(int board[][8],int current_Player)
{
	int counter=(current_Player==1)?-1:0;

	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			int type=board[i][j]%10;
			int color=board[i][j]/10;
			if(color==current_Player)
			{
				for(int k=0;k<8;k++)
				{
					for(int l=0;l<8;l++)
					{
						if(isValid_Play(j,i,l,k,current_Player,board))
					 	{
							int temp=board[k][l];
							board[k][l]= board[i][j];
							board[i][j]=0;
							if(!callCheck(current_Player,board, l, k))
							{
								counter++;
							}
							board[i][j]=board[k][l];
							board[k][l]=temp;
						}
					}
				}
			}
		}
	}
	return counter;
}
void clearScreen()
{
	system("CLS"); //For Windows
}
