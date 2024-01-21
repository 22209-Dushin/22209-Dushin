## О чём проект
Игра Жизнь  

## Как Играть
Перейдите в папку GameOfLife    
выполните следующее команды :

g++ -o main main.cpp View.cpp LineParser.cpp GameBoard.cpp Game.cpp FileParser.cpp Controller.cpp

./main

## Инструкция сборки  
Перейдите в папку TESTS и создайте папку buid для сборки:  

mkdir build  

Перейдите в папку build:  

cd build  

Выполните ряд следующих команд для сборки:  

cmake ..  
make 
## Инструкция использование
Запустите исполняемы файл:  
./runTests  