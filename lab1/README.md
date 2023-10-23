## О чём проект
CitcularBuffer  

## Инструкция сборки  
Перейдите в папку с проектом и создайте папку buid для сборки:  

mkdir build  

Перейдите в папку build:  

cd build  

Выполните ряд следующих команд для сборки:  

cmake ..  
make 
## Инструкция использование
Запустите исполняемы файл:  
./runTests  

Для просмотра покрытиями тестов выдолните следующие команды:  

lcov -c --directory ./CMakeFiles/runTests.dir/ --output-file report.info  
genhtml report.info -o repor  

Внутри папки report вы сможете найти файл index.html, в котором и будет отчет.