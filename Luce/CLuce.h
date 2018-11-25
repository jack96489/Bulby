#pragma once
#include"MyIR.h"
#include<WString.h>
#include"CColore.h"
#define NUMCOLORI 16

//colors index
#define GIALLO_ARANCIO 0
#define VIOLA 1
#define AZZURRO 2
#define AZZURROCHIARO 3
#define GIALLO 4
#define AZZURRO_VERDE 5
#define GIALLO_VERDE 6
#define BLU_VIOLA 7
#define ROSA 8
#define AZZURRO 9
#define BLU 10
#define ROSSO 11
#define BIANCO 12
#define VERDE 13
#define ARANCIONE 14
/*
* Classe che gestisce la luce
*/
class CLuce
{
private:
	MyIR ir;
	CColore colori[NUMCOLORI];
	bool accesa;
public:
	CLuce();
	CLuce(String colore, int intensita);
	CLuce(String colore);
	~CLuce();
	void accendi();
	void spegni();
	void setLuce(String colore, int intensita);
	void setColore(String colore);
	void setIntensita(int intensita);
	String getColore();
	int getIntensita();
	CColore* getAttivo();
	bool isAccesa();
};

