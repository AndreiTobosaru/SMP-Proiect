# SMP-Proiect
Tobosaru Andrei 332AB - Proiect SMP 

Proiectul consta in simularea unui joc "Truck delivery" pe un ecran LCD. Jocul presupune conducerea unui "camion" si evitarea de obstacole (masini) care apar in mod aleator din partea drepta a ecranului LCD. Pentru a misca stanga-dreapta camionul, am folosit un potentiometru connectat la un pin analog de la placuta Arduino.

Pentru implementarea fizica a proiectului am folosit:
- breadboard
- placa Arduino UNO
- potentiometru B100K pt conducerea camionului
- potentiometru B10K pt conectarea LCD-ului
- rezistenta 1K
- fire
- buzzer

In cod sunt implementate pozitiile pe care le pot avea masinile, camionul si accidentul in cazul in care se loveste un obstacol. Pe ecran sunt afisate mesaje corespunzatoare inceputului de joc respectiv finalului (unde vom afla si timpul parcurs de camion). Citim valorea de pe pinul A1 (0 - 1024) dar am setat ca 800 sa fie maxim pentru a nu trebui sa rotim potentiometru prea mult ca sa viram. Masinile (obstacolele) apar aleator iar daca jucatorul reuseste sa conduca camionul fara sa faca accident, dificultatea jocului va creste prin marirea vitezei de deplasare a camionului. Jocul este gandit astfel incat la orice moment de timp sa nu existe blocaje pe drum (nu vor exista masini una langa alta care nu pot fi evitate de catre jucator). In caz de accident buzzer-ul va emite un sunet scurt si pe LCD va aparea timpul parcurs de camion
