#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

class erreur
{
 public:
    virtual void affiche(){cout<<"Erreur !";}
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

class erreur_positive:public erreur
{
 public :
    void affiche(){cout<<"Erreur ! valeur negative ! \n";}
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

class erreur_inf:public erreur
{
     int maxi;
     public:
        erreur_inf(int ma){maxi=ma;}
        void affiche()
            {cout<<"Erreur ! valeur superieure A : "<<maxi<<endl;}
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

class erreur_sup:public erreur
{
     int mini;
     public:
        erreur_sup(int mi){mini=mi;}
        void affiche()
            {cout<<"Erreur ! valeur inferieure A : "<<mini<<endl;}
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void positive(int v)
{
    if(v<0)
     { erreur_positive *er; er=new erreur_positive; throw er;}
}
void inf(int v,int max)
{
    if(v>max)
    { erreur_inf *er; er=new erreur_inf(max); throw er;}
}
void sup(int v,int min)
{
    if(v<min)
     { erreur_sup *er; er=new erreur_sup(min); throw er;}

}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

class telephone
{
		int storage,ram,front_camera,back_camera;
		char marque[50];
		char nom[50];
		telephone* suiv;
		telephone* prec;
	public:
		telephone(int a=1, int b=1,int c=1, int d=1,char  *e="",char  *f="") {storage=a; ram=b;front_camera=c;back_camera=d;strcpy(nom,e);strcpy(marque,f); suiv=NULL; prec=NULL;}
		friend ostream & operator<<(ostream &o, telephone &t);
		friend class liste;
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

class liste
{
    telephone *debut;
    telephone *courant;

public:
    liste(){ debut=NULL; courant=debut; }
    ~liste(){ }
    void ajouter(int , int ,int ,int , char* , char* );
    void supprimer(char* , char* );
    void modifier(char* , char* );
    void visualiser(int pos);
    void afficher();

};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void liste::ajouter(int a, int b,int c,int d, char* e, char* f)
{
    telephone* t=new telephone(a,b,c,d,e,f);
    if(debut==NULL)
        debut=t;
    else{
        courant=debut;
        while(courant->suiv!=NULL && (courant->nom!=e && courant->marque!=f ) ){
            courant=courant->suiv;
        }
        if (courant->nom==e && courant->marque==f )
            cout<<"Un telephone ne peut pas avoir plusieurs specs."<<endl;
        else {courant->suiv=t;
        t->prec=courant;}

    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void liste::modifier(char *e, char *f)
{
    if(debut==NULL)
       cout << "La liste est vide." << endl;
    else
    {
        courant=debut;
        int a,b,c,d;
        while (courant!=NULL && (courant->nom==e || courant->marque==f))
        {courant=courant->suiv;}

    if (courant==NULL)
            cout << "telephone inexistant." << endl;

    else{
            cout << "Entrez la nouvelle taille de stockage : "; cin>>a;
            courant->storage=a;positive(a);inf(a,1000);sup(a,16);
            cout << "Entrez la nouvelle taille de RAM : "; cin>>b;
            courant->ram=b;positive(b);inf(b,32);sup(a,2);
            cout << "Entrez la nouvelle qualite de camera de selfie : "; cin>>c;
            courant->front_camera=c;positive(c);inf(c,200);sup(a,2);
            cout << "Entrez la nouvelle qualite de camera principale: "; cin>>d;
            courant->back_camera=d;positive(d);inf(d,64);sup(d,2);
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void liste::supprimer(char *e, char *f)
{
    if(debut==NULL)
        cout<<"Liste vide."<<endl;
    else
    {courant=debut;
        while(courant!=NULL && (courant->nom==e || courant->marque==f) ){
            courant=courant->suiv;
        }
        if (courant==NULL)
            cout<<"telephone inexistant." << endl;

        //Cas d'un seul telephone dans la liste
        if (courant->suiv==NULL && courant->prec==NULL)
            debut=NULL;

        //Cas du telephone étant en début de liste
        else if (courant->prec==NULL){
            debut=courant->suiv;
            courant->suiv->prec=NULL;}

        //Cas du telephone étant en fin de liste
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
    telephone* courant=debut;
    while (courant!=NULL && i<pos)
        {courant=courant->suiv;
        i++;}
    if (courant==NULL)
        cout<<"telephone inexistant"<<endl;
    cout<<*courant<<endl;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void liste::afficher()
{
    if (debut==NULL)
        cout << "La liste est vide." << endl;
    telephone *courant=debut;
    while(courant!=NULL){
            cout<<*courant<<endl;
            courant=courant->suiv;
 }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

ostream & operator<<(ostream &o, telephone &t)
{
	o.setf(ios::left,ios::adjustfield);
	o<<"Nom du telephone : "; 	o.width(15); o<<t.nom;cout<<endl;
	o<<"Marque du telephone : "; 	o.width(15); o<<t.marque;cout<<endl;
	o<<"De stockage :"; 		o.width(15); o<<t.storage;cout<<endl;
	o<<"De RAM :"; 		o.width(15); o<<t.ram;cout<<endl;
	o<<"De Camera de selfie :"; 		o.width(15); o<<t.front_camera;cout<<"Megapixel"<<endl;
	o<<"De Camera principale :"; 		o.width(15); o<<t.back_camera;cout<<"Megapixel"<<endl;
	 cout<<endl;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

main()
{
    int i,pos;
    int a,b,c,d;
    char e[50];
    char f[50];
    liste l;
    cout<<"*************WELCOME*************"<<endl;
    do {
                cout<<"Choisir une option :"<<endl;
                cout<<"1: Ajouter un telephone."<<endl;
                cout<<"2: Supprimer un telephone."<<endl;
                cout<<"3: Modifier un telephone."<<endl;
                cout<<"4: Visualiser un telephone."<<endl;
                cout<<"5: Visualiser toutes les elements de la liste."<<endl;
                cout<<"6: Quittez."<<endl;
                cin>>i;getchar();
                switch(i){
                case 1: {try {cout<<"Entrer le nom : "<<endl;fgets(e,50,stdin);
                cout<<"Entrer la marque : "<<endl;fgets(f,50,stdin);
                cout<<"Entrez la  taille de stockage : "<<endl; cin>>a;positive(a);inf(a,1000);sup(a,16);
                cout<<"Entrez la  taille de RAM : "<<endl; cin>>b;positive(b);inf(b,32);sup(a,2);
                cout << "Entrez la  qualite de camera de selfie : "; cin>>c;positive(c);inf(c,200);sup(a,2);
                cout << "Entrez la  qualite de camera principale : "; cin>>d;positive(d);inf(d,64);sup(d,2);
                l.ajouter(a,b,c,d,e,f);break;}
                 catch(erreur *e)
                     {
                        e->affiche(); delete e ;break;
                     }
                 catch(...)
                     {
                        cout<<"Erreur inconnue !\n";
                     }}

                case 2: {cout<<"Entrer le nom : "<<endl;cin>>e;
                cout<<"Entrer la marque : "<<endl;cin>>f;
                l.supprimer(e,f);break;}

                case 3: {try {cout<<"Entrer le nom : "<<endl;cin>>e;
                cout<<"Entrer la marque : "<<endl;cin>>f;
                l.modifier(e,f);break;}
                catch(erreur *e)
                     {
                        e->affiche(); delete e ;break;
                     }
                 catch(...)
                     {
                        cout<<"Erreur inconnue !\n";
                     }}

                case 4: {cout<<"Entrer la position : "<<endl;cin>>pos;
                l.visualiser(pos);break;}

                case 5: {l.afficher();break;}

                default: break;

                }
        }while(i!=6);


}
