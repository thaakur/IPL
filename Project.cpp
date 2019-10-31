//BANG BANG LEAGUE DATA MANAGEMENT SYSTEM.
//CREATED BY SIDDHANT KHANDELWAL.
using namespace std;
#include<fstream>
#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<dos.h>
#include<process.h>

const int totalplayers=30;
int entrypcode=0;

class teams
{
	public:
	int noplayers;
	int code;
	char tname[30];
	char description[200];

	teams()
	{
		noplayers=totalplayers/5;
	}
	void getdata()  //FUNCTION TO GET TEAM DETAILS
	{
	cout<<"\nEnter Team's Code(Only Integers): ";
	cin>>code;
	cout<<"\nEnter Team's Name: ";
	gets(tname);
	cout<<"Enter description: ";
	gets(description);
	}

	void putdata()    //FUNCTION TO PRINT TEAM'S DETAILS
	{
	cout<<"\nTeam's Name: ";
	puts(tname);
	cout<<"\nTeam Code: "<<code;
	cout<<"\nNo of players: "<<noplayers;
	cout<<"\nDescription: ";
	puts(description);
	}
	void twriter(int teamno);           //FUNCTION TO WRITE TEAM'S DETAILS INTO FILE TEAMS.DAT

}t,t1;
void teams::twriter(int teamno)
	{
		fstream file;
		if(teamno==0)
		{
			file.open("teams.dat",ios::binary|ios::out);
			file.write((char*)&t,sizeof(t));
		}
		else
		{
			file.open("teams.dat",ios::binary|ios::out|ios::app);
			file.write((char*)&t,sizeof(t));
		}
		file.close();
	}
void tsearcher(int code)   //FUNCTION TO FIND TEAMCODE OF A PLAYER
{	int flag=0;
	fstream file;
	file.open("teams.dat",ios::in|ios::binary);
	while(file)
	{
		file.read((char*)&t,sizeof(t));
		if(t.code==code)
		{
			flag=1;
			break;
		}

	}
	if(flag==0)
	{
	file.close();
	cout<<"\nTeam not found. Bad allocation.\n\nExiting........";
	getch();
	exit(0);
	}
}

class player
{
char name[30];
int pcode,type,teamcode;
public:
int mplayed,trun,sixes,fours,wickets,eco,speed,wkwicket,wk;
float avg;
int bprice,sprice;

int returntype();                     //FUNCTION TO RETURN TYPE OF THE PLAYER
int returnpcode();                  //FUNCTION TO RETURN PLAYER CODE
int returnteamcode();              //FUNCTION TO RETURN TEAM CODE
void getdata();                          //FUNCTION TO ENTER PLAYER'S DETAILS
void putdata();                        //FUNCTION TO DISPLAY PLAYER'S DETAILS
void pwriter();                      //FUNCTION TO WRITE PLAYER'S DETAILS INTO FILE BBL.DAT
void reader();                       //FUNCTION TO READ PLAYER DETAILS

player(int val)
{
	trun=sixes=fours=avg=wickets=eco=speed=wkwicket=wk=val;
}
player()
{
	wk=0;
}
}p,p1;

int player::returnpcode()
{
return pcode;
}

int player::returnteamcode()
{
return teamcode;
}

void player::reader()
{
fstream file;
file.open("BBL.dat",ios::in|ios::binary);
while(file)
{
file.read((char*)&p,sizeof(p));
putdata();
getch();
}
file.close();
}

void player::pwriter()
{
fstream file;
if(entrypcode==0)
{
file.open("BBL.dat",ios::out|ios::binary);
file.write((char*)&p,sizeof(p));
}
else
{
file.open("BBL.dat",ios::out|ios::app|ios::binary);
file.write((char*)&p,sizeof(p));
}
file.close();
}

void player::getdata()
{
p.pcode=entrypcode;
cout<<"\nEnter the Name of the Player: ";
gets(name);

do
{
cout<<"Enter Baseprice of the Player in Auction: ";
cin>>bprice;
cout<<"Enter Saleprice of the Player in Auction: ";
cin>>sprice;
}while(bprice>sprice);

cout<<"Enter Matches Played in BBL: ";
cin>>mplayed;

cout<<"Enter Team Code: ";
cin>>teamcode;

cout<<"Enter Type of Player:\n"<<"1.\tBatsman\n2.\tBowler\n3.\tAll-rounder\n";
do
{
cout<<"Enter choice: ";
cin>>type;
if(type==1)
{
if(mplayed==0)
player(0);
else
{
cout<<"Enter Total Runs Scored: ";
cin>>trun;
do
{
cout<<"Enter Sixes: ";
cin>>sixes;
cout<<"Enter Fours: ";
cin>>fours;
}while(!(sixes*6<=trun&&fours*4<=trun&&((sixes*6)+(fours*4)<=trun)));
avg=trun/mplayed;
}
cout<<"Is player a wicketkeeper too? (1-Y) ";
cin>>wk;
if(wk==1)
{
	if(mplayed!=0)
	{
	cout<<"Enter No. of Wickets taken as a wicket-keeper: ";
	cin>>wkwicket;
	}
}
}
else if(type==2)
{
if(mplayed==0)
player(0);
else
{
cout<<"Enter Wickets Taken: ";
cin>>wickets;
cout<<"Enter Economy: ";
cin>>eco;
cout<<"Enter Avg. Speed: ";
cin>>speed;
}
}
else if(type==3)
{
if(mplayed==0)
player(0);
else
{
cout<<"Enter Total Runs Scored: ";
cin>>trun;
do
{
cout<<"Enter Sixes: ";
cin>>sixes;
cout<<"Enter Fours: ";
cin>>fours;
}while(!(sixes*6<trun&&fours*4<trun&&((sixes*6)+(fours*4)<trun)));

avg=trun/mplayed;

cout<<"Enter Wickets Taken: ";
cin>>wickets;
cout<<"Enter Economy: ";
cin>>eco;
cout<<"Enter Avg. Speed: ";
cin>>speed;
}
}
}while(type!=1&&type!=2&&type!=3);
}

void player::putdata()
{
cout<<"\n\nName of the Player: ";
puts(name);
cout<<"\nPlayer Code: "<<returnpcode();
cout<<"\nBaseprice of the Player in Auction: "<<bprice;
cout<<"\nSaleprice of the Player in Auction: "<<sprice;
cout<<"\nTeam Code: "<<teamcode;
tsearcher(p.teamcode);
cout<<"\nTeam's Name: ";
puts(t.tname);
cout<<"\nMatches Played in BBL: "<<mplayed;

if(type==1)
{
cout<<"\nTotal Runs Scored: "<<trun;
cout<<"\nSixes: "<<sixes;
cout<<"\nFours: "<<fours;
cout<<"\nAverage: "<<avg;
if(wk==1)
cout<<"\nWickets taken as a wicket-keeper: "<<wkwicket;
}

else if(type==2)
{
cout<<"\nWickets Taken: "<<wickets;
cout<<"\nEconomy: "<<eco;
cout<<"\nAvg. Speed: "<<speed;
}

else
{
cout<<"\nTotal Runs Scored: "<<trun;
cout<<"\nSixes: "<<sixes;
cout<<"\nFours: "<<fours;
cout<<"\nAverage: "<<avg;
cout<<"\nWickets Taken: "<<wickets;
cout<<"\nEconomy: "<<eco;
cout<<"\nAvg. Speed: "<<speed;
if(wk==1)
cout<<"\nWickets taken as a wicket-keeper: "<<wkwicket;
}
}

int main()
{
int ch,j,stringcheck=1,i;
char pass[5];
		cout<<"\n\n\t\tIndian Premier League Database Management System.\n________________________________________________________________________________\nCreated by Avinash Kr(Thaakur).";
		cout<<"\n\nThis software enables you to manage player and team details for the league.";

for(j=0;j<4;++j)
	{
		cout<<"\n\n\n\nEnter Password: ";
		for(i=0;i<4;i++)
		{
		pass[i]= getch();
		cout<<"*";
		}
		pass[i]='\0';
		stringcheck=strcmp(pass,"pass");

	if (stringcheck!=0)     //WHEN PASSWORD ENTERED IS WRONG
		{
		if(j!=3)
		{
		cout<<"Oops! Wrong password\n";
		}
		else
		{
			cout<<"\n\n\nWrong Password Again!..You've exceeded your trials.... Goodbye.... \n\n\nHAHHAHAHAHAHAHAHAHAHHAHHAHAHAHAHAHAHAHAHHAHHAHAHAHAHAHAHAHAHHAHHAHAHAHAHAHAHAHAHHAHHAHAHAHAHAHAHAHAH";

			exit(0);
		}
		}
	else
		{
		break;	//WHEN PASSWORRD ENTERED IS CORRECT
		}
	}
do
{
cout <<"\n\t\tTasks"
	 <<"\n\n\t\tPlayers\n"
	 <<"\n1.\tEnter Complete Player Data\n"
	 <<"2.\tDisplay Complete Player Data\n"
	 <<"3.\tDisplay Particular Player's Data\n"
	 <<"4.\tEdit a particular Player's Record\n"
	 <<"\n\n\t\tTeams\n"
	 <<"\n5.\tEnter Complete Team Data\n"
	 <<"6.\tDisplay Complete Team Data\n"
	 <<"7.\tDisplay Particular Team's Data\n"
	 <<"8.\tEdit a particular Team's Record\n"
	 <<"\n\n9.\tExit\n\n";
cout <<"Enter Choice: ";

do
{
	cin>>ch;
}while(!(ch>=1&&ch<=9));

switch(ch)
		{
		case 1:       //TO ENTER COMPLETE PLAYER DATA
			for (i = 0; i < totalplayers; ++i)
			{
			cout<<"Player "<<entrypcode+1<<endl;
			p.getdata();
			p.pwriter();
			++entrypcode;
			}
			cout<<"\nSuccessfully entered complete data.\nFile saved as 'BBL.dat' in the same folder.";
			getch();
			break;

		case 2:    //TO DISPLAY COMPLETE PLAYER DATA
			p.reader();
			break;

		case 3:    //TO DISPLAY A PARTICULAR PLAYER'S DATA
			{
			int chcode,flag=0;
			cout<<"\nEnter Player code whose record is to be displayed: ";
			cin>>chcode;

			fstream file;
			file.open("BBL.dat",ios::in|ios::binary);
			while(file)
			{
				file.read((char*)&p,sizeof(p));
				if(p.returnpcode()==chcode)
				{
					flag=1;
					cout<<"\nData of the searched player is: ";
					p.putdata();
					getch();
				}
			}
			if(flag==0)
			{

			cout<<"\n\nSorry, Entered code does not match to any player's code.";
			getch();
			}
			}
			break;

		case 4:    //TO EDIT A PLAYER'S RECORD
			{
			int chcode,flag=0,pos;
			cout<<"\nEnter The Player code whose details are to be modified: ";
			cin>>chcode;
			fstream file;
			file.open("BBL.dat",ios::binary|ios::in|ios::out);
			while(file)
			{
			pos=file.tellg();
			file.read((char*)&p,sizeof(p));
			if(p.returnpcode()==chcode)
			{
				flag=1;
				entrypcode=chcode;

				cout<<"\nThe player is: ";
				p.putdata();
				cout<<"\n\nPress any key to continue.......";
				getch();

				cout<<"\nModify: \n";
				p.getdata();
				cout<<"\nThe following data is being written: ";
				p.putdata();
				file.seekg(pos);
				file.write((char*)&p,sizeof(p));
				cout<<"\nSuccessfully modified the record.\nFile saved as 'BBL.dat' in the same folder.";
				file.close();
				cout<<"\n\nPress any key to continue.....";
				getch();
				break;
			}
			}
			if(flag==0)
			{
			cout<<"\nEntered Player code was not found";
			getch();
			}
			}
			break;

		case 5:    //TO ENTER COMPLETE TEAM DATA
			{
			fstream file;
			for(int i=0;i<5;++i)
			{
			t.getdata();
			t.twriter(i);
			}
			cout<<"\nSuccessfully entered complete data.\nFile saved as 'teams.dat' in the same folder.";

			}
			break;

		case 6:   //TO DISPLAY COMPLETE TEAM DATA
			{
			fstream file;
			file.open("teams.dat",ios::binary|ios::in);
			while(file)
			{
			file.read((char*)&t,sizeof(t));
			t.putdata();
			getch();
			}
			file.close();
			}
			break;

		case 7:     //TO DISPLAY A PARTICULAR TEAM'S DATA
			{

			int chcode,flag=0;
			cout<<"\nEnter Team code whose record is to be displayed: ";
			cin>>chcode;
			fstream file;
			file.open("teams.dat",ios::in|ios::binary);
			file.seekg(0);
			while(file)
			{
				file.read((char*)&t,sizeof(t));
				if(t.code==chcode)
				{

					flag=1;
					cout<<"\nData of the searched team is: ";
					t.putdata();
					getch();
				}
			}
			if(flag==0)
			{

			cout<<"\n\nSorry, Entered code does not match to any team's code.";
			getch();
			}
			}
		break;

		case 8:     //TO EDIT A PARTICULAR TEAM'S RECORD
			{
			int chcode,flag=0,pos;
			cout<<"\nEnter The Team code whose details are to be modified: ";
			cin>>chcode;
			fstream file;
			file.open("teams.dat",ios::binary|ios::in|ios::out);
			while(file)
			{
			pos=file.tellg();
			file.read((char*)&t,sizeof(t));
			if(t.code==chcode)
			{
				flag=1;
				cout<<"\nThe Team is: ";
				t.putdata();
				cout<<"\n\nPress any key to continue....";
				getch();

				cout<<"\nModify: \n";
				t.getdata();

				cout<<"\nThe following data is being written: ";
				t.putdata();
				file.seekg(pos);
				file.write((char*)&t,sizeof(t));
				cout<<"\nSuccessfully modified the record.\nFile saved as 'teams.dat' in the same folder.";
				file.close();
				cout<<"\n\nPress any key to continue.....";
				getch();
				break;
			}
			}
			if(flag==0)
			{
			cout<<"\nEntered Team code was not found";
			getch();
			}
			}
			break;

		case 9: //TO EXIT
			exit(0);
			break;
		}
}while(stringcheck==0);
}

//ALSO HAS AN UNFINISHED PART. A GAME, THE REAL BBL. LINK TO THE UNFINISHED C++ CODE IS: "".
