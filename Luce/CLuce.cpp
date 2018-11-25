#include "CLuce.h"


CLuce::CLuce()
{
	frame = new finestra(&accesa,getAttivo());
	initBluetooth();
	setLuce("bianco", 100);
}

CLuce::CLuce(String colore, int intensita)
{
	frame = new finestra(&accesa, getAttivo());
	initBluetooth();
	setLuce(colore, intensita);
}

CLuce::CLuce(String colore)
{
	frame = new finestra(&accesa, getAttivo());
	initBluetooth();
	setLuce(colore, 100);
}


CLuce::~CLuce()
{
	delete frame;
}

void CLuce::accendi()
{
	ir.accendi();
	accesa = true;
}

void CLuce::spegni()
{
	ir.spegni();
	accesa = false;
}

void CLuce::initBluetooth()
{
	pinMode(9, OUTPUT);  // questo pin � connesso al relativo pin 34 (pin KEY) del HC-05 che portato a HIGH permette di passare alla modalit� AT
	digitalWrite(9, HIGH);
	Serial.println("Inserire i comandi AT:");
	bt.begin(38400);  // Velocit� di default del modulo HC-05
}

void CLuce::setLuce(String colore, int intensita)
{
	accendi();
	setColore(colore);
	this->getAttivo()->setIntensita(20);
	setIntensita(intensita);
}

void CLuce::setColore(String colore)
{
	Serial.println("colore: " + colore);
	if (this->getAttivo()->getColore() == colore)
		return;
	this->getAttivo()->disattiva();
	resetDisplay();
	if (colore.startsWith("rosso")) {
		this->colori[ROSSO].attiva();
		ir.rosso();
	}
	else if (colore.startsWith("giallo")) {
		this->colori[GIALLO].attiva();
		ir.giallo();
	}
	else if (colore == "verde") {
		ir.verde();
		this->colori[VERDE].attiva();
	}
	else if (colore == "blu") {
		ir.blu();
		this->colori[BLU].attiva();
	}
	else if (colore == "arancione") {

		ir.arancione();
		this->colori[ARANCIONE].attiva();
	}
	else if (colore == "azzurro") {

		ir.azzurro();
		this->colori[AZZURRO].attiva();
	}
	else if (colore == "bianco") {

		ir.bianco();
		this->colori[BIANCO].attiva();
	}
	else if (colore == "giallancione") {

		ir.giallancione();
		this->colori[GIALLO_ARANCIO].attiva();
	}
	else if (colore == "rosa") {

		ir.rosa();
		this->colori[ROSA].attiva();
	}
	else if (colore == "rgbLento") {

		ir.RGBlento();
		this->colori[multicolorLento].attiva();
	}
	else if (colore == "rgbVeloce") {

		ir.RGBveloce();
		this->colori[multicolorVeloce].attiva();
	}
	else return;
	Serial.println(colore);
}

void CLuce::setIntensita(int intensita)
{
	intensita /= 5;			//trasforma da % a 1-20
	Serial.println("Intensita: " + String(intensita));
	if (intensita >= 0 && intensita <= 100)
	{
		int diff = this->getAttivo()->getIntensita() - intensita;
		if (diff >= 0)
			for (int i = 0; i < diff; i++) {
				ir.diminuisciIntensita();
				delay(50);
			}
		else
		{
			for (int i = diff; i < 0; i++) {
				ir.aumentaIntensita();
				delay(50);
			}
		}
		this->getAttivo()->setIntensita(intensita);
		resetDisplay();
	}
}

String CLuce::getColore()
{
	return getAttivo()->getColore();
}

int CLuce::getIntensita()
{
	return getAttivo()->getIntensita() * 5; //trasforma in %
}

CColore* CLuce::getAttivo()
{
	for (int i = 0; i < NUMCOLORI;i++) {
		if (colori[i].isAttiva())
			return colori;
	}
	return nullptr;
}

void CLuce::checkBluetooth()
{
	bool isColore = true;
	String letto = bt.leggi();
	if (letto != "")
	{
		for (int i = 0; i < letto.length(); i++)
			if (letto[i] >= '0'&&letto[i] <= '9')
				isColore = false;
		if (isColore)
			if (letto == "on")
				accendi();
			else if (letto == "off")
				spegni();
			else
			setColore(letto);
		else
			setIntensita(letto.toInt());
	}
	//if (letto != "")
	//{
	//	setColore(letto);
	//	setIntensita(intens);
	//}

}

void CLuce::checkDisplay()
{
	int ris = frame->getTab()->checkBottoni();
	if (ris >= 0 && ris <= 3)
		frame->setTab(ris);
	else if (ris == 10)	//pulsante luce premuto
		if (accesa) {
			spegni();
			bt.invia("spegni");
		}
		else {
			accendi();
			bt.invia("accendi");
		}
	else if (ris == 20)
	{
		setIntensita(getIntensita() - 5);
		bt.invia((String)getIntensita());
	}
	else if (ris == 30)
	{
		//setIntensita(getIntensita() + 5);
		//bt.invia((String)getIntensita());
	}
}

void CLuce::resetDisplay()
{
	delete frame;
	frame = new finestra(&accesa, getAttivo());
}