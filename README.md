# StorPool
**[Task1-counting]**

Пиша на Български, защото виждам, че всички сме такива...
В Task1-counting е първата задача. В нея съм вкарал двва файла, един "C" файл, който генерира binary файла (по малко шантав начин), вместо да генерира случайни 32 битови числа, генерира байтове и ги записва в файла res.bin. 

За да стартирате "C" файла под linux 
```
 gcc write.c
 ./a.out
```
в него не се генерират обаче (10^9) 32 битови числа. Много се извинявам, но не ми се чакаше толкова много. Вярвам, че ако разгледате кода на втория файл [read.py], ще видите, че е все едно колко са числата (стига да са повече от (2^32), защото така или иначе то само инкрементира value -то на един Hash(dictionary) и реално разлиаката е, че само се чака повече и хаби ток. Нито яде повече памет, нито ще даде някаква грешка
Python-a се стартира с 

```
python read.py
```




**[Task2-fizzbuzz]**
Поздравявам Ви за тази задача. Много ми беше интересна. 
Написал съм, а на perl. 
Няма как да избегна напълно циклите и условните оператори, но съм замаскирал цикъла и съм написал grep, което си е същото. Няма If/Else или Switch/Case, но имам едно "||" на ред 21. Ако се напъна и него сигурно мога да разкарам, но как да завъртя числата от 1 до 100 без цикъл не се сещам


```
perl fizzbuzz.pl
```



**Task3-analysis**
Това го направих на Java за разнообразие, но си стана тромаво. Целта беше да се опитам да натоваря цялата машина (всички процесори) да работят по-бързо, но се  получи. Пуснах Thread-ове колкото са процесорите (Без един за IO-от) и ги синхронизирах с един ArrayBlockingQueue,  thread-a който чете от файла (byte по byte) да подава прочетените string-ове на останалите тредове, които да ги parse-ят и да търсят модел-а. За съжаление, не бях тествал толкова интензивно натоварване на тази опашка и то се оказа, че тя е доста тромава и всичко седи и я чака. Практически вместо да натоваря всички процесири на машината реално товаря по 10% от всеки заради бавната и тромава   ArrayBlockingQueue. Има хиляди начини как да го забързам, но не съм се опитвал - не изяждам много памет и работи. 


За да пуснете програмата ви трябва инсталирано JDK (все едно коя версия).Влизате във folder-a. Поставяте там някъде файла bigf.json

```
javac JsonReader.java
java JsonReader //PATH_TO_BIF.JSON

```


**Taks4-reverse engineering**
Това твърдо ми е извън компетенцията. Разбиртам задачата, но досега никога не съм боравил с тези неща. Предполагам, че се изпозлва gdb но не го познавам, стори ми се (по логове), че едното програмче се опитва да линкне някаква library, но сигурно го няма - но отново казвам - никога не съм debug-вал под linux процеси


**Task5-ObjectsAndVersions**
Тук се опитах да го направяв на c. Май стана. ако трябва да се обясни някоя част от алгоритъма съм на линия, но като цяло поне на моя лаптоп се вакарах в 2 минути и 3GB RAM. Само за уточнение, понеже не е написанов условите, съм приел, че objectId: 0 е значеща стойност, както и version: 0. В момента изкарва нещо от сорта на 

```
In 72 files found 4999220 objects that match on conditions from 74963873 objects at all
Operation complete used memory: 2.90 GB, time:  116.51 sec
```

Поне така го изкарва на моята машина. За да го пуснете, трябва да си го компилирате - гледал съм да не използвам никакви екзотики, така че

```
gcc read.c
./a.out /database/files/haystack/
```

трябва да си дадете пътя до folder-a с файловете, които следва да се изчетат.





