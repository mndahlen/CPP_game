# Filip's SFML demo

## Moduler som krävs på IDA's system

```
module add prog/cmake
module add prog/gcc/6.1.0
module add prog/sfml-2-gcc-6
```

Modulen ```prog/cmake``` krävs enbart om cmake används istället för make.

Ovan kommandon påverkar enbart den terminal de körs i. För att aktivera modulerna globalt krävs "initadd" istället för "add" följt av ny inloggning på systemet. Kontrollera alltid att allt fungerar efter "add" innan "initadd" används.

Det går även att använda gcc-7.1.0 med SFML, men det kräver i skrivande stund att moduler läggs till och tas bort i rätt ordning följt av manuellt pillande med miljövariabler. Vi arbetar på att lösa/förenkla detta.


## Kompilering med Make

```make -f Makefile.gnu```

Detta kommando bygger alla steg. Flaggan -f till make specificerar vilken ```Makefile``` som ska användas. Att makefilen heter ```Makefile.gnu``` istället för standard ```Makefile``` beror på att vi inte vill den ska bli överskriven om cmake används istället.

För att rensa bort byggfiler körs:

```make -f Makefile.gnu clean```

För att rensa bort även backupfiler och CMake-filer körs:

```make -f Makefile.gnu superclean```


## Kompilering med CMake

Vi tillhandahåller ett exempel på en ```CMakeList.txt``` för att kunna bygga SFML med CMake.

```
cmake .
make
```

Första kommandot genererar ```Makefile``` och andra kommandot bygger ```shooter```. Övriga steg i exemplet byggs inte av vår ```CMakeLists.txt```.

