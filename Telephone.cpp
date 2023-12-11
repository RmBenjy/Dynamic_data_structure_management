#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class error
{
  public:
     virtual void print(){cout<<"Error!";}
};
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class positive_error:public error
{
  public :
     void print(){cout<<"Error! negative value! \n";}
};
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class error_inf:public error
{
      int max;
      public:
         error_inf(int ma){maxi = ma;}
         void print()
             {cout<<"Error! value greater than : "<<maxi<<endl;}
};
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class error_sup:public error
{
      int mini;
      public:
         error_sup(int mi){mini=mi;}
         void print()
             {cout<<"Error! value lower than : "<<mini<<endl;}
};
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void positive(int v)
{
     if(v<0)
      { positive_error *er; er=new positive_error; throw er;}
}

void inf(int v,int max)
{
     if(v>max)
     { error_inf *er; er=new error_inf(max); throw er;}
}

void sup(int v,int min)
{
     if(v<min)
      { error_sup *er; er=new error_sup(min); throw er;}

}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class telephone
{
int storage, ram, front_camera, back_camera;
char brand[50];
char name[50];
telephone *next;
telephone *prev;
public:
telephone(int a=1, int b=1,int c=1, int d=1,char *e="",char *f="") {storage = a; ram = b; front_camera = c; back_camera = d; strcpy(name,e); strcpy(brand,f); next = NULL; prev = NULL;}
friend ostream & operator<<(ostream &o, telephone &t);
friend class list;
};
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class list
{
     telephone *start;
     telephone *current;

public:
     list(){ start = NULL; current = start; }
     ~list(){ }
     void add_phone(int , int ,int ,int , char* , char* );
     void modify_phone(char*, char*);
     void delete_phone(char*, char*);
     void visualize(int pos);
     void display();

};
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void list::add_phone(int a, int b,int c,int d, char* e, char* f)
{
     telephone *t=new telephone(a,b,c,d,e,f);
     if(start == NULL)
         start = t;
     else{
         current = start;
         while(current->next != NULL && (current->name != e && current->brand != f ) ){
             current = current->next;
         }
         if (current->name == e && current->brand == f )
             cout << "A phone cannot have several specs." << endl;
         else {current->next =t;
         t->prec = current;}

     }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void list::modify_phone(char *e, char *f)
{
     if(start == NULL)
        cout << "The list is empty." << endl;
     else
     {
         current = start;
         int a,b,c,d;
         while (current != NULL && (current->name == e || current->brand == f))
         {current = current->next;}

     if (current == NULL)
             cout << "Non-existent phone." << endl;

     else{
             cout << "Enter the new storage size: "; cin>>a;
             current->storage = a ; positive(a); inf(a,1000); sup(a,16);
	     
             cout << "Enter the new RAM size: "; cin>>b;
             current->ram = b; positive(b); inf(b,32); sup(a,2);
	     
             cout << "Enter the new selfie camera quality: "; cin>>c;
             current->front_camera = c; positive(c); inf(c,200); sup(a,2);
	     
             cout << "Enter the new main camera quality: "; cin>>d;
             current->back_camera = d; positive(d); inf(d,64); sup(d,2);
         }
     }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void list::delete_phone(char *e, char *f)
{
     if(start == NULL)
         cout << "Empty list." << endl;
     else
     {current = start;
         while(current != NULL && (current->name == e || current->brand == f) ){
             current = current->next;
         }
         if (current == NULL)
             cout << "Non-existent phone." << endl;

         // Case of only one phone in the list
         if (current->next == NULL && current->prev == NULL)
             start = NULL;

         // Case of the telephone being at the start of the list
         else if (current->prec == NULL){
             start = current->next;
             current->next->prev = NULL;}

         // Case of the telephone being at the end of the list
         else if(current->next == NULL)
             current->prev->next = NULL;
         else{
             current->prev->next = current->next;
             current->next->prev = current->prev;
         }
          delete current;

     }

}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void list::visualize(int pos)
{
     if(pos<0)
         cout << "Error:Position does not exist." << endl;
     if (start == NULL)
         cout << "The list is empty." << endl;
     int i=1;
     phone *current=start;
     while (current != NULL && i<pos)
         {current = current->next;
         i++;}
     if (current == NULL)
         cout << "Non-existent phone." << endl;
     cout << *current << endl;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void list::display()
{
     if (start == NULL)
         cout << "The list is empty." << endl;
     phone *current = start;
     while(current != NULL){
             cout << *current << endl;
             current = current->next;
  }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ostream & operator<<(ostream &o, telephone &t)
{
o.setf(ios::left,ios::adjustfield);
o<<"Phone name: "; o.width(15); o<<t.name; cout<<endl;
o<<"Phone brand: "; o.width(15); o<<t.brand; cout<<endl;
o<<"Storage:"; o.width(15); o<<t.storage; cout<<endl;
o<<"RAM:"; o.width(15); o<<t.ram; cout<<endl;
o<<"Selfie Camera:"; o.width(15); o<<t.front_camera; cout<<"Megapixel"<<endl;
o<<"Main Camera:"; o.width(15); o<<t.back_camera; cout<<"Megapixel"<<endl;
cout<<endl;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

main()
{
     int i,pos;
     int a,b,c,d;
     char e[50];
     char f[50];
     list l;
     cout<<"*************WELCOME*************"<<endl;
     do {
                 cout<<"Choose an option:"<<endl;
                 cout<<"1: Add a phone."<<endl;
                 cout<<"2: Delete a phone."<<endl;
                 cout<<"3: Modify a phone."<<endl;
                 cout<<"4: View a phone."<<endl;
                 cout<<"5: Display all elements in the list."<<endl;
                 cout<<"6: Exit."<<endl;
                 cin>>i; getchar();
	     
                 switch(i){
                 case 1: {
			 try {cout<<"Enter name: "<<endl; fgets(e,50,stdin);
                 cout<<"Enter the brand: "<<endl; fgets(f,50,stdin);
                 cout<<"Enter the storage size: "<<endl; cin>>a; positive(a); inf(a,1000); sup(a,16);
                 cout<<"Enter the RAM size: "<<endl; cin>>b; positive(b); inf(b,32); sup(a,2);
                 cout << "Enter the selfie camera quality: "; cin>>c; positive(c); inf(c,200); sup(a,2);
                 cout << "Enter the main camera quality: "; cin>>d; positive(d); inf(d,64); sup(d,2);
                 l.add_phone(a,b,c,d,e,f); break;}
			 
                  catch(error *e)
                      {
                         e->print(); delete e ;break;
                      }
                  catch(...)
                      {
                         cout<<"Unknown error!\n";
                      }}

			 
                 case 2: {
			 cout<<"Enter name: "<<endl; cin>>e;
                 cout<<"Enter the brand: "<<endl; cin>>f;
                 l.delete_phone(e,f); break;}

			 
                 case 3: {
			 try {cout<<"Enter name: "<<endl; cin>>e;
                 cout<<"Enter the brand: "<<endl; cin>>f;
                 l.modify_phone(e,f); break;}
				 
                 catch(error *e)
                      {
                         e->print(); delete e ;break;
                      }
                  catch(...)
                      {
                         cout<<"Unknown error!\n";
                      }}

                 case 4: {cout<<"Enter position: "<<endl; cin>>pos;
                 l.visualize(pos); break;}

                 case 5: {l.display(); break;}

                 default: break;

                 }
         }while(i!=6);


}
