#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iomanip.h>
#include<process.h>
#include<ctype.h>

//stucture bank
struct bank
{
 char uname[50];
 char pcode[30];
 char acno[20];
 float balance;
 char pno[12];
 char email[20];
 char adhno[15];
 char panno[15];
 void trans();
};

//input bank details
void input()
{
 ofstream f("bank.dat",ios::binary);
 if(!f)
 {
  cout<<"\nFILE CREATION FAILS.";
  getch();
  return;
 }
 int reply,i;
 cout<<"\nENTER NUMBER OF RECORDS YOU WANT TO INSERT: ";
 cin>>reply;
 bank b;
 for(i=0;i<reply;i++)
 {
  cout<<"\nUSERNAME: ";
  cin>>b.uname;
  cout<<"\nPASSWORD: ";
  cin>>b.pcode;
  cout<<"\nACCOUNT NUMBER: ";
  cin>>b.acno;
  cout<<"\nBALANCE: ";
  cin>>b.balance;
  cout<<"\nPHONE NUMBER: ";
  cin>>b.pno;
  cout<<"\nEMAIL ID: ";
  cin>>b.email;
  cout<<"\nADHAAR NUMBER: ";
  cin>>b.adhno;
  cout<<"\nPAN NUMBER: ";
  cin>>b.panno;

  f.write((char*)&b,sizeof(b));
 }
 f.close();
}

//add new bank records
void append()
{
 ofstream f("student.dat",ios::binary|ios::app|ios::nocreate);
 int reply;
 if(!f)
 {
  cout<<"\nFILE OPENING FAILS.";
  getch();
  return;
 }
 bank b;
 cout<<"\nENTER THE NUMBER OF RECORDS YOU WANT TO ADD: ";
 cin>>reply;
 int i;
 for(i=0;i<reply;i++)
 {
  cout<<"\nUSERNAME: ";
  cin>>b.uname;
  cout<<"\nPASSWORD: ";
  cin>>b.pcode;
  cout<<"\nACCOUNT NUMBER: ";
  cin>>b.acno;
  cout<<"\nBALANCE: ";
  cin>>b.balance;
  cout<<"\nPHONE NUMBER: ";
  cin>>b.pno;
  cout<<"\nEMAIL ID: ";
  cin>>b.email;
  cout<<"\nADHAAR NUMBER: ";
  cin>>b.adhno;
  cout<<"\nPAN NUMBER: ";
  cin>>b.panno;

  f.write((char*)&b,sizeof(b));
 }
 f.close();
}

//delete a bank record
void Delete()
{
 ifstream f1("bank.dat",ios::binary);
 ofstream f2("temp.dat",ios::binary);
 int flag=1;
 if(!f1)
 {
  cout<<"\nFILE READING FAILS.";
  getch();
  return;
 }
 if(!f2)
 {
  cout<<"\nFILE CREATION FAILS.";
  getch();
  return;
 }
 char a[20];
 bank b;
 cout<<"\nENTER THE ACCOUNT NUMBER: ";
 cin>>a;
 while(f1.read((char*)&b,sizeof(b)))
 {
  int c=strcmp(a,b.acno);
  if(c!=0)
   f2.write((char*)&b,sizeof(b));
  else
   flag=0;
 }
 f1.close();
 f2.close();
 if(flag==1)
  cout<<"\nRECORD NOT FOUND.";
 else
 {
  remove("bank.dat");
  rename("temp.dat","bank.dat");
  cout<<"\nRECORD DELETED.";
 }
}

//username password check
void check()
{
 char un[50],pass[30];
 bank b;
 ifstream f("bank.dat",ios::binary);
 if(!f)
 {
  cout<<"\nNO RECORD IN THE BANK DATABASE.";
  getch();
  return;
 }
 int flag;
 do
 {
  cout<<"\nUSERNAME: ";
  cin>>un;
  cout<<"\nPASSWORD: ";
  cin>>pass;
  while(f.read((char*)&b,sizeof(b)))
  {
   int c=strcmp(b.uname,un);
   int d=strcmp(b.pcode,pass);
   if(c==0 && d==0)
    flag=0;//true
   else
    flag=1;//false
  }
  if(flag==1)
   cout<<"\nINVALID USERNAME, PASSWORD.RE ENTER.";
 }while(flag==1);
 f.close();
}

//forgot password
void fpass()
{
 fstream f("bank.dat",ios::binary|ios::in|ios::out);
 if(!f)
 {
  cout<<"\nNO RECORD IN BANK DATABASE.";
  getch();
  return;
 }
 bank b;
 int flag=1;//false
 char un[50],p[12],ad[15];
 cout<<"\nUSERNAME: ";
 cin>>un;
 cout<<"\nPHONE NUMBER: ";
 cin>>p;
 cout<<"\nADHAAR NUMBER: ";
 cin>>ad;
 while(f.read((char*)&b,sizeof(b)))
 {
  int c=strcmp(b.uname,un);
  int d=strcmp(b.pno,p);
  int x=strcmp(b.adhno,ad);
  if(c==0 && d==0 && x==0)
  {
   flag=0;//true
   cout<<"\nENTER NEW PASSWORD: ";
   cin>>b.pcode;
   long loc=(f.tellg(),sizeof(b));
   f.seekg(loc,ios::beg);
   f.write((char*)&b,sizeof(b));
  }
 }
 if(flag==1)
  cout<<"\nRECORD NOT FOUND.";
 else
  cout<<"\nPASSWORD UPDATED.";
 f.close();
}

//input transactions
void bank::trans()
{
 fstream f1("bank.dat",ios::binary|ios::in|ios::out);
 if(!f1)
 {
  cout<<"\nFILE DOESNOT EXIST.";
  getch();
  return;
 }
 bank b;
 float amount;
 int ans,flag=1;//false
 char reply,a[20];
 while(f1.read((char*)&b,sizeof(b)))
 {
  cout<<"\nENTER YOUR ACCOUNT NUMBER: ";
  cin>>a;
  int c=strcmp(a,acno);
  if(c==0)
  {
   flag=0;//true
   char fname[50];
   strcpy(fname,b.uname);
   ifstream f2(fname);
   if(!f2)
   {
    cout<<"\nFILE DOESNOT EXIST.";
    getch();
    return;
   }
   do
   {
    char line[100];
    cout<<"\nENTER YOUR TRANSACTION STATEMENT(TO AND REASON): ";
    f2.getline(line,100,'\n');
    cout<<"\nFOR WITHDRAW OF MONEY ENTER 1.";
    cout<<"\nFOR DEPOSIT OF MONEY ENTER 2.";
    cin>>ans;
    switch(ans)
    {
     case 1 ://withdraw
	     cout<<"\nENTER THE AMOUNT: ";
	     cin>>amount;
	     b.balance-=amount;
	     long loc=f1.tellg()-sizeof(b);
	     f1.seekg(loc,ios::beg);
	     f1.write((char*)&b,sizeof(b));
	     break;

     case 2 ://deposit
	     cout<<"\nENTER THE AMOUNT: ";
	     cin>>amount;
	     b.balance+=amount;
	     loc=f1.tellg()-sizeof(b);
	     f1.seekg(loc,ios::beg);
	     f1.write((char*)&b,sizeof(b));
	     break;

     default:cout<<"\nENTER VALID VALUE.";
    }
    cout<<"\nTO ADD ANOTHER TRANSACTION STATEMENT ENTER Y OR y: ";
    cin>>reply;
   }while(toupper(reply)=='Y');
  }
  if(flag==1)
   cout<<"\nRECORD NOT FOUND.";
 }
 f1.close();
}


//Fund Transfer
void fd()
{
 ofstream f("temp.dat",ios::binary);
 ifstream f1("bank.dat",ios::binary);
 if(!f1)
 {
  cout<<"\nFILE DOESNOT EXIST.";
  getch();
  return;
 }
 if(!f)
 {
  cout<<"\nFILE DOESNOT EXIST.";
  getch();
  return;
 }
 bank b;
 int flag=1,ch;
 char a[20];
 float amount;
 while(f1.read((char*)&b,sizeof(b)))
 {
  cout<<"\nENTER YOUR ACCOUNT NUMBER: ";
  cin>>a;
  int c=strcmp(a,b.acno);
  if(c==0)
  {
   flag=0;//true
   char fname[50],line[100];
   strcpy(fname,b.uname);
   ifstream f2(fname);
   if(!f2)
   {
    cout<<"\nNO TRANSACTION.";
    getch();
    return;
   }
   cout<<"\nENTER YOUR FD AMOUNT: ";
   cin>>amount;
   cout<<"\nENTER YOUR TRANSACTION STATEMENT: ";
   f2.getline(line,100,'\n');
   b.balance-=amount;
   cout<<"\nSNO.\tTIME PERIOD\tINTEREST";
   cout<<"\n 1. \t  1 year   \t   6.50%";
   cout<<"\n 2. \t  2 years  \t   6.50%";
   cout<<"\n 3. \t  3 years  \t   6.25%";
   cout<<"\n 4. \t  4 years  \t   6.25%";
   cout<<"\n 5. \t  5 years  \t   6.00%";
   cout<<"\nENTER YOUR CHOICE: ";
   cin>>ch;
   switch(ch)
   {
    case 1 :amount+=amount*6.5;
	    break;

    case 2 :amount+=amount*6.5;
	    break;

    case 3 :amount+=amount*6.25;
	    break;

    case 4 :amount+=amount*6.25;
	    break;

    case 5 :amount+=amount*6;
	    break;

    default:cout<<"\nENTER YOUR VALID CHOICE.";
   }
   cout<<"\nYOUR MATURE AMOUNT: "<<amount;
  }
  f.write((char*)&b,sizeof(b));
 }
 if(flag==1)
  cout<<"\nRECORD NOT FOUND.";
 else
 {
  remove("bank.dat");
  rename("temp.dat","bank.dat");
 }
 f1.close();
 f.close();
}

//BILL PAYMENT
void bpay()
{
 ofstream f("temp.dat",ios::binary);
 ifstream f1("bank.dat",ios::binary);
 if(!f1)
 {
  cout<<"\nFILE DOESNOT EXIST.";
  getch();
  return;
 }
 if(!f)
 {
  cout<<"\nFILE DOESNOT EXIST.";
  getch();
  return;
 }
 bank b;
 int flag=1,ch;
 char a[20];
 float amount;
 while(f1.read((char*)&b,sizeof(b)))
 {
  cout<<"\nENTER YOUR ACCOUNT NUMBER: ";
  cin>>a;
  int c=strcmp(a,b.acno);
  if(c==0)
  {
   flag=0;//true
   char fname[50],line[100];
   strcpy(fname,b.uname);
   ifstream f2(fname);
   if(!f2)
   {
    cout<<"\nNO TRANSACTION.";
    getch();
    return;
   }
   cout<<"\nENTER YOUR AMOUNT: ";
   cin>>amount;
   cout<<"\nENTER YOUR TRANSACTION STATEMENT: ";
   f2.getline(line,100,'\n');
   b.balance-=amount;
  }
  f.write((char*)&b,sizeof(b));
 }
 if(flag==1)
  cout<<"\nRECORD NOT FOUND.";
 else
 {
  remove("bank.dat");
  rename("temp.dat","bank.dat");
 }
 f1.close();
 f.close();
}

//EDIT PROFILE
void profile_pno()
{
 ofstream f("temp.dat",ios::binary);
 ifstream f1("bank.dat",ios::binary);
 if(!f1)
 {
  cout<<"\nFILE DOESNOT EXIST.";
  getch();
  return;
 }
 if(!f)
 {
  cout<<"\nFILE DOESNOT EXIST.";
  getch();
  return;
 }
 bank b;
 int flag=1,ch;
 char a[20];
 while(f1.read((char*)&b,sizeof(b)))
 {
  cout<<"\nENTER YOUR ACCOUNT NUMBER: ";
  cin>>a;
  int c=strcmp(a,b.acno);
  if(c==0)
  {
   flag=0;//true
   cout<<"\nENTER THE NEW PHONE NUMBER: ";
   cin>>b.pno;
  }
  f.write((char*)&b,sizeof(b));
 }
 if(flag==1)
  cout<<"\nRECORD NOT FOUND.";
 else
 {
  remove("bank.dat");
  rename("temp.dat","bank.dat");
 }
 f1.close();
 f.close();
}

void profile_pno()
{
 ofstream f("temp.dat",ios::binary);
 ifstream f1("bank.dat",ios::binary);
 if(!f1)
 {
  cout<<"\nFILE DOESNOT EXIST.";
  getch();
  return;
 }
 if(!f)
 {
  cout<<"\nFILE DOESNOT EXIST.";
  getch();
  return;
 }
 bank b;
 int flag=1,ch;
 char a[20];
 while(f1.read((char*)&b,sizeof(b)))
 {
  cout<<"\nENTER YOUR ACCOUNT NUMBER: ";
  cin>>a;
  int c=strcmp(a,b.acno);
  if(c==0)
  {
   flag=0;//true
   cout<<"\nENTER THE NEW EMAIL ID: ";
   cin>>b.email;
  }
  f.write((char*)&b,sizeof(b));
 }
 if(flag==1)
  cout<<"\nRECORD NOT FOUND.";
 else
 {
  remove("bank.dat");
  rename("temp.dat","bank.dat");
 }
 f1.close();
 f.close();
}

//display transactions
void disp()
{
 ifstream f1("bank.dat",ios::binary);
 if(!f1)
 {
  cout<<"\nFILE DOESNOT EXIST.";
  getch();
  return;
 }
 bank b;
 int flag=1;
 char a[20];
 while(f1.read((char*)&b,sizeof(b)))
 {
  cout<<"\nENTER YOUR ACCOUNT NUMBER: ";
  cin>>a;
  int c=strcmp(a,b.acno);
  if(c==0)
  {
   flag=0;//true
   char fname[50];
   strcpy(fname,b.uname);
   ifstream f2(fname);
   if(!f2)
   {
    cout<<"\nNO TRANSACTION.";
    getch();
    return;
   }
   while(f2)
   {
    char line[100];
    cout<<"\nTRANSACTION: ";
    f2>>line;
    cout<<'\n'<<line;
   }
  }
  if(flag==1)
   cout<<"\nRECORD NOT FOUND.";
 }
 f1.close();
}

//main
void main()
{
 int ch1;

  clrscr();
  fstream f("bank.dat",ios::binary||ios::in||ios::out);
  if(!f)
  {
   cout<<"\n File does not exist.";
   getch(); return;
  }

  bank b;
  input();
  do
  {
  clrscr();
  //Main Menu
  cout<<setw(35)<<"HS BANKING";
  cout<<'\n'<<setw(35)<<"HOME PAGE";
  cout<<"\n\n 0. Exit.";
  cout<<"\n 1. Login.";
  cout<<"\n 2. New User.";
  cout<<"\n 3. New Password.";
  cout<<"\n ENTER YOUR CHOICE: ";
  cin>>ch1;

  switch (ch1)
  {
   case 0 : exit(0);
	    break;
   case 1 : //Login
	    clrscr();
	    cout<<setw(35)<<"LOGIN PAGE";
	    //login page menu
	    int x, ctr=0;
	    do
	    {
	     x=check();
	     if(x!=-1)
	      break;
	     else
	      cout<<"\n Invalid Username or Passward. Please Try again.";
	      cout<<++ctr;
	     }while(ctr<=3);//it will ask to enter the passward 3 times and then exit itself

	    if(x!=-1)//x stores the location of the user.
	    {
	     do
	     {
	      clrscr();
	      cout<<"\n"<<setw(35)<<" User Page";

	       f.seekg(x,ios::beg);//to access that users info
	       //display ony this user's info

	       //User Page Menu
	       int ch2;
	       cout<<"\n\n\n 0. back";
	       cout<<"\n 1. Transaction (Input)";
	       cout<<"\n 2. Transaction (output)";
	       cout<<"\n 3. Fixed Deposit (FD)";
	       cout<<"\n 4. Edit Profile";
	       cout<<"\n 5. Delete Profile";
	       cout<<"\n\n Enter Your Choice: ";
	       cin>>ch2;

	      switch(ch2)
	      {
	       case 0 : break;
	       case 1 : //Transaction (input)
			b.trans();
			break;
	       case 2 : //Transaction (output)
			cout<<"\n Under Construction.";
			break;
	       case 3 : //FD
			break;
	       case 4 : //Edit Profile
			break;
	       case 5 : //Delete Profile
			Delete(b.acno);
			break;
	       default : cout<<"\n ENTER VALID CHOICE.";
	      }
	      getch();
	      break;
	     }while(1);
	    }

	    else
	     cout<<"\n You have already tried 3 times. Try again later.";
	    break;

   case 2 : //New User
	    append();
	    break;
   case 3 : //New Passward
	    fpass();
	    break;
   default : cout<<"\n Enter A Valid Choice.";
  }
  getch();
 }while(1);
}
