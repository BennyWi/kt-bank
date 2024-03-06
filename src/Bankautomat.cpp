#include <iostream>
#include "Bankautomat.h"
#include "Bankkunde.h"



Bankautomat::Bankautomat(double startBetrag)
{
	this->bargeld = startBetrag; 
}


int Bankautomat::auszahlung(girokonto* girokonto, kreditkonto* kreditkonto, int auszahlungsBetrag) {    

  // Kreditkarte
  if (!girokonto) {
    if (!kreditkonto->getKreditkarte()->kartenCheck()) {
      std::cout << "Diese Kreditkarte oder der PIN ist ung�ltig. Der Vorgang wird abgebrochen!" << std::endl;
      return -1;
    }

    if (!kreditkonto->getGesperrt()) {
      std::cout << "Diese Kreditkarte ist gesperrt. Der Vorgang wird abgebrochen!" << std::endl;
      return -1;
    }

    if ((double)auszahlungsBetrag > this->bargeld) {
      std::cout << "Sie m�chten mehr Geld abheben, als momentan im Bankautomat vorhanden ist. Sie k�nnen momentan maximal: " << getBargeld() << "Euro abheben."
                << std::endl;
      return -1;
    }

    if (kreditkonto->getKontostand() < auszahlungsBetrag) {
      std::cout << "Es ist nicht genug Geld auf dem Konto! Sie k�nnen momentan maximal :" << kreditkonto.getKontostand() << std::endl;
      return -1;
    }

    this->bargeld -= auszahlungsBetrag;

    kreditkonto->setKontoStand(kreditkonto->getKontoStand() - auszahlungsBetrag);
    std::cout << auszahlungsBetrag << " Euro wurden abgehoben!" << std::endl;

    return auszahlungsBetrag;
  }

  // Girokonto

  if (!girokonto->getGirokarte()->kartenCheck()) {
    std::cout << "Diese Girokarte oder der PIN ist ung�ltig. Der Vorgang wird abgebrochen!" << std::endl;
    return -1;
  }

  if (!girokonto->getGesperrt()) {
    std::cout << "Diese Girokarte ist gesperrt. Der Vorgang wird abgebrochen!" << std::endl;
    return -1;
  }

  if ((double)auszahlungsBetrag > this->bargeld) {
    std::cout << "Sie m�chten mehr Geld abheben, als momentan im Bankautomat vorhanden ist. Sie k�nnen momentan maximal: " << getBargeld() << "Euro abheben."
              << std::endl;
    return -1;
  }

  if (girokonto->getKontoStand() < auszahlungsBetrag) {
    std::cout << "Es ist nicht genug Geld auf dem Konto! Sie k�nnen momentan maximal :" << girokonto.getKontostand() << std::endl;
    return -1;
  }

  this->bargeld -= auszahlungsBetrag;

  girokonto->setKontoStand(girokonto->getKontoStand() - auszahlungsBetrag);
  std::cout << auszahlungsBetrag << " Euro wurden abgehoben!" << std::endl;

  return auszahlungsBetrag;

  // muss noch was gemacht werden, f�r den Fall: !Kredikarte und !Girokarte
  // std::cout << "Sie nutzen keine genehemigte Karte" << std::endl;
  //  return -1;
}

    
	
// Getter und Setter f�r Bargeld
double Bankautomat::getBargeld() 
{
  return this->bargeld;
}


void Bankautomat::setBargeld(double betrag) 
{
  this->bargeld += betrag; 
}

// Getter und Setter f�r AutomatID
unsigned int Bankautomat::getAutomatID() 
{
  return this->automatID;
}

void Bankautomat::setAutomatID(unsigned int nummer) 
{ 
    automatID = nummer;
        
}
