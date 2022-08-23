
//***************************************************************************
//HEADER FILES USED IN PROJECT :
//***************************************************************************

#include<fstream.h>
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<iomanip.h>

//***************************************************************************
//CLASS USED IN PROJECT :
//***************************************************************************

class book
{
 char bno[6] ; //Book number
 char bname[50] ; //Book name
 char aname[20] ; //Author name

 public:

void create_book()
 {
  cout<<"New Book Entry :"<<endl<<endl;
  cout<<"Enter The Book No. :"<<endl;
  cin>>bno;
  cout<<"Enter The Name Of The Book :"<<endl;
  gets(bname);
  cout<<"Enter The Author's Name :"<<endl;
  gets(aname);
  cout<<"New Book Entry Created ! "<<endl;
 }

void show_book()
 {
  cout<<"Book No. : "<<bno<<endl;
  cout<<"Book Name : ";
  puts(bname);
  cout<<endl;
  cout<<"Author Name : ";
  puts(aname);
  cout<<endl;
 }

void modify_book()
 {
  cout<<"Book No. : "<<bno<<endl;
  cout<<"Modified Book Name : ";
  gets(bname);
  cout<<"Modified Author Name : ";
  gets(aname);
 }

 char*retbno()
 {
  return bno;
 }

void report()
 {
  cout<<bno<<setw(30)<<bname<<setw(30)<<aname<<endl;
 }

}; //End of first class

class student
{
 char stuid[6]; //Student ID number
 char name[20]; //Student name
 char stbno[6]; //Book no. of the book(s) issued by the student
 int token; //Number of book(s) issued by the student

 public:

void create_student()
 {
  clrscr();
  cout<<"New Student Entry :"<<endl;
  cout<<"Enter The Student ID :"<<endl;
  cin>>stuid;
  cout<<"Enter The Name Of The Student :"<<endl;
  gets(name);
  token=0;
  stbno[0]='/0';
  cout<<"Student Record Created !"<<endl;
 }

void show_student()
 {
  cout<<"Student ID : "<<stuid;
  cout<<" Student name : ";
  puts(name);
  cout<<"Number of books issued : "<<token;
  if(token==1)
  cout<<"Book No. : "<<stbno;
 }

void modify_student()
 {
  cout<<"Student ID : "<<stuid;
  cout<<"Modified Student Name : ";
  gets(name);
 }

char*retstuid()
 {
  return stuid;
 }

char*retstbno()
 {
  return stbno;
 }

int rettoken()
 {
  return token;
 }

void addtoken()
 {
  token=1;
 }

void resettoken()
 {
  token=0;
 }

void getsbno(char t[])
 {
  strcpy(stbno,t);
 }

void report()
 {
  cout<<"\t"<<stuid<<setw(20)<<name<<setw(10)<<token<<endl;
 }

}; //End of second class

//***************************************************************************
//Global Declaration For Stream Object , Object
//***************************************************************************

fstream fio , fio1;
book bk;
student st;

//***************************************************************************
//Function to write in the data file
//***************************************************************************

void write_book()
 {
  char ch;
  fio.open ("BOOK.dat",ios::out|ios::app);
  do
  {
   clrscr();
   bk.create_book();
   fio.write((char*)&bk,sizeof(book));
   cout<<"Want to add more records ? (y/n) "<<endl;
   cin>>ch;
  } while (ch=='y'||ch=='Y');
  fio.close();
 }

void write_student()
 {
  char ch;
  fio.open ("STUDENT.dat",ios::out|ios::app);
  do
  {
   clrscr();
   st.create_student();
   fio.write((char*)&st,sizeof(student));
   cout<<"Want to add more records ? (y/n) "<<endl;
   cin>>ch;
  } while (ch=='y'||ch=='Y');
  fio.close();
 }

//***************************************************************************
//Function to read a specific record from the file
//***************************************************************************
void display_spb(char n[])
{
 cout<<"Book Details"<<endl;
 int flag=0;
 fio.open("BOOK.dat" , ios::in);
 while(fio.read((char*)&bk ,sizeof(book)))
  {
   if(strcmpi(bk.retbno() , n )==0)
    {
     bk.show_book();
     flag=1;
    }
  }
fio.close();
if (flag==0)
cout<<"Book does not exist !" ;
getch();
}

void display_sps(char n[])
 {
  cout<<"Student Details :"<<endl;
  int flag=0;
  fio.open ("STUDENT.dat",ios::in);
  while (fio.read((char*)&st , sizeof(student)))
   {
    if (strcmpi(st.retstuid(),n)==0)
     {
      st.show_student();
      flag=1;
     }
   }
fio.close();
if(flag==0)
cout<<"Student does not exist ";
getch();
}

//***************************************************************************
//Function To Modify Record Of File
//***************************************************************************

void modify_book()
 {
  char n[6];
  int found=0;
  clrscr();
  cout<<"Modify Book Record "<<endl;
  cout<<"Enter The Book No. Of The Book :"<<endl;
  cin>>n;
  fio.open ("BOOK.dat" , ios::in | ios::out);
  while (fio.read ((char*)&bk,sizeof(book)) && found==0)
   {
    if (strcmpi(bk.retbno(),n)==0)
     {
      bk.show_book();
      cout<<"Enter New Details Of The Book :"<<endl;
      bk.modify_book();
      int pos = -1*sizeof(bk);
      fio.seekp (pos,ios::cur);
      fio.write((char*)&bk,sizeof (book));
      cout<<"Record Updated !!";
      found=1;
     }
   }
   fio.close();
   if (found==0)
   cout<<"Record Not Found";
   getch();
 }

void modify_student()
{
  char n[6];
  int found=0;
  clrscr();
  cout<<"Modify Student Record "<<endl;
  cout<<"Enter The Student ID :"<<endl;
  cin>>n;
  fio.open ("STUDENT.dat" , ios::in | ios::out);
  while (fio.read ((char*)&st,sizeof(student)) && found==0)
   {
    if (strcmpi(st.retstuid(),n)==0)
     {
      st.show_student();
      cout<<"Enter New Details Of The Student :"<<endl;
      st.modify_student();
      int pos = -1*sizeof(st);
      fio.seekp (pos,ios::cur);
      fio.write((char*)&st,sizeof (student));
      cout<<"Record Updated !!";
      found=1;
     }
   }
   fio.close();
   if (found==0)
   cout<<"Record Not Found";
   getch();
 }

//***************************************************************************
//Function To Delete Record From File
//***************************************************************************

void delete_student()
 {
  char n[6];
  int flag=0;
  clrscr();
  cout<<"Delete Student:"<<endl;
  cout<<"Enter The Student ID Of The Student You Want To Delete :"<<endl;
  cin>>n;
  fio.open("STUDENT.dat" , ios::in | ios::out);
  fstream fio2;
  fio2.open("TEMP.dat", ios::out ) ;
  fio.seekg ( 0 , ios::beg);
  while (fio.read((char*)&st,sizeof(student)))
   {
    if(strcmpi(st.retstuid() , n) !=0)
    fio2.write((char*)&st,sizeof(student));
    else
    flag=1;
   }
  fio2.close();
  fio.close();
  remove("STUDENT.dat");
  rename("TEMP.dat","STUDENT.dat");
  if (flag==1)
  cout<<"Record Deleted ! "<<endl;
  else
  cout<<"Record Not Found ! "<<endl;
  getch();
 }

void delete_book()
 {
  char n[6];
  clrscr();
  cout<<"Delete Book:"<<endl;
  cout<<"Enter The Book No. Of The Book You Want To Delete :"<<endl;
  cin>>n;
  fio.open("BOOK.dat" , ios::in | ios::out);
  fstream fio2;
  fio2.open("TEMP.dat", ios::out ) ;
  fio.seekg ( 0 , ios::beg);
  while (fio.read((char*)&bk,sizeof(book)))
   {
    if(strcmpi(bk.retbno() , n ) !=0)
    {
     fio2.write((char*)&bk,sizeof(book));
    }
   }
  fio2.close();
  fio.close();
  remove("BOOK.dat");
  rename("TEMP.dat","BOOK.dat");
  cout<<"Record Deleted ! "<<endl;
  getch();
 }

 //**************************************************************************
 //Function To Display All Students List
 //**************************************************************************

 void display_alls()
  {
   clrscr();
   fio.open("STUDENT.dat" , ios::in);
   if (!fio)
    {
     cout<<"ERROR ! "<<endl;
     getch();
     return;
    }
   cout<<"Student List :"<<endl;
   cout<<"=================================================================="<<endl ;
   cout<<"Student ID:"<<setw(10) <<"Name"<<setw(20)<<"Book Issued"<<endl;
   cout<<"=================================================================="<<endl;

   while(fio.read((char*)&st,sizeof(student)))
    {
     st.report();
    }
  fio.close();
  getch();
 }

 //**************************************************************************
 //Function To Display All Books List
 //**************************************************************************

 void display_allb()
  {
   clrscr();
   fio.open("BOOK.dat" , ios::in);
   if (!fio)
    {
     cout<<"ERROR ! "<<endl;
     getch();
     return;
    }
   cout<<"Book List :"<<endl;
   cout<<"=================================================================="<<endl;
   cout<<"Book No:"<<setw(20) <<"Book Name"<<setw(25)<<"Author"<<endl;
   cout<<"=================================================================="<<endl;

   while(fio.read((char*)&bk,sizeof(book)))
    {
     bk.report();
    }
  fio.close();
  getch();
 }

 //**************************************************************************
 //Function To Issue Book
 //**************************************************************************

void book_issue()
 {
  char sn[6] , bn[6] ; //admission no. and book no.
  int found=0 , flag=0 ;
  clrscr();
  cout<<"Book Issue" <<endl;
  cout<<"Enter Student ID :"<<endl;
  cin>>sn;
  fio.open ("STUDENT.dat" ,ios::in | ios::out);
  fio1.open ("BOOK.dat" , ios::in | ios::out);
  while (fio.read((char*)&st , sizeof(student)) && found==0)
  {
   if (strcmpi (st.retstuid() , sn)==0 )
    {
     found=1;
     if (st.rettoken()==0)
      {
       cout<<"Enter Book Number :"<<endl;
       cin>>bn;
       while (fio1.read ((char*)&bk , sizeof(book))&&flag==0)
	{
	 if (strcmpi(bk.retbno(),bn)==0)
	  {
	   bk.show_book();
	   flag=1;
	   st.addtoken();
	   st.getsbno (bk.retbno());
	   int pos= -1*sizeof (st) ;
	   fio.seekp (pos,ios::cur);
	   fio.write((char*)&st, sizeof (student));
	   cout<<"Book issued successfully ! "<<endl;
	   cout<<"Please Note : The date of issue must be mentioned at the backside of your book";
	   cout<<" along with the librarian's signature . The book must be returned within 15 days";
	   cout<<" of issue or a fine of $1 for each day after the 15th day will be charged" ;
	  }

	}
      if (flag==0)
      cout<<"Book does not exist ! ";
      }
     else
     cout<<"You have not returned the last book !";
    }
  }
  if (found==0)
  cout<<"Student record doesnt exist !";
  getch();
  fio.close();
  fio1.close();
 }
//***************************************************************************
//Function To Deposit Book
//***************************************************************************

void book_deposit()
 {
  char sn[6] , bn[6] ;
  int found = 0 , flag = 0 , day , fine ;
  clrscr();
  cout<<"Book Deposit"<<endl;
  cout<<"Enter The Student ID :"<<endl;
  cin>>sn;
  fio.open ("STUDENT.dat" , ios::in | ios::out );
  fio1.open ("BOOK.dat" , ios::in | ios::out);
  while (fio.read((char*)& st , sizeof (student))&& found==0)
   {
    if (strcmpi(st.retstuid() , sn )== 0)
     {
      found=1;
      if(st.rettoken()==1)
       {
	while (fio1.read((char*)& bk , sizeof(book))&&flag==0 )
	 {
	  if (strcmpi(bk.retbno() , st.retstbno ())==0)
	   {
	    bk.show_book();
	    flag=1;
	    cout<<"Enter time period if issue :"<<endl;
	    cin>>day;
	    if (day>15)
	     {
	      fine=(day-15)*1;
	      cout<<"Total fine to be deposited: "<<"$"<<fine<<endl;
	     }
	    st.resettoken();
	    int pos=-1*sizeof (st) ;
	    fio.seekp(pos,ios::cur);
	    fio.write((char*)&st, sizeof(student));
	    cout<<"Book deposited successfully !"<<endl;
	   }
	 }
	if (flag==0)
	cout<<"Book does not exist "<<endl;
       }
      else
      cout<<"No book issued , please check !"<<endl;
     }
   }
  if (found==0)
  cout<<"Student record does not exist ! "<<endl;
  getch();
  fio.close();
  fio1.close();
 }

//***************************************************************************
//Introduction Function
//***************************************************************************

void intro()
 {
  clrscr();
  cout<<"LIBRARY MANAGEMENT SYSTEM PROTOTYPE"<<endl;
  cout<<
  "Made By: Rishita Kar"<<endl;
  getch();
 }

//***************************************************************************
//Administrator Menu Function
//***************************************************************************

void admin_menu()
 {
  clrscr();
  int ch2;
  cout<<"\t ADMINISTRATOR MENU "<<endl;
  cout<<"1.Create Student Record"<<endl;
  cout<<"2.Display All Student Records"<<endl;
  cout<<"3.Display Specific Student Record"<<endl;
  cout<<"4.Modify Student Record"<<endl;
  cout<<"5.Delete Student Record"<<endl;
  cout<<"6.Create Book"<<endl;
  cout<<"7.Display All Books"<<endl;
  cout<<"8.Display Specific Book"<<endl;
  cout<<"9.Modify Book"<<endl;
  cout<<"10.Delete Book"<<endl;
  cout<<"11.BACK TO MAIN MENU"<<endl;
  cout<<endl<<"Enter Your Choice (1-11) :"<<endl;
  cin>>ch2;
  switch(ch2)
   {
    case 1:
    clrscr();
    write_student();
    break;

    case 2:
    display_alls();
    break;

    case 3:
    char num[6];
    clrscr();
    cout<<"Please enter student ID"<<endl;
    cin>>num;
    display_sps(num);
    break;

    case 4:
    modify_student();
    break;

    case 5:
    delete_student();
    break;

    case 6:
    clrscr();
    write_book();
    break;

    case 7:
    display_allb();
    break;

    case 8:
    {char num[6];
    clrscr();
    cout<<"Enter the book number:"<<endl;
    cin>>num;
    display_spb(num);
    break;}

    case 9:
    modify_book();
    break;

    case 10:
    delete_book();
    break;

    case 11:
    return;

    default:
    cout<<"\a" ;

   }
  admin_menu();
 }

//***************************************************************************
//The Main Function Of The Program
//***************************************************************************

void main()
 {
  char ch;
  intro();
  do
   {
    clrscr();
    cout<<"\t MAIN MENU"<<endl;
    cout<<"1.Book Issue"<<endl;
    cout<<"2.Book Deposit"<<endl;
    cout<<"3.Administrator Menu"<<endl;
    cout<<"4.Exit"<<endl;
    cout<<endl<<"Enter Your Choice (1-4) "<<endl;
    ch=getche();
    switch(ch)
     {
      case '1':
      clrscr();
      book_issue();
      break;

      case '2':
      book_deposit();
      break;

      case '3':
      admin_menu();
      break;

      case '4':
      exit(0);

      default:
      cout<<"\a";

     }
   }
  while (ch!='4');
}

//***************************************************************************
//END OF PROJECT
//***************************************************************************
























