#include "Bankautomat.h"
#include <iostream>
#include <string>
#include <sstream>


Bankautomat::Bankautomat(double startBetrag) {
  this->bargeld = startBetrag;
}

bool Bankautomat::validierung(KartenKonto* kkonto) {

              // kredit UND giro-konto sperrcheck
  if (kkonto->isGesperrt()) {
    std::cout << "Das Konto ist gesperrt." << std::endl;
    return false;
     
  }

  // kredit und giro-karte sperrcheck
  if (kkonto->getKarte()->isGesperrt()) {
    std::cout << "Die Karte ist gesperrt." << std::endl;
    return false;
  }

  // kredit und giro-karten check
  if (!kkonto->getKarte()->checkKarte()) {
    std::cout << "Error: kartenCheck nicht erfolgreich." << std::endl;
    return false;
  }

  return true;

}

int Bankautomat::auszahlung(KartenKonto* kkonto, int auszahlungsBetrag) {
  // bargeld-check
  if (this->bargeld < auszahlungsBetrag) {
    std::cout << "Nicht genug Geld im Automaten. Sie können momentan maximal: " << getBargeld() << " Euro abheben." << std::endl;
    return -1;
  }

  if (!validierung(kkonto)) {
    return -1;
  }
  
  if (!kkonto->abheben(auszahlungsBetrag)) {
    // wenn das abheben erfolgreich war, subtrahiere den betrag vom bargeld im
    // automaten
    return -1;
  }
  this->bargeld -= auszahlungsBetrag;

  std::string temp_string = (kkonto->getKarte()->getKartenTyp() == 1) ? "Kreditkonto" : "Girokonto";

  std::cout << auszahlungsBetrag << " Euro werden von " << temp_string << " ausgezahlt." << std::endl;
  return auszahlungsBetrag;
}

int Bankautomat::einzahlung(KartenKonto* kkonto, int einzahlungsBetrag) {

    if (!validierung(kkonto)) {
    return -1;
    }

  // Der Einzahlungsbetrag wird dem Bargeldbestand vom Bankautomaten hinzugerechnet.
  this->bargeld += einzahlungsBetrag;

  // Der Einzahlungsbetrag wird dem Konto (Kredit-/Girokonto) hinzugerechnet
  kkonto->setKontostand(kkonto->getKontostand() + einzahlungsBetrag);

  std::string temp_string = (kkonto->getKarte()->getKartenTyp() == 1) ? "Kreditkonto" : "Girokonto";
  std::cout << einzahlungsBetrag << " Euro werden auf das " << temp_string << " eingezahlt." << std::endl;

  return einzahlungsBetrag;
}

KartenKonto* Bankautomat::kartenauswahl(Bankkunde* current_kunde ) {
  std::cout << "Moechten Sie eine Kreditkarte oder Girokarte nutzen? Tragen Sie bitte Kreditkarte oder Girokarte ein!" << std::endl;


  while (true) {
    std::string eingabe = " ";
    std::cin >> eingabe;
    
    if (eingabe == "Kreditkarte") {
      return current_kunde->getKreditkartenKonto();
    }

    else if (eingabe == "Girokarte") {
      return current_kunde->getGiroKonto();
    } 
    else {
      std::cout << "Bitte tragen Sie Kreditkarte oder Girokarte ein!" << std::endl;
      
          
    }
  }
}


void Bankautomat::menuAuswahl(Bankkunde* bankkunde) {
 
  KartenKonto* current_kartenauswahl = kartenauswahl(bankkunde);

  bool wirdAusgefuehrt = true;

  while (wirdAusgefuehrt) {
    
    // Auswahl des Benutzers
    std::string inputString;    
    int inputInteger;

    std::cout << "Was moechten Sie tun?\n"
              << "1. Kontostand anzeigen\n"
              << "2. Geld abheben\n"
              << "3. Geld einzahlen\n"
              << "4. Programm beenden\n";

    std::cin >> inputString;
        
    // Versuch die Eingabe in einem Integer umzuwandeln
    std::istringstream eingabe(inputString);


    if (eingabe >> inputInteger) {
      // Auswahl prüfen
      if (inputInteger >= 1 && inputInteger <= 4) {
        // Auswahl ist gültig
        switch (inputInteger) {
          case 1: {

            if (!validierung(current_kartenauswahl)) {
              break;
            }
            
            std::cout << "Ihr Kontostand: " << current_kartenauswahl->getKontostand() << " Euro" << std::endl;  //  kkonto anpassen
            // std::cout << kartenauswahl() << std::endl;

            break;
          }
          case 2: {
            std::cout << "Wie viel Geld moechten Sie abheben?" << std::endl;
            std::string ausEingabe = "";
            std::cin >> ausEingabe;
            int ausBetrag = std::stoi(ausEingabe);
            auszahlung(current_kartenauswahl, ausBetrag);
            break;
          }
          case 3: {
            std::cout << "Wie viel Geld moechten Sie einzahlen?" << std::endl;
            std::string einEingabe = "";
            std::cin >> einEingabe;
            int einBetrag = std::stoi(einEingabe);

            einzahlung(current_kartenauswahl, einBetrag);
            break;
          }
          case 4: {
            std::cout << "Die Karte wird ausgegeben!" << std::endl;

            wirdAusgefuehrt = false;

            break;
          }
        }

      } else {
        // Auswahl ist ungültig
        std::cout << "Ungueltige Auswahl. Bitte waehlen Sie eine Zahl zwischen 1 bis 4." << std::endl;
      }
    }
    
    else {

        // Auswahl ist ungültig
        std::cout << "Test _ Ungueltige Auswahl. Bitte waehlen Sie eine Zahl zwischen 1 bis 4." << std::endl;
        
    }
    
  }
 
  //To-Do:  muss ich noch was geschreiben werden , um in das übergeordnete Bankmenu zu kommen?  
}


// Getter und Setter für Bargeld
double Bankautomat::getBargeld() {
  return this->bargeld;
}

void Bankautomat::setBargeld(double betrag) {
  this->bargeld += betrag;
}

// Getter und Setter für AutomatID
unsigned int Bankautomat::getAutomatID() {
  return this->AUTOMAT_ID;
}
