# Test uchun ko‘rsatmalar. 

Dasturning to‘g‘ri ma‘lumot qaytarishidan tashqari avtotest siz tuzgan dastur kodini keyingi punktlar bo‘yicha tekshirib o‘tadi: 

* **Code style.** Siz yozgan chiroyli kod standartga qanchalik mos kelishini tekshirish uchun _clang-format_ utilitidan foydalanishingiz mumkin. 
  ```materials/linters``` papkasida ```.clang-format``` fayli bor, unda stil uchun kerakli sozlamalar mavjud. 
  Bu sozlamali fayl o‘zining ta’sirini o‘zi bilan bir katalogda bo‘lgan barcha fayllarga va shu katalog ichida joylashgan boshqa kataloglarga o‘tkazadi. 
  Bu sozlamarni o‘z fayllaringizda qo‘llash uchun ushbu faylni ```src``` katologiga ko‘chirib o‘kazing. \
  \
  Stilni tekshirish uchun keyingi buyruqdan foydalaning: \
  ```clang-format -n src/sourcefile_name.c```
  
  clang-format kerakli versiyasi: \
  **Linux** - 13.0.1
  
  Google Style: https://google.github.io/styleguide/cppguide.html
  

* **Xotira bilan to‘g‘ri ishlash uchun test.** C tilida dastur yozish jarayonida xotira sarfiga e’tibor berib borish kerak. Buning uchun Unix operatsion tizimlarida yetarli darajada ko‘p _valgrind_ utilitidan foydalaniladi. Bu utilitlarni chuqurlashgan tarzda o‘rganmaymiz, agarda qiziq bo‘lsa googleda o‘qib ko‘rishingiz mumkin. 

  #### _Valgrind (Ubuntu / Linux Mint / Debian)_

  Kompilyatsiga tayyor faylni tekshirish uchun: \
  ```valgrind –tool=memcheck –leak-chek=yes ./main.out``` \
  foydalaning. 

  ---

  #### _Leaks (MacOS uchun)_

  **Muhim!** Agar siz Unix-ga o'xshash tizimdan foydalanayotgan bo'lsangiz (masalan, Ubuntu / Linux Mint / Debian), [VALGRIND-dan foydalanish bo'yicha ko'rsatmalarga o'ting](#valgrind-ubuntu-linux-mint-debian).

  Kopilyatsiya qilingan faylni bu utilita yordamida tekshirish uchun terminalda: \
  ```leaks -atExit -- ./main.out | grep LEAK```
 
  ```| grep LEAK``` buyrug‘iga e’tibor bering biz undan faqat qisqacha, xotira qayerda ko‘p sarflanishini aniq ko‘rib olish uchun foydalanamiz. 
  Agar siz leak buyrug‘i natijasini to‘liq ko‘rishni istasangiz bu buyruqni o‘chirib tashlang. 

  Qo‘shimcha: 
  ```-exclude``` flag yordamida _leak_ utilitasi funksiyalarda xotira sarfini filtrlaydi. Bu flag _leak_ buyrug‘i chiqarib beradigan keraksiz va ortiqcha ma’lumotlarni olib tashlaydi. 
  
  **Dastur to‘g‘ri yi‘g‘ilganini tekshirish**. Dastur to‘g‘ri tuzilganini tekshirish uchun test tizimdan foydalansa bo‘ladi. Buning uchun Docker yuklangan bo‘lishi kerak. Agarda docker yuklangan bo‘lsa ‘materials/build’ papkasiga kirib run.sh skriptni ishga tushirish kerak. Skript sizning dasturni docker tizimiga o‘girib senariya asosida dasturni jamlab ishga tushiradi. 
