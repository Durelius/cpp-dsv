# Game Engine och spel (widu7139, joko5833)

## 1 - Instruktion:

### Krav för att kunna köra spelen:

- SDL3, SDL3_image och SDL3_ttf behöver vara installerat och finnas i din path
- Du behöver en C++ kompilator (g++-14 för Mac, g++ för Linux och Windows)
- Spelen kompileras och körs genom antingen "make w" eller "make j" från projektroten.
  Make j kompilerar och kör spelet 'floppy box' som Joshua skrivit.
  Make w kompilerar och kör spelet 'scuffed snek' som Wilhelm skrivit.

### Alla sökvägar till resources finns i resources mapparna, där de är definierade med relativa sökvägar

## 2 - Spelen

### j - floppy box

I detta spel använder man enbart space bar för att kontrollera karaktären, som då hoppar. Målet är att hoppa igenom så många rör som möjligt utan att röra någon av dem, eller komma utanför rutan. Spelet startas om vid 'död'.

### w - scuffed snek

I detta spel styr man antingen med WASD, eller piltangenterna. Man ska plocka på sig mat (orbs) och varje gång man äter en orb får man en till tail. Åker ormen in i sig själv så dör ormen. Klicka då på space för att starta om. Poängen står längst upp i vänstra hörnet.
