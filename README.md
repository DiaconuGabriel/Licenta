# Licenta - Dispozitiv portabil pentru monitorizarea sănătății și navigare bazat pe Arduino și Flutter

Acest proiect este un ceas gandit sa fie conectat la internet constant, iar daca cumva se deconecteaza de la interent va incerca sa se reconecteze si daca nu exista nici o retea disponibila atunci va activa bluetooth, facand posibila utilizarea aplicatie Android dezvoltata cu Flutter, pentru a trimite alte credentiale pentru ca ESP32 S3, micrrocontrolerul utilizat, sa se poata conecta la internt. Ceasul este echipat cu un senzor IMU pe 9 axe, un MPU9250, un senzor MAX30102 pentru masurarea pulsului si nivelului de oxigen din sange si un modul RTC pentru a putea tine cont de trecerea timpului si cand ceasul nu are alimentare. Cu ajutorul MPU, mai exact cu datele de la accelerometru, se pot determina pasii parcursi intr-o zi. De asemenea se calculeaza si distanta parcursa si caloriile arse in acea zi. Partea de navigare este reprezentata de o busola. Datele despre puls, nivelul de oxigen din sange, pasii, distanta si caloriile arse sunt savlate intr-o baza de date de timp real de la Firebase.

# UI ceas

![image](https://github.com/user-attachments/assets/918e2c23-8301-4bb9-ae0a-a2471fd15064)


# UI aplicatie mobila

![image](https://github.com/user-attachments/assets/633c5f1d-4780-4616-b320-bd0f9e005896)
