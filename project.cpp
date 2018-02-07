/*PROJECT :SANJIVANI- ONLINE MEDICINE PORTAL
	   NOTE :- Only ADMIN of the PORTAL can open a customer account
		   To join SANJIVANI group,
		       contact ADMIN -1800456789(TOLL FREE)
			    */
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<dos.h>
#include<process.h>
#include<iomanip.h>
class medicine                      //medicine details
{char mfg[20],exp[20];
int n;
float cost;
float Rate(float,int)
 {return (cost/n)   ;
 }
public:
char condition[20];
char med_name[20];
float rate;
medicine()
 {strcpy(mfg,"NA");
 strcpy(exp,"NA");
 cost=0;
 strcpy(condition,"OUT OF STOCK");
 strcpy(med_name,"NA");
 }
void input()                         //input medicine information
 {cout<<"\nEnter name of medicine : ";
  gets(med_name);
  cout<<"\nEnter mfg. date,press enter and enter exp. date : ";
  gets(mfg);
  gets(exp);
  cout<<"\nEnter cost and press enter to enter the no. of tablets : ";
  cin>>cost>>n;
  cout<<"\nEnter availability (i.e. OUT OF STOCK/IN STOCK) : ";
  gets(condition);
  rate=Rate(cost,n);
 }
void info_display()                  //display medicine information
 { cout<<"Name : "<<med_name<<"\n";
   cout<<"Mfg. : "<<mfg<<endl;
   cout<<"Exp. : "<<exp<<endl;
   cout<<"Rate (per tablet) : "<<"Rs"<<rate<<endl;
   cout<<"Availability : "<<condition<<endl;
  }
void list()                          //display all medicines list
 {cout<<setw(20)<<med_name<<" ";
  cout<<setw(8)<<mfg<<" ";
  cout<<setw(8)<<exp<<" ";
  cout<<setw(10)<<"Rs"<<rate<<" ";
 }
};
void Add()                             //add medicine
{ medicine s;
ofstream fout;
fout.open("store.dat",ios::binary|ios::app);
if(!fout)
 {cout<<"Error opening file";
 return;
 }
s.input();
fout.write((char*)&s,sizeof(s));
fout.close();
}
float calculate(medicine &s,int n)             //to calculate bill
{if(!(strcmpi(s.condition,"OUT OF STOCK"))==0)
 return (s.rate*n);
 else
 return 0;
}
float printbill()                              //printing bill
{int k,flag,x,i=0;   ifstream fin; medicine s;    char r[20];
float cost;
fin.open("store.dat",ios::in|ios::binary);
if(!fin)
{cout<<"Cannot open store \n";
return 0;
}
cout<<"Enter no. of medicines purchased : ";
cin>>x;
cout<<endl;
do
{cout<<"Enter name of "<<i+1<<" medicine purchased : ";
 gets(r);
 fin.seekg(0);
 while(fin.read((char*)&s,sizeof(s)))
 {if((strcmpi(r,s.med_name))==0)
  {flag=1;
  float cost;
  s.info_display();
  cout<<"Enter no.of tablets purchased : ";
  cin>>k;
  cost=calculate(s,k);
  return cost;
  }
 }
 if(flag!=1)
  cost=0  ;
}while(i<x);
  fin.close();
  return cost;
 }                                     //Customer account records
struct acc
{ char username[20];
 char password[20];
 int eno;
 }cust[100];

 void opencust(acc s)                //Logging into customer's account
{char c;
do
{clrscr();
int ch;
medicine m,n[100],p;ifstream fin;ofstream fout; int i,count=0; float total;
cout<<"WELCOME "<<s.username<<endl;
cout<<"What would you like to do ?\n";
cout<<"1.SEARCH A MEDICINE\n";
cout<<"2.PRINT A BILL\n";
cout<<"3.CHANGE YOUR PASSWORD\n";
cout<<"4.SIGN OUT\n";
cout<<"Enter your choice no. : ";
cin>>ch;
switch(ch)
{case 1 :  char medn[20]; int flag=0;                //searching medicine
fin.open("store.dat",ios::in|ios::binary);
if(!fin)
{cout<<"Cannot open store \n";
return;
}
cout<<"Enter name of medicine to be searched : ";
gets(medn);
fin.seekg(0);
while(fin.read((char*)&m,sizeof(m)))
{ n[count++]=m;
}

for(i=0;i<count;i++)
{if((strcmpi(medn,n[i].med_name))==0)
 {flag=1;
 p=n[i];
 }
}
if(flag==1)
 p.info_display();
else
 cout<<"Not found\n";
 fin.close();
 cout<<"\nPress any key \n";
 getch();
 c='N' ;
 break;
case 2 :  clrscr();                                    //print a bill
      total=printbill()  ;
      cout<<"\nPlease pay Rs"<<total;
      cout<<"\nPress any key \n";
      getch();
      c='N'     ;
      break;
case 3 :   clrscr();                                 //change password
	char p[40],n[40],p_new[40]; int j=0; flag=0;
	fin.open("account.dat",ios::binary|ios::in|ios::nocreate);
	if(!fin)
	{cout<<"Cannot open Account_rec\n";
	return;
	}
	fout.open("temp.dat",ios::binary|ios::out);
	if(!fout)
	{cout<<"Cannot open temp_rec\n";
	return;
	}
	cout<<"Enter username\n";
	gets(n);
	cout<<"Enter old password\n";
	do
	{p[i]=getch();
	  if(p[i]==13)
	   {p[i]='\0';
	    break;
	   }
	 else
	  {cout<<"*";
	  i++;
	  }
	 }while(p[i-1]!=13) ;
	 int count =0; acc s,N[100];
	 fin.seekg(0);
	 while(fin.read((char *)&s,sizeof(s)))
	 { N[count++]=s;
	 }
	 for(i=0;i<count;i++)
	 {if((strcmp(N[i].username,n))==0 && (strcmp(N[i].password,p))==0)
	  {cout<<"\nEnter new password :";
	   do
	   {p_new[j]=getch();
	   if(p_new[j]==13)
	    {p_new[j]='\0';
	     break;
	    }
	   else
	   {cout<<"*";
	    j++;
	    }
	   }while(p_new[j-1]!=13) ;
	  strcpy(N[i].password,p_new);
	  flag=1        ;
	  cout<<"\nPASSWORD CHANGED SUCCESSFULLY\n";
	  }
	 }
	 if(flag!=1)
	 {cout<<"\nPASSWORD CHANGE UNSUCCESSFUL\n ";
	 }
	 for(i=0;i<count;i++)
	 {fout.write((char*)&N[i],sizeof(N[i]));
	 }
	 fin.close();
	 fout.close();
	 remove("account.dat");
	 rename("temp.dat","account.dat");
	 cout<<"\nPress any key \n";
	 getch();
	 c='N'     ;
	 break;
case 4 :                                         //sign out
	cout<<"\n\nAre you sure ?:";
	cin>>c;
	break ;
default:c='Y';cout<<"\nInvalid choice\n";
}
}while(c=='N'||c=='n');
cout<<"Logging out of your account...\n";
delay(10);
}

void excust()                 //Logging into customer's account
{acc s,N[100];
ifstream fin;
fin.open("account.dat",ios::binary|ios::out|ios::nocreate);
if(!fin)
{cout<<"Cannot open Account_rec\n";
return;
}
char p[20],n[20];
int i=0,r;
cout<<"Enter username\n";
gets(n);
cout<<"Enter password\n";
 do
 {p[i]=getch();
 if(p[i]==13)
  {p[i]='\0';
   break;
   }
 else
  {cout<<"*";
   i++;
   }
 }while(p[i-1]!=13) ;
int flag=0;int count=0;
fin.seekg(0);
while(fin.read((char*)&s,sizeof(s)))
{ N[count++]=s;
}
for(i=0;i<count;i++)
 {if((strcmp(N[i].username,n))==0 && (strcmp(N[i].password,p))==0)
   { cout<<"\nLogging into your account....\n";
    delay(1000);
   opencust(s);
   flag=1;
   }

}
if(flag==0)
cout<<"\nInvalid credentials\n";
fin.close();
}

void adminch()                      //Logging into Admin's account
{clrscr();
int n;   char ch;
do
{  clrscr();  ofstream fout ; ifstream fin  ;
cout<<"WELCOME ADMIN\n";
cout<<"1.Add a new medicine \n";
cout<<"2.Delete a medicine \n";
cout<<"3.Display all medicines list\n";
cout<<"4.Open new customer account \n";
cout<<"5.Close a customer account\n";
cout<<"6.Logout\n";
cout<<"What would you like to do? Enter choice no. : ";
cin>>n;
switch(n)
{case 1 :  medicine s[100];  int m,i;          //Add a medicine
fout.open("store.dat",ios::binary|ios::out);
if(!fout)
{cout<<"Cannot open store_rec\n";
return;
}
cout<<"Enter no. of medicines to be added : ";
cin>>m;
for(i=0;i<m;i++)
{s[i].input();
fout.write((char*)&s[i],sizeof(s[i]));
}
fout.close(); ch='n';
cout<<"\nPress any key\n";
getch();
break;
case 2 :     char med[50];                     //Delete a medicine
fin.open("store.dat",ios::binary|ios::in|ios::nocreate) ;
 if(!fin)
{cout<<"Cannot open store_rec\n";
return;
}
fout.open("temp.dat",ios::binary|ios::out);
if(!fout)
{cout<<"Cannot open temp_rec\n";
return;
}
medicine del;
cout<<"Enter name of medicine to be deleted : ";
gets(med);
fin.seekg(0);
while(fin.read((char*)&del,sizeof(del)))
{if(!((strcmpi(del.med_name,med))==0))
 fout.write((char*)&del,sizeof(del));
 }
 fin.close();
 fout.close();
 remove("store.dat");
 rename("temp.dat","store.dat");
cout<<"\n Medicine is deleted successfully\n";    ch='n';
cout<<"\nPress any key\n";
getch();
break;
case 3 : clrscr();               //Display medicine list
	 fin.open("store.dat",ios::binary|ios::in|ios::nocreate) ;
	 if(!fin)
	 {cout<<"Cannot open store_rec\n";
	  return;
	 }
	 fin.seekg(0);
	 gotoxy(0,0)      ;
	 medicine list_m;
	  cout<<setw(20)<<"Name of medicine ";
	  cout<<setw(10)<<"Mfg. ";
	  cout<<setw(10)<<"Exp. ";
	  cout<<setw(8)<<"Rate ";
	 while(fin.read((char*)&list_m,sizeof(list_m)))
	 { cout<<endl           ;
	    list_m.list();
	  }
	 ch='n';
	 cout<<"\nPress any key\n";
	 getch();
	 break;

case 4 :   acc q[100];                    //Open customer accounts
fout.open("account.dat",ios::binary|ios::out);
if(!fout)
{cout<<"Cannot open Account_rec\n";
return;
}
cout<<"Enter no. of accounts to be added : ";
cin>>m;
for(i=0;i<m;i++)
{cout<<"\nEnter username for new account : ";
gets(q[i].username);
cout<<"\nEnter password for new account : ";
gets(q[i].password);
fout.write((char*)&q[i],sizeof(q[i]));
cout<<"\nCustomer enrolled in successfully\n";
}
fout.close();   ch='n';
cout<<"\nPress any key\n";
getch();
break;
case 5 :   clrscr();  char n[40];   i=0;       //close customer account
	fin.open("account.dat",ios::binary|ios::in|ios::nocreate);
	if(!fin)
	{cout<<"Cannot open Account_rec\n";
	return;
	}
	fout.open("temp.dat",ios::binary|ios::out);
	if(!fout)
	{cout<<"Cannot open temp_rec\n";
	return;
	}
	cout<<"Enter username of account to be deleted\n";
	gets(n);
	 int count =0; acc r,N[100];
	 fin.seekg(0);
	 while(fin.read((char *)&r,sizeof(r)))
	 { N[count++]=r;
	 }
	 for(i=0;i<count;i++)
	 {if(!((strcmp(N[i].username,n))==0))
	  {fout.write((char*)&N[i],sizeof(N[i]));
	  }
	 }
	 cout<<"\nACCOUNT DELETION SUCCESSFUL\n ";
	 fin.close();
	 fout.close();
	 remove("account.dat");
	 rename("temp.dat","account.dat");
	 cout<<"\nPress any key \n";
	 getch();
	 ch='N'     ;
	 cout<<"\nPress any key to continue\n";
	 break;
case 6 :                                       //Log out
	cout<<"\n\nAre you sure ?:";
	cin>>ch;
	break ;
default : ch='n'; cout<<"Invalid choice\n" ;
}
}while(ch=='N'||ch=='n');
}

void main()
{clrscr();     char c;
do
 {int i=0,ch;char n[20],p[20];
 cout<<"\n\n\n\n\t\t\tWELCOME TO E-PHARMACY-SANJIVANI\n";
 cout<<"\t\tWORLD'S LARGEST SELLING ONLINE MEDICINE PORTAL\n";
 delay(1000);
 clrscr();
 cout<<"Sign in as\n";
 cout<<"1.ADMIN\n";
 cout<<"2.EXISTING CUSTOMER\n";
 cout<<"3.EXIT\n";
 cout<<"Enter choice no. : ";
 cin>>ch;
 switch(ch)
 {case 1 : cout<<"Enter username \n";     //Admin's account gateway
 gets(n);
 cout<<"Enter password \n";
 do
 {p[i]=getch();
 if(p[i]==13)
  {p[i]='\0';
   break;
   }
 else
  {cout<<"*";
   i++;
   }
 }while(p[i-1]!=13) ;
 if((strcmp("ADMIN",n))==0 && (strcmp("abcd",p))==0)
  {cout<<"\nLogging into admin account....\n";   delay(1000);
   adminch();
   }
 else
 cout<<"\nInvalid credentials\n";
 break;
 case 2 : excust();                      //Customer's account gateway
 break     ;
 case 3 :break;                         //Exit
 default :cout<<"Invalid choice \n";
 }
 cout<<"\nDo you wish to reach main menu? :";
 cin>>c;
 }while(c=='y'||c=='Y');
 if(c=='n'||c=='N')
 cout<<"\t\n\tTHANK YOU ! PLEASE VISIT AGAIN\t\n";
 getch();
 }
