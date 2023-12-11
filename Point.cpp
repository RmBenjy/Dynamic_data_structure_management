#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

class point
{
		float x, y;
		char color[30];
		point *next;
		point *previous;
	public:
		point(float a = 1, float b = 1, char  *c = "") {x = a; y = b; strcpy(color,c); next = NULL; previous = NULL;}
		friend ostream & operator<<(ostream &o, point &p);
		friend class list;
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

class list
{
    point *start;
    point *current;

public:
    list(){ start = NULL; current = start; }
    ~list(){ }
    void add_point(float a, float b, char* c);
    void modify_point(float a, float b);
    void delete_point(float a, float b);
    void show_point(int pos);
    void show();

};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void list::add_point(float a, float b, char* c)
{
    point* p = new point(a,b,c);
    if(start == NULL)
        start = p;
    else{
        current = start;
        while(current->next != NULL && (current->x != a && current->y != b)){
            current = current->next;
        }
        if (current->x == a && current->y == b )
            {cout<<"A point cannot have multiple colors."<<endl;}
        else {current->next = p;
        p->previous = current;}

    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void list::modify_point(float a, float b)
{
    if(start == NULL)
       cout << "The list is empty." << endl;
    else
    {
        current = start;
        char new_color[30];
        while (current != NULL && (current->x != a || current->y != b))
        {current = current->next;}

    if (current == NULL)
            cout << "Non-existent point." << endl;

    else{
            cout << "Enter the new color of the point you want to change : "; getchar(); fgets(new_color,30,stdin);
            strcpy(current->color, new_color);
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void list::delete_point(float a, float b)
{
    if(start == NULL)
        cout<<"Empty list."<<endl;
    else
    {
        current = start;
        while(current != NULL && (current->x != a || current->y != b) ){
            current = current->next;
        }
        if (current == NULL)
            cout<<"Non-existent point." << endl;

        // Case of a single point in the list
        if (current->next == NULL && current->previous == NULL)
            start = NULL;

        // Case of a point being at the start of the list
        else if (current->previous == NULL){
            start = current->next;
            current->next->previous = NULL;}

        // Case of a point being at the end of the list
        else if(current->next == NULL)
            current->previous->next = NULL;
        else{
            current->previous->next = current->next;
            current->next->previous = current->previous;
        }
         delete current;

    }

}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void list::show_point(int pos)
{
    if(pos<0)
        cout<<"Error: Position does not exist."<<endl;
    if (start == NULL)
        cout << "Empty list." << endl;
    int i=1;
    current = start;
    while (current != NULL && i<pos)
        {current = current->next;
        i++;}
    if (current == NULL)
        cout<<"Non-existent point."<<endl;
    cout<<*current<<endl;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void list::show()
{
    if (start == NULL)
        cout << "Empty list." << endl;
    current = start;
    while(current != NULL){
            cout<<*current<<endl;
            current = current->next;
 }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

ostream & operator<<(ostream &o, point &p)
{
	o.setf(ios::left,ios::adjustfield);
	o<<"X coordinate of the point : "; 	o.width(15); o<<p.x;
	o<<"Y coordinate of the point : "; 	o.width(15); o<<p.y;
	o<<"Color :"; 		o.width(15); o<<p.color; cout<<endl;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

main()
{
    int i,pos;
    float a,b;
    char couleur[30];
    list l;
    cout<<"*************WELCOME*************"<<endl;
    do {
               cout<<"Choose an option:"<<endl;
                 cout<<"1: Add a point."<<endl;
                 cout<<"2: Delete a point."<<endl;
                 cout<<"3: Modify a point."<<endl;
                 cout<<"4: View a point."<<endl;
                 cout<<"5: Display all elements in the list."<<endl;
                 cout<<"6: Exit."<<endl;
                cin>>i; getchar();
                switch(i){
                case 1: {cout<<"Enter X : "<<endl; cin>>a;
                cout<<"Enter Y : "<<endl; cin>>b;
                cout<<"Enter color : "<<endl; getchar(); fgets(couleur,30,stdin);
                l.add_point(a,b,couleur); break;}

                case 2: {cout<<"Enter X : "<<endl; cin>>a;
                cout<<"Enter Y : "<<endl; cin>>b;
                l.delete_point(a,b); break;}

                case 3: {cout<<"Enter X : "<<endl; cin>>a;
                cout<<"Enter Y : "<<endl; cin>>b;
                l.modify_point(a,b); break;}

                case 4: {cout<<"Enter position : "<<endl; cin>>pos;
                l.show_point(pos); break;}

                case 5: {l.show(); break;}

                default: break;

                }
        }while(i!=6);


}
