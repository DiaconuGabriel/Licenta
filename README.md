# Licentă - Dispozitiv portabil pentru monitorizarea sănătății și navigare bazat pe Arduino și Flutter

Acest proiect este un ceas gândit să fie conectat la internet constant, iar dacă cumva se deconectează de la interent va încerca să se reconecteze și dacă nu exista nici o rețea disponibilă atunci va activa bluetooth, făcând posibilă utilizarea aplicației Android dezvoltată cu Flutter, pentru a trimite alte credențiale pentru ca ESP32 S3, microcontrolerul utilizat, să se poată conecta la internt. Ceasul este echipat cu un senzor IMU pe 9 axe, un MPU9250, un senzor MAX30102 pentru măsurarea pulsului și nivelului de oxigen din sânge și un modul RTC pentru a putea ține cont de trecerea timpului și când ceasul nu are alimentare. Cu ajutorul MPU, mai exact cu datele de la accelerometru, se pot determina pașii parcurși într-o zi. De asemenea se calculează și distanța parcursă și caloriile arse în acea zi. Partea de navigare este reprezentată de o busolă. Datele despre puls, nivelul de oxigen din sânge, pașii, distanța și caloriile arse sunt salvate într-o bază de date de timp real de la Firebase.

# Diagrama de conexiuni pentru ceas

![pinning_proiect_2](https://github.com/user-attachments/assets/77ffd26c-529c-4fa0-a6c6-646aebf71d60)

# UI ceas

![image](https://github.com/user-attachments/assets/918e2c23-8301-4bb9-ae0a-a2471fd15064)


# UI aplicație mobilă

![image](https://github.com/user-attachments/assets/633c5f1d-4780-4616-b320-bd0f9e005896)
