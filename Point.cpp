#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

class point
{
		float x, y;
		char color[30];
		point* suiv;
		point* prec;
	public:
		point(float a=1, float b=1, char  *c="") {x=a; y=b; strcpy(color,c); suiv=NULL; prec=NULL;}
		friend ostream & operator<<(ostream &o, point &p);
		friend class liste;
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

class liste
{
    point *debut;
    point *courant;

public:
    liste(){ debut=NULL; courant=debut; }
    ~liste(){ }
    void ajouter(float a, float b, char* c);
    void supprimer(float a, float b);
    void modifier(float a, float b);
    void visualiser(int pos);
    void afficher();

};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void liste::ajouter(float a, float b, char* c)
{
    point* p=new point(a,b,c);
    if(debut==NULL)
        debut=p;
    else{
        courant=debut;
        while(courant->suiv!=NULL && (courant->x!=a && courant->y!=b)){
            courant=courant->suiv;
        }
        if (courant->x==a && courant->y==b )
            {cout<<"Un point ne peut pas avoir plusieurs couleurs."<<endl;}
        else {courant->suiv=p;
        p->prec=courant;}

    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void liste::modifier(float a, float b)
{
    if(debut==NULL)
       cout << "La liste est vide." << endl;
    else
    {
        courant = debut;
        char couleur[30];
        while (courant!=NULL && (courant->x!=a || courant->y!=b))
        {courant=courant->suiv;}

    if (courant==NULL)
            cout << "Point inexistant." << endl;

    else{
            cout << "Entrez la nouvelle couleur du point que vous souhaitez modifier : ";getchar(); fgets(couleur,30,stdin);
            strcpy(courant->color,couleur);
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void liste::supprimer(float a, float b)
{
    if(debut==NULL)
        cout<<"Liste vide."<<endl;
    else
    {
        courant=debut;
        while(courant!=NULL && (courant->x!=a || courant->y!=b) ){
            courant=courant->suiv;
        }
        if (courant==NULL)
            cout<<"Point inexistant." << endl;

        //Cas d'un seul point dans la liste
        if (courant->suiv==NULL && courant->prec==NULL)
            debut=NULL;

        //Cas du point étant en début de liste
        else if (courant->prec==NULL){
            debut=courant->suiv;
            courant->suiv->prec=NULL;}

        //Cas du point étant en fin de liste
        else if(courant->suiv==NULL)
            courant->prec->suiv=NULL;
        else{
            courant->prec->suiv=courant->suiv;
            courant->suiv->prec=courant->prec;
        }
         delete courant;

    }

}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void liste::visualiser(int pos)
{
    if(pos<0)
        cout<<"Erreur:Position inexistante."<<endl;
    if (debut==NULL)
        cout << "La liste est vide." << endl;
    int i=1;
    courant=debut;
    while (courant!=NULL && i<pos)
        {courant=courant->suiv;
        i++;}
    if (courant==NULL)
        cout<<"Point inexistant"<<endl;
    cout<<*courant<<endl;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void liste::afficher()
{
    if (debut==NULL)
        cout << "La liste est vide." << endl;
    courant=debut;
    while(courant!=NULL){
            cout<<*courant<<endl;
            courant=courant->suiv;
 }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

ostream & operator<<(ostream &o, point &p)
{
	o.setf(ios::left,ios::adjustfield);
	o<<"Coordonnee X du point : "; 	o.width(15); o<<p.x;
	o<<"Coordonnee Y du point : "; 	o.width(15); o<<p.y;
	o<<"De couleur :"; 		o.width(15); o<<p.color; cout<<endl;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

main()
{
    int i,pos;
    float a,b;
    char couleur[30];
    liste l;
    cout<<"*************WELCOME*************"<<endl;
    do {
                cout<<"Choisir une option :"<<endl;
                cout<<"1: Ajouter un point."<<endl;
                cout<<"2: Supprimer un point."<<endl;
                cout<<"3: Modifier un point."<<endl;
                cout<<"4: Visualiser un point."<<endl;
                cout<<"5: Visualiser toutes les elements de la liste."<<endl;
                cout<<"6: Quittez."<<endl;
                cin>>i;getchar();
                switch(i){
                case 1: {cout<<"Entrer X : "<<endl;cin>>a;
                cout<<"Entrer Y : "<<endl;cin>>b;
                cout<<"Entrer la couleur : "<<endl;getchar();fgets(couleur,30,stdin);
                l.ajouter(a,b,couleur);break;}

                case 2: {cout<<"Entrer X : "<<endl;cin>>a;
                cout<<"Entrer Y : "<<endl;cin>>b;
                l.supprimer(a,b);break;}

                case 3: {cout<<"Entrer X : "<<endl;cin>>a;
                cout<<"Entrer Y : "<<endl;cin>>b;
                l.modifier(a,b);break;}

                case 4: {cout<<"Entrer la position : "<<endl;cin>>pos;
                l.visualiser(pos);break;}

                case 5: {l.afficher();break;}

                default: break;

                }
        }while(i!=6);


}
